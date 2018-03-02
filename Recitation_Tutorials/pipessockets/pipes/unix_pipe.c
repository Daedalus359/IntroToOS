/**
 * Example program demonstrating UNIX pipes.
 *
 * Figures 3.25 & 3.26
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 * 
 * Additional comments by Tommy Lu
 */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER_SIZE 25
#define READ_END	0
#define WRITE_END	1
/*There are two ends to a pipe, the read end, 0, and the write end, 1. 
To write to something we close the read end and utlize the write end, and vice versa for others.
*/


int main(void)
{

	/* The string we are sending over the pipe */	
	char write_msg[BUFFER_SIZE] = "Greetings";

	/* The buffer to hold the string from the pipe. */
	char read_msg[BUFFER_SIZE];
	
	pid_t pid;
	int fd[2];

	/* create the pipe named fd */
	if (pipe(fd) == -1) {
	/* Error checks the pipe, it should return 0 for a success but if it is -1 then it failed*/
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	/* now fork a child process */
	pid = fork();

	if (pid < 0) {
		fprintf(stderr, "Fork failed");
		return 1;
	}

	if (pid > 0) {  /* parent process */
		/* close the unused end of the pipe */
		close(fd[READ_END]);

		/* write to the pipe */
		write(fd[WRITE_END], write_msg, strlen(write_msg)+1); 

		/* strlen("Greetings") returns 9 but our 
		message is really 10 bytes long due to 
		the null terminator. So we would need to add an additional buffer size */

		/* close the write end of the pipe */
		close(fd[WRITE_END]);
	}
	else { /* child process */
		/* close the unused end of the pipe */
		close(fd[WRITE_END]);

		/* read from the pipe */
		read(fd[READ_END], read_msg, BUFFER_SIZE); 

		/* Reads the pipe and writes whatever that is in it to the buffer "read_msg", 
		BUFFER_SIZE in this case simply the size of the message buffer */

		/* Prints out whatever was written to our buffer */
		printf("child read %s\n",read_msg);

		/* close the write end of the pipe */
		close(fd[READ_END]);
	}

	return 0;
}
