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
#include <sys/time.h>
#include <semaphore.h>  

double shubert(double step, double x2);

int main(int argc, char *argv[])
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

	int num_process = 1;
	if (argc > 1)
		num_process = atoi(argv[1]);

	double range = 4.0 / num_process;

	// Setup processes and compute
	double stepSize = 0.005;
	int p_index = 0;
	int next_index;
	global_min[0] = 0;
	pid_t pid;

	struct timeval start, end, diff;  // timers
	gettimeofday(&start,NULL); // Unix timer

	for (next_index = 0; next_index < num_process & !pid; next_index++) {
		pid = fork();
		if (!pid)
			p_index = next_index;
	}

	double x1, x2, y;
	double x_start = p_index * range - 2;
	double x_stop = x_start + range / stepSize;
	double local_min = 0;
	for (x1 = x_start; x1 <= x_stop; x1 += stepSize){
		for (x2 = -2; x2 <= 2; x2 += stepSize){
			y = shubert(x1, x2);
			if (y < local_min)
				local_min = y;
		}
	}

	sem_wait(sem);
	if (local_min < global_min[0])
		global_min[0] = local_min;
	sem_post(sem);
	wait(NULL);

	if (p_index == 0){
		gettimeofday(&end, NULL);
		timersub(&end, &start, &diff);
		printf("min = %.2f, time = %.2f \n", global_min[0], diff.tv_sec+diff.tv_usec/1000000.0);
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
