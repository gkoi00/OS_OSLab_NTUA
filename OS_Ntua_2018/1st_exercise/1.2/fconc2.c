/*
Copies files in arguments except the last one to the file of the last argument.
e.g. ./fconc2 A B C D E copies A, B, C, D to E.
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv){
	/*------------declarations------------------*/
	char buff[1024]; //for files up to 1Kbyte
	int fd[argc - 1], i;

	/*------------open input files------------------*/
	for(i=0; i<(argc - 2); i++)
			fd[i] = open(argv[i + 1], O_RDONLY);

	/*------------open output file------------------*/
	fd[argc - 2] = open(argv[argc - 1], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	
	/*----------------copy-paste------------------*/
	for(i=0; i<(argc - 2); i++){
		read(fd[i], buff, sizeof(buff) - 1);
		write(fd[argc - 2], buff, strlen(buff));
	}

	for(int i=0; i<(argc - 2); i++){
		close(fd[i]);
	}

	return 0;
}

