/*********************************************************************
 *
 *                  ether layer functions for TCP/IP Stack
 *
 *********************************************************************
 * FileName:        ether.c
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
 *
 ********************************************************************/
#include "_tcpip_common.h"

BYTE broadcastMAC[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

/*********************************************************************
 * Function:        WORD GetEtherRxFrameInfo( NET_PKT* sbfr )
 *
 * PreCondition:    None
 * Input:			sbfr - Pointer to New Packet received
 * Output:          None
 * Side Effects:    None
 * Overview:        This function updates packet information in the packet buffer
 * Note:
 ********************************************************************/
WORD GetEtherRxFrameInfo( NET_PKT* sbfr )
{
    ETHER_HEADER *e_hdr;

	sbfr->PktLen 	-= sizeof(ETHER_HEADER);
	if(sbfr->PktFlags&PKT_FLAG_ZC_ALLOC)
	{
		e_hdr = (ETHER_HEADER *)sbfr->PktDcpt[1].bDcpt.pBuff;
	}
	else
	{
		e_hdr = (ETHER_HEADER *)sbfr->PktDcpt[0].bDcpt.pBuff;
	}
	
	sbfr->pNetworkLayer = (BYTE*)e_hdr + sizeof(ETHER_HEADER);

	if( e_hdr->destMAC[0] & 1 )
	{
		if( memcmp( e_hdr->destMAC, broadcastMAC, ETH_ADRLEN ) == 0 )
		{
			sbfr->PktType = PKT_BROADCAST;
		}
		else
		{
			sbfr->PktType = PKT_MULTICAST;
		}
	}
	else if( memcmp( e_hdr->destMAC, SysMACAddr.v, ETH_ADRLEN ) == 0 )
	{
		sbfr->PktType = PKT_LOCAL;
	}
	else
	{
		sbfr->PktType = PKT_NON_LOCAL;
	}

	return( swaps( e_hdr->Type ) );
}

/*********************************************************************
 * Function:        void FormatEtherFrame( NET_PKT* sbfr, WORD proto, BYTE* pSrcMAC )
 *
 * PreCondition:    None
 * Input:			sbfr - Pointer to TX Packet
 *					proto - protocol to use in the ether frame
 *					pSrcMAC - pointer to MAC address of local node
 * Output:          None
 * Side Effects:    None
 * Overview:        This function updates the TX packet's MAC layer
 * Note:
 ********************************************************************/
void FormatEtherTxFrame( NET_PKT* sbfr, WORD proto, BYTE* pSrcMAC )
{
    ETHER_HEADER *hdr;

	//setup next up layer raw pointer
	// for TX the headers are always in the NET_PKT itself, pointed by the 1st buffer descriptor
	hdr = (ETHER_HEADER *)sbfr->PktDcpt[0].bDcpt.pBuff; //MacLayer pointer already setup by Alloc Buffer
	sbfr->pNetworkLayer = (BYTE*)hdr + sizeof(ETHER_HEADER);

	hdr->Type = swaps( proto );
	sbfr->PktLen = sizeof( ETHER_HEADER );
	memcpy( hdr->srcMAC, pSrcMAC, ETH_ADRLEN );
}

/*********************************************************************
 * Function:        void SetEtherTxDestMAC( NET_PKT* sbfr, BYTE* pDestMAC )
 *
 * PreCondition:    None
 * Input:			sbfr - Pointer to TX Packet
 *				pDestMAC - pointer to MAC address of remote node
 * Output:          None
 * Side Effects:    None
 * Overview:        This function updates the remote MAC address in the TX packet
 * Note:
 ********************************************************************/
void SetEtherTxDestMAC( NET_PKT* sbfr, BYTE* pDestMAC )
{
	ETHER_HEADER *hdr;

	// for TX the headers are always in the NET_PKT itself, pointed by the 1st buffer descriptor
	hdr = (ETHER_HEADER *)sbfr->PktDcpt[0].bDcpt.pBuff; // MacLayer pointer already setup by Alloc Buffer
	memcpy( hdr->destMAC, pDestMAC, ETH_ADRLEN );
}

