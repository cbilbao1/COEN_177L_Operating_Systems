// Name: Carlo Bilbao 
// Date: 1/26/23
// Title: Lab3 – step 4, modify the program to run cat
// Description: This program runs the cat /etc/passwd | grep 
// root command using execlp
// using execlp

/*Sample C program for Lab 3*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
	int fds[2];
	pipe(fds);
	/*child 1 duplicates downstream into stdin */
	if (fork() == 0) {
		dup2(fds[0], 0);
		close(fds[1]);
		execlp("grep", "grep", "root", 0); 
	}
	/*child 2 duplicates upstream into stdout */
	else if (fork() == 0) {
		dup2(fds[1], 1);
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", 0); // Searches through the /etc/pass
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0);
	}
	return 0;
	}
