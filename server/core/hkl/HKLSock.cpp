#include "hkl/HKLSock.h"

const HKLSock::TSocketFd SOCKET_ERROR = -1;

//----------------------------------------------------------------------------------------------
//	Public interface of HKLSock Constructor, Copy Constructor, Destructor & operator Overloading 

//  Default Constructor for object HKLSock
HKLSock::HKLSock()
{
	m_tSocketFd = SOCKET_ERROR;
	
	memset(&m_HostAddress, 0, sizeof(struct sockaddr_in));
    m_HostAddress.sin_family = AF_INET;
    m_HostAddress.sin_port = htons(0);
    m_HostAddress.sin_addr.s_addr = INADDR_ANY;
  
	m_ioVec.iov_base = nullptr;
	m_ioVec.iov_len = 0;

	m_MsgHdr.msg_iov = &m_ioVec;
	m_MsgHdr.msg_iovlen = 1;
	m_MsgHdr.msg_name = &m_HostAddress;
	m_MsgHdr.msg_namelen = sizeof(struct sockaddr_in);
	m_MsgHdr.msg_control = m_MsgControl;
	m_MsgHdr.msg_controllen = 1024;
}

//  Constructor with given socket file descriptor type
HKLSock::HKLSock(TSocketFd tSocketFd)
{
	m_tSocketFd = tSocketFd;
}

//  Function used to copy HKLSock
HKLSock& HKLSock::operator=(const HKLSock& oSrc)
{
	m_tSocketFd = oSrc.m_tSocketFd;
	return *this;
}

//  Default Destuctor for object HKLSock
HKLSock::~HKLSock()
{
	if (m_tSocketFd != SOCKET_ERROR)
	{	
		Close();
	}
}

//  Function used to close the open socket
void HKLSock::Close()
{
	if (m_tSocketFd != SOCKET_ERROR)
	{
		close(m_tSocketFd);
		m_tSocketFd = SOCKET_ERROR;
	}
}

//---------------------------------------------------------------------------------------------
//	Public interface of GetPeerName, GetSockName, SetSockOpt, GetSockOpt, GetHandle & SetHandle

//  Function used to return the socket handle / descriptor of object
void HKLSock::GetHandle(TSocketFd& tSocket)
{
	tSocket = m_tSocketFd;
}

//  Function used to set socket handle / descriptor to object
void HKLSock::SetHandle(TSocketFd tSocket)
{
	if (m_tSocketFd != SOCKET_ERROR)
	{
		Close();
	}
	m_tSocketFd = tSocket;	
}