//Kevin Bradner, kmb172
//Modified from core_test_fork4.c from Chris Fietkiewicz


#include <stdio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2000000000

int main() {

	int numCores;
	int coresCreated = 1;

	printf("Enter a numer of cores to use between 1 and 4: ");
	scanf("%d", &numCores);

	if(numCores < 1 || numCores > 4){
		printf("Invlaid Choice. Terminating program.");
		return 1;
	}

	long int i;
	long long int x = 0;
	pid_t pid = 0;
	struct timeval start_time, stop_time, elapsed_time;  // timers
	gettimeofday(&start_time,NULL); // Unix timer

	//create the right numer of processes
	while(numCores > coresCreated){
		if(pid == 0){
			pid = fork();
			coresCreated++;
		}else{
			break;
		}
	}

	for (i = 0; i < (N / numCores); i++) {
		x = x + 1;
	}

	gettimeofday(&stop_time,NULL);
	timersub(&stop_time, &start_time, &elapsed_time); // Unix time subtract routine
	printf("Process %d total time was %f seconds. x = %lld.\n", getpid(), elapsed_time.tv_sec+elapsed_time.tv_usec/1000000.0, x);
	if(pid > 0){
		wait(NULL);
	}
}
