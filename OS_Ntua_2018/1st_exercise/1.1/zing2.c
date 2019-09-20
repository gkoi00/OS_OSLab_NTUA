#include <stdio.h>
#include <unistd.h>
void zing(){
    char *name;

    name = getlogin();
    printf("Welcome to the machine %s!\n",name);

}
