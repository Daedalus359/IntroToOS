// Chris Fietkiewicz. Demonstrates using a pipe to transfer doubles
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1

int main(void)
{
	double write_data[BUFFER_SIZE] = {3.14, 2.71};
	double read_data[BUFFER_SIZE];
	pid_t pid;
	int fd[2];

	/* create the pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}
	printf("File descriptors... read:%d, write:%d\n", fd[READ_END], fd[WRITE_END]);

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* write to the pipe */
		write(fd[WRITE_END], write_data, sizeof(write_data)); 
	}
	else { /* child process */
		/* read from the pipe */
		read(fd[READ_END], read_data, sizeof(write_data));
		printf("Child read %f and %f\n", read_data[0], read_data[1]);
	}

	return 0;
}
