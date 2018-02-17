#include <stdio.h>
#include <stdlib.h>
/*
	Multiple Pointer Usage
	Tommy Lu
	9/12/17
*/

int main(){
	int* ptr1;
	int y = 10;
	int* ptr2;
	int x = 12;

	ptr1 = &x;
	ptr2 = &y;
	printf("x is given the number: %d and an address: %p\n", x, &x);
	printf("y is given the number: %d and an address: %p\n", y, &y);
	printf("ptr1 points to x: %p while ptr2 points to y: %p\n", ptr1, ptr2);
	printf("ptr1 address: %p while ptr2 address: %p\n", &ptr1, &ptr2);

	(*ptr1) = (*ptr2);
	printf("Pointer 2 dereferences y for its number: %d, and then pointer 1 dereferences x to set it to y so that x's number becomes: %d\n", y, x);

	//Obviously when compiling this will give warnings due to ptr2 being an int* rather than int**
	ptr2 = &ptr1;
	printf("Pointer 2 begins pointing to pointer 1, pointer 1's address: %p, address pointer 2 points to: %p\n",&ptr1, ptr2);

	return 0;

}

