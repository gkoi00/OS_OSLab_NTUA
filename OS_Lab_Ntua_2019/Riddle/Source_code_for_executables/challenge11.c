#include <stdio.h>
#include <stdlib.h>     //fork()
#include <unistd.h>     //fork()
#include <sys/wait.h>   //wait()
#include <errno.h>      //errno
#include <fcntl.h>
#include <string.h>

int main(){
    int i, t;
    int fd_read, fd_write;
    char buffer;
    ssize_t bytes_read = 0;

    fd_read = open("secret_number", O_RDONLY|O_CREAT, 0600);

    while (!bytes_read){
        bytes_read = read(fd_read, &buffer, sizeof(char));
        //printf("I read %ld bytes\n", bytes_read);
    }

    while(bytes_read){
        printf("I read: %c\n", buffer);
        bytes_read = read(fd_read, &buffer, sizeof(char));
    }

    close(fd_read);
    return 0;
}
