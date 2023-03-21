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
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buff[1024];
	
	// creating the socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket created...\n");

	server = gethostbyname("localhost");
	if (server == NULL)
	{
		perror("ERROR!\n");
		exit(1);
	}

	bzero((char*)&serv_addr, sizeof(serv_addr));
	// socket family
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	// connecting the socket
	connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
	printf("connected to server successfully...\n");

	time_t cli_time = time(NULL);
	bzero(buff, 1024);
	sprintf(buff, "%ld", cli_time);

	write(sockfd, buff, strlen(buff));

	// receive
	bzero(buff, 1024);
	read(sockfd,buff, 1024);

	// calculate
	int diff = atoi(buff);
	time_t adj_time = cli_time + diff;
	printf("Local time = %s\n", ctime(&cli_time));
	printf("Adjusted time = %s\n", ctime(&adj_time));

	close(sockfd);
	
	return 0;

}
