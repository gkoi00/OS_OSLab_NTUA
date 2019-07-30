/*THIS PROGRAM TAKES AS ARGUMENTS THE NUMBER OF CHILDREN A FATHER GENERATES TO COMPUTE THE 
FACTORIAL OF A NUMBER GIVEN AS SECOND ARGUMENT. FATHER PASSES NUMBER 1 TO FIRST CHILD AND
THEN THIS PASSES 1*2 TO THE SECOND AND SO ON TILL THE FACTORIAL IS COMPUTED. 
EXECUTE WITH eg ./a.out 5 9 (find 9! using 5 children).
THIS IMPLEMENTATION IS MADE WITH ONE PIPE AND SIGNALS. ALTERNATIVELY MULTIPLE PIPES COULD
HAVE BEEN USED EACH FOR EVERY POSSIBLE COMMUNICATION. NOTE THAT WHEN A PROCESS MEETS A
READ FROM PIPE COMMAND IT PAUSES. WHEN SOMETHING IS WRITTEN IN THE PIPE IT READS IT AND
AUTOMATICALLY THE PIPE EMPTIES.
HANDLER FOR SIGCONT DOESNT NEED TO HAVE ANYTHING BUT IT SHOULD EXIST.

This program is the third exercise of Operating Systems in ECE NTUA in 2019. There is a
second implementation using multiple pipes in this repository with the name
"multiple-processes-multiple-pipes.c".

There is a commented printf command in the end that prints the status of exited children.
You may enable it or not depending on what do you prefer to be printed out.
*/
 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
void handler();
 
int main(int argc, char *argv[]){
    int i, j, m, number, numberOfChildren, iteration;
    int buffer[2] = {0, 0};
 
    /*-----cast char to int------*/
    number = atoi(*(argv + 1 + 1));
    numberOfChildren = atoi(*(argv + 1));
  
    pid_t childPid[numberOfChildren];
 
    //open pipe
    int fd[2];
    pipe(fd);
 
    /*---------start children------------*/
    for (i = 0; i < numberOfChildren; ++i){
        childPid[i] = fork();
        if (childPid[i] < 0) {
                printf("error");
        }
        else if (childPid[i] == 0) {
            /*----------------------CHILD's i CODE--------------------------*/
            //when (number - iteration) >= numberOfChildren the current child won't 
            //be needed again, so breaks the while loop and exits.
            if(numberOfChildren < number){
                while(number - (buffer[1] - 1) >= numberOfChildren){
                    signal(SIGCONT, handler);
                    pause();
                     
                    //number to be passed --> buffer[0]
                    //number of iteration --> buffer[1]
                    read(fd[0], buffer, 2*sizeof(int));
                    buffer[0] = buffer[0]*buffer[1];
                     
                    printf("child with pid %d running, iteration %d\n",getpid(), buffer[1]);                            
                    printf("result = %d\n", buffer[0]);
                     
                    //buffer[1] is incremented to be passed to next child 
                    //together with the new result number to be passed in buffer[0]
                    //so from here buffer[1] = iteration + 1;
                    buffer[1]++;
                    write(fd[1], buffer, 2*sizeof(int));
 
                    //sleep(1);
     
                    //while (iteration + 1) <= number of current child call next child
                    if(buffer[1] <= number){
                        if((buffer[1] - 1)%numberOfChildren != 0)
                            //current child calls next with pid-->(pid + 1)
                            kill(getpid() + 1, SIGCONT);
                        else
                            //now child calls the first child
                            kill(getpid() - (numberOfChildren - 1), SIGCONT);
                    }
                }
            }
            //if numberOfChildren > number then no child should enter again. In fact
            //some children aren't needed and should exit at first
            else {
                //children that are not needed exit
                if(i >= number)
                    exit(0);
                //the other children do the work and exit
                //same as above
                signal(SIGCONT, handler);
                pause();
 
                read(fd[0], buffer, 2*sizeof(int));
                buffer[0] = buffer[0]*buffer[1];
                 
                printf("child with pid %d running, iteration %d\n",getpid(), buffer[1]);                            
                printf("result = %d\n", buffer[0]);
                 
                buffer[1]++;
                write(fd[1], buffer, 2*sizeof(int));
 
                //sleep(1);
                //till here, now current child calls the next one
                kill(getpid() + 1, SIGCONT);    
                 }
            exit(0);
        }
    }
 
    // FATHER's CODE
    iteration = 1;
 
    //buffer has information about the number to be passed and the iteration 
    buffer[0] = 1;
    buffer[1] = iteration;
 
    //prints childs' pids
    for(int t=0; t<numberOfChildren; t++)
        printf("%d\n",childPid[t]);
     
    //close unused port
    close(fd[0]);
 
    write(fd[1], buffer, 2*sizeof(int));
 
    //father calls the first child
    kill(childPid[0], SIGCONT);
 
    //wait for children to exit and print their exit status
    int status;
    pid_t pid;
    while (numberOfChildren > 0) {
        pid = wait(&status);
        //printf("CHILD WITH PID %ld EXITED WITH STATUS 0x%x.\n", (long)pid, status);
        --numberOfChildren;
    }
 
    exit(0);    
    return 0;
}
 
void handler(){}
