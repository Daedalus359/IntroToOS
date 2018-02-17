#include <stdio.h>
#include <stdlib.h>
/*
	Basic pointer dereferencing and referencing
	Tommy Lu
	9/12/17
*/

int main(){
	int* ptr;
	int data;
	printf("Currently the pointer ptr and the integer data represent nulls\n");

	data = 20;
	printf("Data is given the number: %d and an address: %p\n", data, &data);

	ptr = &data;
	printf("The pointer ptr references data, pointing to data's address: %p while having its own at this address: %p\n", ptr, &ptr);
	printf("The pointer ptr can also dereference the data, the data's number: %d\n", (*ptr));

	(*ptr)++;
	printf("The pointer ptr can dereference the data and operate on it such as adding 1, the data's number: %d\n", (*ptr));

	return 0;

}

