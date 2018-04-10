// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
#include <pthread.h>
#include <stdio.h>
#include <math.h>
#include <semaphore.h>

#include <stdlib.h>
#include <sys/time.h>

#define PARENT 0
#define CHILD 1
#define N 10000

/* Global variables are shared by the thread(s) */
sem_t sem; // Semaphore
double global_min = 0; // Global minimum
double range;
double stepSize = 0.005;

double shubert(double step, double x2);
void *child(); /* child thread */

int main(int argc, char *argv[])
{
	// Prepare semaphore
	if(sem_init(&sem, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		return -1;
	}

	int num_threads;
	if (argc > 1)
		num_threads = atoi(argv[1]);
	else
		num_threads = 5;

	struct timeval t_start, end, diff;  // timers
	gettimeofday(&t_start, NULL); // Unix timer
	// Prepare the child thread
	pthread_t tid[num_threads]; /* the thread identifier */
	double start[num_threads];
	range = 4.0 / num_threads;

	for (int i = 0; i < num_threads; i++) {
		start[i] = i * range - 2;
		pthread_create(&tid[i], NULL, child, &start[i]);
	}

	for (int i = 0; i < num_threads; i++)
		pthread_join(tid[i], NULL);
	
	gettimeofday(&end, NULL);
	timersub(&end, &t_start, &diff);
	printf("min = %.2f, time = %.2f ", global_min, diff.tv_sec+diff.tv_usec/1000000.0);
}

void *child(void *start) {
	double x1, x2, y;
	double *x1_start = start;
	double x1_stop = *x1_start + range - stepSize;
	// printf("x1_start = %.2f, x1_start = %.2f\n", *x1_start, x1_stop);
	// fflush(stdout);
	double local_min = 0; // Local minimum for each thread
	for (x1 = *x1_start; x1 <= x1_stop; x1 += stepSize) {
		for (x2 = -2; x2 <= 2; x2 += stepSize) {
			y = shubert(x1, x2);
			if (y < local_min)
				local_min = y;
		}
	}
	// *** ENTRY FOR CRITICAL SECTION ***
	sem_wait(&sem);
	// *** BEGIN CRITICAL SECTION ***
	if (local_min < global_min)
		global_min = local_min;
	// *** EXIT FROM CRITICAL SECTION ***
	sem_post(&sem);
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
