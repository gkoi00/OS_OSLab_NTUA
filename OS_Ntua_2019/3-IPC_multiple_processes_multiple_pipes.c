/*THIS PROGRAM TAKES AS ARGUMENTS THE NUMBER OF CHILDREN A FATHER GENERATES TO COMPUTE THE 
FACTORIAL OF A NUMBER GIVEN AS SECOND ARGUMENT. FATHER PASSES NUMBER 1 TO FIRST CHILD AND
THEN THIS PASSES 1*2 TO THE SECOND AND SO ON TILL THE FACTORIAL IS COMPUTED. 
EXECUTE WITH eg ./a.out 5 9 (find 9! using 5 children).
THIS IMPLEMENTATION IS MADE WITH MULTIPLE PIPES. 

COMMUNICATION BETWEEN CHILDREN IS ACHIEVED WITH DIFFERENT PIPES AND COMMUNICATION 
FATHER-FIRST CHILD AND LAST CHILD-FIRST CHILD SHARE A PIPE. 

This program is the third exercise of Operating Systems in ECE NTUA in 2019. There is 
another implementation using one pipe in this repository with the name
"multiple-processes-one-pipe.c".

There is a commented printf command in the end that prints the status of exited children.
You may enable it or not depending on what do you prefer to be printed out.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main(int argc,char *argv[]){
	int i, buffer[2];
	int numberOfChildren, number;
	buffer[0] = 1; //number to be passed for factorial
	buffer[1] = 1; //iteration
 
	//cast char to int
	numberOfChildren = atoi(argv[1]); 
	number = atoi(argv[2]);

	//open pipes
	int fd[2*numberOfChildren];  
	for(i=0; i<numberOfChildren; i++)
		pipe(fd + 2*i);
 
	pid_t childPid[numberOfChildren];
     
	for(i=0; i<numberOfChildren; i++){ 
		childPid[i] = fork();

		if(childPid[i] == 0){
			//CHILD's i CODE

			/*This while loop makes sure that when a child does one operation for the factorial estimation, 
			  returns and is ready for another operation if it is needed. The logical statement makes sure  
			  that if it isn't needed it wont enter the while loop and it will exit.
			*/
			while(((number - (buffer[1] - 1)) >= numberOfChildren)||((numberOfChildren > number)&&(i < number))){
				close(fd[(2*i + 1)%(2*numberOfChildren)]); //close unwanted ports
				close(fd[(2*i + 2)%(2*numberOfChildren)]); //close unwanted ports
                         
				read(fd[(2*i)%(2*numberOfChildren)], buffer, 2*sizeof(int)); //read the value passed from 
                 									     //another child or father
				buffer[0] = buffer[0]*buffer[1]; //factorial estimation
				buffer[1]++; 
          
				write(fd[(2*i +3)%(2*numberOfChildren)], buffer, 2*sizeof(int)); //pass number estimated 
												 //to next process
				printf("child%d with pid %d running, iteration %d with result %d\n",i+1, getpid(), 
											  buffer[1]-1, buffer[0]);
				if(numberOfChildren > number) exit(0);
			}   
			exit(0);
		}
	}

	//FATHER's CODE
	close(fd[0]); //close unwanted ports
	write(fd[1], buffer, 2*sizeof(int)); //pass 1 to the first child
 
	/*---Wait for children to exit and print their exit status---*/
	int status;
	pid_t pid;
	while (numberOfChildren > 0) {
		pid = wait(&status);
		//printf("CHILD WITH PID %ld EXITED WITH STATUS 0x%x.\n", (long)pid, status);
		--numberOfChildren;
	}
	
	exit(0); //father exits

	return 0;
}
