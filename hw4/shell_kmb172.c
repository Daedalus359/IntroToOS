/**
 * Kevin Bradner, kmb172@case.edu
 * Modified from:
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void)
{
	char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    int should_run = 1;

    char line[50];
	
	int i, upper;

	pid_t pid;
		
    while (should_run){
    	//prompt the user for input   
        printf("kmb172_shell>");
        fflush(stdout);

        //store a list of individual command tokens in args[]
		gets(line);
		args[0] = strtok(line, " ");

		//initialize iterator variable for looping through inputs
		i = 0;

		//find the last piece of the input
		while (args[i] != NULL)
			args[++i] = strtok(NULL, " ");

		//check if the fist command command was "exit"
		if (strcmp(args[0], "exit") == 0){
			 printf("exiting\n");
			should_run = 0;
		}else{
			pid = fork();
		}

		if (pid == 0){
			//make sure the child does not loop
			should_run = 0;

			//run the command
			execvp(args[0], args); // Execute the command
		}

		//wait for the child to stop
		if (pid > 0 && should_run){
			wait(NULL);
		}

    }
    
	return 0;
}