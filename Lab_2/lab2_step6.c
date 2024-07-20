// Name: Carlo Bilbao 
// Date: 1/19/23
// Title: Lab2 – step 6, create 5 processes with 5 delays
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
    //Check if the user inputted a delay, inputting 5 delays for 5 processes
    if (argc != 6){
	printf ("Usage: %s <Parent delay> <delay> <delay> <delay> <delay> \n",argv[0]);
	exit(0);
    }

    //The value of n then is taken as 
    int nP = atoi(argv[1]); // n microseconds is taken as command-line argument 
    int n1 = atoi(argv[2]); // n microseconds is taken as command-line argument
    int n2 = atoi(argv[3]); // n microseconds is taken as command-line argument
    int n3 = atoi(argv[4]); // n microseconds is taken as command-line argument
    int n4 = atoi(argv[5]); // n microseconds is taken as command-line argument
    pid_t  pid, pid1, pid2, pid3;
    int i; // n is a delay in microseconds inserted in parent and child iterations
    printf("\n Before forking.\n");
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "can't fork, error %d\n", errno);
 exit(0);
    }    
    if (pid == 0){
        // Child process: pid is == 0
        for (i=0;i<10;i++) {
            printf("\t \t \t I am the 1st child Process displaying iteration %d \n",i);
            usleep(n1);
        }
    }
    else{
	//Create a fork, store new information of what got forked in pid1
	pid1 = fork();
	//Check new pid1 information if child or not
	if (pid1 == 0) {
        	// Child process: pid1 = 0
        	for (i=0;i<10;i++) {
            		printf("I am the 2nd child process displaying iteration %d\n",i);
            		usleep(n2);
        	}
	}
	else {
		//Create a fork, store new information of what got forked in pid2
		pid2 = fork();
		//Check new pid2 information if child or not
		if (pid2 == 0) {
        		// Child process: pid2 = 0
        		for (i=0;i<10;i++) {
            			printf("I am the 3rd child process displaying iteration %d\n",i);
            			usleep(n3);
        		}
		}
		else {	
			//Create a fork, store new information of what got forked in pid3
			pid3 = fork();
			//Check new pid3 information if child or not
			if (pid3 == 0) {
        			// Child process: pid3 = 0
        			for (i=0;i<10;i++) {
            				printf("I am the 4th child process displaying iteration %d\n",i);
            				usleep(n4);
        			}
			} else {
				// Parent case, pid3 > 0
        			// Parent process: pid3 is > 0
       				for (i=0;i<10;i++) {
            				printf("\t \t \t I am the Parent Process displaying iteration %d \n",i);
            				usleep(nP);
        			}
			}
		}
	}
    }
    return 0;
}
