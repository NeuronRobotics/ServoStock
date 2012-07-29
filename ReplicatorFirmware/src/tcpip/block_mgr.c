/*********************************************************************
 *
 *                  Memory Block Manager for BSD TCPIP Stack
 *
 *********************************************************************
 * FileName:        block_mgr.c
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
 * $Id: block_mgr.c,v 1.6 2006/10/24 16:39:07 C12923 Exp $
 *
 ********************************************************************/
#include "_tcpip_common.h"

// definitions

#define BSD_DEBUG               // if debugging the stack

//#define	_BLOCK_MGR_USE_DI	// if needed to disable the interrupts

// prototypes
// 

BYTE* AllocBuffer( WORD BfrSize );

/////////////////////////////////////////////


/////////////////////////////////////////////
NET_PKT* AllocSocketBuffer( UINT16 hdrLen,  UINT16 loadLen, NET_PKT_FLAGS flags )
{
	return AllocPacketBuffer( hdrLen + sizeof(ETHER_HEADER) + sizeof(IP_HEADER), loadLen, flags );
}

/////////////////////////////////////////////
NET_PKT* AllocPacketBuffer(UINT16 hdrLen, UINT16 loadLen, NET_PKT_FLAGS flags )
{
	// we split the packet in 2: headers + load 
	NET_PKT	*pSbfr;
	UINT16	pkt1Len, pkt2Len, allocLen;
	
	allocLen = hdrLen + sizeof(NET_PKT);
	pkt1Len = hdrLen;

#ifdef _STACK_USE_ZC
	if(flags&PKT_FLAG_ZC_ALLOC)
	{	// allocate zero copy
		pkt2Len=loadLen;		// loadLen is the size of the user buffer
	}
	else
	{	// regular alloc
		allocLen+=loadLen;
		pkt1Len+=loadLen;
		pkt2Len=0;
	}
#else
	// always regular alloc
	allocLen+=loadLen;
	pkt1Len+=loadLen;
	pkt2Len=0;
	flags&=~PKT_FLAG_ZC_ALLOC;
#endif
		
	pSbfr = (NET_PKT*)AllocBuffer( allocLen );

	if( pSbfr)
	{
		memset(pSbfr, 0, sizeof(*pSbfr));
		if(pkt1Len)
		{
			pSbfr->PktDcpt[0].bDcpt.pBuff = pSbfr->pPktLoad;
			pSbfr->PktDcpt[0].bDcpt.nBytes = pkt1Len;
		}
		pSbfr->PktDcpt[0].bFlags =BUFF_MGR_ALLOC;
		pSbfr->TimeStamp = SystemTickGet();
		pSbfr->PktFlags=flags;
		
	#ifdef _STACK_USE_ZC
		pSbfr->pOwner=pSbfr;		// show the owner
		if(pkt2Len)
		{	// this is a use buffer, do not allocate space for it
			// just update the buffer info	
			pSbfr->PktDcpt[1].bDcpt.pBuff = 0;	// set by the caller!!
			pSbfr->PktDcpt[1].bDcpt.nBytes = pkt2Len;
			pSbfr->PktDcpt[1].bFlags = BUFF_ZC_ALLOC;
			// now link the buffers
			pSbfr->PktDcpt[0].bDcpt.next = &pSbfr->PktDcpt[1].bDcpt;
		}
	#endif	// _STACK_USE_ZC
	}
	
	return pSbfr;
}


/////////////////////////////////////////////
BYTE* AllocBuffer( WORD BfrSize )
{
	BYTE* ptr;
	
#ifdef _BLOCK_MGR_USE_DI
	unsigned int int_st = INTDisableInterrupts();
#endif
	
	ptr = BsdBuffMgrAlloc( BfrSize );
	
#ifdef _BLOCK_MGR_USE_DI
	INTRestoreInterrupts(int_st);
#endif	
	return ptr;
}	


///////////////////////////////////////////
void DeAllocateBuffer( NET_PKT* pBfr )
{
#ifdef _BLOCK_MGR_USE_DI
	unsigned int int_st = INTDisableInterrupts(); 
#endif
	
	if( !(pBfr->PktFlags&PKT_QUEUES_MASK) )
	{	// packet no longer part of a queue.  can deallocate
	#ifdef _STACK_USE_ZC
		if(pBfr->PktFlags&PKT_FLAG_TX)
		{
			if(pBfr->PktDcpt[1].bFlags&BUFF_ZC_ALLOC && pBfr->PktDcpt[1].bDcpt.pBuff)
			{	// this is an user buffer
				if(pBfr->buffXmitAck)
				{
					(*pBfr->buffXmitAck)(pBfr->PktDcpt[1].bDcpt.pBuff);
				}
			}
		}
		else if(pBfr->PktFlags&PKT_FLAG_RX)
		{
			if(pBfr->PktDcpt[1].bFlags&BUFF_ZC_ALLOC && pBfr->PktDcpt[1].bDcpt.pBuff)
			{	// this is an ETHC buffer
				eEthRes res=EthRxAckBuffer(pBfr->PktDcpt[1].bDcpt.pBuff, 0);
				_BsdASSERT(res==ETH_RES_OK);
			}
		}

	#endif	// _STACK_USE_ZC
		
		if(pBfr->PktDcpt[0].bFlags&BUFF_MGR_ALLOC)
		{	// this should always be the case
			BsdBuffMgrFree(pBfr);
		}
	}
				
#ifdef _BLOCK_MGR_USE_DI
	INTRestoreInterrupts(int_st);
#endif
}



