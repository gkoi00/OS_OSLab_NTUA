# simplesync.c

#### NEW STUFF HERE:
###### THREADS, ATOMIC OPERATIONS, MUTEXES, TWO EXECUTABLES FROM ONE SOURCE FILE

This program uses two threads. The first increase the value of variable val and the second decreases it.  
It produces an executable where the two threads are syncronized with mutexes and another where synchronization is achieved with atomic operations.

To see the assempbly code run:
* gcc -S -DSYNC_ATOMIC simplesync.c
* or gcc -S -DSYNC_MUTEX simplesync.c
