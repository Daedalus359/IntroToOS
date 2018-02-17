#include <stdio.h>

int main() {

	//similar code to those found in the instructions
	const int a = 0;
	int b = 1;
	printf("%p, %p\n", &a, &b);

	//a for loop to kill time so I can run pmap, taken from for.c by chris fietkiewicz
	int i, j, k, N = 2000;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
			}
		}
	}
}