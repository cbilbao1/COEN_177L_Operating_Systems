// Name: Carlo Bilbao
// Date: 3/15/23
// Title: Lab7, Step 1 – Generate test
// Description: This program generates the
// testInput.txt file
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int main(int argc, char *argv[]) {
	int someNumber = 10000;	// This number corresponds to the number of characters we want in the text file
	int capNumber = 50;	// This is the highest number we want to be generated in the range, where 0 is minimum

	FILE *fp;
	char buffer [sizeof(int)];
	int i;
	fp = fopen("testInput10k.txt", "w");
	for (i=0; i<someNumber; i++) {
		sprintf(buffer, "%d\n", rand()%capNumber);
		fputs(buffer, fp);
	}
	fclose(fp);
	return 0;
}
