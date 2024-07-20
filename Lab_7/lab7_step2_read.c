// Name: Carlo Bilbao
// Date: 3/15/23
// Title: Lab7, Step 2 – Read test
// Description: This program reads the page
// requests iteratively
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {//to
int pageno;
} ref_page;

//Reads characters in the pipeline stream and then stores into string pointed to by str
//Stops when n-1 characters read or if newline is read
//Returns the character that was read
//char *fgets(char *str, int n, FILE *stream)

int main(int argc, char *argv[]){
	if (argc < 2) {
		printf("Usage: %s <cacheSize> \n", argv[0]);
		exit(1);
	}

	int C_SIZE = atoi(argv[1]);	// First argument, Size of Cache passed by user
	char pageCache[100];	// Cache that holds the input from test file, Create our page buffer to be used when reading
	ref_page cache[C_SIZE]; // Cache that stores pages

	int i;
	int totalFaults = 0; // keeps track of the total page faults

	for (i = 0; i < C_SIZE; i++){//initialise cache array
		cache[i].pageno = -1;
	}

	//printf("Passed caches, entering while");

	while (fgets(pageCache, sizeof(pageCache), stdin)) {
		//printf("Entered while loop\n");
		//puts(pageCache);
		int page_num = atoi(pageCache); // Stores number read from file as an int
		printf("%d\n", page_num);	// Then output the page_num
	}
	return 0;
}
