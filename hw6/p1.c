//Kevin Bradner
//kmb172@case.edu

//Problem 1: OpemMP Approach

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <string.h>

#include <omp.h>

double shubert(double x1, double x2);

int main ()
{

	//region to serach over for shubert function
	double step = 0.5;
	double x1_start = -2;
	double x1_stop = 2;

	//the smallest value found so far
	double min = 0;

	double y;

	#pragma omp parallel for
	for (int x1 = -4; x1 <= 4; x1 += 1)
	{
		for (double x2 = -2; x2 <= 2; x2+=step)
		{
			y = shubert((x1 / 2), x2);
			#pragma omp critical
			{
				if(y < min)
				{
					min = y;
				}
			}
		}
	}
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