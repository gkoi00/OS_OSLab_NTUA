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

This is the second implementetion of the same exercise. The other version is the file
"processes-scheduling-with-signals.c" in this repository. The differrence here is that the father process
generates its children with recursion.

You are adviced to see signals.c before looking at this implementation.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
  
void forker(int, int , char **);
void handlerOfContinue();
volatile sig_atomic_t e_flag = 0;
  
/*------------MAIN-------------*/
int main(int argc, char *argv[]){
  
    int status, i=0;
      
    forker(5, argc, argv);
  
    return 0;
}
  
/*------------FORKER FUNCTION---------------------*/
void forker(int nprocesses, int argc, char *argv[]){
      
    int n = 0, m = 0, j = 0;
    static int count = 0; //static because I dont want it to reset in every recursion 
    static int childPid[5] = {0, 0, 0, 0, 0}; 
    int intArgv[5] = {0, 0, 0, 0, 0}; 
      
    if(nprocesses > 0){
  
        pid_t child;
        child = fork();
          
        if(child < 0){
            printf("error\n");
        }
        if(child == 0){
            /*---------------------CHILD'S CODE----------------------*/
             
            signal(SIGCONT, handlerOfContinue);
            pause();
	    
            if(e_flag){
                while (1){
                    n++;
                    printf("Child%d %d is executed (%d)\n",(getpid() - getppid()), getpid(), n);
                    sleep(1);           
                }
            }
  
            exit(0);
        }
        else{
            /*-------------FATHERS'S CODE--------------------------*/
            count++;
            childPid[count - 1] = child;
  
            forker(nprocesses - 1, argc, argv);
              
            for(j=0;j<count;(j)++)
                intArgv[j] = atoi(*(argv + 1 + j)); //cast char to int
            for(m=0;m<count;m++){
                    for(j=0;j<count;(j)++){
                        if (m<4){
                            printf("\n");
                            kill(childPid[intArgv[j] - 1], SIGCONT);
                            sleep(3);
                            kill(childPid[intArgv[j] - 1], SIGSTOP);
                        }
                        else{
                            kill(childPid[intArgv[j] - 1], SIGKILL);
                        }
                    }
            }
            wait(0);
            exit(0);
        }
    }
}
  
void handlerOfContinue(){
    e_flag = 1;
}
