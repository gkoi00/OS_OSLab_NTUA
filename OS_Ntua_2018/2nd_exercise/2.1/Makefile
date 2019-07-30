CC = gcc
CFLAGS = Wall

all: fork-tree.o proc-common.o
	$(CC) -$(CFLAGS) fork-tree.o proc-common.o -o fork-tree

proc-common.o: proc-common.c
	$(CC) -$(CFLAGS) -c proc-common.c

fork-tree.o: fork-tree.c
	$(CC) -$(CFLAGS) -c fork-tree.c

clean:
	rm fork-tree.o proc-common.o fork-tree
