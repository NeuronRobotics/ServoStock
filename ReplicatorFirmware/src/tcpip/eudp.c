/*********************************************************************
 *
 *                  UPD Layer for TCP/IP Stack
 *
 *********************************************************************
 * FileName:        udp.c
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

// Header struct to calculate udp checksum
struct tempHdr
{
	DWORD   srcIP;
	DWORD   DstIP;
	BYTE    filler;
	BYTE    proto;
	WORD    len;
};


/*********************************************************************
 * Function:        int UDPTransmit( BYTE* buf, int loadLen, struct MCSocket* pSocket, 
 *					DWORD remoteIP, WORD remotePort )
 *
 * PreCondition:    None
 * Input:			loadBuff      - data pointer
 *					loadLen      - data length
 *					pSocket  - socket to use
 *					remoteIP - destination ip address
 *					remotePort - destination port number
 * Output:          returns number of bytes sent, or -1 on error
 * Side Effects:    None
 * Overview:        Packages and transmits a udp data packet
 * Note:
 ********************************************************************/
int UDPTransmit( BYTE* loadBuff, int loadLen, struct MCSocket* pSocket, DWORD remoteIP, WORD remotePort )
{
	UDP_HEADER*	pUDP;
	WORD		totSize;
	DWORD		csum;
	struct tempHdr	vhdr;
	NET_PKT*	sbfr; 
	NET_PKT_FLAGS	pktFlags;
	

	totSize = sizeof(UDP_HEADER) + loadLen;
	pktFlags=PKT_FLAG_TX|PKT_TX_AUTO_DEALLOC;
	if(pSocket->sockFlags&SOCK_FLAG_ZCOPY)
	{
		pktFlags|=PKT_FLAG_ZC_ALLOC;
	}

	sbfr = AllocSocketBuffer( sizeof(UDP_HEADER), loadLen, pktFlags);
	if( sbfr == NULL )	//make sure we have good buffer
	{
		return SOCKET_BFR_ALLOC_ERROR;
	}

	IP_FormatPacket( sbfr, remoteIP, IP_PROT_UDP, totSize );

	pUDP = 	(UDP_HEADER*)sbfr->pTransportLayer;

	pUDP->Checksum			= 0;
	pUDP->SourcePort		= swaps(pSocket->localPort);
	pUDP->DestinationPort 	= swaps(remotePort);
	pUDP->Length         	= swaps(totSize);

	csum = 0;
	
#ifdef _STACK_USE_ZC
	if(pktFlags & PKT_FLAG_ZC_ALLOC)
	{	// ZC: put owr own buffer here
		sbfr->PktDcpt[1].bDcpt.pBuff = loadBuff;
		sbfr->buffXmitAck=pSocket->sockXmitAck;

		checksum16_partial((BYTE*)pUDP, sizeof(UDP_HEADER), &csum);
		checksum16_partial(loadBuff, loadLen, &csum);
	}
	else
	{	// one big buffer
		memcpy( ((BYTE*)pUDP) + sizeof(UDP_HEADER), loadBuff, loadLen );
		checksum16_partial((BYTE*)pUDP, totSize, &csum);
	}
#else
	memcpy( ((BYTE*)pUDP) + sizeof(UDP_HEADER), loadBuff, loadLen );
	checksum16_partial((BYTE*)pUDP, totSize, &csum);
#endif	// _STACK_USE_ZC	
	
	vhdr.srcIP	= SysIPAddr.Val;
	vhdr.DstIP	= remoteIP;
	vhdr.filler = 0;
	vhdr.proto 	= IP_PROT_UDP;
	vhdr.len	= pUDP->Length;

	checksum16_partial((BYTE*)&vhdr, sizeof(struct tempHdr), &csum );
	pUDP->Checksum	= ~fold_checksum( csum );
	
	IP_TransmitPkt( sbfr );
	return loadLen;
}


/*********************************************************************
 * Function:        int UDPExtractData( NET_PKT *RxPkt, BYTE* bfr, int len )
 *
 * PreCondition:    None
 * Input:			RxPkt - Raw UDP Packet
 *					bfr - data buffer to receive data
 *					len - buffer length
 * Output:          returns number of bytes copied to app buffer, or -1 on error
 * Side Effects:    None
 * Overview:        this function taked the raw data packet and 
 *					extracts the data portion and copies it to the application
 *					buffer
 * Note:
 ********************************************************************/
int UDPExtractData( NET_PKT *RxPkt, BYTE* bfr, int len )
{
	UDP_HEADER* pUDP;
	BYTE *pData;
	WORD DataLen;

	pUDP = (UDP_HEADER*)RxPkt->pTransportLayer;

	pData = RxPkt->pTransportLayer + sizeof(UDP_HEADER);

	DataLen = pUDP->Length;
	
	if( len < DataLen ) //bfr length is not enough for the entire packet
		DataLen = len;

	memcpy( bfr, pData, DataLen );
	return DataLen;
}

/*********************************************************************
 * Function:        void UDP_RxHandler( NET_PKT *RxPkt )
 *
 * PreCondition:    None
 * Input:			RxPkt - Raw UDP Packet received
 * Output:          None
 * Side Effects:    None
 * Overview:        Process new udp message received
 * Note:
 ********************************************************************/
void UDP_RxHandler( NET_PKT *RxPkt )
{
	UDP_HEADER* pUDP;
	SOCKET sk;
	struct MCSocket* pSock = NULL;
    DWORD   src_ip, dest_ip;


	pUDP = (UDP_HEADER*)RxPkt->pTransportLayer;
	src_ip = _arrayToDword(((IP_HEADER*)(RxPkt->pNetworkLayer))->SourceAddr);
	dest_ip = _arrayToDword(((IP_HEADER*)(RxPkt->pNetworkLayer))->DestAddr);

#if UDP_VERIFY_CHECKSUM
    if(pUDP->Checksum!=0xffff)
    {   // transmitter generated a checksum
        struct tempHdr  vhdr;
    	DWORD           csum=0;

        // calculate packet checksum
     	checksum16_partial((BYTE*)pUDP, swaps(pUDP->Length), &csum );
        // add the pseudo header
        vhdr.srcIP	= src_ip;
        vhdr.DstIP 	= dest_ip;
        vhdr.filler = 0;
        vhdr.proto 	= IP_PROT_UDP;
        vhdr.len	= pUDP->Length;
        checksum16_partial((BYTE*)&vhdr, sizeof(struct tempHdr), &csum );
        csum= (WORD)~fold_checksum( csum );

        if(csum != 0)
        {   // wrong packet checksum, discard
       		DeAllocateBuffer(RxPkt);
            return;
        }
    }
#endif  // UDP_VERIFY_CHECKSUM

    
    pUDP->SourcePort        = swaps(pUDP->SourcePort);
    pUDP->DestinationPort   = swaps(pUDP->DestinationPort);
    pUDP->Length            = swaps(pUDP->Length) - sizeof(UDP_HEADER);;
    pUDP->Checksum          = swaps(pUDP->Checksum);

	if( (sk = FindTargetSocket(SOCK_DGRAM, src_ip, dest_ip, pUDP->DestinationPort)) != INVALID_SOCKET )
	{
		pSock = &SocketArray[sk];
		Que_AddTail( &pSock->RxMsgQueue, RxPkt ); //Add packet to socket incoming msg queue
		RxPkt->PktFlags |= RXMSG_QUE_MASK;
	}
	else
	{
		//no matching socket found - discard
   		DeAllocateBuffer(RxPkt);
	}
}

