//Modified by Kevin Bradner, kmb172@case.edu

// Chris Fietkiewicz. Searches for a minimum in Shubert function.
// Note that an interval of 0.5 gives a very inaccurate result but
// works as a fast demonstration. For a realistic search, we would
// use a much small interval and remove the printing from the loop.
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
#include <pthread.h>

// Prototype for computation
double shubert(double x1, double x2);

void *half_shubert( void *ptr )
{

    double x1, x2, y, min = 0;
     int *thread_num;
     thread_num = (int *) ptr;
     printf("%d \n", * thread_num);

     // Loops 
  for (x1 = -2 + 2 * *thread_num; x1 <= 0 + 2 * *thread_num; x1 += 0.5) {
    for (x2 = -2; x2 <= 2; x2 += 0.5) {
      y = shubert(x1, x2);
      printf("%.2f ", y);
      if (y < min)
        min = y;
    }
    //printf("\n", y);
  }
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

int main(){
     pthread_t thread1, thread2;
     const int *number0 = 0;
     const int *number1 = 1;
     int  iret1, iret2;

    /* Create independent threads each of which will execute function */

     iret1 = pthread_create( &thread1, NULL, half_shubert, (void*) number0);
     if(iret1)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1);
         exit(EXIT_FAILURE);
     }

     iret2 = pthread_create( &thread2, NULL, half_shubert, (void*) number1);
     if(iret2)
     {
         fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2);
         exit(EXIT_FAILURE);
     }

     printf("pthread_create() for thread 1 returns: %d\n",iret1);
     printf("pthread_create() for thread 2 returns: %d\n",iret2);

     /* Wait till threads are complete before main continues. Unless we  */
     /* wait we run the risk of executing an exit which will terminate   */
     /* the process and all threads before the threads have completed.   */

     pthread_join( thread1, NULL);
     pthread_join( thread2, NULL); 

     return 0;
}