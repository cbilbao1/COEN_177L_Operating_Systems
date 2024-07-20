// Name: Carlo Bilbao 
// Date: 2/6/23
// Title: Lab4 – step 5, Program with Threads 
// Description: This program creates N*L threads 
// and performs matrix multiplication

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int N, M, L; //N, M, L - global
//A, B, C matrices
double **matrixA, **matrixB, **matrixC; //A, B, C matrices - global

struct d {
	int row;
	int col;
}; //Structure to hold values row, column to pass to thread

//function prototypes
void initializeMatrix(int r,int c, double **matrix); //initialize matrix with random values
void printMatrix(int r,int c, double **matrix); //print matrix
void *multiplyRow(void* arg); //thread multiply function

int main(int argc,char *argv[]) { //read N, M, and L as command-line arguments
	if (argc != 4) {
		printf("USage: %s <N><M><L> \n", argv[0]);
		exit(1);
	}
	N = atoi(argv[1]);
	M = atoi(argv[2]);
	L = atoi(argv[3]);
	
	//Iterative variables for matrix A, B, and C respectively
	int i, j, k = 0;
	
	//Fill in data for the three matrices
	matrixA = (double**)malloc(sizeof(double*)*N);
	for(i = 0; i < N; i++)
	{
		matrixA[i] = (double*)malloc(M);
	}
	matrixB = (double**)malloc(sizeof(double*)*M);
	for(i = 0; i < M; i++)
	{
		matrixB[i] = (double*)malloc(L);
	}
	matrixC = (double**)malloc(sizeof(double*)*N);
	for(i = 0; i < N; i++)
	{
		matrixC[i] = (double*)malloc(L);
	}
	
	//N threads
	pthread_t threads[N];
	
	initializeMatrix(N, M, matrixA); //Initialize matrixA with random values
	initializeMatrix(M, L, matrixB); //Initialize matrixB with random values
	
	struct d *data;
	
	//Multiply row A by all columns for B to produce
	//creating N threads, each multiplying ith row of matrixA by each column of matrixB to produce the row of matrixC
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < L; j++)
		{
			data = (struct d*)malloc(sizeof(struct d));
			data->row = i;
			data->col = j;
			pthread_create(&threads[i*L + j],NULL,multiplyRow,data); // Pass in the data structure d
		}
	}
	
	//Main thread waits for child threads to complete
	for(k = 0; k < N*L; k++)
	{
		pthread_join(threads[k],NULL);
	}
	
	//Print Matrix A, B, and C
	printf("Printing Matrix A: \n");
	printMatrix(N,M,matrixA);
	printf("\nPrinting Matrix B:\n");
	printMatrix(M,L,matrixB);
	printf("\nPrinting Matrix C:\n");
	printMatrix(N,L,matrixC);
	return 0;
}

//Initialize matrixA and matrixB with random values
void initializeMatrix(int r, int c, double **matrix) {
	srand(time(NULL));
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < c; j++) {
			matrix[i][j] = rand()%5;
		}
	}
}

//Thread function: multiply row of A by columns of B --> row of C
void* multiplyRow(void* arg) {
	struct d *data = arg; // Use our data structure argument
	
	int i, j, k;
	//Thread multiply the ith row of matrixA by jth column of matrixB and adding them to get matrixC
	i = data->row;
	j = data->col;

	printf("Thread %lu is multiplying %dth row by %dth colimn and adding them\n", pthread_self(), i, j);
	double temp = 0;
	for (k = 0; k < M; k++) {
		temp += matrixA[i][k]*matrixB[k][j];
		matrixC[i][j] = temp;
	}
	
	pthread_exit(0);
}

//Print matrices
void printMatrix(int r, int c, double **matrix) {
	int i, j;
	for(i = 0; i < r; i++) {
		for(j = 0; j < c; j++) {
			printf("%d ", (int)matrix[i][j]);
		}
		printf("\n");
	}
}
