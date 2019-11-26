#include <stdio.h>
#include <stdlib.h>     //fork()
#include <unistd.h>     //fork()
#include <sys/wait.h>   //wait()
#include <errno.h>      //errno
#include <fcntl.h>
#include <string.h>

int main(){
    int i, numOfProcs;
	numOfProcs = 0;
    pid_t childPid = 99; //random initialization

    while (childPid != 32767){
        childPid = fork();
		numOfProcs++;
 		if (childPid == 0){
			if (getpid() == 32767){
				//printf("%d\n", getpid());
            	char executable[] = "riddle";
            	char *newargv[] = {executable, NULL};
            	char *newenviron[] = {NULL};
            	execve(executable, newargv, newenviron);
			}
			exit(0);
        }
    }
	for (i=0; i<numOfProcs; i++)
    	wait(NULL);
    exit(0);

    return 0;
}
