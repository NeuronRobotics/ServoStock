/*********************************************************************
 *
 *     MAC Module (Microchip ENC28J60) for Microchip TCP/IP Stack
 *
 *********************************************************************
 * FileName:        emac.c
 * Dependencies:    see the include section below
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
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
 * $Id: ENC28J60.c,v 1.7 2006/10/24 16:39:06 C12923 Exp $
 *
********************************************************************/
#include "_tcpip_common.h"

#ifdef _EMBEDDED_ETHC

#include "TCPIP-BSD/eth_phy.h"



/** D E F I N I T I O N S ****************************************************/


#define LINK_REFRESH_MS 100     // refresh link status time, ms

typedef struct
{
    void*           pOwner;         // Stack reserved field: the owner of a received buffer
    unsigned long   data[0];        // the revceive buffer itself
}sRxBuffDcpt;   // descriptor of a buffer used for RX


typedef union
{
    sBuffDcpt   bDcpt;

    void*       padding[(sizeof(sBuffDcpt)+sizeof(void*)-1)/sizeof(void*)]; // alignment padding
}uRxPktDcpt;    // descriptor of a RX packet (consisting potentially of multiple buffers)
    
  

/** LOCAL DATA ****************************************************/

// default opening modes
//
static eEthOpenFlags    _stackOFlags=EMAC_OPEN_LINK;      // default opening flags

#ifdef PHY_RMII
    #ifdef PHY_CONFIG_ALTERNATE
    static eEthPhyCfgFlags  _stackCfgFlags=ETH_PHY_CFG_RMII|ETH_PHY_CFG_ALTERNATE;  
    #else
    static eEthPhyCfgFlags  _stackCfgFlags=ETH_PHY_CFG_RMII|ETH_PHY_CFG_DEFAULT;  
    #endif
#else // PHY_MII
    #ifdef PHY_CONFIG_ALTERNATE
    static eEthPhyCfgFlags  _stackCfgFlags=ETH_PHY_CFG_MII|ETH_PHY_CFG_ALTERNATE;  
    #else
    static eEthPhyCfgFlags  _stackCfgFlags=ETH_PHY_CFG_MII|ETH_PHY_CFG_DEFAULT;  
    #endif
#endif
// default PHY configuration


static eEthRxFilters        _stackRxFlags=(ETH_FILT_CRC_ERR_REJECT|ETH_FILT_RUNT_REJECT|ETH_FILT_ME_UCAST_ACCEPT|ETH_FILT_MCAST_ACCEPT|ETH_FILT_BCAST_ACCEPT);
// default RX filtering


static int          _stackRxDcptsNo=EMAC_RX_DESCRIPTORS;      // default number of RX descriptors/buffers
static int          _stackRxBuffSize=EMAC_RX_BUFF_SIZE;      // default size of the RX buffer

static int          _stackTxDcptsNo=EMAC_TX_DESCRIPTORS;      // default number of TX descriptors


// run-time data

static uRxPktDcpt*       _stackRxPktDcpt=0;          // array of rx buffer descriptors

static sRxBuffDcpt**     _stackRxBuffers= 0;        // array of pointers to rx buffers for incoming data 


static PktQueue         _stackMACTxQueue;          // Transmission delayed packets (because of not enough TX descriptors). Need to be re-scheduled



// timing and link status maintenance
static TICK             _linkUpdTick;                       // last tick value when the link update was started
static eEthLinkStat     _linkPrev;                          // last value of the link status
static int              _linkPresent;                       // if connection to the PHY properly detected
static int              _linkNegotiation;                   // if an auto-negotiation is in effect



/*static*/ int  _stackMgrRxAllocFails=0;
/*static*/ int  _stackMgrRxBadPkts=0;
/*static*/ int  _stackMgrTxDelayed=0;


/** LOCAL Prototypes ****************************************************/

static BOOL     XmitPkt( NET_PKT* sbfr );
static void     XmitAcknowledge(void);
static BOOL     XmitPendingPkts(void);
static void     XmitAckCBack(void* pBuff, int buffIx);

static int      _LinkReconfigure(int waitComplete);                     // link reconfiguration



/*
 * interface functions
 *
*/

/****************************************************************************
 * Function:        MACSetOpenFlags
 *
 * PreCondition:    None
 *
 * Input:           oFlags  - flags for opening the Eth communication link
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function sets the flags to be used for the opening of the Eth link,
 *                  i.e. the flags used for EthOpen() call.
 *                  Call it before MACInit().
 *
 * Note:            None 
 *****************************************************************************/
void MACSetOpenFlags(eEthOpenFlags oFlags)
{
    _stackOFlags=oFlags;        
}

/****************************************************************************
 * Function:        MACSetPhyConfigFlags
 *
 * PreCondition:    None
 *
 * Input:           cfgFlags  - flags for configuring the PHY
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function sets the flags to be used for the configuration of the PHY
 *                  i.e. the flags used for EthPhyInit() call.
 *                  Call it before MACInit().
 *
 * Note:            None 
 *****************************************************************************/
void MACSetPhyConfigFlags(eEthPhyCfgFlags cfgFlags)
{
    _stackCfgFlags=cfgFlags;        
}


/****************************************************************************
 * Function:        MACSetRxFilters
 *
 * PreCondition:    None
 *
 * Input:           rxFilters  - RX filters for configuring the MAC
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function sets the RX filters to be used for the configuration of the MAC
 *                  i.e. the flags used for EthRxFiltersSet() call.
 *                  Call it before MACInit().
 *
 * Note:            None 
 *****************************************************************************/
void MACSetRxFilters(eEthRxFilters rxFilters)
{
    _stackRxFlags=rxFilters;        
}

/****************************************************************************
 * Function:        MACSetRxDescriptors
 *
 * PreCondition:    None
 *
 * Input:           rxDescriptors   - number of RX descriptors to be used
 *                  rxBuffSize      - size of each buffer 
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function sets the RX descriptors and buffer sizes.
 *                  The reception process will use these buffers.
 *                  Call it before MACInit().
 *
 * Note:            None 
 *****************************************************************************/
void MACSetRxDescriptors(int rxDescriptors, int rxBuffSize)
{
    _stackRxDcptsNo=rxDescriptors;
    _stackRxBuffSize=rxBuffSize;  
}

/****************************************************************************
 * Function:        MACSetTxDescriptors
 *
 * PreCondition:    None
 *
 * Input:           txDescriptors   - number of TX descriptors to be used
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function sets the TX descriptors.
 *                  The transmission process will use the allocated number of deswcriptors.
 *                  Call it before MACInit().
 *
 * Note:            None 
 *****************************************************************************/
void MACSetTxDescriptors(int txDescriptors)
{
    _stackTxDcptsNo=txDescriptors;
}



/****************************************************************************
 * Function:        MACInit
 *
 * PreCondition:    None
 *
 * Input:           waitComplete - wait for auto-negotiation to complete
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function initializes the Eth controller, the MAC and the PHY. It should be called to be able to schedule
 *                  any Eth transmit or receive operation.
 *
 * Note:           The flags used for EthOpen() call are fixed for now. This will change in the future! 
 *****************************************************************************/
int MACInit(int waitComplete)
{
    int     ix;
    uRxPktDcpt* pRxDcpt;
    eEthRes     ethRes, phyInitRes;
    int     success=0;

    _stackMgrRxAllocFails=_stackMgrRxBadPkts=0;

    // Init transmit holding queue
    Que_Init( &_stackMACTxQueue );

    
    _linkNegotiation=_linkPresent=0;
    _linkPrev=ETH_LINK_ST_DOWN;
    
    while(1)
    {
        eEthLinkStat    linkStat;
        eEthOpenFlags   linkFlags;
        eMacPauseType   pauseType;
        int             rxPktDcpts;
        

        pauseType=(_stackOFlags&ETH_OPEN_FDUPLEX)?MAC_PAUSE_CPBL_MASK:MAC_PAUSE_TYPE_NONE;
        
        // start the initialization sequence    
        EthInit();

        phyInitRes=EthPhyInit(_stackOFlags, _stackCfgFlags, &linkFlags);

        if(phyInitRes!=ETH_RES_OK)
        {
            break;
        }

        // let the auto-negotiation (if any) take place
        // continue the initialization
        EthRxFiltersClr(ETH_FILT_ALL_FILTERS);
        EthRxFiltersSet(_stackRxFlags);

        
        EthMACSetAddress(SysMACAddr.v);
                
        if(EthDescriptorsAdd(_stackTxDcptsNo, ETH_DCPT_TYPE_TX, 0)!=_stackTxDcptsNo)
        {
            break;
        }

        if(EthDescriptorsAdd(_stackRxDcptsNo, ETH_DCPT_TYPE_RX, 0)!=_stackRxDcptsNo)
        {
            break;
        }

        EthRxSetBufferSize(_stackRxBuffSize);

        // allocate RX packet descriptors
        rxPktDcpts=MAX_ETHERNET_FRAME_SZ/_stackRxBuffSize+2;        // number of such descriptors
        _stackRxPktDcpt=(uRxPktDcpt*)calloc(rxPktDcpts, sizeof(uRxPktDcpt));
        if(!_stackRxPktDcpt)
        {
              break;    // failed
        }

        for(ix=0, pRxDcpt=_stackRxPktDcpt; ix<rxPktDcpts; ix++)
        {
            pRxDcpt->bDcpt.next=&((pRxDcpt+1)->bDcpt);
            pRxDcpt++;
        }
        _stackRxPktDcpt[ix-1].bDcpt.next=0; // end properly

        // allocate memory for the rx buffers
        _stackRxBuffers=(sRxBuffDcpt**)calloc(_stackRxDcptsNo, sizeof(sRxBuffDcpt*));
        if(!_stackRxBuffers)
        {
            break;
        }

        for(ix=0; ix<_stackRxDcptsNo; ix++)
        {
            unsigned char*  pRxBuff;
            
            if(!(_stackRxBuffers[ix]=(sRxBuffDcpt*)malloc(sizeof(sRxBuffDcpt)+_stackRxBuffSize)))
            {
                break;
            }
            // set this buffer as permanent receive buffers
            pRxBuff=(unsigned char*)_stackRxBuffers[ix]->data;
            ethRes=EthRxBuffersAppend((void *)&pRxBuff, 1, BUFF_FLAG_RX_STICKY);
            if(ethRes!=ETH_RES_OK)
            {
                break;
            }
        }

        if(ix!=_stackRxDcptsNo)
        {   // either allocation or the buffer append failed
            break;
        }
        

        // continue the MAC set-up based on the (possible) PHY negotiation
        _linkPresent=1;     // show we have valid connection to the PHY
        if(_stackOFlags&ETH_OPEN_AUTO)
        {   // have to wait the negotiation to be done
            _linkNegotiation=1;     // PHY performing negotiation if unplugged/plugged       
            linkStat=_LinkReconfigure(waitComplete)?ETH_LINK_ST_UP:ETH_LINK_ST_DOWN;    // if negotiation not done yet we need to try it next time
        }
        else
        {   // no need of negotiation results; just update the MAC 
            EthMACOpen(linkFlags, pauseType);
            linkStat=EthPhyGetLinkStatus(0);
        }

        _linkUpdTick=SystemTickGet();     // the last time we performed the link read
        _linkPrev=linkStat;
        
        success=1;
        break;
    }

    if(!success)
    {
        MACClose();
    }
    
    return success;
    
}


/****************************************************************************
 * Function:        MACClose
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *                
 * Side Effects:    None
 *
 * Overview:        This function performs a clean-up of the resources allocated by the MAC
 *                  It also disables Eth controller, without changing the set-up.
 *                  Any Eth transmit or receive operation i saborted.
 *
 * Note:            None 
 *****************************************************************************/
void MACClose(void)
{
        int ix;
        
        EthClose(0);

        EthDescriptorsCleanUp(ETH_DCPT_TYPE_ALL, 0);

        if(_stackRxPktDcpt)
        {
            free(_stackRxPktDcpt);
            _stackRxPktDcpt=0;
        }

        if(_stackRxBuffers)
        {
            for(ix=0; ix<_stackRxDcptsNo; ix++)
            {
                free(_stackRxBuffers[ix]);
                _stackRxBuffers[ix]=0;
            }
            free(_stackRxBuffers);
            _stackRxBuffers=0;
        }
    
}




/****************************************************************************
 * Function:        MACTxProcess
 *
 * PreCondition:    MACInit should have been called
 *
 * Input:           None
 *
 * Output:          TRUE if link is up 
 *                
 * Side Effects:    None
 *
 * Overview:        This function processes the transmit side of the stack.
 *                  It's main function is to acknowledge the transmitted packets and to schedule for transmission
 *                  packets for which we didn't have TX descriptors available.
 *                  
 *
 * Note:            It should be called whenever the Eth controller signals that transmission of a scheduled packet
 *                  has completed. It can also be called on a periodic basis. 
 *****************************************************************************/
int MACTxProcess(void)
{
    NET_PKT* pPktBfr;

    XmitAcknowledge();

    // Make sure link is up. If not discard the Tx Queue
    if( !MACIsLinked() )
    {
        //link is down. empty the queue
        while( Que_GetHead( &_stackMACTxQueue, &pPktBfr ) )
        {
            pPktBfr->PktFlags &= ~MACTX_QUE_MASK;
            
            if( pPktBfr->PktFlags&PKT_TX_AUTO_DEALLOC )
                DeAllocateBuffer( pPktBfr );
        }
        return 0;
    }


    // link up
    XmitPendingPkts();

    return 1;
    
}

/****************************************************************************
 * Function:        MACGetRxPacket
 *
 * PreCondition:    MACInit should have been called
 *
 * Input:           None
 *
 * Output:          a pointer to a received packet
 *                  0 if no packet available
 *                
 * Side Effects:    None
 *
 * Overview:        This function retrieves received packets
 *
 * Note:            None 
 *****************************************************************************/
NET_PKT* MACGetRxPacket(void)
{
    int         buffsPerRxPkt;
    const sRxPktStat*   pRxPktStat;
    eEthRes         res;
    NET_PKT*        pNetPkt=0;
    




    res=EthRxGetPacket(&_stackRxPktDcpt->bDcpt, &buffsPerRxPkt, &pRxPktStat);
    
    if(res==ETH_RES_OK)
    {   // available packet; minimum check
        int keepEthPkt=0;   // the Eth RX pkt discarded or not

        if(pRxPktStat->rxOk && !pRxPktStat->runtPkt && !pRxPktStat->crcError)
        {   // valid packet; calculate size
            int     pktIx, pktSize;
            NET_PKT_FLAGS   pktFlags;
            sBuffDcpt*  pPktDcpt;
        
            pktSize=pRxPktStat->rxBytes;
        #ifdef _STACK_USE_ZC
            pktFlags=(buffsPerRxPkt==1)?PKT_FLAG_RX|PKT_FLAG_ZC_ALLOC:PKT_FLAG_RX;      // if the packet is noncontiguous will have to allocate space and copy it.
                                                    // very inefficient!
        #else
            pktFlags=PKT_FLAG_RX;                               // no ZC support, always copy it, always inefficient!
        #endif
            // Get a new NET_PKT for this packet
            pNetPkt = (NET_PKT*)AllocPacketBuffer(0, pktSize, pktFlags);        // there's no header here, everything is one big packet/load
            if(pNetPkt)
            {
                // save packet size
                pNetPkt->PktLen=pktSize;
                if(pktFlags&PKT_FLAG_ZC_ALLOC)
                {
                    pNetPkt->PktDcpt[1].bDcpt.pBuff = _stackRxPktDcpt->bDcpt.pBuff; // set our buffer
                    keepEthPkt=1;   // ok, will use the Eth RX buffer which will be acknowledged eventually
                #ifdef _STACK_USE_ZC
                    sRxBuffDcpt* pRxDcpt=(sRxBuffDcpt*)(_stackRxPktDcpt->bDcpt.pBuff-offsetof(sRxBuffDcpt,data ));              
                    pRxDcpt->pOwner=pNetPkt;    // store the packet we belong to. Space reserved for us
                #endif  // _STACK_USE_ZC
                }
                else
                {   // fragmented/!ZC packet, have to copy it to the stack's own buffer...
                    // the owner is already set
                    unsigned char* pDest=(unsigned char*)pNetPkt->PktDcpt[0].bDcpt.pBuff;
                    for(pktIx=0, pPktDcpt=&_stackRxPktDcpt->bDcpt; pktIx<buffsPerRxPkt; pktIx++)
                    {
                        memcpy(pDest, pPktDcpt->pBuff, pPktDcpt->nBytes);
                        pDest+=pPktDcpt->nBytes;
                        pPktDcpt=pPktDcpt->next;
                    }
                }
            }
            else
            {
                _stackMgrRxAllocFails++;
            }
        }
        else
        {
            _stackMgrRxBadPkts++;
        }
        
        if(!keepEthPkt)
        {   // done with this packet, acknowledge
            res=EthRxAckPacket(&_stackRxPktDcpt->bDcpt, 0);
            _BsdASSERT(res==ETH_RES_OK);
        }
    }
    
    return pNetPkt;
}

/****************************************************************************
 * Function:        MACTransmit
 *
 * PreCondition:    MACInit should have been called
 *
 * Input:           sbfr - packet pointer
 *
 * Output:          TRUE if the packet is scheduled for transmission
 *                  FALSE if some error occurred
 *
 * Side Effects:    None
 *
 * Overview:        This function schedules a packet for transmission
 *
 * Note:            None 
 *****************************************************************************/
BOOL MACTransmit( NET_PKT* sbfr )
{
    BOOL isScheduled=0; 

    XmitAcknowledge();  // acknowledge already transmitted packets
    
    sbfr->PktFlags |= MACTX_QUE_MASK;   // flag it in use

    // see if anything pending...don't transmit out of order
    if(XmitPendingPkts())
    {   // ok, no other pending packets
        isScheduled=XmitPkt(sbfr);
    }
        
    if(!isScheduled)    
    {   // delayed, store it for later
        Que_AddTail( &_stackMACTxQueue, sbfr );
    }
    
    return TRUE;
}

/****************************************************************************
 * Function:        XmitPkt
 *
 * PreCondition:    None
 *
 * Input:           sbfr - packet pointer
 *
 * Output:          TRUE if the packet is sent
 *                  FALSE if not enough descriptors for the operation
 *
 * Side Effects:    None
 *
 * Overview:        This function tries to schedule a packet for transmission
 *
 * Note:            None 
 *****************************************************************************/
static BOOL XmitPkt( NET_PKT* sbfr )
{
    eEthRes     res;
    
    res=EthTxSendPacket(&sbfr->PktDcpt[0].bDcpt);

    if(res==ETH_RES_NO_DESCRIPTORS)
    {   // ok, no more descriptors, we have to try later
        _stackMgrTxDelayed++;
        return FALSE;
    }
    
    _BsdASSERT(res==ETH_RES_OK);    // want to catch this one
        
    return TRUE;
}

/****************************************************************************
 * Function:        XmitPendingPkts
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if all the pending packets are sent
 *                  FALSE if still pending
 *
 * Side Effects:    None
 *
 * Overview:        This function deals with the packets that could not be transmitted because of not enough TX descriptors.
 *
 * Note:            None 
 *****************************************************************************/
static BOOL XmitPendingPkts(void)
{
    NET_PKT*    head;
    
    while((head=_stackMACTxQueue.pFirst))
    {
        if(XmitPkt(head))
        {   // packet scheduled, remove from the queue
            Que_GetHead(&_stackMACTxQueue, &head);
        }
        else
        {   // try later 
            return FALSE;
        }
    }

    
    return TRUE;    // completed the queue
}




/****************************************************************************
 * Function:        XmitAcknowledge
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function acknowledges the buffers scheduled for transmission by the Eth controller.
 *
 * Note:            None 
 *****************************************************************************/
static void XmitAcknowledge(void)
{
    EthTxAckPacket(0, XmitAckCBack);
}


/****************************************************************************
 * Function:        XmitAckCBack
 *
 * PreCondition:    None
 *
 * Input:           pBuff - TX buffer to be acknowledged
 *                  buffIx - index of the buffer for multiple buffer packets
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function acknowledges the buffers scheduled for transmission.
 *                  It is called by the Eth API as a result of EthTxAckPacket() and should be called for each buffer in turn.
 *
 * Note:            None 
 *****************************************************************************/
static void XmitAckCBack(void* pBuff, int buffIx)
{
    _BsdASSERT(pBuff!=0);

    if(buffIx==0)
    {   
        NET_PKT* sbfr=(NET_PKT*)((char*)pBuff-offsetof(NET_PKT, pPktLoad));

        _BsdASSERT((sbfr->PktFlags&MACTX_QUE_MASK)!=0);
        sbfr->PktFlags &= ~MACTX_QUE_MASK;
        if(sbfr->PktFlags&PKT_TX_AUTO_DEALLOC)
        {
            DeAllocateBuffer(sbfr);
        }
    }
}


/****************************************************************************
 * Function:        MACIsLinked
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if link is up
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function checks the link status
 *
 * Note:            None 
 *****************************************************************************/
BOOL MACIsLinked(void)
{
    return (_linkPrev&ETH_LINK_ST_UP)!=0;
}



/****************************************************************************
 * Function:        MACCheckLink
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          TRUE if link is up
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function periodically checks the link status
 *                  performing the MAC reconfiguration if the link went up
 *                  after being down.
 *
 * Note:            None 
 *****************************************************************************/
BOOL MACCheckLink(void)
{
    while(_linkPresent)
    {
        eEthLinkStat    linkCurr;
        TICK            currTick=SystemTickGet();
    
        if(currTick-_linkUpdTick< (TICKS_PER_SECOND/1000)*LINK_REFRESH_MS)
        {   // not time to do anything yet
            break;
        }

        linkCurr=EthPhyGetLinkStatus(0);    // read current PHY status
        _linkUpdTick=currTick;          // start a new counting period

        if(_linkNegotiation)
        {   // the auto-negotiation turned on
            if((linkCurr&ETH_LINK_ST_UP) && !(_linkPrev&ETH_LINK_ST_UP))
            {   // we're up after being done. do renegotiate!
                linkCurr=_LinkReconfigure(0)?ETH_LINK_ST_UP:ETH_LINK_ST_DOWN;    // if negotiation not done yet we need to try it next time
            }
            // else link went/still down; nothing to do yet
        }
        _linkPrev=linkCurr;
    
        break;
    }

    return (_linkPrev&ETH_LINK_ST_UP)!=0;

}



/*********************************************************************
* Function:        int  _LinkReconfigure(int waitComplete)
 *
 * PreCondition:    None
 * 
 * Input:           waitComplete    -  wait for negotiation to be done
 * 
 * Output:          TRUE if negotiation succeeded and MAC was updated
 *                  FALSE otherwise
 * 
 * Side Effects:    None
 * 
 * Overview:        Performs re-configuration after auto-negotiation performed.
 * 
 * Note:            None
 ********************************************************************/
static int _LinkReconfigure(int waitComplete)
{

    eEthOpenFlags   linkFlags;
    eEthLinkStat    linkStat;
    eMacPauseType   pauseType;
    int             success=0;

    if(EthPhyNegotiationComplete(waitComplete)==ETH_RES_OK)
    {    // negotiation complete
        linkStat=EthPhyGetNegotiationResult(&linkFlags, &pauseType);
        if(linkStat&ETH_LINK_ST_UP)
        {   // negotiation succeeded; properly update the MAC
    #ifdef PHY_RMII
            EthMIIMInit(GetSystemClock(), EthPhyMIIMClock(), linkFlags, 1);
        #else
            EthMIIMInit(GetSystemClock(), EthPhyMIIMClock(), linkFlags, 0);
        #endif
            EthMACOpen(linkFlags, pauseType);
            success=1;
        }
    }

    return success;
}


#endif  // _EMBEDDED_ETHC


