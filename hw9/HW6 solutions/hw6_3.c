// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <math.h>
#include <semaphore.h>  

double shubert(double step, double x2);

int main()
{
	// Setup shared memory for data
	const int SIZE = 1;
	const char *name = "ChrisF";
	int shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);
	double *global_min = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (global_min == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	// Setup shared memory for semaphore
	const int SIZE2 = 1;
	const char *name2 = "ChrisF2";

	int shm_fd2 = shm_open(name2, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd2,SIZE2);
	sem_t *sem = mmap(0,SIZE2, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd2, 0);
	if (sem == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}
	if(sem_init(sem, 1, 1) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		return -1;
	}

	// Setup processes and compute
	global_min[0] = 0;
	pid_t pid;
	pid = fork();
	if (pid) { // If parent
		double step = 0.5, x1_start, x1_stop, x1, x2, y;
		x1_start = step; x1_stop = 2;
		for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
			for (x2 = -2; x2 <= 2; x2 += step) {
				y = shubert(x1, x2);
				// *** ENTRY FOR CRITICAL SECTION ***
				sem_wait(sem);
				// *** BEGIN CRITICAL SECTION ***
				if (y < global_min[0])
					global_min[0] = y;
				// *** EXIT FROM CRITICAL SECTION ***
				sem_post(sem);
			}
		}
		wait(NULL);
		printf("min = %.2f ", global_min[0]);
		// Unlink shared memory
		if (shm_unlink(name) == -1) {
			printf("Error removing %s\n",name);
			exit(-1);
		}
		if (shm_unlink(name2) == -1) {
			printf("Error removing %s\n",name2);
			exit(-1);
		}
	}
	else { // Child
		double step = 0.5, x1_start, x1_stop, x1, x2, y;
		x1_start = -2; x1_stop = 0;
		for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
			for (x2 = -2; x2 <= 2; x2 += step) {
				y = shubert(x1, x2);
				// *** ENTRY FOR CRITICAL SECTION ***
				sem_wait(sem);
				// *** BEGIN CRITICAL SECTION ***
				if (y < global_min[0])
					global_min[0] = y;
				// *** EXIT FROM CRITICAL SECTION ***
				sem_post(sem);
			}
		}
	}
	return 0;
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
