// Chris Fietkiewicz. Finds minimum of Shubert function
// using parallel programming (one parent thread, one child thread)

#include <pthread.h>
#include <stdio.h>
#include <math.h>

/* this variable is shared by the thread(s) */
double child_min;

void *child(); /* child thread */
double shubert(double x1, double x2);

int main(int argc, char *argv[])
{
	// These variables are private to the parent
	double x1, x2, y, parent_min = 0;
	double step = 0.5, x1_start, x1_stop;

	// Prepare the child thread
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of attributes for the thread */
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr, child, NULL);

	// Parent does work
	x1_start = step; x1_stop = 2;
	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
		  y = shubert(x1, x2);
		  if (y < parent_min)
			parent_min = y;
		}
	}
	
	// Collate results and print
	pthread_join(tid, NULL);
	if (parent_min < child_min)
		printf("min = %.5f\n", parent_min);
	else
		printf("min = %.5f\n", child_min);
}

void *child() {
	// These variables are private to the child
	double x1, x2, y;
	double step = 0.5, x1_start, x1_stop;

	x1_start = -2; x1_stop = 0;
	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
		  y = shubert(x1, x2);
		  if (y < child_min)
			child_min = y;
		}
	}
	pthread_exit(0);
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
