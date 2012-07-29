/*********************************************************************
 *
 *            BSD Socket API Header File
 *
 *********************************************************************
 * FileName:        socket.h
 * Description:     Socket API for BSD TCPIP Stack
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the �Company�) for its PICmicro� Microcontroller is intended and
 * supplied to you, the Company�s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN �AS IS� CONDITION. NO WARRANTIES,
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
 * the following acknowledgement: �This product includes software developed by 
 * the University of California, Berkeley and its contributors.�
 * 4. Neither the name of the University nor the names of its contributors may be 
 * used to endorse or promote products derived from this software without specific
 * prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS �AS IS�
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
*/

#ifndef _SOCKET_H_
#define _SOCKET_H_


/*************************
     socket definitions
 ************************/

typedef int SOCKET;

#define SOCK_STREAM     100
#define SOCK_DGRAM      110

#define INVALID_SOCKET          (-1)
#define SOCKET_ERROR            (-1)
#define SOCKET_BFR_ALLOC_ERROR  (-2)
#define SOCKET_HOST_NO_ROUTE    (-3)
#define SOCKET_MAX_LEN_ERROR    (-4)
#define SOCKET_NOT_READY        (-5)
#define SOCKET_CNXN_IN_PROGRESS (-6)



/*************************
     socket options
 ************************/


#define MSG_PEEK        0x2             /* peek at incoming message */

// Level number for (get/set)sockopt() to apply to socket itself.
#define SOL_SOCKET      0xffff          /* options for socket level */

#define TCP_NODELAY     0x0001
#define SO_SNDBUF       0x1001          /* send buffer size */
#define SO_RCVBUF       0x1002          /* receive buffer size */



/*************************
     MAC addresses
 ************************/
#if !defined(BOWLERSTRUCTDEF_H_)
typedef union __attribute__((__packed__)) _MAC_ADDR
{
	struct{
		unsigned char v[6];
	};
} MAC_ADDR;
#endif

#define DEFAULT_MAC_ADDRESS "00-04-a3-00-00-00"    // choosing this address will result in using the factory pre-programmed one




/*************************
    IP addresses
 ************************/

typedef union _IP_ADDR
{
    BYTE        v[4];
    WORD        w[2];
    DWORD       Val;
}IP_ADDR;           // IP address



#define AF_INET                 2   // Internet Address Family - UDP, TCP, etc.

 
#define IPPROTO_TCP             6               // tcp
#define IPPROTO_UDP             17              // user datagram protocol

#define IP_ADDR_ANY             0
#define IP_ADDR_BROADCAST       0xffffffffu

#define INADDR_ANY              0x00000000
#define INADDR_LOOPBACK         0x7f000001
#define INADDR_BROADCAST        0xffffffff
#define INADDR_NONE             0xffffffff

#define ADDR_ANY                INADDR_ANY


struct in_addr {
    union {
            struct { BYTE s_b1,s_b2,s_b3,s_b4; } S_un_b;
            struct { WORD s_w1,s_w2; } S_un_w;
            DWORD S_addr;
    } S_un;
    
#define s_addr  S_un.S_addr
                                /* can be used for most tcp & ip code */
#define s_host  S_un.S_un_b.s_b2
                                /* host on imp */
#define s_net   S_un.S_un_b.s_b1
                                /* network */
#define s_imp   S_un.S_un_w.s_w2
                                /* imp */
#define s_impno S_un.S_un_b.s_b4
                                /* imp # */
#define s_lh    S_un.S_un_b.s_b3
                                /* logical host */  
    
};

struct sockaddr {
        unsigned short  sa_family;              /* address family */
        char    sa_data[14];            /* up to 14 bytes of direct address */
};

struct sockaddr_in {
    short   sin_family;
    WORD    sin_port;
    struct  in_addr sin_addr;
    char    sin_zero[8];
};

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr_in *PSOCKADDR_IN;
typedef struct sockaddr_in *LPSOCKADDR_IN;

typedef struct sockaddr SOCKADDR;
typedef struct sockaddr *PSOCKADDR;
typedef struct sockaddr *LPSOCKADDR;



/*************************
     Socket Interface functions
 ************************/

/*********************************************************************
 * Function:        SOCKET socket( int af, int type, int protocol )
 *
 * PreCondition:    None
 * 
 * Input:           af - address family - AF_INET
 *                  type - socket type SOCK_DGRAM or SOCK_STREAM
 *                  protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP
 *                  
 * Output:          New socket descriptor or SOCKET_ERROR if the socket cannot be created.
 * 
 * Side Effects:    None
 * 
 * Overview:        This function creates a new socket.
 *
 * Note:
 ********************************************************************/
SOCKET socket( int af, int type, int protocol );

/*********************************************************************
 * Function:        int bind( SOCKET s, const struct sockaddr * name, int namelen )
 *
 * PreCondition:    None
 * 
 * Input:           s - Socket descriptor returned from a previous call to socket
 *                  name - pointer to the the sockaddr structure containing the
 *                         local address of the socket.
 *                  namelen - length of the sockaddr structure.
 *                  
 * Output:          If bind is successful, a value of 0 is returned. A return value 
 *                  of SOCKET_ERROR indicates an error.
 *                  
 * Side Effects:    None
 * 
 * Overview:        The bind function assigns a name to an unnamed socket.  The name 
 *                  represents the local address of the communication endpoint. 
 *                  For sockets of type SOCK_STREAM, the name of the remote endpoint 
 *                  is assigned when a connect or accept function is executed.
 *
 * Note:
 ********************************************************************/
int bind( SOCKET s, const struct sockaddr * name, int namelen );

/*********************************************************************
 * Function:        int listen( SOCKET s, int backlog )
 *
 * PreCondition:    None
 * 
 * Input:           s - Socket identifier
 *                  backlog - maximum number of connection requests that can be queued
 *                  
 * Output:          returns 0 on success, else return SOCKET_ERROR on error.
 * 
 * Side Effects:    None
 * 
 * Overview:        The listen function sets the specified socket in a listen mode.  
 *                  Calling the listen function indicates that the application is ready to 
 *                  accept connection requests arriving at a socket of type SOCK_STREAM. 
 *                  The connection request is queued (if possible) until accepted with an 
 *                  accept function. The backlog parameter defines the maximum number of 
 *                  pending connections that may be queued.
 * Note:
 ********************************************************************/
int listen( SOCKET s, int backlog );

/*********************************************************************
 * Function:        SOCKET accept( SOCKET s, struct sockaddr * addr, int * addrlen )
 *
 * PreCondition:    None
 * 
 * Input:           s       - Socket descriptor returned from a previous call to socket.  
 *                            must be bound to a local name and in listening mode.
 *                  addr    - pointer to the the sockaddr structure that will receive 
 *                            the connecting node IP address and port number.
 *                  addrlen - A value-result parameter and should initially contain 
 *                            the amount of space pointed to by addr; on return it contains 
 *                            the actual length (in bytes) of the addr returned.
 *                          
 * Output:          If the accept() function succeeds, it returns a non-negative integer 
 *                  that is a descriptor for the accepted socket. Otherwise, the value 
 *                  SOCKET_ERROR is returned.
 *                   
 * Side Effects:    None
 *
 * Overview:        The accept function is used to accept a connection request queued 
 *                  for a listening socket.  If a connection request is pending, accept 
 *                  removes the request from the queue, and a new socket is created for 
 *                  the connection. The original listening socket remains open and 
 *                  continues to queue new connection requests.  The socket s must be 
 *                  a SOCK_STREAM type socket.
 * Note:
 ********************************************************************/
SOCKET accept( SOCKET s, struct sockaddr * addr, int * addrlen );

/*********************************************************************
 * Function:        int connect( SOCKET s, struct sockaddr * name, int namelen )
 *
 * PreCondition:    None
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  name    - pointer to the the sockaddr structure containing the 
 *                            local address of the socket.
 *                  namelen - length of the sockaddr structure.
 *                  
 * Output:          If the connect() function succeeds, it returns 0. Otherwise, 
 *                  the value SOCKET_ERROR is returned to indicate an error condition.
 *                  For stream based socket, if the connection is not established yet, 
 *                  connect returns SOCKET_CNXN_IN_PROGRESS.
 *                  
 * Side Effects:    None
 *
 * Overview:        The connect function assigns the address of the peer communications
 *                  endpoint.  For stream sockets,  connection is established between 
 *                  the endpoints. For datagram sockets, an address filter is established 
 *                  between the endpoints until changed with another connect() function.
 * Note:
 ********************************************************************/
int connect( SOCKET s, struct sockaddr * name, int namelen );

/*********************************************************************
 * Function:        int sendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
 *
 * PreCondition:    None
 * Input:           s     - Socket descriptor returned from a previous call to socket
 *                  buf   - application data buffer containing data to transmit
 *                  len   - length of data in bytes
 *                  flags - message flags. Currently this field is not supported and must be 0.
 *                  to    - pointer to the the sockaddr structure containing the destination address.
 *                  tolen - length of the sockaddr structure.
 *                  
 * Output:          On success, sendto returns number of bytes sent.  In case of error, one of 
 *                  the following values is returned:
 *                      - SOCKET_BFR_ALLOC_ERROR
 *                          No memory is available to allocate packet buffer.
 *                      - SOCKET_ERROR
 *                          General error code. check format of address structure and also make 
 *                          sure socket descriptor is correct. 
 *                      - SOCKET_MAX_LEN_ERROR
 *                          The maximum length of the data buffer must be less than the MTU value 
 *                          which for ethernet is 1500 bytes.
 *
 * Side Effects:    None
 *
 * Overview:        The sendto function is used to send outgoing data on a socket 
 *                  of type datagram.  The destination address is given by to and 
 *                  tolen.  If no memory block is available to create the datagram, 
 *                  the function returns an error code.
 * Note:
 ********************************************************************/
int sendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen );

/*********************************************************************
 * Function:        int send( SOCKET s, const char* buf, int len, int flags )
 *
 * PreCondition:    None
 * Input:           s     - Socket descriptor returned from a previous call to socket
 *                  buf   - application data buffer containing data to transmit
 *                  len   - length of data in bytes
 *                  flags - message flags. Currently this field is not supported and must be 0.
 *                  
 * Output:          On success, send returns number of bytes sent.  In case of error, one of 
 *                  the following values is returned:
 *                      - SOCKET_BFR_ALLOC_ERROR
 *                          No memory is available to allocate packet buffer.
 *                      - SOCKET_ERROR
 *                          General error code. check format of address structure and also make 
 *                          sure socket descriptor is correct. 
 *                      - SOCKET_MAX_LEN_ERROR
 *                          The maximum length of the data buffer must be less than the MTU value 
 *                          which for ethernet is 1500 bytes.
 *                      - SOCKET_NOT_READY
 *                          The TCP transmit functionality is temporarily disabled because of the
 *                          TCP flow control mechanism.
 *
 * Side Effects:    None
 *
 * Overview:        The send function is used to send outgoing data on an already connected 
 *                  socket. This function is normally used to send a reliable, ordered stream 
 *                  of data bytes on a socket of type SOCK_STREAM, but can also be used to send 
 *                  datagrams on a socket of type SOCK_DGRAM.
 * Note:
 ********************************************************************/
int send( SOCKET s, const char* buf, int len, int flags );

/*********************************************************************
 * Function:        int recvfrom( SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen )
 *
 * PreCondition:    None
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  buf     - application data receive buffer
 *                  len     - buffer length in bytes
 *                  flags   - message flags. Currently this field supports only the 
 *                            MSG_PEEK flag.
 *                  from    - pointer to the the sockaddr structure that will be filled 
 *                            in with the destination address.
 *                  fromlen - size of buffer pointed by from.
 *                  
 * Output:          If recvfrom is successful, the number of bytes copied to application 
 *                  buffer buf is returned. A value of zero indicates no data available.  
 *                  A return value of SOCKET_ERROR indicates an error condition.
 *                  
 * Side Effects:    None
 * 
 * Overview:        The recvfrom() function is used to receive incoming data that has been 
 *                  queued for a socket. This function can be used with both datagram 
 *                  and stream type sockets.  If the available data is too large to fit 
 *                  in the supplied application buffer buf, excess bytes are discarded 
 *                  in case of SOCK_DGRAM type sockets.  For SOCK_STREAM types, the data 
 *                  is buffered internally so the application can retreive all data by 
 *                  multiple calls of recvfrom.  If MSG_PEEK flag is specified, no data is 
 *                  deleted from the socket receive queue. 
 *
 * Note:
 ********************************************************************/
int recvfrom( SOCKET s, char * buf, int len, int flags, struct sockaddr * from, int * fromlen );

/*********************************************************************
 * Function:        int recv( SOCKET s, char * buf, int len, int flags )
 *
 * PreCondition:    None
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  buf     - application data receive buffer
 *                  len     - buffer length in bytes
 *                  flags   - message flags. Currently this field supports only the 
                              MSG_PEEK flag.
                        
 * Output:          If recv is successful, the number of bytes copied to application 
 *                  buffer buf is returned. A value of zero indicates no data available.  
 *                  A return value of SOCKET_ERROR indicates an error condition.
 *                  
 * Side Effects:    None
 *
 * Overview:        The recv() function is used to receive incoming data that has been 
 *                  queued for a socket. This function can be used with both datagram 
 *                  and stream type sockets.  If the available data is too large to fit 
 *                  in the supplied application buffer buf, excess bytes are discarded 
 *                  in case of SOCK_DGRAM type sockets.  For SOCK_STREAM types, the data 
 *                  is buffered internally so the application can retreive all data by 
 *                  multiple calls of recv.  If MSG_PEEK flag is specified, no data is 
 *                  deleted from the socket receive queue. 
 * Note:
 ********************************************************************/
int recv( SOCKET s, char * buf, int len, int flags );

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
int setsockopt( SOCKET s, int level, int optname, char * optval, int optlen );

/*********************************************************************
 * Function:        int closesocket( SOCKET s )
 *
 * PreCondition:    None
 * 
 * Input:           s - Socket descriptor returned from a previous call to socket
 * 
 * Output:          If closesocket is successful, a value of 0 is returned. 
 *                  A return value of SOCKET_ERROR indicates an error.
 *                  
 * Side Effects:    None
 * 
 * Overview:        The closesocket function closes an existing socket.  
 *                  This function releases the socket descriptor s.  
 *                  Further references to s fails with SOCKET_ERROR code.  
 *                  Any data buffered at the socket is discarded.  If the 
 *                  socket s is no longer needed, closesocket() must be 
 *                  called in order to release all resources associated 
 *                  with s.
 * Note:
 ********************************************************************/
int closesocket( SOCKET s );


#if (( (__PIC32_FEATURE_SET__ >= 500) && (__PIC32_FEATURE_SET__ <= 799) && defined(_ETH) && defined(MAC_EMBEDDED_PIC32) && defined(ZC_SOCKET_API) ))

/*************************
     Zero copy functionality sockets
 ************************/

/*
 * If you're running on a PIC32MX7 family and need Zero copy functionality
 * define ZC_SOCKET_API in TCPIP-BSD-Config.h 
*/ 


typedef void (*pzSendAckF)(void* pzSockXmitBuff);       // zero copy socket send/sendto (transmit buffer) acnowledge function


/*********************************************************************
 * Function:        SOCKET zsocket( int af, int type, int protocol )
 *
 * PreCondition:    None
 * Input:           af       - address family - AF_INET
 *                  type     - socket type SOCK_DGRAM or SOCK_STREAM
 *                  protocol - IP protocol IPPROTO_UDP or IPPROTO_TCP
 *                  
 * Output:          New socket descriptor.
 * 
 * Side Effects:    None
 * 
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
 *                    or to the MAC driver.
 *                    Once the processing of the received data in the buffer is done the user has to call into the stack to notify that the buffer
 *                    is freed and re-used for another reception.
 ********************************************************************/
SOCKET zsocket( int af, int type, int protocol );

/*********************************************************************
 * Function:        int zsocketSetSendCBack( SOCKET s, pzSendAckF zAckFnc )
 *
 * PreCondition:    None
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  zAckFnc - acknowledge function for transmitted buffers
 *                  
 * Output:          0 for success, SOCKET_ERROR otherwise
 * 
 * Side Effects:    None
 *
 * Overview:        This function sets the transmission acknowledge callback function for a zero copy socket.
 *                  Whenever a zero copy socket finishes transmitting a user buffer this acknowledge
 *                  function will be called back by the stack to indicate that the buffer has been transmittted
 *                  and is no longer locked.
 *                  It has to be called before binding the socket and start transmitting/receiving on it 
 *                   
 * Note:            When transmitting data using a zero copy socket the caller has to lock and preserve the contents of the supplied buffer
 *                  until it has been sucessfully transmitted by the stack and the corresponding callback function has been called.
 ********************************************************************/
int     zsocketSetSendCBack( SOCKET s, pzSendAckF zAckFnc );


/*********************************************************************
 * Function:        int zsendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen )
 *
 * PreCondition:    None
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  buf     - application data buffer containing data to transmit
 *                  len     - length of data in bytes
 *                  flags   - message flags. Currently this field is not supported and must be 0.
 *                  to      - pointer to the the sockaddr structure containing the destination address.
 *                  tolen   - length of the sockaddr structure.
 *                  
 * Output:          On success, zsendto returns number of bytes sent.  In case of error, one of 
 *                  the following values is returned:
 *                      - SOCKET_BFR_ALLOC_ERROR
 *                          No memory is available to allocate packet buffer.
 *                      - SOCKET_ERROR
 *                          General error code. check format of address structure and also make 
 *                          sure socket descriptor is correct. 
 *                      - SOCKET_MAX_LEN_ERROR
 *                          The maximum length of the data buffer must be less than the MTU value 
 *                          which for ethernet is 1500 bytes.
 *
 * Side Effects:    None
 * 
 * Overview:        The zsendto function is used to send outgoing data on a socket 
 *                  of type datagram.  The destination address is given by to and 
 *                  tolen.  If no memory block is available to create the datagram, 
 *                  the function returns an error code.
 *                  
 * Note:            When transmitting data using a zero copy socket the caller has to lock and preserve the contents of the supplied buffer
 *                  until it has been sucessfully transmitted by the stack and the corresponding callback function has been called.
 ********************************************************************/
int     zsendto( SOCKET s, const char * buf, int len, int flags, const struct sockaddr * to, int tolen );

/*********************************************************************
 * Function:        int zsend( SOCKET s, const char* buf, int len, int flags )
 *
 * PreCondition:    None
 * Input:           s       - Socket descriptor returned from a previous call to socket
 *                  buf     - application data buffer containing data to transmit
 *                  len     - length of data in bytes
 *                  flags   - message flags. Currently this field is not supported and must be 0.
 *                  
 * Output:          On success, zsend returns number of bytes sent.  In case of error, one of 
 *                  the following values is returned:
 *                      - SOCKET_BFR_ALLOC_ERROR
 *                          No memory is available to allocate packet buffer.
 *                      - SOCKET_ERROR
 *                          General error code. check format of address structure and also make 
 *                          sure socket descriptor is correct. 
 *                      - SOCKET_MAX_LEN_ERROR
 *                          The maximum length of the data buffer must be less than the MTU value 
 *                          which for ethernet is 1500 bytes.
 *                      - SOCKET_NOT_READY
 *                          The TCP transmit functionality is temporarily disabled because of the
 *                          TCP flow control mechanism.
 *
 * Side Effects:    None
 *
 * Overview:        The zsend function is used to send outgoing data on an already connected 
 *                  socket. This function is normally used to send a reliable, ordered stream 
 *                  of data bytes on a socket of type SOCK_STREAM, but can also be used to send 
 *                  datagrams on a socket of type SOCK_DGRAM.
 *
 * Note:            When transmitting data using a zero copy socket the caller has to lock and preserve the contents of the supplied buffer
 *                  until it has been sucessfully transmitted by the stack and the corresponding callback function has been called.
 ********************************************************************/
int     zsend( SOCKET s, const char* buf, int len, int flags );

/*********************************************************************
 * Function:        int zrecvfrom( SOCKET s, char** pBuf, void** pAckHandle, int flags, struct sockaddr * from, int * fromlen )
 *
 * PreCondition:    None
 * Input:           s           - Socket descriptor returned from a previous call to socket
 *                  pBuf        - address to store the address of the data receive buffer
 *                  pAckHandle  -  handle to be used for acknowledge
 *                  flags       - message flags. Currently this field supports only the
 *                                MSG_PEEK flag. 
 *                  from        - pointer to the the sockaddr structure that will be filled
 *                                in with the destination address.
 *                  fromlen     - size of buffer pointed by from.
 *                  
 * Output:          If zrecvfrom is successful, the number of bytes available to the application in pBuf 
 *                  A value of zero indicates no data available.
 *                  A return value of SOCKET_ERROR indicates an error condition.
 *
 * Side Effects:    None
 * 
 * Overview:        The zrecvfrom() function returns a pointer to a data buffer that stores received incoming data
 *                  that has been queued for a Zero Copy socket.
 *                  This function can be used with both datagram and stream type sockets.
 *                  For SOCK_DGRAM type sockets the function returns the next data packet
 *                  available for that socket.
 *                  For SOCK_STREAM types, the data is buffered internally so the application can retreive all data by 
 *                  multiple calls of zrecvfrom.
 *                  If MSG_PEEK flag is specified, no data is  deleted from the socket receive queue.
 *                  
 * Note:            If MSG_PEEK is specified the pAckHandle wil contain 0 so that the RX buffer cannot be acknowledged.
 *                  A new call to zrecvfrom has to be performed without the MSG_PEEK flag set.
 ********************************************************************/
int     zrecvfrom( SOCKET s, char** pBuf, void** pAckHandle, int flags, struct sockaddr * from, int * fromlen );

/*********************************************************************
 * Function:        int zrecv( SOCKET s, char** pBuf, void** pAckHandle, int flags )
 *
 * PreCondition:    None
 * Input:           s           - Socket descriptor returned from a previous call to socket
 *                  pBuf        - address to store the address of the data receive buffer
 *                  pAckHandle  - handle to be used for acknowledge
 *                  flags       - message flags. Currently this field supports only the
 *                                MSG_PEEK flag.
 *
 * Output:          If zrecv is successful, the number of bytes available to the application in pBuf 
 *                  A value of zero indicates no data available.
 *                  A return value of SOCKET_ERROR indicates an error condition.
 *
 * Side Effects:    None
 * 
 * Overview:        The zrecv() function returns a pointer to a data buffer that stores received incoming data
 *                  that has been queued for a Zero Copy socket.
 *                  This function can be used with both datagram and stream type sockets.
 *                  For SOCK_DGRAM type sockets the function returns the next data packet
 *                  available for that socket.
 *                  For SOCK_STREAM types, the data is buffered internally so the application can retreive all data by 
 *                  multiple calls of zrecv.
 *                  If MSG_PEEK flag is specified, no data is  deleted from the socket receive queue.
 *                  
 * Note:            If MSG_PEEK is specified the pAckHandle wil contain 0 so that the RX buffer cannot be acknowledged.
 *                  A new call to zrecv has to be performed without the MSG_PEEK flag set.
 ********************************************************************/
int     zrecv( SOCKET s, char** pBuf, void** pAckHandle, int flags );

/*********************************************************************
 * Function:        int zrecvAck( SOCKET s, void * ackHandle )
 *
 * PreCondition:    None
 * 
 * Input:           s           - Socket descriptor returned from a previous call to socket
 *                  ackHandle   - acknowledge handle returned by a call to zrecv/zrecvfrom
 *                  
 * Output:          A value of zero indicates success.
 *                  A return value of SOCKET_ERROR indicates an error condition.          
 *
 * Side Effects:    None
 * 
 * Overview:        The zrecvAck() function is used to acknowledge a zero copy received buffer previously obtained by a call to
 *                  zrecv/zrecfrom.
 *                  Since the buffer is owned by the stack it has to be released to be used in other receive operations.
 *
 * Note:
 ********************************************************************/
int     zrecvAck( SOCKET s, void* ackHandle );



#endif  // (( (__PIC32_FEATURE_SET__ >= 500) && (__PIC32_FEATURE_SET__ <= 799) && defined(_ETH) && defined(MAC_EMBEDDED_PIC32) && defined(ZC_SOCKET_API) ))


#endif  // _SOCKET_H_

