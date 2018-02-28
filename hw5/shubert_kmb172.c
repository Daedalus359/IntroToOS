//Modified by Kevin Bradner, kmb172@case.edu

// Chris Fietkiewicz. Searches for a minimum in Shubert function.
// Note that an interval of 0.5 gives a very inaccurate result but
// works as a fast demonstration. For a realistic search, we would
// use a much small interval and remove the printing from the loop.
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/wait.h>



// Prototype for computation
double shubert(double x1, double x2);

int main (){

  //create pipe array
  int fd1[2];  // Used to store two ends of first pipe
  if (pipe(fd1)==-1)
     {
         fprintf(stderr, "Pipe Failed" );
         return 1;
      }

  //initialize common variables
  double x1, x2, y, min = 0;

  //declare varaibles that vary between processes
  double x1_min, x1_max;

  //fork into 2 processes
  pid_t pid;
  pid = fork();

  if (pid == 0){
    x1_min = -2;
    x1_max = 0;
  }else{
    x1_min = 0;
    x1_max = 2;
  }

  
  // Loops 
  for (x1 = x1_min; x1 <= x1_max; x1 += 0.5) {
    for (x2 = -2; x2 <= 2; x2 += 0.5) {
      y = shubert(x1, x2);
      printf("%.2f ", y);
      if (y < min)
        min = y;
    }
    //printf("\n", y);
  }

  //local minima for each process are now in min
  //make child write its min into the pipe
  if (pid == 0){
    close(fd1[0]);  // Close reading end of first pipe
    write(fd1[1], &min, sizeof(min));
    return 0;
  }

  //have the parent read from the pipe
  double other_min;
  read(fd1[0], &other_min, sizeof(other_min));

  if (other_min < min){
    min = other_min;
  }
  
  printf("minimum = %.2f ", min);
}

// Compute Shubert value for x1,x2 combination
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