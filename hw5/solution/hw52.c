// Chris Fietkiewicz. Finds minimum of Shubert function
// using parallel programming (one parent, one child)

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <string.h>

# define BUFFER_SIZE 25
# define READ_END	0
# define WRITE_END	1

double shubert(double x1, double x2);

int main (){
	double x1, x2, y, my_min = 0, child_min;
	double step = 0.5, x1_start, x1_stop;
	char write_value[BUFFER_SIZE];
	char read_value[BUFFER_SIZE];
	int fd[2];

	/* create the pipe */
	if (pipe(fd) == -1) {
		fprintf(stderr,"Pipe failed");
		return 1;
	}

	pid_t pid = fork();
	if (pid == 0) { // child
		x1_start = -2; x1_stop = 0;
	}
	else { // parent
		x1_start = step; x1_stop = 2;
	}
	// Both processes
	for (x1 = x1_start; x1 <= x1_stop; x1 += step) {
		for (x2 = -2; x2 <= 2; x2 += step) {
		  y = shubert(x1, x2);
		  if (y < my_min)
			my_min = y;
		}
	}

	if (pid == 0) {  /* child */
		close(fd[READ_END]);
		sprintf(write_value, "%.5f", my_min);
		write(fd[WRITE_END], write_value, strlen(write_value)+1); 
		close(fd[WRITE_END]);
	}
	else { /* parent */
		close(fd[WRITE_END]);
		read(fd[READ_END], read_value, BUFFER_SIZE);
		close(fd[READ_END]);
		child_min = atof(read_value);
		if (my_min < child_min)
			printf("min = %.5f\n", my_min);
		else
			printf("min = %.5f\n", child_min);
	}
}

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
