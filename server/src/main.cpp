#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>

using namespace std;

int main()
{
	int sock, connected;
	int portNum = 1500;
	bool isExit = false;
	int bufsize = 1024;
	char send_data[bufsize], recv_data[bufsize];

	struct sockaddr_in server_addr;

	// init socket
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		cout << "Error establishing connection." << endl;
		exit(1);
	}
	else
		cout << "Server Socket connection created..." << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htons(INADDR_ANY); //inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
	server_addr.sin_port = htons(portNum);

	// binding socket
	if(bind(sock, (struct sockaddr*)& server_addr, sizeof(struct sockaddr)) < 0)
	{
		close(sock);
		cout << "Error binding socket..." << endl;
		exit(1);
	}
	else
		cout << "Waiting for clients to connect..." << endl;

	// listening socket
	if(listen(sock, 10) < 0)
	{
		cout << "Can't listen..." << endl;
		return -2;
	}

	// accept client
	struct sockaddr_in client_addr;
	socklen_t size = sizeof(struct sockaddr_in);
	connected = accept(sock, (struct sockaddr*)&client_addr, &size);

	if(connected < 0)
	{
		cout << "Error on accepting..." << endl;
		exit(1);
	}

	strcpy(send_data, "Welcome to my server!");
	send(connected, send_data, bufsize, 0);

	cout << "Connected with client (IP = " 
	     << inet_ntoa(client_addr.sin_addr) 
	     << ", PORT = " 
	     << ntohs(client_addr.sin_port) << ")" << endl;

	do{		
		recv(connected, recv_data, bufsize, 0);
		cout << "Received from Client: " << recv_data << endl;

		if(*recv_data == '#')
			isExit = true;
	}while(!isExit);
		
	cout << "Connection terminated..." << endl;
	cout << "Goodbye..." << endl;
	isExit = false;

	close(sock);
	return 0;
}