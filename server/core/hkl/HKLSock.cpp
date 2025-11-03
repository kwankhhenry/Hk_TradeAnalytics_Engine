#include "hkl/HKLSock.h"

const HKLSock::TSocketFd SOCKET_ERROR = -1;

//----------------------------------------------------------------------------------------------
//	Public interface of HKLSock Constructor, Copy Constructor, Destructor & operator Overloading 

//  Default Constructor for object HKLSock
HKLSock::HKLSock()
{
	m_tSocketFd = SOCKET_ERROR;

	memset(&m_HostAddress, 0, sizeof(struct sockaddr_in));	// memset to initialize and zeroed out garbage values
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
	if(this != &oSrc)
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
//	Protected interface to create socket used by Create() method only

//  Protected function used to create a socket, only called by Create();
HKLSock::TSocketFd HKLSock::Socket(Int32 iType, Int32 iProtocol, 
	Int32 iFamily)
{
	return socket(iFamily, iType, iProtocol);
}

//------------------------------------------------------------------------------
//	Public interface of Accept, Create, Close, Bind, Connect & Listen

//  Function used to close the open socket by the socket Fd
void HKLSock::Close()
{
	if (m_tSocketFd != SOCKET_ERROR)
	{
		close(m_tSocketFd);
		m_tSocketFd = SOCKET_ERROR;
	}
}

//  Function used to bind a socket to a specific port with given Socket Port and Address (E.g. 8080, "0.0.0.0")
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

//  Function used to create SocketFd and bind a socket Port and IP at the same time
bool HKLSock::Create(UInt32 uSocketPort, Int32 iSocketType, 
	const IString& sSocketAddress, Int32 iEvent)
{
	//	Socket only can create once
	if (m_tSocketFd != SOCKET_ERROR)
		return false;

	m_tSocketFd = Socket(iSocketType); 	// Obtain a socket file descriptor

	// Only return true if create and bind socket successfully with m_tSocketFd
	if (m_tSocketFd != SOCKET_ERROR && Bind(uSocketPort, sSocketAddress))
	{
		return true;
	}
	Close();
	return false;
}

//  Function used to establish a connection with specify port and address - Call Connect(sockaddr*, Int32)
bool HKLSock::Connect(const IString& sHostAddress, UInt16 uHostPort)
{
	struct sockaddr_in tSockAddr;				//	Store target address to be connected
	memset (&tSockAddr, 0 , sizeof(tSockAddr));
	struct hostent* ptHost;							//	Returns a structure of type hostent for the given host name

	//	converts IPv4 dotted decimal notation into a proper address
	tSockAddr.sin_family = AF_INET;
	tSockAddr.sin_addr.s_addr = inet_addr(sHostAddress.c_str());

	//	Get an IP address from hostname if sHostAddress is not a IPv4 dotted decimal notation
	if (tSockAddr.sin_addr.s_addr == SOCKET_ERROR)
	{
		ptHost = gethostbyname(sHostAddress.c_str());
		if (ptHost != NULL)
		{
			tSockAddr.sin_addr.s_addr = 
				((struct in_addr*)ptHost->h_addr)->s_addr;	//	h_addr_list[0]
		}
		else
		{
			//  Wrong Host Address 
			return false;
		}
	}

	tSockAddr.sin_port = htons(uHostPort);
	return HKLSock::Connect((struct sockaddr*)&tSockAddr, sizeof(tSockAddr));
}

//  Function used to establish a connection
bool HKLSock::Connect(const struct sockaddr* ptSockAddr, UInt32 iSockAddrLen)
{
	return (SOCKET_ERROR != connect(m_tSocketFd, ptSockAddr, iSockAddrLen));
}

//  Function used to accept connection
bool HKLSock::Listen(Int32 iConnectionBacklog) 
{
	return (listen(m_tSocketFd, iConnectionBacklog) != SOCKET_ERROR);
}

//  Function used to extract the connection request
bool HKLSock::Accept(HKLSock& oSocket, struct sockaddr* ptClientAddr, Int32* piClientAddrLen)
{
	struct sockaddr tTmpClientAddr;			//	Use when the ptClientAddr is NULL
	struct sockaddr* ptTmpClientAddr;		//	Pointer for tTmpClientAddr
	Int32 iTmpClientAddrLen;				//	Use when the piClientAddrLen is NULL
	Int32* piTmpClientAddrLen;				//	Pointer for iTmpClientAddrLen
	Int32 iFd;								//	value = -1 if failed to accept connection request, otherwise return the non-negative file descriptor of the accepted socket

	// Ensure the input sockaddr* is not null in order to retrieve back the connecting client address
	// if it is NULL, use tTmpClientAddr instead
	ptTmpClientAddr = (ptClientAddr == NULL) ? (&tTmpClientAddr) : (ptClientAddr);
	
	// Ensure the input piClientAddrLen* is not null in order to retrieve back the connecting client address length
	// if it is NULL, use iTmpClientAddrLen instead
	if (piClientAddrLen == NULL)
	{
		iTmpClientAddrLen = sizeof(tTmpClientAddr);
		piTmpClientAddrLen = &iTmpClientAddrLen;
	}
	else
	{
		piTmpClientAddrLen = piClientAddrLen;
	}
	
	iFd = accept(m_tSocketFd, ptTmpClientAddr, (socklen_t*)piTmpClientAddrLen);
	if (iFd == SOCKET_ERROR)
	{
		return false;
	}
		
	oSocket.SetHandle(iFd);
	return true;
}

//---------------------------------------------------------------------------------------------
//	Public interface of GetPeerName, GetSockName, SetSockOpt, GetSockOpt, GetHandle & SetHandle

//  Function used to return the name of peer connected to socket
bool HKLSock::GetPeerName(IString& sPeerAddress, UInt32& uPeerPort)
{
	struct sockaddr_in tSockAddr;			//	use for store Peer name
	memset (&tSockAddr, 0 , sizeof(tSockAddr));
	int iSockAddrLen;									//	length of socket address
	
	iSockAddrLen = sizeof(tSockAddr);
	if (GetPeerName((struct sockaddr*)&tSockAddr, &iSockAddrLen))
	{
		sPeerAddress = inet_ntoa(tSockAddr.sin_addr);
		uPeerPort = ntohs(tSockAddr.sin_port);
		return true;
	}
	return false;
}

//  Function used to return the name of peer connected to socket
bool HKLSock::GetPeerName(struct sockaddr* ptSockAddr, Int32* piSockAddrLen)
{
	//	getpeername return -1 if fail to get peer name, otherwise return 0
	return (SOCKET_ERROR != getpeername(m_tSocketFd, ptSockAddr, (socklen_t*)piSockAddrLen));
}

//  Function used to return the current name of socket
bool HKLSock::GetSockName(IString& sSocketAddress, UInt32& uSocketPort)
{
	struct sockaddr_in tSockAddr;			//	use for store Sock name
	memset (&tSockAddr, 0 , sizeof(tSockAddr));
	Int32 iSockAddrLen;								//	length of socket address
	
	iSockAddrLen = sizeof(tSockAddr);
	if (GetSockName((struct sockaddr*)&tSockAddr, &iSockAddrLen))
	{
		sSocketAddress = inet_ntoa(tSockAddr.sin_addr);
		uSocketPort = ntohs(tSockAddr.sin_port);
		return true;
	}	
	return false;
}

//  Function used to return the current name of socket
bool HKLSock::GetSockName(struct sockaddr* ptSockAddr, Int32* piSockAddrLen)
{
	//	getsockname return -1 if fail to get peer name, otherwise return 0
	return (SOCKET_ERROR != getsockname(m_tSocketFd, ptSockAddr, (socklen_t*)piSockAddrLen));
}

//  Function used to return the value of Socket Option
bool HKLSock::GetSockOpt(Int32 iOptionName, void* pOptionValue, 
	Int32* piOptionLen, Int32 iLevel)
{
	return (SOCKET_ERROR != getsockopt(m_tSocketFd, iLevel, iOptionName,
		pOptionValue, (socklen_t*)piOptionLen));
}

//  Function used to set socket options 
bool HKLSock::SetSockOpt(Int32 iOptionName, const void* pOptionValue,
	Int32 iOptionLen, Int32 iLevel)
{
	return (SOCKET_ERROR != setsockopt(m_tSocketFd, iLevel, iOptionName,
			 pOptionValue, iOptionLen));
}

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