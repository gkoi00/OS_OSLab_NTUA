CC = gcc
CFLAGS = -Wall

all: zing zing2

zing2: main.o zing2.o
	$(CC) $(CFLAGS) main.o zing2.o -o zing2

zing: main.o zing.o
	$(CC) $(CFLAGS) main.o zing.o -o zing

main.o:
	$(CC) $(CFLAGS) -c main.c

zing.o:
	$(CC) $(CFLAGS) -c zing.c

zing2.o:
	$(CC) $(CFLAGS) -c zing2.c

clean:
		rm zing.o main.o zing zing2.o zing2
