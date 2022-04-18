#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>




int main()
{
	int clientSocket, ret;
	struct sockaddr_in cliAddr, servaddr;
	char buffer[1024];
	clientSocket = socket(AF_INET,SOCK_STREAM, 0);
	if (clientSocket < 0) {
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Client Socket is created.\n");
	memset(&cliAddr, '\0', sizeof(cliAddr));
	memset(buffer, '\0', sizeof(buffer));

	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(4444);
	servaddr.sin_addr.s_addr= inet_addr("127.0.0.1");

	ret = connect(clientSocket,(struct sockaddr*)&servaddr,sizeof(servaddr));
	if (ret < 0) {
		printf("Error in connection.\n");
		exit(1);
	}
	printf("Connected to Server.\n");
	while (1) {
		if (recv(clientSocket, buffer, 1024, 0)
			< 0) {
			printf("Error in receiving data.\n");
		}
		else {
			printf("Server: %s\n", buffer);
			bzero(buffer, sizeof(buffer));
		}
	}

	return 0;
}

