# scheduler.c

#### NEW STUFF HERE:
###### sigaction(), execve(), SIGALRM and SIGCHLD, rand() and srand(), pointer to function.


This program implements a scheduler for the execution of a number of processes. The processes print a simple iterative message, and the frequency of these iterations is random.

The scheduler starts a process, lets it run for TQ seconds and then stops it. It then continues with the next one.

All processes are in a cirqular FIFO linked list. When a process terminates it is removed from the list. When all processes terminate, the scheduler terminates too.

##### Usage:
eg:  
* ./scheduler prog prog prog prog

The scheduler schedules four "prog" executables
