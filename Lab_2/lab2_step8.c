// Name: Carlo Bilbao 
// Date: 1/19/23
// Title: Lab2 – step 8, create 2 threads
// Description: This program creates 2 threads instead
// of 2 processes

/* C program to demonstrate the use of fork()*/
#include <stdio.h>      /* printf, stderr */
#include <sys/types.h>  /* pid_t */
#include <unistd.h>     /* fork */
#include <stdlib.h>     /* atoi */
#include <errno.h>      /* errno */ 
#include <pthread.h>


/*struct arg_struct
{
   int arg1;
   int arg2;
} *args;*/

//Create the function that we want to call when creating the thread
void *thread(void *arg) {
  char *ret;	// This is the return character
 
  int i = 0; 
  // Process: pid = 0
  for (i=0;i<10;i++) {
      printf("I am a thread %d\n",i);
      usleep(n);
  }

  //strcpy(ret, "This is a test");
  //pthread_exit(ret);
  return NULL;
}

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
    
    



    pthread_t thid1,thid2;
    void *ret;

    //Create first thread
    //if (pthread_create(&thid1, NULL, thread, "Thread 1") != 0) {
    //	perror("pthread_create() error");
    //	exit(1);
    //}

    if (pthread_create(&thid1, NULL, thread, n) != 0) {
    	perror("pthread_create() error");
    	exit(1);
    }
    //Create second thread
    if (pthread_create(&thid2, NULL, thread, n) != 0) {
    	perror("pthread_create() error");
    	exit(1);
    }
    pthread_join(thid1, NULL);
    pthread_join(thid2, NULL);






    /*if (pid){
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
    }*/
    return 0;
}

