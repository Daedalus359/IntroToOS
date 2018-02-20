//Kevin Bradner, kmb172@case.edu
//Modified from shm_producer & shm_consumer example files

#include <unistd.h>
#include <sys/types.h>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "Hello";
	const char *message1= "From ";
	const char *message2= "Your Child!";

	pid_t pid;

	int shm_fd;
	void *ptr;

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	

	pid = fork();

	//have the parent wait for the child to write, then read
	if(pid > 0){
		wait(NULL);

		/* now read from the shared memory region */
		printf("%s\n",ptr);
		


		/* remove the shared memory segment */
		if (shm_unlink(name) == -1) {
			printf("Error removing %s\n",name);
			exit(-1);
		}
	}

	//have the child write the message
	else{

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	sprintf(ptr,"%s",message0);
	ptr += strlen(message0);
	sprintf(ptr,"%s",message1);
	ptr += strlen(message1);
	sprintf(ptr,"%s",message2);
	ptr += strlen(message2);
		
	}



	return 0;
}