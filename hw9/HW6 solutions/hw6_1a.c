// Chris Fietkiewicz. OpenMP solution without "for" clause
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <omp.h>

double shubert(double step, double x2);

int main (){
	double min = 0, stepSize = 0.5;
	int nSteps = (int) (4.0 / stepSize);
	int step; // Step index

	#pragma omp parallel
	{
		int tid = omp_get_thread_num();
		double x1_start, x1_stop;
		if (tid == 0) { // Parent thread
			x1_start = -2; // Starting x1 value
			x1_stop = 0; // Stopping x1 value
		}
		else { // Child thread
			x1_start = stepSize; // Starting x1 value
			x1_stop = 2; // Stopping x1 value
		}
		double y, x1, x2;
		for (x1 = x1_start; x1 <= x1_stop; x1 += stepSize) {
			for (x2 = -2; x2 <= 2; x2 += stepSize) {
				y = shubert(x1, x2);
				printf("%.2f ", y);
				#pragma omp critical
				if (y < min)
					min = y;
			}
			printf("\n", y);
		}
	}
	printf("min = %.2f ", min);
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