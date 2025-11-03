////////////////////////////////////////////////////////////////////////////////
//
// HKLSock.h
//
// Copyright 2025 HK
// All Rights Reserved.
//
// This software is the confidential and proprietary information of HK
// ("Confidential Information"). You shall not disclose such Confidential
// Information and shall use it only in accordance with the terms of the license
// agreement you entered into with HK.
//
// Description: Header file for declare class HKLSock
//
// Revision History:
//   Date         Version         Name    Description
//   20250825     r1              -       Initial version
//
////////////////////////////////////////////////////////////////////////////////

#ifndef HKLSOCK_H
#define HKLSOCK_H

#include "HKLType.h"
#include <sys/socket.h>		// struct msghdr, struct iovec, socket functions, SOCK_STREAM
#include <arpa/inet.h>		// inet_addr, inet_ntoa
#include <netinet/in.h>		// struct sockaddr_in, AF_INET
#include <netdb.h>			// For gethostbyname()
#include <unistd.h>			// For socket functions

class HKLSock
{
public:
	using TSocketFd = int;	// socket file descriptor type.

	enum SelectFlags
	{
		SELECT_READ = 0x0001,
		SELECT_WRITE = 0x0002,
		SELECT_ERROR = 0x0004,
		SELECT_TIMEOUT = 0x0008
	};
	enum ShutDownFlags
	{
		SHUTDOWN_READ,
		SHUTDOWN_WRITE,
		SHUTDOWN_READWRITE
	};
	
	// default event for sockets
	enum 
	{
		DEFAULT_EVENT = HKLSock::SELECT_READ | HKLSock::SELECT_ERROR
	};

	//* 
	//  Default Constructor for object HKLSock
	//  @return		None
	//  @param		None
	//* 
    HKLSock();

	//* 
	//  Constructor with given socket handle for object HKLSock
	//  @return		None
	//  @param		tSocket - given socket handle
	//* 
	explicit HKLSock(TSocketFd tSocket);

	//* 
	//  Copy constructor (deleted) to avoid copy a object
	//  @return		reference to assigned HKLSock object
	//  @param		None
	//* 
	HKLSock(const HKLSock& oSrc) = delete;

	//* 
	//  Assignment operator (deleted) to avoid copy a object
	//  @return		reference to assigned HKLSock object
	//  @param		None
	//* 
	HKLSock& operator=(const HKLSock& oSrc) = delete;

	//* 
	//  Copy constructor that transfer fd from the source to the new object
	//  @return		reference to assigned HKLSock object
	//  @param		None
	//* 
	HKLSock(HKLSock&& oSrc) noexcept;

	//* 
	//  Assignment operator that transfer fd from the source to the new object
	//  @return		reference to assigned HKLSock object
	//  @param		None
	//* 
	HKLSock& operator=(HKLSock&& oSrc) noexcept;

	//* 
	//  Default Destuctor for object HKLSock, it will
	// 				close the socket if it is already opened.
	//  @return		None
	//  @param		None
	//* 
    virtual ~HKLSock();

	//* 
	//  Close the open socket by the socket Fd
	//  @return		None
	//  @param		None
	//* 
	virtual void Close();

	//* 
	//  Bind a socket to a specific port and address (E.g. "0.0.0.0", 8080)
	//  @return		bool to indicate success / fail
	//  @param		uSocketPort - the port number to bind with socket
	//  @param		sSockAddress - address allow to accept on this socket
	//* 
	virtual bool Bind(UInt16 uSocketPort, const IString& sSockAddress);

	//* 
	//  Bind a socket to a specific port - Calls on OS functions
	//  @return		boolean to indicate success / fail
	//  @param		ptSockAddr - pointer to struct sockaddr, which describe
	//  			the address and port to bind with
	//  @param		iSockAddrLen - the length of struct sockaddr
	//* 
	virtual bool Bind(const struct sockaddr* ptSockAddr, Int32 iSockAddrLen);

	//* 
	//  Create SocketFd and bind a socket Port and IP at the same time
	//  @return		boolean to indicate operation success or fail
	//  @param		uSocketPort - the port number of socket
	//  @param		iSocketType - the type of socket
	//  @param		sSocketAddress - the specify addess of socket accept
	//* 
	virtual bool Create(UInt32 uSocketPort = 0, Int32 iSocketType = SOCK_STREAM,
        const IString& sSocketAddress = IString(""), Int32 iEvent = DEFAULT_EVENT); 

	//* 
	//  Try to establish a connection with specify port and address - Call Connect(sockaddr*, Int32)
	//  @return		boolean to indicate success / fail
	//  @param		sHostAddress - the string of the address, it could be in 
	// 							   dot-format or in host name
	//  @param		uHostPort - the port number want to connect
	//* 
	virtual bool Connect(const IString& sHostAddress, UInt16 uHostPort);
	
	//* 
	//  Try to establish a connection
	//  @return		boolean to indicate success / fail
	//  @param		ptSockAddr - pointer to struct sockaddr which stored the
	// 							 address and port number want to connect
	//  @param		iSockAddrLen - the length of given structure
	//* 
	virtual bool Connect(const struct sockaddr* ptSockAddr, UInt32 iSockAddrLen);

	//* 
	//  To accept connection
	//  @return		boolean to indicate success / fail
	//  @param		iConnectionBacklog - max length the queue of pending
	// 									 connection may grow to.
	//* 
	virtual bool Listen(Int32 iConnectionBacklog=5);

	//* 
	//  Extracts the first connection on the queue of pending connections, 
	//  creates a HKLSock for it.
	//  @return		pointer to a new HKLSock with connection socket
	// 				Caller is responsible to delete the object
	//  @param		oSocket - the socket to return
	//  @param		pClientAddr - pointer to struct sockaddr which store client address
	//  @param		piClientAddrLen - pointer to the length of return structure
	//* 	
	virtual bool Accept(HKLSock& oSocket, 
		struct sockaddr* ptClientAddr = NULL, Int32* piClientAddrLen = NULL);

	//* 
	//  Return the name of peer connected to socket
	//  @return		boolean to indicate success / fail
	//  @param		sPeerAddress - the address name of the connected peer
	//  @param		uPeerPort - the port number of the connected peer	
	//* 
 	bool GetPeerName(IString& sPeerAddress, UInt32& uPeerPort);
	
	//* 
	//  Return the name of peer connected to socket
	//  @return		boolean to indicate success / fail
	//  @param		ptSockAddr - pointer to struct sockaddr which stored
	// 					address and port number of connected peer 
	//  @param		piSockAddrLen - pointer to len given structure. It should
	// 					initial by the length of struct pointed by ptSockAddr.
	//* 
	bool GetPeerName(struct sockaddr* ptSockAddr, Int32* piSockAddrLen);

	//* 
	//  Return the current name of socket
	//  @return		boolean to indicate success / fail
	//  @param		sSocketAddress - return the address name of socket
	//  @param		uSocketPort - return the port number of socket	
	//* 
	bool GetSockName(IString& sSocketAddress, UInt32& uSocketPort);
	
	//* 
	//  Return the current name of socket
	//  @return		boolean to indicate success / fail
	//  @param		ptSockAddr - pointer to structure sockaddr which stored
	// 					address and port of current socket
	//  @param		piSockAddrLen - pointer to the length of ptSockAddr. It 
	// 					should initial by the len of struct point by ptSockAddr
	//* 
	bool GetSockName(struct sockaddr* ptSockAddr, Int32* piSockAddrLen);

	//* 
	//  Return the value of Socket Option
	//  @return		boolean to indicate success / fail
	//  @param		iOptionName - the name of the option to get
	//  @param		pOptionValue - the pointer to value related with Option
	//  @param		iOptionLen - the length of the value pointed by pOptionValue
	// 					it should initial contain the size of buffer pointed to.
	//* 
  bool GetSockOpt(Int32 iOptionName, void* pOptionValue, Int32* piOptionLen, 
		Int32 iLevel = SOL_SOCKET);

	//* 
	//  Set socket options 
	//  @return		boolean to indicate success / fail
	//  @param		iOptionName - the name of the option to set
	//  @param		pOptionValue - pointer to the value related with the option
	//  @param		iOptionLen - the length of data pointed by pOptionValue
	//  @param		iLevel - protocol num of protocol that controls the option
	//* 
	bool SetSockOpt(Int32 iOptionName, const void* pOptionValue, 
		Int32 iOptionLen, Int32 iLevel = SOL_SOCKET);

	//* 
	//  Return the socket handle / descriptor of object
	//  @return		None
	//  @param		tSocket - stored the current socket handle of this object
	//* 
	void GetHandle(TSocketFd& tSocket);

	//* 
	//  Set socket handle / descriptor to object
	//  @return		None
	//  @param		tSocket - the new socket handle;
	//* 
	void SetHandle(TSocketFd tSocket);

    /*bool Create();
    bool Connect(const char* ip, int port);
    bool Send(const char* data, int size);
    int Receive(char* buffer, int size);*/

protected:
	//* 
	//  To Create a socket
	//  @return		if success, return a socket handle / descriptor
	// 						if fail, return -1
	//  @param		type - type of socket, such as SOCK_STREAM 
	//  @param		protocol - type of protocol
	//  @param		family - the family of protocol, such as AF_INET
	//* 
	TSocketFd Socket(Int32 iType=SOCK_STREAM, 
					 Int32 iProtocol=0, 
					 Int32 iFamily=AF_INET);

	// socket descriptor
    TSocketFd m_tSocketFd;

	// struct using by ReceiveMsg
	struct sockaddr_in m_HostAddress;
	struct iovec m_ioVec;
	struct msghdr m_MsgHdr;
	char   m_MsgControl[1024];
};

#endif //HKLSOCK_H
