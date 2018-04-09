// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <semaphore.h>  

#define PARENT 0
#define CHILD 1
#define N 10000

/* Global variables are shared by the thread(s) */
sem_t sem; // Semaphore
double global_min = 0; // Global minimum

double shubert(double step, double x2);
void *child(); /* child thread */

int main(int argc, char *argv[])
{
	// Prepare semaphore
	if(sem_init(&sem, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}
	// Prepare the child thread
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, child, NULL);

	// Parent does work
	double step = 0.5, x1_start, x1_stop, x1, x2, y;
	x1_start = step; x1_stop = 2;
	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
			y = shubert(x1, x2);
			// *** ENTRY FOR CRITICAL SECTION ***
			sem_wait(&sem);
			// *** BEGIN CRITICAL SECTION ***
			if (y < global_min)
				global_min = y;
			// *** EXIT FROM CRITICAL SECTION ***
			sem_post(&sem);
		}
	}
	// Join and print result
	pthread_join(tid, NULL);
	printf("min = %.2f ", global_min);
}

void *child() {
	double step = 0.5, x1_start, x1_stop, x1, x2, y;
	x1_start = -2; x1_stop = 0;
	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
			y = shubert(x1, x2);
			// *** ENTRY FOR CRITICAL SECTION ***
			sem_wait(&sem);
			// *** BEGIN CRITICAL SECTION ***
			if (y < global_min)
				global_min = y;
			// *** EXIT FROM CRITICAL SECTION ***
			sem_post(&sem);
		}
	}
	pthread_exit(0);
}

double shubert(double step, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((i + 1) * step + i);
		sum2 += i * cos((i + 1) * x2 + i);
	}
	return sum1 * sum2;
}
