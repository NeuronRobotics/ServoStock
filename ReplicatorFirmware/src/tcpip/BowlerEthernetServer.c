/********************************************************************
 * FileName:		FTP.c
 * Dependencies:
 * Company:		Microchip Technology, Inc.
 *
 * Software License Agreement:
 * The software supplied herewith by Microchip Technology Incorporated
 * (the Company) for its PICmicro Microcontroller is intended and
 * supplied to you, the Companys customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN AS IS CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 *********************************************************************
 * File Description:
 *
 * FTP Server
 *
 * Change History:
 * Name				Date            Changes
 * Sean Justice		03/10/06		Initial Version
 ********************************************************************/


#include "BowlerEthernetServer.h"
#include "Bowler/Bowler_Struct_Def.h"
#include "Bowler/Debug.h"
void EthTx(BowlerPacket * Packet);
void EthRXadd(BYTE b);
static BYTE privateRX[BOWLER_PacketSize];
static BYTE_FIFO_STORAGE storeRX;
extern MAC_ADDR MyMAC __attribute__ ((section (".scs_global_var"))); 

static BYTE privateRX[BOWLER_PacketSize];
static BYTE_FIFO_STORAGE storeRX;
static BYTE privateTX[BOWLER_PacketSize];
static BYTE_FIFO_STORAGE storeTX;

#define FTP_TIMEOUT                     (TICK)((TICK)180 * TICKS_PER_SECOND)
#define MAX_FTP_ARGS                    (7)
#define MAX_FTP_CMD_STRING_LEN          (sizeof(BowlerPacket))

PRIVATE SOCKET			_ftpListenSocket;
PRIVATE SOCKET			_ftpDataSocket;
PRIVATE SOCKET			_ftpConnectionSocket;
PRIVATE SOCKADDR_IN		_ftpSockAddr;
PRIVATE WORD_VAL		_ftpDataPort;
//PRIVATE SM_FTP			_ftpStage;
//PRIVATE SM_FTP_CMD		_ftpStageCmd;
//PRIVATE	FTP_COMMAND		_ftpCmd;
//PRIVATE FTP_RESPONSE	_ftpResponce;	
//PRIVATE BYTE			_ftpUser[FTP_USER_NAME_LEN];
PRIVATE	BYTE			_ftpStr[MAX_FTP_CMD_STRING_LEN + 2];
PRIVATE	int				_ftpStrLen;
//PRIVATE	BYTE			*_ftpArgv[MAX_FTP_ARGS];
PRIVATE BYTE			_ftpNumArg;
PRIVATE TICK			_lastActivity;
PRIVATE FSFILE			*_ftpFile;
//PRIVATE FTP_FLAGS		_ftpFlags;
PRIVATE BOOL			_ftpConnection;
PRIVATE BYTE			_ftpTxBuf[FTP_TX_BUF_SIZE];
PRIVATE int				_ftpTxSize;
PRIVATE DWORD			_ftpFilePtr;
PRIVATE SOCKADDR_IN		saServer;
BOOL initialize = TRUE;
void InitializeBowlerEthernetServer(int port){
	
    int             nResult;
	saServer.sin_port           = port;
    saServer.sin_family         = AF_INET;
	saServer.sin_addr.s_addr    = INADDR_ANY;

    _ftpListenSocket = socket(  AF_INET,
                                SOCK_STREAM,
						        IPPROTO_TCP);
	if(_ftpListenSocket == INVALID_SOCKET)
        return;
	

    nResult = bind( _ftpListenSocket,
                    (LPSOCKADDR)&saServer,
                    sizeof(struct sockaddr));
    if(nResult == SOCKET_ERROR)
    {
        closesocket(_ftpListenSocket);
		_ftpListenSocket = INVALID_SOCKET;
        return;
    }

    nResult = listen(_ftpListenSocket, 1);

    if(nResult == SOCKET_ERROR)
    {
        closesocket(_ftpListenSocket);
		_ftpListenSocket = INVALID_SOCKET;
        return;
    }
	initialize = FALSE;
	InitByteFifo(&storeRX,privateRX,sizeof(privateRX));
	return;
}

BOOL checkBowlerEthernetServer(BowlerPacket * Packet){
    //enableDebug();
    int i;

    if(initialize)
            InitializeBowlerEthernetServer(saServer.sin_port );
    int result;
    if(_ftpListenSocket == INVALID_SOCKET){
        println_I("Invalid Socket, not using");
        initialize=FALSE;
        return FALSE;
    }
    if(!_ftpConnection){
        _ftpConnection = _AcceptConnection();
    }
    if(!_ftpConnection){
            return FALSE;
    }
    /*
    int error = 0;
    socklen_t len = sizeof (error);
    if(!getsockopt (_ftpConnectionSocket, SOL_SOCKET, SO_ERROR, &error, &len )){
            _CloseConnection(_ftpConnectionSocket);
            return FALSE;
    }
    */
    _ftpStrLen = sizeof( _ftpStr);
    if((result = _GetTCPRecv(_ftpConnectionSocket, _ftpStr, &_ftpStrLen))){
        if(result == INVALID_SOCKET)
        {
            return FALSE;
        }else{
            println_I("Getting Data on Bowler Socket");
            SetColor(0,1,0);
            for(i=0;i<result;i++){
                    EthRXadd(_ftpStr[i]);
            }
        }

        if (GetBowlerPacket(Packet, & storeRX)){
            println_I("Got Eth>>");printPacket(Packet,INFO_PRINT);
            Process_Self_Packet(Packet);
            println_I("Rx Eth<<");printPacket(Packet,INFO_PRINT);
            EthTx(Packet);
            return TRUE;
        }

    }else{
       return FALSE;
    }
    return FALSE;
}


/*********************************************************************
 * Function:        PRIVATE BOOL _AcceptConnection(void)
 *
 * PreCondition:    None.
 *
 * Input:           None.
 *
 * Output:          true if there is a FTP connection, else false
 *
 * Side Effects:    None.
 *
 * Overview:        This function accepts incoming connections on the 
 *					FTP port.  If there is an incoming connection, the 
 *					socket will be assigned and the service function will
 *					be able to Rx FTP commands.
 ********************************************************************/
PRIVATE BOOL _AcceptConnection(void)
{
	SOCKET		peersocket;
	int			nlen;

	nlen        = sizeof(SOCKADDR_IN);

	peersocket  = accept(   _ftpListenSocket,
					        (LPSOCKADDR)&_ftpSockAddr,
						    &nlen);

	if(peersocket == INVALID_SOCKET)
		return FALSE;

	_ftpConnectionSocket = peersocket;
        //enableDebug();
	println_I("Connecting Bowler Socket");
	return TRUE;
}
/*********************************************************************
 * Function:        PRIVATE void _CloseConnection(SOCKET socket)
 *
 * PreCondition:    None.
 *
 * Input:           socket	- socket to close
 *
 * Output:          None.
 *
 * Side Effects:    None.
 *
 * Overview:        This function closes the socket.  If a file is 
 *					open, this function will close and initialize the
 *					pointer.  Other variables will be initialized as well
 ********************************************************************/
PRIVATE void _CloseConnection(SOCKET socket)
{
	//enableDebug();
	println_I("Disconnecting Bowler Socket");
	_ftpConnection = FALSE;
	closesocket(socket);
}
/*********************************************************************
 * Function:		PRIVATE int _GetTCPRecv(	SOCKET socket, 
 *												BYTE *data, 
 *												BYTE *data_len)        
 *
 * PreCondition:    None
 *
 * Input:           socket		- socket handle to get pending data from
 *					data		- pointer to the buffer to place the data
 *					data_len	- pointer to the size of the data gotten, it
 *									will also pass the max size of the data
 *
 * Output:          The result of the recv funciton
 *
 * Side Effects:    None
 *
 * Overview:        This function gets pending data from a socket.
 ********************************************************************/
PRIVATE int _GetTCPRecv(SOCKET socket, BYTE *data, int *data_len)
{
	int			result;
	result = recv(	socket,
					data,
					*data_len,
					0);
	if(result == SOCKET_ERROR){
		 _CloseConnection(socket);
		return INVALID_SOCKET;
	}
	if(result == 0)
		return INVALID_SOCKET;

	if(result > 0)
		*data_len = (BYTE)result;

	return result;
	
}

/*********************************************************************
 * Function:		PRIVATE int _SendData(	SOCKET socket, 
 *											BYTE *buf, 
 *											int len)
 *
 * PreCondition:	None    
 *
 * Input:           socket	- socket handle 
 *					buf		- buffer of data to send
 *					len		- size of data in bytes to transfer
 *
 * Output:          result of the send function
 *
 * Side Effects:    none
 *
 * Overview:        This funciton sends data on the TCP/IP socket. 
 *					If the data is not sent, it will return the remaining
 *					amount that needs to be sent.
 ********************************************************************/
PRIVATE int _SendData(SOCKET socket, BYTE *buf, int len)
{
	if(!(socket>0))
		return;
    int result;
	int i, size;
    result = send(  socket,
                    buf,
                    len,
                    0);

    if(result == SOCKET_ERROR){
		_CloseConnection(socket);
		return result;
	}
	if(result <= 0)					// does not include SOCKET ERROR
		return len;					// re-xmit the packet

	size = len - result;			// bytes left in the buffer
	
	if(size)
	{
		for(i = 0; i < size; i++)		// move the buffer 
			buf[i] = buf[result + i];	
	}
	return size;
}



void EthTx(BowlerPacket * Packet){
	if(!_ftpConnection)
	{
		return;
	}
	int end = BowlerHeaderSize + Packet->use.head.DataLegnth;
	int i;
	for(i=0;i<6;i++){
		Packet->use.head.MAC.v[i]=MyMAC.v[i];
	}
	SetCRC(Packet);
	_SendData(_ftpConnectionSocket, Packet->stream, end);
}
static BYTE err;
void EthRXadd(BYTE b){
	FifoAddByte(&storeRX,b,&err);
}

