// Name: Carlo Bilbao
// Date: 3/15/23
// Title: Lab7, Step 3 – FIFO
// Implement the FIFO
// page replacement
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

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
	int placeInArray = 0;	
	ref_page cache[C_SIZE]; // Cache that stores pages

	int i;
	int totalFaults = 0; // keeps track of the total page faults
	int totalRequests = 0;

	for (i = 0; i < C_SIZE; i++){//initialise cache array
		cache[i].pageno = -1;
	}

	//printf("Passed caches, entering while");

	while (fgets(pageCache, sizeof(pageCache), stdin)) {
		bool foundInCache = false;
		//printf("Entered while loop\n");
		//puts(pageCache);
		int page_num = atoi(pageCache); // Stores number read from file as an int
		for(i = 0; i < C_SIZE; i++) {
			if (cache[i].pageno == page_num) {
				foundInCache = true;
				break;
			}
		}
		if (foundInCache == false) {
			printf("Page %d caused a page fault.\n", page_num);
			totalFaults++; // Increment total number of page faults
			cache[placeInArray].pageno = page_num;
			if (placeInArray > C_SIZE - 2) { placeInArray = 0; }
			else { placeInArray++; }
		}
		//printf("%d\n", page_num);	// Then output the page_num
		totalRequests++;	// Keep track of requests
	}
	printf("%d Total Page Faults\n", totalFaults);
	printf("Total Requests: %d\n", totalRequests);
	float hitRate = (float)totalFaults / totalRequests;	// This is the miss rate
	hitRate = 1 - hitRate;
	printf("Hit Rate = %f\n", hitRate);
	return 0;
}
