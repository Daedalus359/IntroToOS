// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
// Demonstrates the use of:
// 1. pthread_self() 
// 2. creating multiple child threads
// 3. using a string buffer
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>     
#include <sys/types.h>  
#include <stdlib.h>     
#include <semaphore.h>  
#include <string.h>

#define BUFFER_SIZE 20

/* Global variables are shared by the thread(s) */
char buffer[BUFFER_SIZE];

void *child(); /* child thread */

int main(int argc, char *argv[]) {
	pthread_t tid1, tid2; /* the thread identifiers */
	pthread_create(&tid1, NULL, child, NULL);
	pthread_create(&tid2, NULL, child, NULL);

	// Parent
	sprintf(buffer, "%s", "Hello");

	// Join
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
}

void *child() {
	sleep(1); // Wait for parent to write to buffer (poor synchronization, but this is only a demo)
	long long tid = (long long) pthread_self();
	printf("My thread ID is %d, my parent is %lld, and the buffer contains: %s.\n", tid, getpid(), buffer);
	pthread_exit(0);
}
