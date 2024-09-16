#include "TCPListener.h"

void HK::TCPListener::init()
{
    // Create a socket
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(m_socket < 0)
		errorCheck("Error creating socket...");
    else
        std::cout << "Server socket connection created..." << "(socketfd = " << m_socket << ")" << std::endl;

	// Initialize struct of server address
	struct sockaddr_in m_server_addr;
	bzero(&m_server_addr, sizeof(m_server_addr));
	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(m_port);

	// Convert string of IP address to binary equivalent
	// server_addr.sin_addr.s_addr = htons(INADDR_ANY); // if hosted at 0.0.0.0
    if(inet_pton(AF_INET, m_ipAddress, &m_server_addr.sin_addr) <= 0)
		errorCheck("Error establishing IP address...");

    // Binding ip address and port to a socket
	if(bind(m_socket, (struct sockaddr*)& m_server_addr, sizeof(struct sockaddr)) < 0)
	{
		close(m_socket);
		errorCheck("Error binding socket...");
	}
	else
		std::cout << "Server socket is binded at address = " << m_ipAddress << ":" << m_port << std::endl;

	// Listening socket (Default 10 connections)
	if(listen(m_socket, m_maxConnect) < 0)
		errorCheck("Error listening...");
	else
		std::cout << "Waiting for clients to connect..." << std::endl;

	// Clear all bits of master file descriptor
	FD_ZERO(&m_master_fd);

	// Add listening socket to master file descriptor
	FD_SET(m_socket, &m_master_fd);
}

int HK::TCPListener::run()
{
	// Wait to accept connection and return new connection socket fd
	while(true)
	{
		struct sockaddr_in client_addr;
		socklen_t size = sizeof(struct sockaddr_in);
		int connfd = accept(m_socket, (struct sockaddr*)& client_addr, &size);

		if(connfd < 0)
			errorCheck("Error on accepting...");

		std::cout << "Connected with client (IP = " 
			<< inet_ntoa(client_addr.sin_addr) 
			<< ", PORT = " 
			<< ntohs(client_addr.sin_port) 
			<< ", clientfd = " << connfd << ")" << std::endl;

		std::thread t(&HK::TCPListener::handle_connection, this, connfd);
		//OnClientConnection(connfd, client_addr);
	}

	std::cout << "Server connection terminated..." << std::endl;
	std::cout << "Goodbye..." << std::endl;

	close(m_socket);
    return 0;
}

void HK::TCPListener::OnClientConnection(const int& clientfd, struct sockaddr_in client_addr)
{
	/*char send_data[BUFSIZE];

	strcpy(send_data, "Welcome to my server!\n");
	size_t str_size = strlen(send_data);
	send(clientfd, send_data, str_size, 0);*/

	// Action to perform on client connection
	handle_connection(clientfd);
}

void HK::TCPListener::OnClientDisconnect(const int& clientfd)
{
	std::cout << "Client (IP = "
		<< inet_ntoa(m_client_addr[0].sin_addr) 
		<< ", PORT = " 
		<< ntohs(m_client_addr[0].sin_port) << ") is disconnected." << std::endl;
	
	close(clientfd);
}

void HK::TCPListener::handle_connection(const int& connfd)
{
	// Receive data buffer
	char data_buffer[BUFSIZE];
	size_t bytes_read;

	// Receive and remove null terminated character at the end 
	bytes_read = recv(connfd, data_buffer, BUFSIZE, 0);
	data_buffer[bytes_read-1] = 0;
	std::cout << "Received from Client: (" << bytes_read << " bytes) " << std::endl;

	if(*data_buffer == '#')
	{
		std::cout << "Client (fd=" << connfd << ") disconnected." << std::endl;
		OnClientDisconnect(connfd);
		return;
	}

	//std::cout << "Attempting to open file: " << data_buffer << std::endl;
	std::ifstream file(data_buffer, std::ios_base::in);
	if (!file.is_open()) {
		std::cout << "Error opening file\n";
		return;
	}

	// Read size of the file
	file.seekg (0, file.end);
	int file_size = file.tellg();
	file.seekg (0, file.beg);  // Reset file position to beginning
	std::cout << "Received request for file (" << file_size << " bytes) from client...\n";

	// Output file contents
	while(file.peek()!=EOF){
		memset(data_buffer, 0, BUFSIZE);
		file.read(data_buffer, BUFSIZE);
		std::cout << "Sending contents (" << file.gcount() << " bytes) to client...\n";
		send(connfd, data_buffer, file.gcount(), 0);
	}
	std::cout << std::endl;
	file.close();

	/*FILE *fp = fopen(data_buffer, "r");
	if(fp == NULL) {
		printf("ERROR(open: %s\n)", data_buffer);
		return;
	}

	while((bytes_read = fread(data_buffer, 1, BUFSIZE, fp)) > 0)
	{
		printf("Sending contents (%zu bytes) to client\n", bytes_read);
		write(connfd, data_buffer, bytes_read);
	}
	fclose(fp);*/

	// Disconnect after sending client contents
	close(connfd);
}