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

void *child(); /* child thread */

sem_t sem;

//the smallest value found so far
double min;
pthread_t tid; /* the thread identifier */

int main ()
{

	double y;
	if(sem_init(&sem, 0, 1) < 0) { // 0 = multithreaded
		fprintf(stderr, "ERROR: could not initialize &semaphore.\n");
		exit(0);
	}

	// Prepare the child thread
	
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, child, NULL);

	for (double x1 = -2; x1 <= 0; x1 += 0.5)
	{
		for (double x2 = -2; x2 <= 2; x2+=0.5)
		{
			y = shubert(x1, x2);

			//critical section
			sem_wait(&sem);
				if(y <min)
				{
					min = y;
				}
			sem_post(&sem);
		}
	}

	printf("parent min: %f\n",min);

	pthread_join(tid, NULL); // Need to wait because someone needs to clean up

	printf("min: %f\n",min);

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

void *child(){
	double y;
	for (double x1 =0; x1 <=2; x1 += 0.5)
	{
		for (double x2 = -2; x2 <= 2; x2+=0.5)
		{
			y = shubert(x1, x2);

			//critical section
			sem_wait(&sem);
				if(y <min)
				{
					min = y;
				}
			sem_post(&sem);
		}
	}
	printf("child min: %f\n",min);
	pthread_exit(0);
}