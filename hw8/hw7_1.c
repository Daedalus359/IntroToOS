// Chris Fietkiewicz (chris.fietkiewicz@case.edu)

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <stdlib.h>     
#include <semaphore.h>  

#define N 10
#define BUFFER_SIZE 5

/* Global variables are shared by the thread(s) */
sem_t mutex, full, empty;
int buffer[BUFFER_SIZE];

void *child(); /* child thread */

int main(int argc, char *argv[])
{
	if(sem_init(&mutex, 0, 1) < 0 || sem_init(&full, 0, 0) < 0 || sem_init(&empty, 0, BUFFER_SIZE) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		exit(0);
	}
	// Prepare the child thread
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, child, NULL);

	// Parent does work
	int data[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100}; // Must have N values
	int i, in = 0; // Index for writing
	for(i = 0; i < N; i++) {
		sem_wait(&empty);
		sem_wait(&mutex);
		sleep((double) data[i] / 50); // Not required. Used for testing.
		buffer[in] = data[i];
		sem_post(&mutex);
		sem_post(&full);
		in = (in + 1) % BUFFER_SIZE;
	}
	// Join and print result
	pthread_join(tid, NULL);
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
}

void *child() {
	int i, out = 0; // Index for reading
	for(i = 0; i < N; i++) {
		sem_wait(&full);
		sem_wait(&mutex);
		int data = buffer[out];
		sleep((double) data / 50); // Not required. Used for testing.
		printf("%d\n", data);
		sem_post(&mutex);
		sem_post(&empty);
		out = (out + 1) % BUFFER_SIZE;
	}
	pthread_exit(0);
}
