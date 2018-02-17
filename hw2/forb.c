// Chris Fietkiewicz (cxf47)
// Stays busy with nested for loops
#include <stdio.h>

int main() {
	printf("Looping\n");
	int i, j, k, N = 50;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			for(k = 0; k < N; k++) {
				printf("Hello, world! sdklfjsldkgfhlksdfghksajdfhgkljsdfghlkjdfhglkjdhfgkjh");
			}
		}
	}
}
