#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

/*Usage eg: ./challenge12 /tmp/riddle-w3mNVp T*/
int main(int argc, char **argv){

    int fd_map_file;
    char letter;

    fd_map_file = open(argv[1], O_RDWR);
    if (fd_map_file < 0){
        perror("OPENING MAP FILE\n");
        exit (-1);
    }

    letter = *argv[2];

    lseek(fd_map_file, 0x6f, SEEK_SET);
    write(fd_map_file, &letter, sizeof(letter));
}
