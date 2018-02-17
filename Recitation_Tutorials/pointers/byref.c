#include <stdio.h>
#include <stdlib.h>
/*
	By Reference
	Tommy Lu
	9/12/17
*/

void increment(int* val);
int main(){
	int i = 3;
	printf("i before incrementing: %d\n", i);
	increment(&i);
	printf("i increases incremented in another function by address: %d\n", i);
	return 0;

}

void increment(int* val){
	(*val)++;
}
