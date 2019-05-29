/*
This program implements pipes use as semaphores for the critical section problem.
It is the fourth exercise of Operating Systems lecture in ECE NTUA in 2019.

The father generates three children and these three cgildren have a code
divided in 5 section as shown bellow:
CHILD1:				CHILD2:				CHILD3:
CRITICAL SECTION		NONCRITICAL SECTION		CRITICAL SECTION
NONCRITICAL SECTION		CRITICAL SECTION		NONCRITICAL SECTION
NONCRITICAL SECTION		NONCRITICAL SECTION		CRITICAL SECTION
CRITICAL SECTION		CRITICAL SECTION		NONCRITICAL SECTION
NONCRITICAL SECTION		NONCRITICAL SECTION		CRITICAL SECTION
CRITICAL SECTION		CRITICAL SECTION		NONCRITICAL SECTION
A critical section uses printf to type a message 5 times and a noncritical
is a printf that executes 7 times. The point is that when a child process 
runs a critical section the other processes are not allowed to enter theirs'.
They are allowed though to enter a noncritical section.

This implementation uses the fact that when a read command commes up,
the process should wait for another one to write to the pipe.
So in fact i dont care about the value I am passing 
but about the passing itself.


*/
#include <stdio.h>	//printf()
#include <unistd.h>	
#include <sys/types.h> 	//key_t, sem_t, pid_t
#include <stdlib.h> 	//exit(), malloc(), free()
#include <sys/wait.h> 	//wait()

void critical(int *);
void nonCritical(int *);

int main(int argc, char *argv[]){
	/*-----------------------DECLARATIONS---------------------------*/
	int i,t;
	int buffer = 1; //any value
	
	pid_t childPid[3];

	//open pipe
	int fd[2];
	pipe(fd);
	
	/*--------------------------FORKING-----------------------------*/
	for(i=0; i<3; i++){
		childPid[i] = fork();
		if(childPid[i] < 0){
			printf("Error");
			abort();
		}
		if(childPid[i] == 0){
			/*------------CHILD's i CODE------------*/
			//CHILD 1
			if(i == 0){
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);
				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));
				
			}//CHILD 2
			 else if(i == 1){
				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));
			
			}//CHILD 3
			 else if(i == 2){
				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);

				read(fd[0],&buffer,sizeof(int));
				critical(&i);
				write(fd[1],&buffer,sizeof(int));

				nonCritical(&i);
			}
		exit(0);
		}
	}
	/*---------------------FATHER's CODE--------------------------*/

	//wait for children to exit and print their exit status
	int status;
	pid_t pid;
	for(t=0; t<3; t++){
		pid = wait(&status);
		//printf("CHILD WITH PID %ld EXITED WITH STATUS 0x%x.\n", (long)pid, status);
	}

	exit(0); //father exits
	return 0;
}

void critical(int *i){
	int j=0;
	for(j=0; j<5; j++){
		printf("!!!!!!!!!!!!!!!!!!!!!!!");
		printf("CHILD%d %d EXECUTES A CRITICAL SECTION(%d)\n",*i + 1, getpid(),j + 1);
	}	
}

void nonCritical(int *i){
	int j=0;
	for(j=0; j<7; j++)
		printf("Child%d %d executes a non critical section(%d)\n",*i + 1, getpid(),j + 1);
}
