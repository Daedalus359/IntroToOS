// Chris Fietkiewicz. Solves problem with critical section
// using OpenMP "critical" construct.
#include <stdio.h>
#include <omp.h>

double shubert(double x1, double x2);

int main () { 
	int trial; 
	for (trial = 1; trial <= 1000; trial++) {
		int i, sum = 0;
		#pragma omp parallel for
		for (i = 1; i <= 100; i++) {
			#pragma omp critical
			sum = sum + i;
		} /* All threads join master thread and terminate */ 
		if (sum != 5050)
			printf("****** ERROR *******");
	}
	printf("\n");
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
