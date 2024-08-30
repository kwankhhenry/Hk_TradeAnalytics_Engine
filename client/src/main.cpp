#include<iostream>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netdb.h>

using namespace std;

int main()
{
	int sock;
	int portNum = 1500; // note the server and clients IP are the same
	bool isExit = false;
	int bufsize = 1024;
	
	char send_data[bufsize], recv_data[bufsize];
	struct hostent *ip;
	struct sockaddr_in server_addr;

	//init socket
	ip = gethostbyname("127.0.0.1");

	bzero(&server_addr, sizeof(sockaddr_in));  // Clear Structure memory
	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0)
	{
		cout << "Error creating socket..." << endl;
		exit(1);
	}
	else
		cout << "Client Socket created" << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(portNum);
	server_addr.sin_addr = *((struct in_addr *) ip->h_addr);

	// connecting socket server

	if(connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
	{
		cout << "Failed to connect server..." << endl;
		exit(1);
	}
	else
		cout << "Connection successful" << endl;

	cout << "Connected to server (IP= " 
	     << inet_ntoa(server_addr.sin_addr)
	     << ", PORT= " 
	     << ntohs(server_addr.sin_port) << "): " 
	     << recv_data << endl;

	recv(sock, recv_data, bufsize, 0);
	
	cout << "Reponse from server: " << recv_data << endl;
	cout << "Enter # to end the connection" << endl;

	do{
		cout << "Client: ";
		cin.getline(send_data,bufsize);

		if (*send_data == '#')
			isExit = true;
		
		send(sock, send_data, bufsize, 0);

	}while(!isExit);

	cout << "Connection terminated..." << endl;
	cout << "Goodbye" << endl;

	close(sock);
	
	return 0;
}