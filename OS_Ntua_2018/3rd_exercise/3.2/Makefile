CC = gcc
#compile multi-threaded applications with -pthread and when -g
#is use(for gdb info) use -O2 to optimize compilation again
CFLAGS = -Wall -O2 -pthread

all: mandel

##################### Mandelbrot #############################
mandel: mandel.o mandel-lib.o
	$(CC) $(CFLAGS) -o mandel mandel.o mandel-lib.o

mandel.o: mandel.c
	$(CC) $(CFLAGS) -c -o mandel.o mandel.c

mandel-lib.o: mandel-lib.c
	$(CC) $(CFLAGS) -c -o mandel-lib.o mandel-lib.c

########################### Clean ###############################
clean:
	rm -f *.o mandel
