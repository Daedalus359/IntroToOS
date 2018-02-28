//Kevin Bradner
//kmb172@case.edu

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void) {


	const int SIZE = 4096;
	const char *name = "OS";
	int *sharedInt = malloc(sizeof(int));

	int shm_fd;

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	sharedInt = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (sharedInt == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	//the parent's counter
	int i = 0;
	int np = 1000000;
	while(i < np){
		i++;
	}

	//step 1: create child process to run top

	pid_t pid;

	pid = fork();

	if(pid ==0){
		char *args[4];
 		args[0] = "top";
 		args[1] = "-u";
 		args[2] = "abc12";
 		args[3] = 0;
 		execvp(args[0], args);
 		return 0;
	}

	wait(NULL);

	//step 2: create second child to be counter
	pid = fork();

	if(pid == 0){
		int i = 0;
		int nc = 1000000;
		while(i < nc){
			i++;
		}

		*sharedInt = nc;

		return 0;
	}

	wait(NULL);

	int total = *sharedInt;

	fprintf("%d\n", *sharedInt);

}