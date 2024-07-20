// Name: Carlo Bilbao 
// Date: 1/26/23
// Title: Lab3 – step 5, consumer / producer problem 
// Description: This program works on a shared 
// buffer using pipes

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
 #include <string.h>
#include <sys/wait.h> 
//main
int main() {
	int fds[2];
	char buff[100], *str;
	int count;
	int i;
	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		printf("Enter message! ");
		fgets(str, 100, stdin);	// Reads from stdin
		printf("\n ");	// The producer is writing upstream
		//dup2(fds[0], 0);
		close(fds[0]);
		//Now, write to the upstream end
		write(fds[1],str,strlen(str));
		exit(0);
		 
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		close(fds[1]);
		//Read from downstream end and print
		//The consumer is reading from downstream
		while((count=read(fds[0],buff,60))>0){
			for(i=0;i<count;i++){
				write(1,buff+i,1);
			}
			printf("\n");
		}
		exit(0);
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
	}
