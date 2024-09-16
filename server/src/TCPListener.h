#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>     /* For socket */
#include <netinet/in.h>     /* For IP Address */
#include <arpa/inet.h>      /* For ip inet_pton() */
#include <unistd.h>         /* for close() */
#include <sys/select.h>     /* for multiplexing (select) */
#include <thread>           /* for multi-threading */
#include <fstream>          /* for reading files */

#include "../../common/common.h"

#define BUFSIZE 1024

namespace HK{
    class TCPListener{
    public:
        TCPListener() = delete;
        TCPListener(const char* ipAddress, int port, int maxConnect = 50):
            m_ipAddress(ipAddress), 
            m_port(port),
            m_maxConnect(maxConnect),
            m_client_addr((struct sockaddr_in*) malloc(maxConnect * sizeof(struct sockaddr_in))){};
        void init();
        int run();
        void handle_connection(const int& connfd);

        // Event callbacks
        void OnClientConnection(const int& clientfd, struct sockaddr_in client_addr);
        void OnClientDisconnect(const int& connfd);
    private:
        const char* m_ipAddress;             // IP Address server will run on
        int         m_port;                  // Port # to connect to
        int         m_socket;                // Internal FD socket descriptor
        int         m_maxConnect;            // Maximum number of connections allowed

        struct sockaddr_in* m_client_addr;   // Hosting client details (pointer to store multiple clients at run-time)
        int m_client_size;

        fd_set      m_master_fd;             // Master file descriptor set (containing all connected file descriptors)
    };
};