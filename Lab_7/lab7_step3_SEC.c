// Name: Carlo Bilbao
// Date: 3/15/23
// Title: Lab7, Step 3 – SEC
// Implement the SEC
// page replacement
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>

typedef struct {//to
int pageno;
int bit;
//int age;
} ref_page;

//Reads characters in the pipeline stream and then stores into string pointed to by str
//Stops when n-1 characters read or if newline is read
//Returns the character that was read
//char *fgets(char *str, int n, FILE *stream)

int inCache(int page_num, ref_page cache[], int cacheSize) {
	int i;
	for(i = 0; i < cacheSize; i++) {
		if(cache[i].pageno == page_num) {
			return i;
		}
	}
	return -1;
}

int findPlace(int iterCache, ref_page cache[], int cacheSize) {
	int i;
	int j = 0;

	for(i = 0; i < cacheSize; i++) {
		if(cache[i].bit == -1) {	// There is an available spot
			return i;
		}
	}
	for(i = 0; i < cacheSize; i++) {
		if(cache[i].bit == 1) {
			cache[i].bit = 0;	// Page is given a second chance, so flip to 0
		} else if(cache[i].bit == 0) {
			j = i;
		}
	}
	return j;
}

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
		cache[i].bit = -1;
	}

	//printf("Passed caches, entering while");

	while (fgets(pageCache, sizeof(pageCache), stdin)) {
		bool foundInCache = false;
		//printf("Entered while loop\n");
		//puts(pageCache);
		int page_num = atoi(pageCache); // Stores number read from file as an int
		int curPage = inCache(page_num, cache, C_SIZE);	// This is the current page that we are on
		int iterCache = 0;	// Initialize the iteration cache to 0

		

        	if(curPage == -1) {	// If not found in the cache
            		iterCache = findPlace(iterCache, cache, C_SIZE);	// Find the replacement

			printf("Page %d caused a page fault.\n", page_num);
           		totalFaults++; // Increment total number of page faults
			cache[iterCache].pageno = page_num;	// Add the page to the cache
			cache[iterCache].bit = 0;	// Set the page's bit to 0

        	} else { cache[curPage].bit = 1; }	// If page is in cache, set to 1 and give it a second chance

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
