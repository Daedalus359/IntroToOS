// Chris Fietkiewicz (chris.fietkiewicz@case.edu)

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <stdlib.h>     
#include <semaphore.h>  

#define N 10
#define BUFFER_SIZE 5

// Struct for condition variable
struct condition {
	sem_t sem; // Semaphore to be initialized to 0
	int count; // Count of threads waiting
};

//not empty count: number of producers waiting to produce
//not full count: number of consumers waiting to consume

struct condition not_full, not_empty;
//call cpost not empty after adding an item
//call cpost not full 

void cwait(struct condition *c); // Semaphore implementation of conditional wait
void cpost(struct condition *c); // Semaphore implementation of conditional signal

/* Global variables are shared by the thread(s) */
sem_t mutex, next; //got rid of original 2nd and 3rd, added a next
int buffer[BUFFER_SIZE];

void *child(); /* child thread */

int main(int argc, char *argv[])
{
	//init sems within the conditions
	if(sem_init(&mutex, 0, 1) < 0 || sem_init(&next, 0, 0) < 0 || sem_init(&(not_full.sem), 0, 0) < 0 || sem_init(&(not_empty.sem), 0, 0) < 0) { // 0 = multithreaded
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
		cwait(&not_full);//CHECK??
		sem_wait(&mutex);
		sleep((double) data[i] / 50); // Not required. Used for testing.
		buffer[in] = data[i];
		cpost(&not_empty);//CHECK?


		//CHECK??
		if (next_count > 0)
			sem_post(&next);
		else{
			sem_post(&mutex);
			out = (out + 1) % BUFFER_SIZE;
		}
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
		cwait(&not_empty);//CHECK??
		sem_wait(&mutex);
		int data = buffer[out];
		sleep((double) data / 50); // Not required. Used for testing.
		printf("%d\n", data);
		cpost(&not_full);//CHECK?

		//CHECK??
		if (next_count > 0)
			sem_post(&next);
		else{
			sem_post(&mutex);
			out = (out + 1) % BUFFER_SIZE;
		}	
	pthread_exit(0);
}

// Semaphore implementation of conditional wait
void cwait(struct condition *c) {
	c->count++;
	if (next_count > 0)
		sem_post(&next);
	else
		sem_post(&mutex);
	sem_wait(&(c->sem));
	c->count--;
}

// Semaphore implementation of conditional signal
void cpost(struct condition *c) {
	if (c->count > 0) {
		next_count++;
		sem_post(&(c->sem));
		sem_wait(&next);
		next_count--;
	}
}