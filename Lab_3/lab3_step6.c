// Name: Carlo Bilbao 
// Date: 1/26/23
// Title: Lab3 – step 6, consumer / producer problem 
// Description: This program works on a shared 
// buffer using shared memory

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//main
int main() {
	key_t key = 1243;
	//char buff[100];
	char *str;	// The buffer that the consumer/producer will work on
	//int count;
	//int i;
	int id;
	
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		if ( (id = shmget(key, sizeof(str), IPC_CREAT | 0666) ) < 0) {
			perror("shared memory not created");
			exit(1);
		}
		str = (char*) shmat(id, 0, 0);
		if (str <= (char*) (0) ) {
			perror("shared memory not attached");
			exit(1);
		}
		while(1) {
			printf ("Enter message! ");
			fgets(str, 100, stdin);	// Reads from stdin
			sleep(1);
			printf("\n");
		}
		
	}
	/*child 2 duplicates upstream into stdout */
	else {  
		sleep(5);
		if( (id = shmget(key, sizeof(str), 0 )) < 0) {
			perror("Shared memory not accessed ");
			exit(1);
		}
		str = (char*) shmat( id, 0, 0);
		if (str <= (char*)(0) ) {
			perror("Shared memory not attached");
			exit(1);
		}
		while(sizeof(str)>0) {
			sleep(1);
			puts(str);
		}
	}
	return 0;
	}
