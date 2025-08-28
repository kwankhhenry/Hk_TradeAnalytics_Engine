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

//  Copy constructor that transfers fd from the source to the new object
HKLSock::HKLSock(HKLSock&& oSrc) noexcept
	: m_tSocketFd(oSrc.m_tSocketFd)
{
	oSrc.m_tSocketFd = SOCKET_ERROR;
}

//  Assignment operator that transfers fd from the source to the new object
HKLSock& HKLSock::operator=(HKLSock&& oSrc) noexcept
{
	if(this != &oSrc && m_tSocketFd != SOCKET_ERROR)
	{
		Close(); // Close current fd if open
		m_tSocketFd = oSrc.m_tSocketFd;
		oSrc.m_tSocketFd = SOCKET_ERROR;
	}
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

//------------------------------------------------------------------------------
//	Public interface of Accept, Create, Close, Bind, Connect & Listen

//  Function used to close the open socket
void HKLSock::Close()
{
	if (m_tSocketFd != SOCKET_ERROR)
	{
		close(m_tSocketFd);
		m_tSocketFd = SOCKET_ERROR;
	}
}

//  Function used to bind a socket to a specific port with given Socket Port and Address (E.g. "0.0.0.0", 8080)
bool HKLSock::Bind(UInt16 uSocketPort, const IString& sSockAddress)
{
	struct sockaddr_in tSockAddr;					//	Store target bind address
	memset (&tSockAddr, 0 , sizeof(tSockAddr));		//  Allocate memory for sockaddr_in structure
	UInt32 iResult;									//	return -1 if convert to internet address failed,
													//	otherwise return the Internet address

	tSockAddr.sin_family = AF_INET;
	tSockAddr.sin_port = htons(uSocketPort);
	if (sSockAddress == "") 
	{
		//	 Bind to any of the Ip/interfaces if no address is specified
		 tSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{		
		iResult = inet_addr(sSockAddress.c_str());
		if (iResult == INADDR_NONE)
		{
			return false;	//  Error in Convert to internet address 
		}
		//	Bind with known Ip/interface address.		
		tSockAddr.sin_addr.s_addr = iResult;				
	}
	return HKLSock::Bind((struct sockaddr*)&tSockAddr, sizeof(tSockAddr));
}

//  Function used to bind a socket to a specific port with given Socket Address - Calls on OS functions
bool HKLSock::Bind(const struct sockaddr* ptSockAddr, Int32 iSockAddrLen)
{
	return (SOCKET_ERROR != bind( m_tSocketFd, ptSockAddr, iSockAddrLen));
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