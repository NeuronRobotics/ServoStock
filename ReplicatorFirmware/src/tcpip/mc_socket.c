/*********************************************************************
 *
 *                  Socket definitions TCP/IP Stack
 *
 *********************************************************************
 * FileName:        mc_socket.c
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its dsPIC30F and PICmicro® Microcontroller is intended 
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip's dsPIC30F and PICmicro Microcontroller products. 
 * The software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * This files includes code under copyright (c) 1982-1986 Regents 
 * of the University of California.  All rights reserved.  The following license
 * agreements specifies the terms and conditions of redistribution of such code.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software must display
 * the following acknowledgement: “This product includes software developed by 
 * the University of California, Berkeley and its contributors.”
 * 4. Neither the name of the University nor the names of its contributors may be 
 * used to endorse or promote products derived from this software without specific
 * prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS”
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE 
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ********************************************************************/
#include <string.h>

#include "_tcpip_common.h"

/*********************************
 *  local prototypes
 *********************************/
static SOCKET	_socketCreate( int af, int type, int protocol, SOCK_FLAGS extraFlags );


/*********************************
 *  local data
 *********************************/
static int		lastSktCreateIx=0;		// last socket create index
static WORD		gAutoPortNumber = 1024;

/*********************************
 *  global data
 *********************************/
struct MCSocket*	SocketArray=0;

/*********************************************************************
 * Function:        void SocketInitialize( SOCKET s )
 *
 * PreCondition:    Must empty the RxMsgQueue before calling this function
 * Input:			s - Socket identifier
 * Output:          None
 * Side Effects:    None
 * Overview:        Initialize the socket structure to a known initial value
 * Note:
 ********************************************************************/
void SocketInitialize( SOCKET s )
{
	struct MCSocket		*pSocket;
	
	pSocket = (struct MCSocket *)&SocketArray[s];
	
	pSocket->SocketType 		= SOCK_DGRAM;
	pSocket->smState 			= SKT_CLOSED;
	
	pSocket->localPort 		= INVALID_TCP_PORT;
	pSocket->localIP			= IP_ADDR_ANY; // = 0

	pSocket->remotePort		= INVALID_TCP_PORT;
	pSocket->remoteIP			= IP_ADDR_ANY; // = 0

	pSocket->ActiveRxSrcIP	= IP_ADDR_ANY;
    pSocket->ActiveRxSrcPort	= INVALID_TCP_PORT;

	pSocket->DataByteIndex 	= 0;  // Rx Data Index
	pSocket->TxDataIndex 		= 0;  // Tx Data Index
	pSocket->TxBfrSize		= TCP_DEFAULT_TX_BFR_SZ;
	pSocket->RxBfrSize		= TCP_DEFAULT_RX_BFR_SZ;
	pSocket->pRxActivePacket  = NULL;
	pSocket->pTxActivePacket  = NULL;
	pSocket->sockFlags = TCP_FIRST_SEND;

    pSocket->RetryCount= pSocket->KeepAliveRetrys = 0;
    pSocket->startTick = pSocket->KeepAliveTick = SystemTickGet();
    pSocket->backlog			= 5;
    pSocket->pParentSocket	= NULL;
    pSocket->SocketID			= s;

	Que_Init( &pSocket->RxMsgQueue );
	Que_Init( &pSocket->CnxnQueue );
	
    pSocket->pTCPListHead		= NULL;
    pSocket->pTCPListTail		= NULL;
    pSocket->AckListCount		= 0;
    pSocket->TCPAppClosed 	= 0;

}

/*********************************************************************
 * Function:        int SocketLayerInit(void)
 *
 * PreCondition:    None
 * Input:			None
 * Output:          TRUE if success, FALSE otherwise
 * Side Effects:    None
 * Overview:        Initialize the entire socket structure array
 * Note:
 ********************************************************************/
int SocketLayerInit(void)
{

    SocketArray=(struct MCSocket*)calloc(_StackSockets, sizeof(struct MCSocket));

    if(SocketArray)
    {
        int s;
        for ( s = 0; s < _StackSockets; s++ )
        {
            SocketInitialize( s );
        }
    }
    lastSktCreateIx=0;

    return SocketArray!=0;
}

/*********************************************************************
 * Function:        void SocketLayerClose(void)
 *
 * PreCondition:    None
 * Input:			None
 * Output:          None
 * Side Effects:    None
 * Overview:        Releases the allocated resources
 * Note:
 ********************************************************************/
void SocketLayerClose(void)
{
    if(SocketArray)
    {
        free(SocketArray);
        SocketArray=0;
    }   
}



/*********************************************************************
 * Function:        SOCKET socket( int af, int type, int protocol )
 *
 * PreCondition:    None
 * Input:			af - address family - AF_INET
 *					type - socket type SOCK_DGRAM or SOCK_STREAM
 *					protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP
 * Output:          New socket descriptor.
 * Side Effects:    None
 * Overview:        This function creates a new socket
 * Note:
 ********************************************************************/
SOCKET socket( int af, int type, int protocol )
{
	return _socketCreate(af, type, protocol, 0);	
}


/*********************************************************************
 * Function:        SOCKET _socketCreate( int af, int type, int protocol, SOCK_FLAGS extraFlags )
 *
 * PreCondition:    None
 * Input:           af - address family - AF_INET
 *                  type - socket type SOCK_DGRAM or SOCK_STREAM
 *                  protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP
 * Output:          New socket descriptor or an error.
 * Side Effects:    None
 * Overview:        This function creates a new socket
 * Note:
 ********************************************************************/
static SOCKET _socketCreate( int af, int type, int protocol, SOCK_FLAGS extraFlags )
{
    struct MCSocket	*socket, *pS;
    int			sIx;

	if( af != AF_INET || (type == SOCK_DGRAM && protocol != IPPROTO_UDP) || (type == SOCK_STREAM && protocol != IPPROTO_TCP) )
	{
		return SOCKET_ERROR;
	}

	socket=0;
	for ( sIx = lastSktCreateIx, pS=SocketArray+lastSktCreateIx; sIx < _StackSockets; sIx++, pS++ )
	{
		if( pS->smState == SKT_CLOSED )
		{	// available socket
			socket=pS;
			break;
		}
	}

	if(!socket)
	{
		for ( sIx = 0, pS=SocketArray; sIx < lastSktCreateIx; sIx++, pS++ )
		{
			if( pS->smState == SKT_CLOSED )
			{	// available socket
				socket=pS;
				break;
			}
		}
	}
	

	if(socket)
	{
		socket->smState = SKT_CREATED;
		socket->SocketType = type;
		socket->sockFlags|=extraFlags;

		lastSktCreateIx=sIx+1;
		if(lastSktCreateIx==_StackSockets)
		{
			lastSktCreateIx=0;
		}
			
		return sIx;
	}

	return SOCKET_ERROR;
}



/*********************************************************************
 * Function:        int setsockopt(  SOCKET s, int level, int optname, char * optval, int optlen )
 *
 * PreCondition:    None
 * 
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  level   - must be SOL_SOCKET
 *                  optname - option to configure. The possible values are:
 *                            SO_SNDBUF   configures the send buffer size to use with 
 *                                        send api for tcp sockets.
 *                            TCP_NODELAY enable or disable the Nagle algorithm for the 
 *                                        socket.  By default the Nagle algorithm is enabled.  
 *                                        To turn it off, use a non-zero value for the optval data.
 *                            SO_RCVBUF   configures the receive buffer size for a socket.
 *                                        For a stream socket it affects directly the advertised window size.
 *                                        The receive buffer is shared in common by all the sockets from the common heap.
 *                                        No effect for a datagram socket.
 *                  optval  - pointer to the option data.
 *                  optlen  - length of option data
 *
 * Output:          0 on success, SOCKET_ERROR otherwise.
 * 
 * Side Effects:    None
 * 
 * Overview:        This function sets the socket options.
 *
 * Note:
 ********************************************************************/
int setsockopt( SOCKET s, int level, int optname,char * optval, int optlen )
{
	struct MCSocket *pSock;

	if( s >= _StackSockets )
		return SOCKET_ERROR;

	pSock = &SocketArray[s];
	
	if( level != SOL_SOCKET || optlen < sizeof(int) )
		return SOCKET_ERROR;
		
	switch( optname )
	{
	//////////////////////
	case SO_SNDBUF:
		pSock->TxBfrSize = *(int*)optval;
		return 0;
		
	//////////////////////
	case TCP_NODELAY:
		if( *optval )
			pSock->sockFlags|= TCP_NO_DELAY;
		else
			pSock->sockFlags&= ~TCP_NO_DELAY;
			
		return 0;

    case SO_RCVBUF:
        pSock->RxBfrSize=*(int*)optval;
        return 0;

    default:
        break;

	}
	return SOCKET_ERROR;
}


/*********************************************************************
 * Function:        int listen( SOCKET s, int backlog )
 *
 * PreCondition:    None
 * Input:			s - Socket identifier
 *					backlog - maximum number of connection requests that can be queued
 * Output:          returns 0 on success, else return SOCKET_ERROR on error. 
 * Side Effects:    None
 * Overview:        The listen function sets the specified socket in a listen mode.  
 *					Calling the listen function indicates that the application is ready to 
 *					accept connection requests arriving at a socket of type SOCK_STREAM. 
 *					The connection request is queued (if possible) until accepted with an 
 *					accept function. The backlog parameter defines the maximum number of 
 *					pending connections that may be queued.
 * Note:
 ********************************************************************/
int listen( SOCKET s, int backlog )
{
	struct MCSocket *ps;

	if( s >= _StackSockets )
		return SOCKET_ERROR;

	ps = &SocketArray[s];

	if ( ps->smState != SKT_BOUND || ps->SocketType != SOCK_STREAM )
		return SOCKET_ERROR;

	// put this socket in listen mode
	ps->smState             = TCP_LISTEN;
	ps->backlog				= backlog;
	return 0;
}


/*********************************************************************
 * Function:        SOCKET accept( SOCKET s, struct sockaddr * addr, int * addrlen )
 *
 * PreCondition:    None
 * Input:			s  	    Socket descriptor returned from a previous call to socket.  
 *							must be bound to a local name and in listening mode.
 *					name    pointer to the the sockaddr structure that will receive 
 *							the connecting node IP address and port number.
 *					namelen A value-result parameter and should initially contain 
 *							the amount of space pointed to by name; on return it contains 
 *							the actual length (in bytes) of the name returned. 
 * Output:          If the accept() function succeeds, it returns a non-negative integer 
 *					that is a descriptor for the accepted socket. Otherwise, the value 
 *					SOCKET_ERROR is returned. 
 * Side Effects:    None
 * Overview:        The accept function is used to accept a connection request queued 
 *					for a listening socket.  If a connection request is pending, accept 
 *					removes the request from the queue, and a new socket is created for 
 *					the connection. The original listening socket remains open and 
 *					continues to queue new connection requests.  The socket s must be 
 *					a SOCK_STREAM type socket.
 * Note:
 ********************************************************************/
SOCKET accept( SOCKET s,
    			struct sockaddr * addr,
    			int * addrlen )
{
	struct MCSocket *pListenSock;

	if( s >= _StackSockets )
		return SOCKET_ERROR;

	pListenSock = &SocketArray[s]; /* Get the pointer to listening socket */

	if ( pListenSock->smState != TCP_LISTEN )
		return SOCKET_ERROR;

	return TCPAccept( pListenSock, addr, addrlen );
}

/*********************************************************************
 * Function:        
 *
 * PreCondition:    
 * Input:			
 * Output:          
 * Side Effects:    None
 * Overview:
 * Note:
 ********************************************************************/
static BOOL skPortInUse( int Proto, int lport )
{
    struct MCSocket *socket = SocketArray;
    int s;

    for ( s = 0; s < _StackSockets; s++,socket++ )
    {
		if( socket->smState > SKT_CREATED ) //socket is bound
		{
			if( socket->SocketType == Proto && socket->localPort == lport )
				return TRUE;  //port number is in use
		}
	}
	return FALSE;
}	

/*********************************************************************
 * Function:        int bind( SOCKET s, const struct sockaddr * name, int namelen )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 *					name - pointer to the the sockaddr structure containing the 
 *							local address of the socket.
 *					namelen - length of the sockaddr structure.
 * Output:          If bind is successful, a value of 0 is returned. A return value 
 *					of SOCKET_ERROR indicates an error.
 * Side Effects:    None
 * Overview:        The bind function assigns a name to an unnamed socket.  The name 
 *					represents the local address of the communication endpoint. 
 *					For sockets of type SOCK_STREAM, the name of the remote endpoint 
 *					is assigned when a connect or accept function is executed.
 * Note:
 ********************************************************************/
int bind( SOCKET s, const struct sockaddr * name, int namelen )
{
    struct MCSocket *socket;
	struct sockaddr_in *local_addr;
	int lPort;
		
	if( s >= _StackSockets )
		return SOCKET_ERROR;

	socket = &SocketArray[s];

	if( socket->smState != SKT_CREATED ) //only work with recently created socket
		return SOCKET_ERROR;

	if( namelen < sizeof(struct sockaddr_in) )
		return SOCKET_ERROR;

	local_addr = (struct sockaddr_in *)name;

	lPort = local_addr->sin_port;
	if( lPort == 0 ) //pick a port
	{
		while(1)
		{
			lPort = gAutoPortNumber++;
			if( gAutoPortNumber == 5000 ) //then reset the port numbers
				gAutoPortNumber = 1024;
				
			if( !skPortInUse( socket->SocketType, lPort ) )
				break;
		}	
	}
	else if( skPortInUse( socket->SocketType, lPort ) )
		return SOCKET_ERROR;
	

	socket->localPort 	= lPort;
	socket->localIP 	= local_addr->sin_addr.S_un.S_addr;
	socket->smState 	= SKT_BOUND;
	return 0; //success
}

/*********************************************************************
 * Function:        int connect( SOCKET s, struct sockaddr * name, int namelen )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 *					name - pointer to the the sockaddr structure containing the 
 *							local address of the socket.
 *					namelen - length of the sockaddr structure.
 * Output:          If the connect() function succeeds, it returns 0. Otherwise, 
 *					the value SOCKET_ERROR is returned to indicate an error condition.
 *					For stream based socket, if the connection is not established yet, 
 *					connect returns SOCKET_CNXN_IN_PROGRESS.
 * Side Effects:    None
 * Overview:        The connect function assigns the address of the peer communications
 *					endpoint.  For stream sockets,  connection is established between 
 *					the endpoints. For datagram sockets, an address filter is established 
 *					between the endpoints until changed with another connect() function.
 * Note:
 ********************************************************************/
int connect( SOCKET s, struct sockaddr * name, int namelen )
{
	struct MCSocket *pSock;
	struct sockaddr_in *addr;
	DWORD remoteIP;
	WORD remotePort;

	if( s >= _StackSockets )
		return SOCKET_ERROR;

	pSock = &SocketArray[s];

	if( pSock->smState < SKT_BOUND ) //only work with sockets bound to a local ip & port
		return SOCKET_ERROR;

	if( namelen < sizeof(struct sockaddr_in) )
		return SOCKET_ERROR;

	addr = (struct sockaddr_in *)name;

	remotePort 	= addr->sin_port;		
	remoteIP 	= addr->sin_addr.S_un.S_addr;
	
	if( remoteIP == 0 || remotePort == 0 ) 
		return SOCKET_ERROR;
		
	if( pSock->SocketType == SOCK_STREAM )
	{
 		if( pSock->smState >= TCP_EST )
 			return 0; // already established
		
		if( pSock->smState == TCP_SYN_SENT )
			return SOCKET_CNXN_IN_PROGRESS;
		
		if( pSock->smState == SKT_BOUND )
		{
		    pSock->remotePort = remotePort;
			pSock->remoteIP = remoteIP;		
			TCPInitiateCnxn(pSock);
			return SOCKET_CNXN_IN_PROGRESS;
		}
		else
			return SOCKET_ERROR;
	}
	else
	{	
		// UDP: remote port is used as a filter only.  no need to call
		// 'connect' if recieving from a number of host
	    pSock->remotePort = remotePort;
	    pSock->remoteIP = remoteIP;
		
		return 0; //success
	}
}


/*********************************************************************
 * Function:        int send( SOCKET s, const char* buf, int len, int flags )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 * 					buf - application data buffer containing data to transmit
 *					len - length of data in bytes
 *					flags - message flags. Currently this field is not supported and must be 0.
 * Output:          On success, send returns number of bytes sent.  In case of error, one of 
 * 					the following values is returned:
 *
 *					SOCKET_BFR_ALLOC_ERROR
 *					No memory is available to allocate packet buffer.
 *					
 *					SOCKET_ERROR
 *					General error code. check format of address srtucture and also make 
 *					sure socket descriptor is correct. 
 *					
 *					SOCKET_NOT_READY
 *					The TCP transmit functionality is temporarily disabled because of the
 *					TCP flow control mechanism.
 *					
 *					SOCKET_MAX_LEN_ERROR
 *					The maximum length of the data buffer must be less than the MTU value 
 *					which for ethernet is 1500 bytes.
 *
 * Side Effects:    None
 * Overview:        The send function is used to send outgoing data on an already connected 
 *					socket. This function is normally used to send a reliable, ordered stream 
 *					of data bytes on a socket of type SOCK_STREAM, but can also be used to send 
 *					datagrams on a socket of type SOCK_DGRAM.
 * Note:
 ********************************************************************/
int send( SOCKET s, const char* buf, int len, int flags )
{
	struct MCSocket *socket;

	socket = SocketArray+s;
	
	if( s >= _StackSockets || (socket->SocketType == SOCK_DGRAM &&  socket->smState < SKT_BOUND) )
	{	// must properly create and bind before send
		return SOCKET_ERROR;
	}
	
	
	if( socket->SocketType == SOCK_DGRAM )
	{
		return UDPTransmit( (char* )buf, len, socket, socket->remoteIP, socket->remotePort );
	}
	else
	{
		return TCPTransmitData( socket, (char* )buf, len );
	}	
}

/*********************************************************************
 * Function:        int sendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 * 					buf - application data buffer containing data to transmit
 *					len - length of data in bytes
 *					flags - message flags. Currently this field is not supported and must be 0.
 *					to - pointer to the the sockaddr structure containing the destination address.
 *					tolen - length of the sockaddr structure.
 * Output:          On success, sendto returns number of bytes sent.  In case of error, one of 
 * 					the following values is returned:
 *
 *					SOCKET_BFR_ALLOC_ERROR
 *					No memory is available to allocate packet buffer.
 *					
 *					SOCKET_ERROR
 *					General error code. check format of address srtucture and also make 
 *					sure socket descriptor is correct. 
 *					
 *					SOCKET_MAX_LEN_ERROR
 *					The maximum length of the data buffer must be less than the MTU value 
 *					which for ethernet is 1500 bytes.
 *
 * Side Effects:    None
 * Overview:        The sendto function is used to send outgoing data on a socket 
 *					of type datagram.  The destination address is given by to and 
 *					tolen.  If no memory block is available to create the datagram, 
 *					the function returns an error code.
 * Note:
 ********************************************************************/
int sendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
{
	struct MCSocket *socket;
	struct sockaddr_in *addr;
	DWORD remoteIP;
	WORD remotePort;


	socket = SocketArray+s;
	
	if( s >= _StackSockets || tolen < sizeof(struct sockaddr_in) || socket->SocketType != SOCK_DGRAM ||  socket->smState < SKT_BOUND )
	{	// must properly create and bind before send
		return SOCKET_ERROR;
	}
	

	addr = (struct sockaddr_in *)to;

	remotePort 	= addr->sin_port;		
	remoteIP 	= addr->sin_addr.S_un.S_addr;

	return UDPTransmit( (char*)buf, len, socket, remoteIP, remotePort );
}

/*********************************************************************
 * Function:        int recv( SOCKET s, char * buf, int len, int flags )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 *					buf - application data receive buffer
 *					len - buffer length in bytes
 *					flags - message flags. Currently this field supports only the 
 						MSG_PEEK flag.
 * Output:          If recv is successful, the number of bytes copied to application 
 *					buffer buf is returned. A value of zero indicates no data available.  
 *					A return value of SOCKET_ERROR (-1) indicates an error condition.
 * Side Effects:    None
 * Overview:        The recv() function is used to receive incoming data that has been 
 *					queued for a socket. This function can be used with both datagram 
 *					and stream type sockets.  If the available data is too large to fit 
 *					in the supplied application buffer buf, excess bytes are discarded 
 *					in case of SOCK_DGRAM type sockets.  For SOCK_STREAM types, the data 
 *					is buffered internally so the application can retreive all data by 
 *					multiple calls of recv.  If MSG_PEEK flag is specified, no data is 
 *					deleted from the socket receive queue. 
 * Note:
 ********************************************************************/
int recv( SOCKET s, char * buf, int len, int flags )
{
	return recvfrom( s, buf, len, flags, NULL, NULL );
}

/*********************************************************************
 * Function:        int recvfrom( SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 *					buf - application data receive buffer
 *					len - buffer length in bytes
 *					flags - message flags. Currently this field supports only the 
 *						MSG_PEEK flag.
 *					from - pointer to the the sockaddr structure that will be filled 
 *						in with the destination address.
 *					fromlen - size of buffer pointed by from.
 * Output:          If recvfrom is successful, the number of bytes copied to application 
 *					buffer buf is returned. A value of zero indicates no data available.  
 *					A return value of SOCKET_ERROR (-1) indicates an error condition.
 * Side Effects:    None
 * Overview:        The recvfrom() function is used to receive incoming data that has been 
 *					queued for a socket. This function can be used with both datagram 
 *					and stream type sockets.  If the available data is too large to fit 
 *					in the supplied application buffer buf, excess bytes are discarded 
 *					in case of SOCK_DGRAM type sockets.  For SOCK_STREAM types, the data 
 *					is buffered internally so the application can retreive all data by 
 *					multiple calls of recvfrom.  If MSG_PEEK flag is specified, no data is 
 *					deleted from the socket receive queue. 
 * Note:
 ********************************************************************/
int recvfrom( SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen )
{
    struct MCSocket *socket;
	NET_PKT* rcvPkt;
	int temp, BytesRead = 0;
	UDP_HEADER* pUDP;
	struct sockaddr_in *rem_addr;
	
	if( s >= _StackSockets )
		return SOCKET_ERROR;

	socket = &SocketArray[s];

	if( socket->SocketType == SOCK_DGRAM )
	{
		if( socket->smState < SKT_BOUND ) //must call bind before recv
			return SOCKET_ERROR;

		if( socket->RxMsgQueue.PktCount )
		{
			if( flags & MSG_PEEK )
				rcvPkt = socket->RxMsgQueue.pFirst;
			else
			{
				//retreive the Datagram from Rx Fifo
				Que_GetHead( &socket->RxMsgQueue, &rcvPkt );
				rcvPkt->PktFlags &= ~RXMSG_QUE_MASK;
			}
			
			//extract data
			BytesRead = UDPExtractData( rcvPkt, buf, len );
					
			pUDP = (UDP_HEADER*)rcvPkt->pTransportLayer;

			if( from && fromlen && *fromlen >= sizeof(struct sockaddr_in) )
			{
				DWORD   src_ip;

				src_ip = _arrayToDword(((IP_HEADER*)(rcvPkt->pNetworkLayer))->SourceAddr);

				 rem_addr = (struct sockaddr_in *)from;
				 *fromlen = sizeof(struct sockaddr_in);
				 
				 rem_addr->sin_family = AF_INET;
				 rem_addr->sin_port = pUDP->SourcePort;
				 rem_addr->sin_addr.S_un.S_addr  = src_ip;
		
				 for( temp = 0; temp < 8; temp++ )
				 {
					 rem_addr->sin_zero[temp] = 0;
				 }
			}

			if( flags & MSG_PEEK )
			{
				BytesRead = pUDP->Length;
			}
			else
			{
				//Release packet memory
				DeAllocateBuffer( rcvPkt );
			}
		}
	}
	else	//TCP
	{
		if( flags & MSG_PEEK )
			BytesRead = TCPPeekData( socket, buf, len );
		else
			BytesRead = TCPExtractData( socket, buf, len );

		if( from && fromlen && *fromlen >= sizeof(struct sockaddr_in) )
		{
			 rem_addr = (struct sockaddr_in *)from;
			 *fromlen = sizeof(struct sockaddr_in);
			 
			 rem_addr->sin_family 			 = AF_INET;
			 rem_addr->sin_port				 = socket->remotePort;
			 rem_addr->sin_addr.S_un.S_addr  = socket->remoteIP;
	
			 for( temp = 0; temp < 8; temp++ )
			 	rem_addr->sin_zero[temp] = 0;
		}
	}

	return BytesRead;
}



/*********************************************************************
 * Function:        int closesocket( SOCKET s )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 * Output:          If closesocket is successful, a value of 0 is returned. 
 *					A return value of SOCKET_ERROR (-1) indicates an error.
 * Side Effects:    None
 * Overview:        The closesocket function closes an existing socket.  
 * 					This function releases the socket descriptor s.  
 *					Further references to s fails with SOCKET_ERROR code.  
 *					Any data buffered at the socket is discarded.  If the 
 *					socket s is no longer needed, closesocket() must be 
 *					called in order to release all resources associated 
 *					with s.
 * Note:
 ********************************************************************/
int closesocket( SOCKET s )
{
    struct MCSocket *socket;
	NET_PKT* rcvPkt;

	if( s >= _StackSockets )
		return SOCKET_ERROR;

	socket = &SocketArray[s];

	if( socket->SocketType == SOCK_DGRAM )
	{
		if( socket->smState != SKT_CLOSED ) //this is actually in use
		{
			//empty rcv fifo
			while( Que_GetHead( &socket->RxMsgQueue, &rcvPkt ) )
			{
				rcvPkt->PktFlags &= ~RXMSG_QUE_MASK;
				DeAllocateBuffer( rcvPkt );
			}	

			if( socket->pRxActivePacket )
				DeAllocateBuffer( socket->pRxActivePacket );

			if( socket->pTxActivePacket )
				DeAllocateBuffer( socket->pTxActivePacket );

			SocketInitialize(s); //initialize the socket memory
			return 0; //success
		}
		else
			return SOCKET_ERROR;
	}
	else //tcp sockets
	{
		TCPCloseSocket(socket);
		return 0; //success
	}	
}

/*********************************************************************
 * Function:        SOCKET FindTargetSocket( int SockType, DWORD SrcIP, 
 *					DWORD DestIP, WORD DestPort )
 *
 * PreCondition:    None
 * Input:		 	SockType - Datagram
 *					SrcIP - Source IP address
 *					DestIP	- Destination IP address
 *					DestPort - Detination Port
 * Output:          
 * Side Effects:    None
 * Overview:        Match the incomming packet with socket.
 * Note:
 ********************************************************************/
SOCKET FindTargetSocket( int SockType, DWORD SrcIP, DWORD DestIP, WORD DestPort )
{
    int s;
    struct MCSocket *socket = SocketArray;

    for ( s = 0; s < _StackSockets; s++,socket++ )
    {
		if( socket->SocketType != SockType )
			continue;

		if( socket->smState < SKT_BOUND ) //socket not initialized
			continue;

        if( DestPort == socket->localPort && 	//Port must match
			( DestIP == socket->localIP || 		//exact match with IP
			  socket->localIP == IP_ADDR_ANY || //socket is accepeting all IP addresses (for multi-homed devices)
			  DestIP == IP_ADDR_BROADCAST ) )	//DestIP is a broadcast address
		{
			if( socket->remoteIP == IP_ADDR_ANY || ( socket->remoteIP && socket->remoteIP == SrcIP ) )
				return s;
		}
	}

	return INVALID_SOCKET;
}

#ifdef _STACK_USE_ZC

/*********************************************************************
 * Function:        SOCKET zsocket( int af, int type, int protocol )
 *
 * PreCondition:    None
 * Input:           af - address family - AF_INET
 *                  type - socket type SOCK_DGRAM or SOCK_STREAM
 *                  protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP
 *                  
 * Output:          New socket descriptor.
 * Side Effects:    None
 * Overview:        This function creates a new zero copy socket.
 *                  A zero copy socket has to use zsend, zsendto, zrecv and zrecvfrom functions.
 *                  All the other standard BSD functions are available and can be used normally:
 *                  bind, listen, accept, connect, setsockopt, closesocket.
 *                  
 *                   
 * Note:            - When transmitting data using a zero copy socket the caller has to lock and preserve the contents of the supplied buffer
 *                    until it has been sucessfully transmitted by the stack.
 *                    That's why a TX callback function has to be supplied so that the stack can inform the user
 *                    that the TX buffer is no longer in use.
 *                  - When receiving data with a zero copy buffer the user gets just a pointer to a buffer that could belong to the stack
 *                    (if the RX buffer has the "sticky" atttribute when created).
 *                    Once the processing of the received data in the buffer is done the user should call into the stack to notify that the buffer
 *                    is freed (and the corresponding descriptors freed) ans possibly re-use the sticky buffers for another reception.
 ********************************************************************/
SOCKET zsocket( int af, int type, int protocol )
{
	return _socketCreate(af, type, protocol, SOCK_FLAG_ZCOPY);
}


/*********************************************************************
 * Function:        int zsocketSetSendCBack( SOCKET s, pzSendAckF zAckFnc )
 *
 * PreCondition:    None
 * Input:           s - Socket descriptor returned from a previous call to socket
 *                  zAckFnc - acknowledge function for transmitted buffers
 *                  
 * Output:          0 for success, SOCKET_ERROR otherwise
 * Side Effects:    None
 * Overview:        This function sets the transmission acknowledge callback function for a zero copy socket.
 *                  Whenever a zero copy socket finishes transmitting a user buffer this acknowledge
 *                  function will be called back by the stack to indicate that the buffer has been transmittted
 *                  and is no longer locked.
 *                  It has to be called before binding the socket and start transmitting/receiving on it 
 *                  
 *                   
 * Note:            - When transmitting data using a zero copy socket the caller has to lock and preserve the contents of the supplied buffer
 *                    until it has been sucessfully transmitted by the stack and the corresponding callback function has been called.
 ********************************************************************/
int zsocketSetSendCBack( SOCKET s, pzSendAckF zAckFnc )
{
	struct MCSocket *socket;

	socket = SocketArray+s;

	if( s >= _StackSockets || socket->smState != SKT_CREATED || !(socket->sockFlags&SOCK_FLAG_ZCOPY))
	{	// only work with recently created socket
		return SOCKET_ERROR;
	}

	socket->sockXmitAck=zAckFnc;
	return 0;

}

/*********************************************************************
 * Function:        int zsendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 * 					buf - application data buffer containing data to transmit
 *					len - length of data in bytes
 *					flags - message flags. Currently this field is not supported and must be 0.
 *					to - pointer to the the sockaddr structure containing the destination address.
 *					tolen - length of the sockaddr structure.
 * Output:          On success, zsendto returns number of bytes sent.  In case of error, one of 
 * 					the following values is returned:
 *
 *					SOCKET_BFR_ALLOC_ERROR
 *					No memory is available to allocate packet buffer.
 *					
 *					SOCKET_ERROR
 *					General error code. check format of address srtucture and also make 
 *					sure socket descriptor is correct. 
 *					
 *					SOCKET_MAX_LEN_ERROR
 *					The maximum length of the data buffer must be less than the MTU value 
 *					which for ethernet is 1500 bytes.
 *
 * Side Effects:    None
 * Overview:        The zsendto function is used to send outgoing data on a socket 
 *					of type datagram.  The destination address is given by to and 
 *					tolen.  If no memory block is available to create the datagram, 
 *					the function returns an error code.
 * Note:
 ********************************************************************/
int zsendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
{
	struct MCSocket *socket;
	struct sockaddr_in *addr;
	DWORD remoteIP;
	WORD remotePort;

	socket = SocketArray+s;
	
	if( s >= _StackSockets || tolen < sizeof(struct sockaddr_in) || socket->SocketType != SOCK_DGRAM ||  socket->smState < SKT_BOUND ||
		       !(socket->sockFlags&SOCK_FLAG_ZCOPY)|| !socket->sockXmitAck )
	{	// must properly create and bind before send
		return SOCKET_ERROR;
	}
	
	addr = (struct sockaddr_in *)to;

	remotePort 	= addr->sin_port;		
	remoteIP 	= addr->sin_addr.S_un.S_addr;

	return UDPTransmit( (char*)buf, len, socket, remoteIP, remotePort );
}

/*********************************************************************
 * Function:        int zsend( SOCKET s, const char* buf, int len, int flags )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 * 					buf - application data buffer containing data to transmit
 *					len - length of data in bytes
 *					flags - message flags. Currently this field is not supported and must be 0.
 * Output:          On success, zsend returns number of bytes sent.  In case of error, one of 
 * 					the following values is returned:
 *
 *					SOCKET_BFR_ALLOC_ERROR
 *					No memory is available to allocate packet buffer.
 *					
 *					SOCKET_ERROR
 *					General error code. check format of address srtucture and also make 
 *					sure socket descriptor is correct. 
 *					
 *					SOCKET_NOT_READY
 *					The TCP transmit functionality is temporarily disabled because of the
 *					TCP flow control mechanism.
 *					
 *					SOCKET_MAX_LEN_ERROR
 *					The maximum length of the data buffer must be less than the MTU value 
 *					which for ethernet is 1500 bytes.
 *
 * Side Effects:    None
 * Overview:        The zsend function is used to send outgoing data on an already connected 
 *					socket. This function is normally used to send a reliable, ordered stream 
 *					of data bytes on a socket of type SOCK_STREAM, but can also be used to send 
 *					datagrams on a socket of type SOCK_DGRAM.
 * Note:
 ********************************************************************/
int zsend( SOCKET s, const char* buf, int len, int flags )
{
	struct MCSocket *socket;

	socket = SocketArray+s;
	
	if( s >= _StackSockets || (socket->SocketType == SOCK_DGRAM &&  socket->smState < SKT_BOUND) || 
		       !(socket->sockFlags&SOCK_FLAG_ZCOPY)|| !socket->sockXmitAck )
	{	// must properly create and bind before send
		return SOCKET_ERROR;
	}
	
	if( socket->SocketType == SOCK_DGRAM )
	{
		return UDPTransmit( (char* )buf, len, socket, socket->remoteIP, socket->remotePort );
	}
	else
	{
		return TCPTransmitData( socket, (char* )buf, len );
	}	
}

/*********************************************************************
 * Function:        int zrecv( SOCKET s, char** pBuf, void** pAckHandle, int flags )
 *
 * PreCondition:    None
 * Input:           s - Socket descriptor returned from a previous call to socket
 *                  pBuf  - address to store the address of the data receive buffer
 *                  pAckHandle -  handle to be used for acknowledge
 *                  flags - message flags. Currently this field supports only the
 *                          MSG_PEEK flag.
 * Output:          If zrecv is successful, the number of bytes copied to application 
 *					buffer buf is returned. A value of zero indicates no data available.  
 *					A return value of SOCKET_ERROR (-1) indicates an error condition.
 * Side Effects:    None
 * Overview:        The zrecv() function is used to receive incoming data that has been 
 *					queued for a socket. This function can be used with both datagram 
 *					and stream type sockets.  If the available data is too large to fit 
 *					in the supplied application buffer buf, excess bytes are discarded 
 *					in case of SOCK_DGRAM type sockets.  For SOCK_STREAM types, the data 
 *					is buffered internally so the application can retreive all data by 
 *					multiple calls of zrecv.  If MSG_PEEK flag is specified, no data is 
 *					deleted from the socket receive queue. 
 * Note:
 ********************************************************************/
int zrecv( SOCKET s, char** pBuf, void** pAckHandle, int flags )
{

	return zrecvfrom(s, pBuf, pAckHandle, flags, 0, 0);
}



/*********************************************************************
 * Function:        int zrecvfrom( SOCKET s, char** pBuf, int flags, struct sockaddr * from, int * fromlen )
 *
 * PreCondition:    None
 * Input:			s - Socket descriptor returned from a previous call to socket
 *					buf - application data receive buffer
 *					len - buffer length in bytes
 *					flags - message flags. Currently this field supports only the 
 *						MSG_PEEK flag. @@@ ?
 *					from - pointer to the the sockaddr structure that will be filled 
 *						in with the destination address.
 *					fromlen - size of buffer pointed by from.
 * Output:          If zrecvfrom is successful, the number of bytes available to the application in pBuf 
 *                  A value of zero indicates no data available.
 *                  A return value of SOCKET_ERROR (-1) indicates an error condition.
 *
 * Side Effects:    None
 * Overview:        The zrecvfrom() function is used to receive incoming data that has been
 *                  queued for a Zero Copy socket. This function can be used with both datagram
 *                  and stream type sockets.
 *                  @@@@
 *                  If the available data is too large to fit
 *                  in the supplied application buffer buf, excess bytes are discarded 
 *                  in case of SOCK_DGRAM type sockets.  For SOCK_STREAM types, the data 
 *                  is buffered internally so the application can retreive all data by 
 *                  multiple calls of zrecvfrom.
 *                  If MSG_PEEK flag is specified, no data is 
 *                  deleted from the socket receive queue. 
 * Note:
 ********************************************************************/
int zrecvfrom( SOCKET s, char** pBuf, void** pAckHandle, int flags, struct sockaddr * from, int * fromlen )
{
	struct MCSocket *socket;
	NET_PKT* rcvPkt;
	int temp, AvlblBytes;
	UDP_HEADER* pUDP;
	struct sockaddr_in *rem_addr;


	*pBuf=0;
	*pAckHandle=0;
    
	if( s >= _StackSockets || !((socket=SocketArray+s)->sockFlags&SOCK_FLAG_ZCOPY) )
	{
		return SOCKET_ERROR;
	}

	AvlblBytes = 0;

	if( socket->SocketType == SOCK_DGRAM )
	{
		if( socket->smState < SKT_BOUND )
		{	// must call bind before recv
			return SOCKET_ERROR;
		}

		if( socket->RxMsgQueue.PktCount )
		{
			if( flags & MSG_PEEK )
			{
				rcvPkt = socket->RxMsgQueue.pFirst;
			}
			else
			{	// retreive the Datagram from Rx Fifo
				Que_GetHead( &socket->RxMsgQueue, &rcvPkt );
				rcvPkt->PktFlags &= ~RXMSG_QUE_MASK;
			}
			
			// update the data	
			pUDP = (UDP_HEADER*)rcvPkt->pTransportLayer;
			*pBuf = (char*)pUDP + sizeof(UDP_HEADER);
			AvlblBytes = pUDP->Length;

            if( !(flags & MSG_PEEK) )
            {
                    rcvPkt->PktDcpt[0].bFlags|=BUFF_ZC_WACK;	// signal ack is needed
        			*pAckHandle=rcvPkt;
            }

			if( from && fromlen && *fromlen >= sizeof(struct sockaddr_in) )
			{
				DWORD   src_ip;

				src_ip = _arrayToDword(((IP_HEADER*)(rcvPkt->pNetworkLayer))->SourceAddr);

				 rem_addr = (struct sockaddr_in *)from;
				 *fromlen = sizeof(struct sockaddr_in);
				 
				 rem_addr->sin_family = AF_INET;
				 rem_addr->sin_port = pUDP->SourcePort;
				 rem_addr->sin_addr.S_un.S_addr  = src_ip;
		
				 for( temp = 0; temp < 8; temp++ )
				 {
					 rem_addr->sin_zero[temp] = 0;
				 }
			}

			// Release packet memory done by the caller
		}
	}
	else	//TCP
	{
		AvlblBytes = TCPExtractDataZc( socket, pBuf, pAckHandle, flags );

		if( from && fromlen && *fromlen >= sizeof(struct sockaddr_in) )
		{
			 rem_addr = (struct sockaddr_in *)from;
			 *fromlen = sizeof(struct sockaddr_in);
			 
			 rem_addr->sin_family 			 = AF_INET;
			 rem_addr->sin_port				 = socket->remotePort;
			 rem_addr->sin_addr.S_un.S_addr  = socket->remoteIP;
	
			 for( temp = 0; temp < 8; temp++ )
			 	rem_addr->sin_zero[temp] = 0;
		}
	}

	return AvlblBytes;


}

/*********************************************************************
 * Function:        int zrecvAck( SOCKET s, void * pAckHandle )
 *
 * PreCondition:    None
 * Input:           s - Socket descriptor returned from a previous call to socket
 *                  pBuf - address of a ZC receive buffer
 *					
 * Output:          None          
 *
 * Side Effects:    None
 * 
 * Overview:        The zrecvAck() function is used to acknowledge a zero copy received buffer previously obtained by a call to
 *                  zrecv/zrecfrom.
 *                  Since the buffer is owned by the stack it has to be released to be used in other receive operations.
 *
 * Note:
 ********************************************************************/
int zrecvAck( SOCKET s, void * pAckHandle )
{
	struct MCSocket *socket;
	NET_PKT* pOwner;
	
	if( s >= _StackSockets || !((socket=SocketArray+s)->sockFlags&SOCK_FLAG_ZCOPY) || !pAckHandle )
	{
		return SOCKET_ERROR;
	}

	pOwner= (NET_PKT*)pAckHandle;

	if(!(pOwner->PktDcpt[0].bFlags & BUFF_ZC_WACK))
	{
		return SOCKET_ERROR;	// not waiting for ack?
	}

	DeAllocateBuffer(pOwner);

	return 0;

	
}



#endif	// _STACK_USE_ZC





