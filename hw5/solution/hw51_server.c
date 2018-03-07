// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
// Based on socket example from http://www.linuxhowtos.org/C_C++/socket.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <math.h>

#define PORT_NUMBER 9383

// Helper function for error messages (not required)
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
	// Prepare for socket communication
	int sockfd, newsockfd, portno = PORT_NUMBER;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n; // Number of bytes written/read
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
		error("ERROR on binding");
	printf("Listening for client...\n"); fflush(stdout);
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd < 0) 
		error("ERROR on accept");
	bzero(buffer, sizeof(buffer));

	// Send question to client
	sprintf(buffer, "How many steps does it take for a client to change a light bulb?");
	n = write(newsockfd, buffer, strlen(buffer));
	if (n < 0) error("ERROR reading from socket");

	// Receive answer from client
	bzero(buffer, sizeof(buffer));
	n = read(newsockfd, buffer, sizeof(buffer));
	printf("Server received: %s\n", buffer); fflush(stdout); // Not required

	// Check client's response and send reply
	if (strcmp(buffer, "3") == 0) {
		bzero(buffer, sizeof(buffer));
		sprintf(buffer, "Correct! The 3 steps are: create a socket, connect to it, and send a new bulb.");
		printf("Client was correct.\n"); fflush(stdout);
	} else {
		bzero(buffer, sizeof(buffer));
		sprintf(buffer, "Nope. The answer is 3 steps: create a socket, connect to it, and send a new bulb.");
		printf("Client was NOT correct.\n"); fflush(stdout);
	}
	n = write(newsockfd, buffer, sizeof(buffer));

	// Cleanup
	close(newsockfd);
	close(sockfd);
    return 0; 
}
