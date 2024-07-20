// Name: Carlo Bilbao 
// Date: 2/16/23 
// Title: Lab5 – Producer/Consumer Condition Variables 
// Description: This program will solve the producer 
// consumer problem using condition variables

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>


#define NTHREADS_P 5
#define NTHREADS_C 5
#define BUFSIZE 5

void *producer(void *arg);	// Producer function
void *consumer(void *arg);	// Consumer function
//void cleanup(int sigtype);

pthread_t threadsP[NTHREADS_P];	// Producer threads
pthread_t threadsC[NTHREADS_C];	// Consumer threads
//sem_t *mutex;
//pthread_t tidP[NP], tidC[NC];
int buff[BUFSIZE];
pthread_mutex_t mutex;
pthread_cond_t full, empty;
int p, c, in, out, count;



int main() {
    //signal(SIGINT,cleanup);
    //--mutex = sem_open("mutex", O_CREAT, 0644, 1);
    int i;
    /*for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
        */
    //Create the producer and consumer threads
    for(int i = 0; i < NTHREADS_P; i++) {
        pthread_create(&threadsP[i], NULL, (void *)producer, (void *)(size_t)i);
    }
    for(int i = 0; i < NTHREADS_C; i++) {
        pthread_create(&threadsC[i], NULL, (void *)consumer, (void *)(size_t)i);
    }
    /*for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
        */
    //--sem_unlink("mutex");
    
    
	//Terminate the producer and consumer threads
    for(int i = 0; i < NTHREADS_P; i++) {
        pthread_join(threadsP[i], NULL);
    }
    for(int i = 0; i < NTHREADS_C; i++) {
        pthread_join(threadsC[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);
    
    
    return 0;
}

void *producer(void *arg) {
    int item;
    int p = (int)arg;	// ID number
    srand(time(0));	// Set the time for randum number generation
    do {
		item = (rand() % 100);	// Generate a random number for the producer
		pthread_mutex_lock(&mutex);	// Lock the critical section
		while(count == BUFSIZE)
			pthread_cond_wait(&empty, &mutex);
			printf("Thread %d is now attempting ....\n",  p);
			buff[in] = item;
			printf("Producer #: %d produced item: %d at buffer space: %d\n", p, item, in);
			in = (in + 1) % BUFSIZE;
			count++;
			pthread_cond_signal(&full);
			printf("Thread %d is running in its Critical Section........\n",  p);
			pthread_mutex_unlock(&mutex);	// Unlock the critical section
			sleep(1);
		} while (1);
		return (NULL);
}

void *consumer(void *arg) {
    int item;
    int c = (int)arg;	// ID number
    srand(time(0));	// Set the time for randum number generation
    do {
		pthread_mutex_lock(&mutex);	// Lock the critical section
		while(count == 0)
			pthread_cond_wait(&full, &mutex);
			printf("Thread %d is now attempting ....\n",  c);
			item = buff[out];
			printf("Consumer #: %d consumed item: %d at buffer space: %d\n", c, item, out);
			out = (out + 1) % BUFSIZE;
			count--;
			pthread_cond_signal(&empty);
			printf("Thread %d is running in its Critical Section........\n",  c);
			pthread_mutex_unlock(&mutex);	// Unlock the critical section
			sleep(12);
		} while (1);
		return (NULL);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/
