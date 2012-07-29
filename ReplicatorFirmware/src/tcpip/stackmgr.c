/*********************************************************************
 *
 *                  Stack Manager for TCP/IP Stack
 *
 *********************************************************************
 * FileName:        StackMgr.c
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended 
 * and supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip's PICmicro Microcontroller products. 
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
 *
 ********************************************************************/
#include "_tcpip_common.h"
 

#ifndef STACK_MGR_RX_PKT_CNT
#error "Please make sure that STACK_MGR_RX_PKT_CNT is defined in TCPIP-BSD-Config.h"
#endif


IP_ADDR     SysIPAddr;		// big endian
IP_ADDR 	SysIPMask;		// big-endian
IP_ADDR 	SysIPGateway;	// big-endian
MAC_ADDR    SysMACAddr;		// big-endian

int         _StackSockets=MAX_SOCKET;       // number of sockets in use

static int  _stackRxPktLim=STACK_MGR_RX_PKT_CNT;        // default value for the number of processed packets

extern PktQueue MACTxQueue;	//MAC Transmit Queue

void IP_RxHandler( NET_PKT *sbfr );
void ARP_RxHandler( NET_PKT *sbfr );
void eTCPInit();
void TCPTimer();



/*********************************************************************
 * Function:        int TCPIPInit(void)
 *
 * PreCondition:    None
 * Input:           sys_clk - system running frequency, Hz
 * Output:          TRUE if success,
 *                  FALSE if failed
 * Side Effects:    None
 * Overview:        Initialize internal stack variables
 * Note:
 ********************************************************************/
int TCPIPInit(unsigned int sys_clk)
{
	int	success;
	
	success=BsdBuffMgrInit();
	InitHostRouteTable();
	InitIPLayer();
	eTCPInit();
	success&=SocketLayerInit();

#ifdef _EMBEDDED_ETHC
	TCPIPEventInit(TCPIP_EVENT_IPL, TCPIP_EVENT_SIPL);
#endif	// _EMBEDDED_ETHC
	
	success&=TCPTickInit(TCP_TICKS_PER_SECOND);
	success&=MACInit(0);

	return success;
}

/*********************************************************************
 * Function:        void TCPIPClose(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          None
 * Side Effects:    None
 * Overview:        Releases all the allocated resources, closes the MAC layer
 * Note:
 ********************************************************************/
void TCPIPClose(void)
{
#ifdef _EMBEDDED_ETHC
    TCPIPEventClose();
#endif	// _EMBEDDED_ETHC
    TCPTickClose();
    MACClose();
    SocketLayerClose();
    BsdBuffMgrClose();
}


/*********************************************************************
 * Function:        void TCPIPSetRxProcessLimit(int rxUpLim)
 *
 * PreCondition:    None
 * Input:			rxUpLim
 * Output:          None 
 * Side Effects:    None
 * Overview:        This function sets the maximum number of RX packets that
 *                  the stack state machine can process for each call of the
 *                  TCPIPProcess() function.
 * Note:            None
 ********************************************************************/
void TCPIPSetRxProcessLimit(int rxUpLim)
{
    _stackRxPktLim=rxUpLim;   
}

/*********************************************************************
 * Function:        void TCPIPSetBuffMgrHeapSize(int nBytes)
 *
 * PreCondition:    None
 * 
 * Input:           nBytes - the size of the heap
 * 
 * Output:          None 
 * Side Effects:    None
 * Overview:        This function sets the size of the internal heap for the
 *                  BSD buffer manager.
 *                  The stack uses this heap to store data for incoming/outgoing sockets
 *                  or packets.
 *                  Define it large enough to handle the packets based on the number of TX
 *                  connections and the kind of RX traffic you want to handle.
 *                  When using ZC functionality the heap is used just for the sockets themselves,
 *                  not for packet data so the size could be much less.
 *
 * Note:            - The default value of this limit is BUFF_MGR_HEAP_SIZE
 *                    in TCPIP-BSD-Config.h
 *                  - Use before TCPIPInit().
 *                  - This heap is dinamically allocated when the TCPIPInit() is called.
 ********************************************************************/
void TCPIPSetBuffMgrHeapSize(int nBytes)
{
    BsdBuffMgrSetHeapSize(nBytes);
}


/*********************************************************************
 * Function:        void TCPIPSetSocketsNo(int nSockets, int incrNo)
 *
 * PreCondition:    None
 * 
 * Input:           nSockets - the number of requested sockets
 *                  incrNo   - reserved for future use
 * 
 * Output:          None 
 * Side Effects:    None
 * 
 * Overview:        This function sets the the number of sockets instantiated by the BSD stack.
 *                  This represents the number of all available sockets that all applications
 *                  may use.
 *                  Adjust accordingly based on the number of the middle layer protocols/apps
 *                  running.
 *
 * Note:            - The default value of this number is MAX_SOCKET
 *                    in TCPIP-BSD-Config.h
 *                  - Use before TCPIPInit().
 *                  - This memory for the sockets is dinamically allocated when the TCPIPInit() is called.
 ********************************************************************/
void TCPIPSetSocketsNo(int nSockets, int incrNo)
{
    _StackSockets=nSockets;
}



/*********************************************************************
 * Function:        void TCPIPSetMaxAckQueue(int nPackets)
 *
 * PreCondition:    None
 * 
 * Input:           nPackets - number of packets waiting to be acknowledged
 * 
 * Output:          None 
 * 
 * Side Effects:    None
 * 
 * Overview:        This function sets the maximum number of packets waiting to be acknowledged
 *                  for a socket.
 *                  When this limit is reached another transmit on that particular socket will fail.
 *                  Some previously sent packet will have to be first acknowledged before another one can be sent.
 *
 * Note:            - The default value of this limit is MAX_TCP_TX_PKT_BFR
 *                    in TCPIP-BSD-Config.h
 *                  - Use before/after TCPIPInit().
 ********************************************************************/
void TCPIPSetMaxAckQueue(int nPackets)
{
    TCPSetAckLimit(nPackets);
}

/*********************************************************************
 * Function:        void TCPIPProcess(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          TRUE is link status is up and processing ok
 *                  FALSE otherwise 
 * Side Effects:    None
 * Overview:        Executes state machine and processes of stack
 * Note:
 ********************************************************************/
int TCPIPProcess(void)
{
	int linkUp;
	
	linkUp=TCPIPProcessRx();

	linkUp&=TCPIPProcessTick();

	linkUp&=TCPIPProcessTx();

	return linkUp;	
}

/*********************************************************************
 * Function:        void TCPIPProcessRx(void)
 *
 * PreCondition:    None
 * Input:			None
 * Output:          TRUE if processing ok
 *                  FALSE otherwise
 * Side Effects:    None
 * Overview:        Executes the Rx state machine and processes of stack
 * Note:
 ********************************************************************/
int TCPIPProcessRx(void)
{
	NET_PKT *sbfr;
	WORD protocol;
	int RxPktCnt = 0;

	//Process new packets Rx
	while( RxPktCnt < _stackRxPktLim )
	{
		if( !(sbfr = MACGetRxPacket()) )
			break;

		RxPktCnt++;
		protocol = GetEtherRxFrameInfo( sbfr );

		if( protocol == ETH_PROTO_IP )
			IP_RxHandler( sbfr );
		else if( protocol == ETH_PROTO_ARP )
			ARP_RxHandler( sbfr );
		else
		{
		   	DeAllocateBuffer(sbfr);
		}
	}

	return 1;
}


/*********************************************************************
 * Function:        int TCPIPProcessTick(void)
 *
 * PreCondition:    None
 * Input:	None
 * Output:          0 if link is down
 *                  1 otherwise
 * Side Effects:    None
 * Overview:        Executes the tick based state machine and processes of stack
 * Note:
 ********************************************************************/
int TCPIPProcessTick(void)
{
	// resolve any pending ARPs
	IPProcess();
	
	// TCP Socket Timers
	TCPTimer();
	return MACCheckLink();

}


/*********************************************************************
 * Function:        int TCPIPProcessTx(void)
 *
 * PreCondition:    None
 * Input:           None
 * Output:          1 if link is up, 0 otherwise
 * Side Effects:    None
 * Overview:        Executes the Tx based state machine and processes of stack
 * Note:
 ********************************************************************/
int TCPIPProcessTx(void)
{
	//process outgoing packets sitting in TxQueue
	return MACTxProcess();
}


/*********************************************************************
 * Function:        TCPIPSetDefaultAddr       
 *
 * PreCondition:    Call before TCPIPInit   
 *
 * Input:           ipAddr, ipMask, ipGateway, hostMACAddress          
 *
 * Output:          None
 *
 * Side Effects:    Sets the IP address, IP mask, IP Gateway and
 *                  MAC address to the required values
 ********************************************************************/
void TCPIPSetDefaultAddr(const char* ipAddr, const char* ipMask, const char* ipGateway, const char* hostMACAddr)
{
    union
    {
        double      align;
        MAC_ADDR    hostAddr;
    }ua;        // aligned MAC address

    // Initialize default IP and MAC address
	SysIPAddr.Val =TCPIPAddrStrToDword( ipAddr);	
	SysIPMask.Val =TCPIPAddrStrToDword( ipMask);	
	SysIPGateway.Val=TCPIPAddrStrToDword( ipGateway);	


    MAC_StrToBin ( hostMACAddr,	ua.hostAddr.v );

#ifdef _EMBEDDED_ETHC

    if(!strncmp(hostMACAddr, DEFAULT_MAC_ADDRESS, sizeof(DEFAULT_MAC_ADDRESS)))
    {   // use the factory pre-programmed one
    	unsigned short* pS=(unsigned short*)ua.hostAddr.v;
	    *pS++=EMACxSA2;
	    *pS++=EMACxSA1;
    	*pS=EMACxSA0;
    }
#endif	// _EMBEDDED_ETHC

    // store it
    memcpy(SysMACAddr.v, ua.hostAddr.v, sizeof(ua.hostAddr.v));        
}
/*********************************************************************
 * Function:            TCPIPSetIPAddrByte      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               addr1 - addr4 Ip address in bytes
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP address with explicit bytes
 * 
 * Note:                None
 *
 * Example:             Set the IP address to 10.10.33.201 
 *                      TCPIPSetIPAddr( 10,  10, 33, 201);
 ********************************************************************/
void TCPIPSetIPAddrByte(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4)
{
    SysIPAddr.v[0] = addr1;
    SysIPAddr.v[1] = addr2;
    SysIPAddr.v[2] = addr3;
    SysIPAddr.v[3] = addr4;
    
}
/*********************************************************************
 * Function:            TCPIPSetIPAddrStr      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               ip_addr - Ip address in ASCII format
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP address
 * 
 * Note:                Set the IP address to 10.10.33.201
 *                      TCPIPSetIPAddrStr( "10.10.33.201");
 ********************************************************************/
void TCPIPSetIPAddrStr(BYTE *ip_addr)
{
	SysIPAddr.Val=TCPIPAddrStrToDword( ip_addr);	
}
/*********************************************************************
 * Function:            TCPIPGetIPAddr     
 *
 * PreCondition:        None
 *
 * Input:               None
 *
 * Output:              IP address as a 32 bit value
 *
 * Side Effects:        None
 * 
 * Note:                DWORD_VAL curr_ip =   TCPIPGetIPAddr();         
 ********************************************************************/
DWORD TCPIPGetIPAddr(void)
{
    return SysIPAddr.Val;
}


/*********************************************************************
 * Function:            TCPIPSetIPAddr      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               addr - Ip address as a 32 bit value
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP address using a 4 byte value
 * 
 * Note:                The address has to be in BE order
 *
 * Example:             Set the IP address to 10.10.33.201
 *                      DWORD curr_ip = 0x0a0a21c9;  
 *                      TCPIPSetIPAddr(curr_ip);
 ********************************************************************/
void TCPIPSetIPAddr(DWORD addr)
{
    SysIPAddr.Val=addr;    
}


/*********************************************************************
 * Function:            TCPIPSetIPMaskByte      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               addr1 - addr4 Ip mask in bytes
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP mask
 * 
 * Note:                Set the IP mask to 255.255.255.201
 *                      TCPIPSetIPMaskByte( 255,
 *                                      255,
 *                                      255,
 *                                      201);
 ********************************************************************/
void TCPIPSetIPMaskByte(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4)
{
    SysIPMask.v[0] = addr1;
    SysIPMask.v[1] = addr2;
    SysIPMask.v[2] = addr3;
    SysIPMask.v[3] = addr4;
    
}
/*********************************************************************
 * Function:            TCPIPSetIPMaskStr      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               ip_addr - Ip mask in ASCII format
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP mask
 * 
 * Note:                Set the IP mask to 255.255.255.201
 *                      TCPIPSetIPMaskStr( "255.255.255.201");
 ********************************************************************/
void TCPIPSetIPMaskStr(BYTE *ip_addr)
{
	SysIPMask.Val=TCPIPAddrStrToDword( ip_addr);	
}
/*********************************************************************
 * Function:            TCPIPGetIPMask     
 *
 * PreCondition:        None
 *
 * Input:               None
 *
 * Output:              IP mask as a 32 bit value
 *
 * Side Effects:        None
 * 
 * Note:                DWORD_VAL curr_ip =   TCPIPGetIPMask();         
 ********************************************************************/
DWORD TCPIPGetIPMask(void)
{
    return SysIPMask.Val;
}
/*********************************************************************
 * Function:            TCPIPSetIPGatewayByte      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               addr1 - addr4 Ip gateway in bytes
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP gateway
 * 
 * Note:                Set the IP gateway to 10.10.33.201
 *                      TCPIPSetIPGatewayByte(  10,
 *                                          10,
 *                                          33,
 *                                          201);
 ********************************************************************/
void TCPIPSetIPGatewayByte(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4)
{
    SysIPGateway.v[0] = addr1;
    SysIPGateway.v[1] = addr2;
    SysIPGateway.v[2] = addr3;
    SysIPGateway.v[3] = addr4;
    
}
/*********************************************************************
 * Function:            TCPIPSetIPGatewayStr      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               ip_addr - Ip gateway in ASCII format
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP gateway
 * 
 * Note:                Set the IP gateway to 10.10.33.201
 *                      TCPIPSetIPGatewayStr( "10.10.33.201");
 ********************************************************************/
void TCPIPSetIPGatewayStr(BYTE *ip_addr)
{
	SysIPGateway.Val=TCPIPAddrStrToDword( ip_addr);	
}
/*********************************************************************
 * Function:            TCPIPGetIPGateway     
 *
 * PreCondition:        None
 *
 * Input:               None
 *
 * Output:              IP gateway as a 32 bit value
 *
 * Side Effects:        None
 * 
 * Note:                DWORD_VAL curr_ip =   TCPIPGetIPGateway();         
 ********************************************************************/
DWORD TCPIPGetIPGateway(void)
{
    return SysIPGateway.Val;
}

/*********************************************************************
 * Function:            TCPIPSetIPGateway      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               addr1 - addr4 Ip gateway in bytes
 *
 * Output:              None
 *
 * Side Effects:        Sets the IP gateway as a 32 bit value
 * 
 * Note:                IP addresses are in network order (BE).
 *
 * Example:             Set the IP gateway to 10.10.33.201
 *                      DWORD addr=0x0a0a21c9;
 *                      TCPIPSetIPGateway( addr);
 ********************************************************************/
void TCPIPSetIPGateway(DWORD addr)
{
    SysIPGateway.Val=addr;

}




/*********************************************************************
 * Function:       
 *
 * PreCondition:    
 *
 * Input:           
 *
 * Output:          
 *
 * Side Effects:    
 *
 * Overview:        
 *
 * Note:           
 ********************************************************************/
void TCPIPSetMACAddr(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4, BYTE addr5, BYTE addr6)
{
    SysMACAddr.v[0] = addr1;
    SysMACAddr.v[1] = addr2;
    SysMACAddr.v[2] = addr3;
    SysMACAddr.v[3] = addr4;
    SysMACAddr.v[4] = addr5;
    SysMACAddr.v[5] = addr6;
    
}


void TCPIPSetMACAddrStr(BYTE *mac_addr)
{
	MAC_StrToBin( mac_addr, 	SysMACAddr.v );	
}

/*********************************************************************
 * Function:       
 *
 * PreCondition:    
 *
 * Input:           
 *
 * Output:          
 *
 * Side Effects:    
 *
 * Overview:        
 *
 * Note:           
 ********************************************************************/
void TCPIPGetMACAddr(MAC_ADDR *mac_addr)
{
     mac_addr->v[0] = SysMACAddr.v[0];
     mac_addr->v[1] = SysMACAddr.v[1];
     mac_addr->v[2] = SysMACAddr.v[2];
     mac_addr->v[3] = SysMACAddr.v[3];
     mac_addr->v[4] = SysMACAddr.v[4];
     mac_addr->v[5] = SysMACAddr.v[5];
    
}

/*********************************************************************
 * Function:       
 *
 * PreCondition:    
 *
 * Input:           
 *
 * Output:          
 *
 * Side Effects:    
 *
 * Overview:        
 *
 * Note:           
 ********************************************************************/
const MAC_ADDR* TCPIPGetMACAddrStr(void)
{
    return &SysMACAddr;
}


/****************************************************************************
 * Function:        TCPIPAddrStrToDword
 *
 * PreCondition:    None
 *
 * Input:           szDot - an IP address in standard dot notation 
 *
 * Output:          The IP address as an BE dword.
 *
 * Side Effects:    None
 *
 * Overview:        Converts a dot-address string to big-endian dword.
 *
 * Note:            None
 * 
 * Example:        DWORD myAddr=TCPIPAddrStrToDword("192.168.2.105");         
 ******************************************************************************/
DWORD TCPIPAddrStrToDword(const char* szDot)
{
	DWORD_VAL dw;
	const char* pip;
	char c;

    int index = 0;
	BYTE acc = 0;
	dw.Val = 0;
	pip = szDot;
	
	while( (c = *pip++) ) 
	{
        if( c == '.' )
		{
            dw.v[index++] = acc;
            acc = 0;
        }
		else if( c == ' ' )
			continue;
		else 
            acc = acc*10 + (c - '0');
    }

    dw.v[3] = acc;
    return dw.Val;

}



