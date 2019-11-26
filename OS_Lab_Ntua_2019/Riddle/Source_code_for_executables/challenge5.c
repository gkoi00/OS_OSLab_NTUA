#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>   //wait()

int main(){
    pid_t childPid;

    dup2(0, 99);
    childPid = fork();

    if (childPid < 0) {
        perror("fork");
        exit(1);
    }

    if (childPid == 0){
        char executable[] = "riddle";
        char *newargv[] = {executable, NULL};
        char *newenviron[] = {NULL};
        execve(executable, newargv, newenviron);
    }

    wait(NULL);
    exit(0);

    return 0;
}
