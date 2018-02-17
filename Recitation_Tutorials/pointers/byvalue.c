#include <stdio.h>
#include <stdlib.h>
/*
	By Value
	Tommy Lu
	9/12/17
*/

void increment(int val);
int main(){
	int i = 3;
	printf("i before incrementing: %d\n", i);
	increment(i);
	printf("i remains the same number: %d\n", i);
	return 0;

}

void increment(int val){
	val++;
}
