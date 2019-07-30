/*This program implements signal handling between processes. It is the second exercise
of Operating Systems lecture in ECE NTUA in 2019.

Run giving 5 arguments eg ./a.out 1 3 2 5 4. This is the order of the children explained
below:

The father generates 5 children and these pause. After that, the father process continues
child1, which types "Child1 PID is executed (number of iteration)" 3 times. Then father
pauses child1 and continues next child given in arguments, child3. This types 3 times
its status as well and then gets paused. Child 2 is then continued .......... When all 
children run one time, the same thing will have to be done another 3 times, meaning
4 total iterarions. We need exactly 5 arguments and no argument repetitions.

There is a second implementation in file "processes-scheduling-with-signals-vol2.c" that
uses recursion to generate all 5 children.
.*/
#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int j; //needs to be global to be visible inside the function handler
void handler();
 
int main(int argc,char**argv){
    
	int b = 0, i;
	int intArgv[5]; //contains the order of the children as integers
	int status;

	pid_t childpid[5]; //contains the pid of each child

	/*-------------check for not exactly 5 children arguments-------------*/
	if(argc!=6){
		printf("Error, not right number of arguments. Please repeat\n");
		exit(0);
	}

	/*-convert argv's strings to integers for intArgv-*/
	for(int i=0; i<5; i++){ 
		intArgv[i] = *argv[i + 1] - '0';        
	}
	
	/*-------------------check for repeating arguments-----------------*/
	while(b<4){ 
		for(i=b+1; i<5; i++){
			if (intArgv[b] == intArgv[i]){
				printf("Error, you are repeating numbers\n"); 
				exit(0);
			}
		}
		b++;
	}
	
	/*----------------------forking----------------------*/
	for(i=0;i<5;i++){          
		childpid[i] = fork(); //create 5 children

		if(childpid[i]==0){
		/*------CHILD's CODE-----------*/
			j=i+1;
			signal(SIGCONT, handler);
			pause(); //children pause until father sends a signal to continue
			exit(0);
		}
	}

        /*------------------FATHER's CODE--------------------*/
	for(int k=0;k<4;k++){
		for(int i=0;i<5;i++){
			printf("\n"); //This is needed. Without it the first iteration wont be printed 
				      //because child tries to print but it hasnt yet been created
			kill(childpid[intArgv[i] - 1],SIGCONT); //father continues a child
			sleep(3);				//father waits 3 seconds and lets child to print
			kill(childpid[intArgv[i] - 1],SIGSTOP); //father pauses a child
		}
	}

	for(i=0;i<5;i++)
		kill(childpid[intArgv[i] - 1],SIGKILL); //father kills children   
	for(i=0;i<5;i++) 
		wait(&status); //waits for them to exit with their exit status
	exit(0); 	       //fathers exits
}    
 
void handler(){
	int n=1;

	while(1){
		printf("Child%d %d is executed (%d)\n", j, getpid(), n);
		sleep(1);
		n++;
	}  
}
