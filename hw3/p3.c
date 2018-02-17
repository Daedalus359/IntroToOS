//Kevin Bradner, kmb172
// based on code by Chris Fietkiewicz.
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For wait()

int main() {
	pid_t pid1;
	pid_t pid2;

	printf("I am the parent process. My pid is %d. My parent's pid is %d\n", getpid(), getppid());

	/* make the 2nd process*/
	pid1 = fork();

	if (pid1 == 0) { /* child process */
		printf("I am the first child process. My pid is %d. My parent's pid is %d\n", getpid(), getppid());
		pid2 = fork();//make the 3rd process
		if (pid2 ==0){
			printf("I am the second child process. My pid is %d. My parent's pid is %d\n", getpid(), getppid());
		}
	}
    return 0;
}
