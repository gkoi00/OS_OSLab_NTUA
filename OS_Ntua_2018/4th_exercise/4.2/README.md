# scheduler-shell.c
#### NEW STUFF HERE:
###### Shell implementation and interaction with the scheduler

This program is an extention of the previous one.
Now the scheduler also includes another process, the "shell". The source code is in the file shell.c and request.h has the declarations of the requests
from the shell to the scheduler.  
###### The available commands are:
* "k id": kill process
* "p exec": spawn a new process
* "p": print all processes and the current one
* "q": exit

###### Known bug (1)
If I have shell----prog(id=1)----prog(id=2)
and kill prog with id=1 then the remaining process will still have id=2.  
This needs to be fixed.

###### Known bug (2)
When all processes terminate the scheduler still schedules the shell. So in order to terminate I should type "q" to terminate the shell, or to fix it so that the shell terminates when no process is alive.

###### Usage:
eg:
* ./scheduler prog prog
* and during the execution I can use the available shell commands.

###### HOW THE SHELL WORKS:
It receives as arguments two file descriptors. One for writing requests into apipe and one to write return values to another pipe. These return values giveinformation about the achievement of the request. In general it reads with "get_cmdline" a command given by the user and constructs a struct with all theinformation needed for that command to be executed. Then it writes it in the pipe.Another process (scheduler) reads it and as soon as it finishes its actions writesto pipe the return value. Shell reads it and sees whether the result was ok ornot.HOW SHCEDULER WORKS:    It constructs the processes given as arguments by the user plus the shell.he processes raise SIGSTOP signal. It puts them in a cirqular queue and starts thefirst process which is the shell. Then it gets stuck in "shell_request_loop". Thereit waits for the shell to make a request, it reads it, processes it and finally wites in the other pipe the return value of the request.In 2 seconds alarm goes on and scheduler goes in sigalarm_handler where it stops thefirst child. Then it goes in sigchld_handler since a child has stoppedo terminated or killed) and starts the next one and so on ...     
