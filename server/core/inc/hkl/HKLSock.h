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

#include "HKLSimpleType.h"
#include <sys/socket.h>		// struct msghdr, struct iovec, socket functions, SOCK_STREAM
#include <netinet/in.h>		// struct sockaddr_in, AF_INET
#include <unistd.h>			// For socket functions

class HKLSock
{
public:
	using TSocketFd = int;	// socket file descriptor type.

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
	//  Assignment operator allow copy a object
	//  @return		reference to assigned HKLSock object
	//  @param		None
	//* 
	HKLSock& operator=(const HKLSock& oSrc);

	//* 
	//  Default Destuctor for object HKLSock, it will
	// 				close the socket if it is already opened.
	//  @return		None
	//  @param		None
	//* 
    virtual ~HKLSock();

	//* 
	//  Close the open socket
	//  @return		None
	//  @param		None
	//* 
	virtual void Close();

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
    void Close();
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
	TSocketFd Socket(Int32 iType=SOCK_STREAM, Int32 iProtocol=0, 
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
