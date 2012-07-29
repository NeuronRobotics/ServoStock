/*********************************************************************
 *
 *            BSD TCPIP Stack Control API Header File
 *
 *********************************************************************
 * FileName:        tcpip_bsd_control.h
 * Description:     Control API for BSD TCPIP Stack
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
 * This file includes parts which are Copyright (c) 1982-1986 Regents
 * of the University of California.  All rights reserved.  The
 * Berkeley Software License Agreement specifies the terms and
 * conditions for redistribution.
 *
 *
*/

#ifndef _TCPIP_BSD_CONTROL_H_
#define _TCPIP_BSD_CONTROL_H_


/*************************
     Stack Interface and configuration functions
 ************************/

/*********************************************************************
 * Function:        void TCPIPInit(unsigned int sys_clk)
 *
 * PreCondition:    None
 * Input:           sys_clk - system running frequency, Hz
 * Output:          TRUE if successful,
 *                  FALSE otherwise
 * Side Effects:    None
 * Overview:        Initialize internal stack variables,
 *                  allocates resources, opens the MAC layer
 * Note:
 ********************************************************************/
int TCPIPInit(unsigned int sys_clk);


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
void TCPIPClose(void);


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
int TCPIPProcess(void);

/*********************************************************************
 * Function:        void TCPIPSetRxProcessLimit(int rxUpLim)
 *
 * PreCondition:    None
 * Input:           rxUpLim - upper limits for RX packets to be processed
 * Output:          None 
 * Side Effects:    None
 * Overview:        This function sets the maximum number of RX packets that
 *                  the stack state machine can process for each call of the
 *                  TCPIPProcess() function.
 *
 * Note:            - The default value of this limit is STACK_MGR_RX_PKT_CNT
 *                    in TCPIP-BSD-Config.h
 *                  - Can be used before/after TCPIPInit().
 ********************************************************************/
void TCPIPSetRxProcessLimit(int rxUpLim);

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
void TCPIPSetBuffMgrHeapSize(int nBytes);

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
void TCPIPSetSocketsNo(int nSockets, int incrNo);

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
void TCPIPSetMaxAckQueue(int nPackets);


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
 *                  
 * Note:            The addresses have to be in BE order
 ********************************************************************/
void TCPIPSetDefaultAddr(const char* ipAddr, const char* ipMask, const char* ipGateway, const char* hostMACAddr);


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
void TCPIPSetIPAddr(DWORD addr);



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
 * Note:                The address has to be in BE order
 *
 * Example:             Set the IP address to 10.10.33.201 
 *                      TCPIPSetIPAddr( 10,  10, 33, 201);
 ********************************************************************/
void TCPIPSetIPAddrByte(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4);

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
 * Note:                The address has to be in BE format
 * 
 * Example:             Set the IP address to 10.10.33.201
 *                      TCPIPSetIPAddrStr( "10.10.33.201");
 ********************************************************************/
void TCPIPSetIPAddrStr(BYTE *ip_addr);

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
 * Note:                None         
 * 
 * Example:             DWORD_VAL curr_ip =   TCPIPGetIPAddr();         
 ********************************************************************/
DWORD TCPIPGetIPAddr(void);

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
 * Note:                None
 *
 * Example:             Set the IP mask to 255.255.255.201
 *                      TCPIPSetIPMaskByte( 255, 255, 255, 201);
 ********************************************************************/
void TCPIPSetIPMaskByte(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4);

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
 * Note:                None
 *
 * Example:             Set the IP mask to 255.255.255.201
 *                      TCPIPSetIPMaskStr( "255.255.255.201");
 ********************************************************************/
void TCPIPSetIPMaskStr(BYTE *ip_addr);

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
 * Note:                None
 *
 * Example:             DWORD_VAL curr_ip =   TCPIPGetIPMask();         
 ********************************************************************/
DWORD TCPIPGetIPMask(void);

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
 * Note:                IP addresses are in network order (BE).
 *
 * Example:             Set the IP gateway to 10.10.33.201
 *                      TCPIPSetIPGatewayByte( 10, 10, 33, 201);
 ********************************************************************/
void TCPIPSetIPGatewayByte(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4);

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
 * Note:                IP addresses are in network order (BE).
 *
 * Example:             Set the IP gateway to 10.10.33.201
 *                      TCPIPSetIPGatewayStr( "10.10.33.201");
 ********************************************************************/
void TCPIPSetIPGatewayStr(BYTE *ip_addr);


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
void TCPIPSetIPGateway(DWORD addr);


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
 * Note:                IP addresses are in network order (BE).
 *
 * Example:             DWORD_VAL curr_ip =   TCPIPGetIPGateway();         
 ********************************************************************/
DWORD TCPIPGetIPGateway(void);

/*********************************************************************
 * Function:            TCPIPSetMACAddr      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               addr1 - addr6 MAC address in bytes
 *
 * Output:              None
 *
 * Side Effects:        Sets the MAC address
 * 
 * Note:                None
 *
 * Example:             Set the MAC address to 00-04-a3-00-00-02
 *                      TCPIPSetMACAddr(0x00, 0x04, 0xa3, 0x00, 0x00, 0x02);
 ********************************************************************/
void TCPIPSetMACAddr(BYTE addr1, BYTE addr2, BYTE addr3, BYTE addr4, BYTE addr5, BYTE addr6);

/*********************************************************************
 * Function:            TCPIPSetMACAddrStr      
 *
 * PreCondition:        Call before TCPIPInit   
 *
 * Input:               mac_addr - MAC address in ASCII format
 *
 * Output:              None
 *
 * Side Effects:        Sets the MAC address
 * 
 * Note:                None
 *
 * Example:             Set the MAC address to 00-04-a3-00-00-02
 *                      TCPIPSetMACAddrStr( "00-04-a3-00-00-02");
 ********************************************************************/
void TCPIPSetMACAddrStr(BYTE *mac_addr);

/*********************************************************************
 * Function:            TCPIPGetMACAddr     
 *
 * PreCondition:        None
 *
 * Input:               MAC address as a 6 byte array value
 *
 * Output:              None
 *
 * Side Effects:        None
 * 
 * Note:                None
 *
 * Note:                MAC_ADDR mac_addr;
 *                      TCPIPGetMACAddr(&mac_addr);         
 ********************************************************************/
void TCPIPGetMACAddr(MAC_ADDR *mac_addr);

/*********************************************************************
 * Function:            TCPIPGetMACAddrStr     
 *
 * PreCondition:        None
 *
 * Input:               None
 *
 * Output:              None
 *
 * Side Effects:        None
 * 
 * Note:                None
 *
 * Example:             const MAC_ADDR* pMacAddr=TCPIPGetMACAddrStr();         
 ********************************************************************/
const MAC_ADDR* TCPIPGetMACAddrStr(void);

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
DWORD   TCPIPAddrStrToDword(const char* szDot);


/**********************************
 *        Stack event notifications
 ****************************************/


#if (( (__PIC32_FEATURE_SET__ >= 500) && (__PIC32_FEATURE_SET__ <= 799) && defined (_ETH) && defined(MAC_EMBEDDED_PIC32) ))

/*  Ethernet notifications are available
    when running with an embedded Ethernet Controller.
    If you're running on a PIC32MX7 family define MAC_EMBEDDED_PIC32 in TCPIP-BSD-Config.h 
 * ***********************************************/



typedef enum
{
    TCPIP_EV_NONE       = 0x0000,       // no event
    // normal transfer events that are passed from the stack to the user
    // and can be processed by the stack
    // if processed by the stack they don't need to be acknowledged
    TCPIP_EV_TXDONE     = 0x0008,       // a packet was transmitted and it's status is available
    TCPIP_EV_RXDONE     = 0x0080,       // a packet was sucessfully received
    TCPIP_EV_TICK       = 0x80000000,   // TCP tick occurred
    //
    TCPIP_EV_STACK_PROCESSED= (TCPIP_EV_TXDONE|TCPIP_EV_RXDONE|TCPIP_EV_TICK),  // all events processed by the stack
    //  
    // events that are passed from the stack to the user
    // no default processing is provided for these events
    // they need to be aknowledged in order to be re-enabled
    TCPIP_EV_RXOVFLOW   = 0x0001,       // RX FIFO overflow (system level latency, no descriptors, etc.)            
    TCPIP_EV_RXBUFNA    = 0x0002,       // no descriptor available to receive a new packet
    TCPIP_EV_TXABORT    = 0x0004,       // a transmit packet was aborted by the MAC (jumbo/system underrun/excessive defer/late collision/excessive collisions)
    TCPIP_EV_RXACT      = 0x0020,       // there's data available in the RX FIFO 
    TCPIP_EV_PKTPEND    = 0x0040,       // a receive packet is pending
    TCPIP_EV_FWMARK     = 0x0100,       // the number of received packets is >= than the RX Full Watermark
    TCPIP_EV_EWMARK     = 0x0200,       // the number of received packets is <= than the RX Empty Watermark
    TCPIP_EV_RXBUSERR   = 0x2000,       // RX DMA encountered a bus error during a transfer
    TCPIP_EV_TXBUSERR   = 0x4000,       // TX DMA encountered a bus error during a transfer
    //
    TCPIP_EV_ERRORS     = (TCPIP_EV_RXOVFLOW|TCPIP_EV_RXBUFNA|TCPIP_EV_TXABORT|TCPIP_EV_RXBUSERR|TCPIP_EV_TXBUSERR),    // events showing some abnormal traffic/system condition
    //
    //
    TCPIP_EV_ALL        = 0xffffffff        // all of the above         
}eTCPIPEvent;   // list of the events that can be reported by the TCPIP stack




typedef void (*pTCPIPEventF)(eTCPIPEvent);      // TCPIP event notification handler
                                                // called from within an ISR


/****************************************************************************
 * Function:        TCPIPEventSetNotifyEvents
 *
 * PreCondition:    TCPIPInit should have been called.
 *
 * Input:           eventFlags - events the user of the stack wants to add for notification 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets new enabled events.
 *                  Multiple events can be orr-ed together.
 *                  All events that are set will be added to the notification process. The other events will not ne touched.
 *                  The stack user has to catch the events that are notified and process them:
 *                   - use them eventually in a call to TCPIPEventProcess(). The stack will process only the normal transfer events
 *                   - process the specific condition and acknowledge them calling TCPIPEventAck() so that they can be re-enabled.
 *
 * Note:            - The event notification system enables the user of the TCPIP stack to call into the stack
 *                    for processing only when there are relevant events rather than being forced to periodically call
 *                    from within a loop.
 *                  - If the notification events are nill the interrupt processing will be disabled.
 *                    Otherwise the event notification will be enabled and the interrupts relating to the requested events will be enabled.
 *                  - Note that once an event has been caught by the stack ISR (and reported to the user if a notification handler is in place)
 *                    it will be disabled until the user calls TCPIPEventProcess()/TCPIPEventAck().
 ******************************************************************************/
void    TCPIPEventSetNotifyEvents(eTCPIPEvent eventFlags);

/****************************************************************************
 * Function:        TCPIPEventClearNotifyEvents
 *
 * PreCondition:    TCPIPInit should have been called.
 *
 * Input:           eventFlags - pointer to the events the user of the stack wants to remove from notification 
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function removes from the enabled events.
 *                  Multiple events can be orr-ed together.
 *                  All events that are set will be removed from the notification process. The other events will not ne touched.
 *
 * Note:            - If the notification events are nill the interrupt processing will be disabled.
 *                    Otherwise the event notification will be enabled and the interrupts relating to the requested events will be enabled.
 ******************************************************************************/
void    TCPIPEventClearNotifyEvents(eTCPIPEvent eventFlags);

/****************************************************************************
 * Function:        TCPIPEventAck
 *
 * PreCondition:    TCPIPInit should have been called.
 *
 * Input:           eventFlags - the events that the user processed and need to be re-enabled
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function acknowledges and re-enables processed events.
 *                  Multiple events can be orr-ed together as they are processed together.
 *                  The events acknowledged by this function should be the events that have been retrieved from the stack
 *                  by calling TCPIPEventGetPending() or have been passed to the user by the stack using the notification handler
 *                  (TCPIPEventSetNotifyHandler()) and have been processed and have to be re-enabled.
 *
 * Note:            - There's no acknowledge needed for the normal transfer events: TCPIP_EV_TXDONE, TCPIP_EV_RXDONE and TCPIP_EV_TICK;
 *                    These events are acknowledged using the TCPIPEventProcess().
 *                  - Some events are fatal errors and should not be acknowledged (TCPIP_EV_RXBUSERR, TCPIP_EV_TXBUSERR).
 *                    Stack re-initialization is needed under such circumstances.
 *                  - Some events are just system/application behavior and they are intended only as simple info (TCPIP_EV_RXOVFLOW,
 *                    TCPIP_EV_RXBUFNA, TCPIP_EV_TXABORT, TCPIP_EV_RXACT, TCPIP_EV_PKTPEND).
 *                  - The TCPIP_EV_FWMARK and TCPIP_EV_EWMARK events are part of the normal flow control operation (if auto flow control was enabled).
 *                    They should be enabled alternatively, if needed.
 *                  - The events are persistent. They shouldn't be re-enabled unless they have been processed and the condition that generated them was removed.
 *                    Re-enabling them immediately without proper processing will have dramatic effects on system performance.
 *                    
 ******************************************************************************/
void    TCPIPEventAck(eTCPIPEvent eventFlags);


/****************************************************************************
 * Function:        TCPIPEventGetPending
 *
 * PreCondition:    TCPIPInit should have been called.
 *
 * Input:           None
 *
 * Output:          the stack pending events
 *
 * Side Effects:    None
 *
 * Overview:        This function returns the currently pending events that have to be processed.
 *                  Multiple events can be orr-ed together as they accumulate.
 *                  The user should call back into the stack whenever a stack managed event is present (TCPIPEventProcess()).
 *                  The user is supposed to process the other events not managed by the stack and
 *                  eventually acknowledge them if re-enabling is needed.
 *                  
 *
 * Note:            - This is the preferred method to get the current pending stack events.
 *                    The stack maintains a proper image of the events from their occurrence to their acknowledgement.
 *                  - Even with a notification handler in place it's better to use this function to get the current pending events
 *                    rather than using the events passed by the notification handler which could be stale.
 *                  - The events are persistent. They shouldn't be re-enabled unless they have been processed and the condition that generated them was removed.
 *                    Re-enabling them immediately without proper processing will have dramatic effects on system performance.
 *                    
 ******************************************************************************/
eTCPIPEvent TCPIPEventGetPending(void);


/****************************************************************************
 * Function:        TCPIPEventSetNotifyHandler
 *
 * PreCondition:    TCPIPInit should have been called.
 *
 * Input:           eventHandler - the event notification handler
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function sets the a new event notification handler.
 *                  This is a handler specified by the user of the stack.
 *                  The caller can use the handler to be notified of stack events.
 *                  Whenever a notification occurs the passed events have be eventually processed:
 *                   - call the TCPIPEventProcess() if stack processed events are reported
 *                   - process the specific (error) condition and acknowledge them calling TCPIPEventAck() so that they can be re-enabled.
 *
 * Note:            - The notification handler will be called from the ISR which detects the corresponding event.
 *                    The event notification handler has to be kept as short as possible and non-blocking.
 *                    Mainly useful for RTOS integration where this handler will wake-up a thread that waits for a stack event to occur.
 *                  - The event notification system enables the user of the TCPIP stack to call into the stack
 *                    for processing only when there are relevant events rather than being forced to periodically call
 *                    from within a loop at unknown moments.
 *                  - Without a notification handler the stack user can still call TCPIPEventGetPending() to see if processing by the stack needed.
 *                  - This is a default way of adding interrupt processing to the stack. The user can write a separate ISR to catch the ETHC
 *                    events and process accordingly. 
 ******************************************************************************/
void    TCPIPEventSetNotifyHandler(pTCPIPEventF eventHandler);


/****************************************************************************
 * Function:        TCPIPEventProcess
 *
 * PreCondition:    TCPIPInit, TCPIPEventSetNotifyEvents should have been called.
 *
 * Input:           eventFlags - the events the stack that were asserted by calling the event notification handler
 *
 * Output:          TRUE if the link is up and processing ok
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function processes the events that have been reported by the stack (multiple events can be reported orr-ed together).
 *                  The processing is meant only for the normal transfer events: TCPIP_EV_TXDONE, TCPIP_EV_RXDONE and TCPIP_EV_TICK.
 *                  Other events are not processed by this call. They should be processed by the application.
 *                   
 *
 * Note:            - The call advances the internal TCPIP state machine. It's intended as a more efficient replacement
 *                    for the TCPIPProcess(). Using the event notification system the processing is done only when there's a need to do so.
 *                  - The TCPIPEventProcess() can be called even when notification is not enabled (TCPIPEventSetNotifyEvents() has not been called).
 *                    The call will behave the same as TCPIPProcess() and serves as an unique entry point.
 ******************************************************************************/
int TCPIPEventProcess(eTCPIPEvent eventFlags);




#endif  // (( (__PIC32_FEATURE_SET__ >= 500) && (__PIC32_FEATURE_SET__ <= 799) && defined (_ETH) && defined(MAC_EMBEDDED_PIC32) ))


#endif  // _TCPIP_BSD_CONTROL_H_

