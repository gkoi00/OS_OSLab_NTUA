# fconc.c

This program takes as arguments two files to be read and a third file that is used
to copy contents of the other two files combined.
execute with, eg: ./fconc A B C . It copies contents of A and B to C.
* If user doesn't give a third argument (output file), a default "fconc.out" file
 should be generated.
* The program should check if there is a wrong number of arguments and print a hint on
 how to use the executable on the right way.
* It should also check if one of the two input files does not exist and abort with a
 message
* File "mystrace.txt" contains the system calls of the executable.

# fconc2.c
* Copies files in arguments except the last one to the file of the last argument.
e.g. ./fconc2 A B C D E copies A, B, C, D to E.
