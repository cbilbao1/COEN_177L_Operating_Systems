// Name: Carlo Bilbao 
// Date: 1/19/23
// Title: Lab2 – step 7, has the child run the ls command
// Description: This program simply creates a fork
// or child instances of the parent program

/* C program to demonstrate the use of fork()*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
/* main function */
int main() {
    pid_t  pid;
    int i, n = 3000; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
 exit(0);
    }
    else if(pid == 0)
    {
        execlp("/bin/ls", "ls", 0);
    }
    else
    {
        wait(0);
        printf("Child has completed the task! \n");
        exit(0);
    }
    return 0;
}
