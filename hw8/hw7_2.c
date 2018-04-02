// Chris Fietkiewicz (chris.fietkiewicz@case.edu)

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <stdlib.h>     
#include <semaphore.h>  
#include <string.h>
#define BUFFER_SIZE 20

/* Global variables are shared by the thread(s) */
sem_t rw_mutex, mutex;
char buffer[BUFFER_SIZE];
int buffer_version = 0;
int read_count = 0;

void *child(); /* child thread */

int main(int argc, char *argv[])
{
	if(sem_init(&rw_mutex, 0, 1) < 0 || sem_init(&mutex, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		exit(0);
	}
	// Prepare the child thread
	pthread_t tid1, tid2; /* the thread identifiers */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid1, &attr, child, NULL);
	pthread_create(&tid2, &attr, child, NULL);

	// Writer
	sem_wait(&rw_mutex);
	sprintf(buffer, "%s", "Roses are red");
	buffer_version = 1;
	sem_post(&rw_mutex);
	sleep(1);
	sem_wait(&rw_mutex);
	sprintf(buffer, "%s", "Violets are blue");
	buffer_version = 2;
	sem_post(&rw_mutex);
	sleep(1);
	sem_wait(&rw_mutex);
	sprintf(buffer, "%s", "Synchronization is");
	buffer_version = 3;
	sem_post(&rw_mutex);
	sleep(1);
	sem_wait(&rw_mutex);
	sprintf(buffer, "%s", "Quite fun to do");
	buffer_version = 4;
	sem_post(&rw_mutex);
	sleep(1);

	// Join
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	sem_destroy(&rw_mutex);
	sem_destroy(&mutex);
}

void *child() {
	int j = 0, old_version = 0;
	pthread_t tid = pthread_self();
	while (old_version != 4) {
		sem_wait(&mutex);
		read_count++;
		if (read_count == 1)
			sem_wait(&rw_mutex);
		sem_post(&mutex);
		if (buffer_version != old_version) {
			printf("%d: %s\n", tid, buffer);
			fflush(stdout); // Not required, but may help
			old_version = buffer_version;
		}
		sem_wait(&mutex);
		read_count--;
		if (read_count == 0)
			sem_post(&rw_mutex);
		sem_post(&mutex);
	}
	pthread_exit(0);
}
