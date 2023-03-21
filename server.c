#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<time.h>

#define PORT 8080

int main()
{
	int sockfd, newsockfd, n;
	socklen_t clilen;
	char buff[1024];
	struct sockaddr_in serv_addr, cli_addr;
	struct hostent *server;

	// creating the socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("server socket created...\n");
	
	bzero((char*)&serv_addr, sizeof(serv_addr));
	// socket family
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// binding the socket
	bind(sockfd, (struct  sockaddr*) &serv_addr, sizeof(serv_addr));
	printf("bind successfully...\n");

	// listening to the client
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, (struct sockaddr*) &cli_addr, &clilen);

	bzero(buff, 1024);
	read(newsockfd, buff, 1024);
	printf("Time received from client = %s\n", buff);
	
	//calculate the time difference
	time_t server_time = time(NULL);
	int diff = server_time - atoi(buff);
	printf("Time difference = %d\n", diff);

	bzero(buff, 1024);
	sprintf(buff, "%d", diff);
	write(newsockfd, buff, strlen(buff));

	close(newsockfd);
	close(sockfd);
	
	return 0;



}
