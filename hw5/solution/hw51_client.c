// Chris Fietkiewicz (chris.fietkiewicz@case.edu)
// Based on socket example from http://www.linuxhowtos.org/C_C++/socket.htm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <math.h>

#define PORT_NUMBER 9383

// Helper function for error messages (not required)
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
	// Prepare for socket communication
    int sockfd, portno = PORT_NUMBER, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[256];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname("127.0.0.1");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

	// Receive question from server
	n = read(sockfd, buffer, sizeof(buffer));
	if (n < 0) error("ERROR reading from socket");
	printf("Client received:\n%s\n", buffer);

	// Get user's answer and send to server
	bzero(buffer, sizeof(buffer));
	gets(buffer);
	n = write(sockfd, buffer, strlen(buffer));
	if (n < 0) error("ERROR writing to socket");

	// Receive answer from server
	n = read(sockfd, buffer, sizeof(buffer));
	if (n < 0) error("ERROR reading from socket");
	printf("Client received: %s\n", buffer);

	// Cleanup
    close(sockfd);
    return 0;
}
