// Name: Carlo Bilbao 
// Date: 2/16/23 
// Title: Lab5 – Mutex Lock 
// Description: This program simulates a multithreaded 
// program using mutex locks 
//Thread Synchronization - Mutex lock
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h> 
#include <unistd.h>
#include <fcntl.h>


#define NTHREADS 10

void *go(void *arg);
//void cleanup(int sigtype);

pthread_t threads[NTHREADS];
sem_t *mutex;
pthread_mutex_t count_mutex;	// Declare a mutex variable

int main() {
    //signal(SIGINT,cleanup);
    //mutex = sem_open("mutex", O_CREAT, 0644, 1);
    int i;
    for (i = 0; i < NTHREADS; i++)  
        pthread_create(&threads[i], NULL, go, (void *)(size_t)i);
    for (i = 0; i < NTHREADS; i++) 
        pthread_join(threads[i],NULL);
    sem_unlink("mutex");
    return 0;
}

void *go(void *arg) {
    printf("Thread %d is now attempting ....\n",  (int)arg);
    //sem_wait(mutex);
	pthread_mutex_lock(&count_mutex);	// Lock the critical section
    sleep(1);
    printf("Thread %d is running in its Critical Section........\n",  (int)arg);
    //sem_post(mutex);
    pthread_mutex_unlock(&count_mutex);	// Unlock the critical section
    pthread_exit(0);
}

/*void cleanup(int sigtype){
    sem_unlink("mutex");
    printf("\n Terminating\n");
    exit(0);
}*/
