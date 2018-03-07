//Kevin Bradner
//kmb172@case.edu

//Problem 3: fork() Approach

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <string.h>
#include <fcntl.h> // For shared memory
#include <sys/shm.h> // For shared memory
#include <sys/mman.h> // For shared memory
#include <sys/wait.h> // For wait
#include <semaphore.h> // For semaphores
#include <pthread.h>

double shubert(double x1, double x2);

int main ()
{

	// Set up shared memory for semaphore
	const int SIZE = 1;
	const char *name = "ChrisFietkiewicz";
	int shm_fd;
	sem_t *sem;
	// Create shared memory for semaphore
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd,SIZE);
	sem = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (sem == MAP_FAILED) {
		printf("Map failed\n");
		exit(0);
	}
	// Set up semaphore
	if(sem_init(sem, 1, 1) < 0) { // 1 = multiprocess
		fprintf(stderr, "ERROR: could not initialize semaphore.\n");
		exit(0);
	}

	//region to serach over for shubert function
	double step = 0.5;
	double x1_start = -2;
	double x1_stop = 2;

	int tid;

	//the smallest value found so far
	double *min;
	double min_c = 0;
	double min_p = 0;

	min = mmap(NULL, sizeof *min, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	double y;

	//split into 2 processes
	pid_t pid;
	pid = fork();

	if(pid == 0){
		x1_start = 0;
	}else{
		x1_stop = 0;
	}

	for (double x1 = x1_start; x1 <= x1_stop; x1 += step)
	{
		for (double x2 = -2; x2 <= 2; x2+=step)
		{
			y = shubert(x1, x2);

			//critical section
			sem_wait(sem);
				if(y < *min)
				{
					*min = y;
					if(pid == 0){
						min_c = y;
					}else{
						min_p = y;
					}
				}
			sem_post(sem);
		}
	}

	if(pid == 0){
		printf("child min: %f\n",min_c);
	}else{
		printf("parent min: %f\n",min_p);
		printf("min: %f\n",*min);
	}

	return 0;
}

double shubert(double x1, double x2) {
	double sum1 = 0; 
	double sum2 = 0;
	int i;
	for (i = 1; i <= 5; i++) {
		sum1 += i * cos((i + 1) * x1 + i);
		sum2 += i * cos((i + 1) * x2 + i);
	}
	return sum1 * sum2;
}