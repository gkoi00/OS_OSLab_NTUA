/*
This program takes as arguments two files to be read and a third file that is used
to copy contents of the other two files combined.
execute with, eg: ./fconc A B C . It copies contents of A and B to C.
-If user doesn't give a third argument (output file), a default "fconc.out" file
 should be generated.
-The program should check if there is a wrong number of arguments and print a hint on
 how to use the executable on the right way.
-It should also check if one of the two input files does not exist and abort with a
 message

File "mystrace.txt" contains the system calls of the executable.
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv){
	/*------------declarations------------------*/
	int fd_input1, fd_input2, fd_output;
	char *output_file;
	ssize_t bytes_read_input1, bytes_read_input2; //like size_t but signed
	size_t length; //size_t type is for memory blocks
	char buff[1024]; //reads up to 1Kbyte files

	/*If wrong number of inputs print usage hint*/
	if ((argc < 3)||(argc > 4)){
		printf("Usage: ./fconc infile1 infile2 [outfile (default:fconc.out)]\n");
		return 1;
	}

	/*--------open first input file-------------*/
	fd_input1 = open(argv[1], O_RDONLY);
	if(fd_input1 < 0){
		printf("%s: No such file or directory\n", argv[1]);
	}

	/*--------open second input file-------------*/
	fd_input2 = open(argv[2], O_RDONLY);
	if(fd_input2 < 0){
		printf("%s: No such file or directory\n", argv[2]);
	}

	/*----abort if one of inputs doesn't exist-----*/
	if((fd_input1 < 0) || (fd_input2 < 0))
		return 1;

	/*-----------generate output file--------------*/
	if(argc == 4){
		output_file = argv[3];
	}
	else{
		output_file = "fconc.out";
	}
	fd_output = open(output_file, O_WRONLY | O_CREAT |O_TRUNC , S_IRUSR | S_IWUSR);
	if(fd_output < 0){
		printf("Output file failed to open!");
	}

	/*------------------READ-----------------------*/
	bytes_read_input1 = read(fd_input1, buff, sizeof(buff) - 1);

	/*------------------WRITE-----------------------*/
	length = strlen(buff);
	write(fd_output, buff, length);

	/*------------------READ-----------------------*/
	read(fd_input2, buff, sizeof(buff) - 1);

	/*------------------WRITE-----------------------*/
	length = strlen(buff);
	write(fd_output, buff, length);

	/*-----------close files------------------------*/
	close(fd_input1);
	close(fd_input2);
	close(fd_output);

	return 0;
}
