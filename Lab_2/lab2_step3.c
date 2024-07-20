// Name: Carlo Bilbao 
// Date: 1/19/23
// Title: Lab2 – step 3, allow the user to determine the delay
// Description: This program simply creates a fork
// or child instances of the parent program

/* C program to demonstrate the use of fork()*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function */
/* main function with command-line arguments to pass */
int main(int argc, char *argv[]) {
    //Check if the user inputted a delay
    if (argc != 2){
	printf ("Usage: %s <delay> \n",argv[0]);
	exit(0);
    }

    //The value of n then is taken as 
    int n = atoi(argv[1]); // n microseconds is taken as command-line argument
    pid_t  pid;
    int i; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
 exit(0);
    }    
    if (pid){
        // Parent process: pid is > 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the parent Process displaying iteration %d \n",i);
            usleep(n);
        }
    }
    else{
        // Child process: pid = 0
        for (i=0;i<10;i++) {
            printf("I am the child process displaying iteration %d\n",i);
            usleep(n);
        }
    }
    return 0;
}
