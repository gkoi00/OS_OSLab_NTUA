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

#define SLEEP_TREE_SEC 1

void forks(struct tree_node *);
void handler();

int got_signal = 0;

int main(int argc, char **argv){
    struct tree_node *root;
    pid_t pid;
    int status;

    //usage
    if(argc != 2){
        fprintf(stderr,"Usage: ./ask2-signals [input file]\n");
        exit(1);
    }

    if(open(argv[1], O_RDONLY) < 0){
        perror("Error");
    }

    root = get_tree_from_file(argv[1]);

    //create root
    pid = fork();
    if(pid < 0){
        perror("Error");
        exit(2);
    }
    if(pid == 0){
        forks(root);
        exit(0);
    }

    //wait SLEEP_TREE_SEC and print the tree that is already built
    sleep(SLEEP_TREE_SEC);
    show_pstree(pid);

    //starts A (root)
    kill(pid,SIGCONT);

    //wait for A (root) to exit and print its exit status
    pid = wait(&status);
    explain_wait_status(pid, status);
    return 0;
}

//function that recursively generates the tree
void forks(struct tree_node *ptr){
    int i = 0;
    int status;
    pid_t childPid[ptr->nr_children];
    pid_t pid;

    change_pname(ptr->name);

    while(i < ptr->nr_children){
        //a tree node generates its children, if a child has no nr_children
        //it enters the if statement and if it does have children it enters
        //the else statement where recursively calls forks() and gererates
        //its children
        childPid[i] = fork();
        if(childPid[i] == 0){
            change_pname((ptr->children + i)->name);

            if((ptr->children + i)->nr_children == 0){
                //procedure that has no children
                signal(SIGCONT, handler);
                raise(SIGSTOP); //same as kill(getpid(), SIGSTOP);
                                //pause() would work as well
                printf("%s\n", (ptr->children + i)->name);
                exit(0);
            }
            else{
                forks(ptr->children + i);
            }
        }
        i++; //go to next child
    }

    //process (tree node) that has children, after their creation it comes here
    signal(SIGCONT, handler);
    raise(SIGSTOP);

    i = 0;
    //wait for children to exit and print their exit status
    while(i < ptr->nr_children)
    {
        kill(childPid[i], SIGCONT);

        pid = wait(&status);
        explain_wait_status(pid, status);
        i++;
    }

    printf("%s\n", ptr->name);

    exit(0);
}

//handler function
void handler(){
    got_signal = 1;
}
