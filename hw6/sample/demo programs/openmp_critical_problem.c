// Chris Fietkiewicz. Demonstrates problem with critical section
// by having multiple threads change the value of a variable "sum"
// without any synchronization. Each thread should add its share
// of the numbers, and the final total should be 5050. If the total
// is not correct, an error message is printed. Many trials are used.
#include <stdio.h>
#include <omp.h> 

int main () { 
	int trial; 
	for (trial = 1; trial <= 1000; trial++) {
		int i, sum = 0;
		#pragma omp parallel for
		for (i = 1; i <= 100; i++) {
			sum = sum + i;
		} /* All threads join master thread and terminate */ 
		if (sum != 5050)
			printf("****** ERROR *******");
	}
	printf("\n");
	return 0;
} 
