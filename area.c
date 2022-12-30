/*
 * Asg1 CPSC 3220
 * John Mathews
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int main(int argc, char *argv[]){

    //check number of command-line arguments
    if (argc != 3){

        if (argc > 3) printf("Too many arguments passed through execl() to area.c\n");
        else if (argc < 3) printf("Not enough arguments passed through execl() to area.c\n");
        exit(-1);
    }

    //print to terminal routine results:
    printf("Child1: pid %d, ppid %d, area is %d\n", getpid(), getppid(), atoi(argv[1]) * atoi(argv[2]));
    
    return 0;
}