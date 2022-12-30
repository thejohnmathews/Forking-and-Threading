/*
 * Asg1 CPSC 3220
 * John Mathews
 *
 */

//include statements
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

//function prototypes
void* thread1(void *param);
void* thread2(void *param);

//global structure to hold c-l information
 struct inputStruct{

    int num1;
    int num2;
    char message[100];
};

//call main():
int main(int argc, char* argv[]){

    //main() local variables
    struct inputStruct information;
    int areaPid = 0;
    int perimeterPid = 0;
    pthread_t thread1Tid = 0;
    pthread_t thread2Tid = 0;
    void* result = 0;
    void* result2 = 0;
    char argument1[5];
    char argument2[5];

    //check number of command-line arguments
    if (argc != 4){

        if (argc > 4) printf("There are too many command-line arguments to main().\n");
        else if (argc < 4) printf("There are not enough command-line arguments to main().\n");
        exit(-1);
    }

    //place command-line arguments into struct
    information.num1 = atoi(argv[1]);
    information.num2 = atoi(argv[2]);
    strcpy(information.message, argv[3]);

    //spawn area child process
    areaPid = fork();

    //area child:
    if (areaPid == 0){

        //convert function arguments into strings so that they can pass through execl()
        sprintf(argument1, "%d", information.num1);
        sprintf(argument2, "%d", information.num2);

        //execute ./area
        execl("./area", "area", argument1, argument2, NULL);
    }
    else{

        //spawn perimeter child process
        perimeterPid = fork();

        //call sleep() to ensure area routine goes first
        sleep(1);

        //perimeter child:
        if (perimeterPid == 0){

            //convert function arguments into strings so that they can pass through execl()
            sprintf(argument1, "%d", information.num1);
            sprintf(argument2, "%d", information.num2);

            //execute ./perimeter
            execl("./perimeter", "perimeter", argument1, argument2, NULL);
        }
        //parent process:
        else{

                //wait for children processes to finish before continuing
                while (wait(NULL) > 0);
                printf("\n");

                //create threads and execute their functions
                pthread_create(&thread1Tid, NULL, thread1, (void*)&information);
                pthread_create(&thread2Tid, NULL, thread2, (void*)&information);

                //terminate threads and get results
                pthread_join(thread1Tid, &result);
                pthread_join(thread2Tid, &result2);

                //convert results to usable type
                int* ratio = (int*) result;
                char* reverseMessage = (char*) result2;

                //print parent statements
                printf("Parent: pid %d, ratio: %d, message: \"%s\"\n", getpid(), *ratio, reverseMessage);
        }
    }

    return 0;
}

//thread1(): calculates ratio between num1 & num2
void* thread1(void *param){

    //thread1() local variables
    int* returnPtr = (int*)malloc(sizeof(int));

    //convert struct to usable form and calculate ratio
    struct inputStruct *struct_ptr = (struct inputStruct*) param;
    *returnPtr = struct_ptr->num1 / struct_ptr->num2;

    //print thread1's tid and ratio
    printf("Thread 1: tid %ld, ratio is %d\n", pthread_self(), *returnPtr);

    //return result from calculating ratio
    pthread_exit((void*)(returnPtr));
}

//thread2(): reverses string
void* thread2(void *param){

    //thread2() local variables
    char* returnPtr = (char*)malloc(sizeof(char*));

    //call sleep() to prevent thread2 from finishing before thread1
    sleep(2);

    //convert struct to usable form
    struct inputStruct *struct_ptr = (struct inputStruct*) param;

    //reverse the string inside of struct_ptr
    int length = strlen(struct_ptr->message) - 1;
    for (int i = 0; i < strlen(struct_ptr->message); i++){

        returnPtr[i] = struct_ptr->message[length];
        length--;
    }

    //print thread2's tid and reverse string
    printf("Thread 2: tid %ld, message is \"%s\"\n\n", pthread_self(), returnPtr);

    //return result from reversing message
    pthread_exit((void*)(returnPtr));

}