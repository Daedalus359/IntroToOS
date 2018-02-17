//Kevin Bradner, kmb172
//based on fork0.c by Chris Fietkiewicz
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> // For pid_t
#include <sys/wait.h>  // For wait()

int main() {
	pid_t exitPID;
	pid_t pid1;
	pid_t pid2;

	printf("I am the original parent process. My pid is %d. My parent's pid is %d\n", getpid(), getppid());

	/* fork a child process */
	pid1 = fork();

	if (pid1 == 0) { /* child process */
		printf("I am the first child process. My pid is %d. My parent's pid is %d\n", getpid(), getppid());
		sleep(1);
	}
	else { /* parent process */

		pid2 = fork(); //create the second child (in the else block so only the parent does this)
		if(pid2==0){
			printf("I am the second child process. My pid is %d. My parent's pid is %d\n", getpid(), getppid());
			sleep(1);
		}

		else{//parent process
			exitPID = wait(NULL); /* parent will wait for a child to complete */
			printf("Child with pid = %d has exited.\n",exitPID);
			exitPID = wait(NULL); /* parent will wait for another child to complete */
			printf("Child with pid = %d has exited.\n",exitPID);
		}
	}

    return 0;
}