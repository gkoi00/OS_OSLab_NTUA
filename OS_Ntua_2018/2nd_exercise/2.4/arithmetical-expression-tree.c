#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <assert.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#include "proc-common.h"
#include "tree.h"

#define SLEEP_TREE_SEC 0.1
#define SLEEP_LEAF 1
void forks(struct tree_node *, int);

int main(int argc, char **argv){
    struct tree_node *root;
    int status, fd[2], result;
    pid_t pid;

    if(argc != 2){
        fprintf(stderr,"Usage: ./arithmetical-expression-tree [input file]\n");
        exit(1);
    }

    if(pipe(fd) < 0){
        perror("Initial pipe creation");
        exit(1);
    }

    if(open(argv[1], O_RDONLY) < 0){
        perror("tree-file error");
    }

    root = get_tree_from_file(argv[1]);

    pid = fork();
    if(pid < 0){
        perror("Initial fork error");
        exit(2);
    }
    if(pid == 0){
        close(fd[0]);           //close read port for child
        forks(root, fd[1]);     //pass file descriptor for writing
                                //into the function for further use
        exit(0);
    }

    //parent waits 0.1 sec and prints the tree
    sleep(SLEEP_TREE_SEC);
    show_pstree(pid);

    //here parent waits till the result is ready and reads it
    close(fd[1]); //close write port for parent
    if(read(fd[0], &result, sizeof(int)) != sizeof(int)){
        perror("read pipe");
    }

    pid = wait(&status);
    explain_wait_status(pid, status);

    printf("Result: %d\n", result);
    return 0;
}

void forks(struct tree_node *ptr, int pd){
    int i = 0;
    int status, result, *number, temp;
    pid_t pid;

    change_pname(ptr->name);
    int fd[2*ptr->nr_children];

    while(i < ptr->nr_children){
        //Open one pipe for every child. In each iteration
        //a pipe is opened.
        if(pipe(fd + 2*i) < 0){
            perror("pipe creation");
            exit(1);
        }

        if(!fork()){
            change_pname((ptr->children + i)->name);
            if((ptr->children + i)->nr_children == 0){
                /*---------------LEAF NODE-----------------*/
                sleep(SLEEP_LEAF);     //wait so the right tree is printed

                int num = atoi((ptr->children + i)->name);

                close(fd[2*i]);     //close read port
                if(write(fd[2*i + 1], &num, sizeof(int)) != sizeof(int)){
                    perror("write pipe");
                }

                exit(0);
            }
            else{
                forks(ptr->children + i, fd[2*i + 1]); //pass write port
            }
        }
        i++;
    }

    /*------------------INTERVAL NODE--------------------*/
    number = (int *) malloc (ptr->nr_children * sizeof(int));

    //calculations
    for(i = 0; i < ptr->nr_children; i++){
        if(read(fd[2*i], &temp, sizeof(temp)) != sizeof(temp)){
            perror("read pipe");
        }
        *(number + i)= temp;
    }

    switch(strcmp(ptr->name,"+")) {
        case 0:
            result = *(number + 1) + *number;
            break;
        default:
            result = *(number + 1) * *number;
    }

    //pass the result into the process before here
    if(write(pd, &result, sizeof(int)) != sizeof(int)){
        perror("write pipe");
    }

    //wait for children to exit and exit printing their exit status
    for (i=0; i<ptr->nr_children; i++){
        pid = wait(&status);
        explain_wait_status(pid, status);
    }
    free(number)
    exit(0);
}
