// Demonstrates how to execute top using execvp. Shows only process for user "abc12".
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
 char *args[4];
 args[0] = "top";
 args[1] = "-u";
 args[2] = "abc12";
 args[3] = 0;
 execvp(args[0], args);
 return 0;
}
