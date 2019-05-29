/*THIS PROGRAM IMPLEMENTS A TREE OF FORKED PROCESSES AS SHOWN BELOW AND EACH PROCESS PRINTS ITS STATUS
------------F---------------
----------/---\-------------
--------CH1---CH2-----------
-------/---\----\-----------
-----CH3--CH4---CH5---------

This is the first exercise of Operating Systems lecture in ECE NTUA in 2019.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
 
int main(){
	int status;
	int i = 0;
	pid_t child1, child2, child3, child4, child5;
 
	child1 = fork(); //father generates child1
 
	if(child1 < 0)
		 printf("Forking failed\n");
	else if(child1 == 0){ 
                child3 = fork(); //child1 generates child3

                        if(child3 < 0)
				printf("Forking failed\n");
            		else if(child3 == 0){
				/*--------------------------------child3 code---------------------------------*/
                		for(i=0; i<10; i++){ 
                            		printf("Process %d is executed,my father is %d\n", getpid(), getppid());
                        		sleep(1);
                        	}
                		exit(0); //child3 exits
            		}
            		else{
				child4 = fork(); //child1 generates child4

				if(child4 < 0)
					printf("Forking failed\n");
				else if(child4 == 0){
					/*---------------------------------child4 code--------------------------------*/
                    			for(i=0; i<10; i++){ 
                                		printf("Process %d is executed,my father is %d\n", getpid(), getppid());
                            			sleep(1);
                            		}
                               		exit(0); //child4 exits
				}
                                else{
					/*-------------------------------child1 code----------------------------------*/
					for(i=0; i<10; i++){ 
						printf("Process %d is executed,my father is %d\n", getpid(), getppid());
						sleep(1);
                                 	}
                                     	wait(&status); //child1 waits for children 3 and 4 to exit
                             		exit(0);       //and exits
                		}
			}
	}         
	else {
		child2 = fork(); //father generates child 2
		
		if(child2 < 0) 
			printf("Forking failed\n");
		else if(child2 == 0){
                	child5 = fork(); //child2 generates child 5

			if(child5 < 0)
				printf("Forking failed\n");
			else if(child5 == 0){
				/*--------------------------------child5 code---------------------------------*/
				for(i=0;i<10;i++){ 
                                	printf("Process %d is executed,my father is %d\n", getpid(), getppid());
                            		sleep(1);
                            	}
                    		exit(0); //child5 exits
                	}
			else{
				/*-------------------------------child2 code---------------------------------*/
				for(i=0;i<10;i++){ 
					printf("Process %d is executed,my father is %d\n",getpid(),getppid());
					sleep(1);
				}
                		wait(&status); //child2 waits for child5 to exit
                        	exit(0);       //and exits
                        }
                }
		else{
			wait(&status); //father waits for children 1 and 2 to exit
			exit(0);       //and exits
		} 
	}
	
	return 0;
}
