#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>

#include "../../common/common.h"

#define MAX_BUFFER_SIZE 1024

int main()
{
	int sockfd;
	int portNum = 5000; // note the server and clients IP are the same
	bool isExit = false;
	
	char send_data[MAX_BUFFER_SIZE], recv_data[MAX_BUFFER_SIZE];

	//init socket
	struct hostent *ip;
	ip = gethostbyname("127.0.0.1");

	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sockfd < 0)
		errorCheck("Error creating socket...");
	else
		std::cout << "Client Socket created" << std::endl;

	struct sockaddr_in server_addr;
	bzero(&server_addr, sizeof(sockaddr_in));  // Clear Structure memory
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);
	server_addr.sin_addr = *((struct in_addr *) ip->h_addr);

	// Connecting socket server
	if(connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
		errorCheck("Failed to connect server...");
	else
		std::cout << "Connection successful" << std::endl;

	std::cout << "Connected to server (IP= " 
			<< inet_ntoa(server_addr.sin_addr)
			<< ", PORT= " 
			<< ntohs(server_addr.sin_port) << ")" << std::endl;

	/*recv(sockfd, recv_data, bufsize, 0);
	
	std::cout << "Reponse from server: " << recv_data << std::endl;*/
	std::cout << "Enter # to end the connection" << std::endl;

	do{
		std::cout << "Client: ";
		std::cin.getline(send_data, MAX_BUFFER_SIZE);

		if (*send_data == '#')
			isExit = true;

		send(sockfd, send_data, std::cin.gcount(), 0);

	}while(!isExit);

	std::cout << "Client connection terminated..." << std::endl;
	std::cout << "Goodbye" << std::endl;

	close(sockfd);
	
	return 0;
}