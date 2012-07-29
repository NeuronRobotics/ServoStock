/*********************************************************************
 *
 *                 BSD TcpIp Stack events implementation 
 *
 *********************************************************************
 * FileName:        tcpip_events.c
 * Dependencies:
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * Microchip Audio Library – PIC32 Software.
 * Copyright © 2008 Microchip Technology Inc.  All rights reserved.
 * 
 * Microchip licenses the Software for your use with Microchip microcontrollers
 * and Microchip digital signal controllers pursuant to the terms of the
 * Non-Exclusive Software License Agreement accompanying this Software.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION,
 * ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS
 * FOR A PARTICULAR PURPOSE.
 * MICROCHIP AND ITS LICENSORS ASSUME NO RESPONSIBILITY FOR THE ACCURACY,
 * RELIABILITY OR APPLICATION OF THE SOFTWARE AND DOCUMENTATION.
 * IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED
 * UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH
 * OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL,
 * SPECIAL, INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS
 * OR LOST DATA, COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY,
 * SERVICES, OR ANY CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED
 * TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *
 *$Id: $
 ********************************************************************/

#include "_tcpip_common.h"


#ifdef _EMBEDDED_ETHC


/*************************
 * local data
 *************************/
pTCPIPEventF		_TcpNotifyFnc=0;		// user notification handler
eEthEvents		_TcpEnabledEvents=0;	// user enabled notification events
volatile eEthEvents	_TcpPendingEvents=0;	// notification events that are set, waiting to be re-acknowledged


/*********************************
 *  local definitions
 ******************************************/

/*********************************
 *  local proto 
 ******************************************/

static void	_TcpIpEventAck(eTCPIPEvent eventFlags);


/****************************************************************************
 * Function:        _XtlEventsTcp2Eth
 *
 * PreCondition:    None
 *
 * Input:           tcpipEvents - the TcpIp events to be translated
 *
 * Output:          Ethernet events
 *
 * Side Effects:    None
 *
 * Overview:        This function translates from  events to Ethernet events
 *
 * Note:            The translation is automatic for now!
 ******************************************************************************/
static __inline__ eEthEvents __attribute__((always_inline)) _XtlEventsTcp2Eth(eTCPIPEvent tcpipEvents)
{
	return (eEthEvents)tcpipEvents;
}

/****************************************************************************
 * Function:        _XtlEventsEth2Tcp
 *
 * PreCondition:    None
 *
 * Input:           eEvents - the Eth events to be translated
 *
 * Output:          TcpIp events
 *
 * Side Effects:    None
 *
 * Overview:        This function translates from Ethernet events to TcpIp events
 *
 * Note:            The translation is automatic for now!
 ******************************************************************************/
static __inline__ eTCPIPEvent __attribute__((always_inline)) _XtlEventsEth2Tcp(eEthEvents eEvents)
{
	return (eTCPIPEvent)eEvents;
}

/*********************************
 *  implementation
 ******************************************/



/****************************************************************************
 * Function:        TCPIPEventInit
 *
 * PreCondition:    None.
 *
 * Input:           intPri    - interrupt priority to use
 *                  intSubPri - interrupt sub-priority to use
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function initializes the ethernet event notification.
 *
 * Note:            None
 ******************************************************************************/
void TCPIPEventInit(int intPri, int intSubPri)
{

	INTEnable(INT_ETHERNET, INT_DISABLED);		// stop Eth ints
	INTClearFlag(INT_ETHERNET);
	INTSetVectorPriority(INT_ETH_VECTOR, (INT_PRIORITY_LEVEL_1-1)+intPri);
	INTSetVectorSubPriority(INT_ETH_VECTOR, INT_SUB_PRIORITY_LEVEL_0+intSubPri);

	_TcpNotifyFnc=0;
	_TcpEnabledEvents=_TcpPendingEvents=0;
	

}

/****************************************************************************
 * Function:        TCPIPEventClose
 *
 * PreCondition:    None.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function closes the ethernet event notification.
 *
 * Note:            None
 ******************************************************************************/
void TCPIPEventClose(void)
{

	INTEnable(INT_ETHERNET, INT_DISABLED);		// stop Eth ints
	INTClearFlag(INT_ETHERNET);

	_TcpNotifyFnc=0;
	_TcpEnabledEvents=_TcpPendingEvents=0;
}


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
 * Note:            - The event notification system enables the user of the Tcp/Ip stack to call into the stack
 *                    for processing only when there are relevant events rather than being forced to periodically call
 *                    from within a loop.
 *                  - If the notification events are nill the interrupt processing will be disabled.
 *                    Otherwise the event notification will be enabled and the interrupts relating to the requested events will be enabled.
 *                  - Note that once an event has been caught by the stack ISR (and reported to the user if a notification handler is in place)
 *                    it will be disabled until the user calls TCPIPEventProcess()/TCPIPEventAck().
 ******************************************************************************/
void TCPIPEventSetNotifyEvents(eTCPIPEvent eventFlags)
{
	eEthEvents	setEvents;
	
	if(_TcpEnabledEvents!=0)
	{	// already have some active		
		INTEnable(INT_ETHERNET, INT_DISABLED);		// stop ints for a while
	}
	
	setEvents=_XtlEventsTcp2Eth(eventFlags);
	_TcpEnabledEvents|=setEvents;		// add more 
	
	if(_TcpEnabledEvents!=0)
	{
		setEvents&=~_TcpPendingEvents;		// keep just the new un-ack events
		EthEventsClr(setEvents);		// clear the old pending ones
		EthEventsEnableSet(setEvents);		// enable the new un-ack ones!
		
		INTEnable(INT_ETHERNET, INT_ENABLED);	// re-enable
	}
			
}



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
void TCPIPEventClearNotifyEvents(eTCPIPEvent eventFlags)
{
	eEthEvents	clrEvents;
	
	if(_TcpEnabledEvents!=0)
	{	// already have some active		
		INTEnable(INT_ETHERNET, INT_DISABLED);		// stop ints for a while
	}

	clrEvents=_XtlEventsTcp2Eth(eventFlags);
	clrEvents&=_TcpEnabledEvents;		// keep just the enabled ones
	_TcpEnabledEvents&=~clrEvents;		// clear some of them
	_TcpPendingEvents&=~clrEvents;		// remove them from un-ack list
	
	EthEventsEnableClr(clrEvents);		// no longer enabled
	EthEventsClr(clrEvents);		// clear the pending ones

    if(_TcpEnabledEvents!=0)
	{
		INTEnable(INT_ETHERNET, INT_ENABLED);	// re-enable
	}

}

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
void TCPIPEventAck(eTCPIPEvent eventFlags)
{
	_TcpIpEventAck(eventFlags&(~TCPIP_EV_STACK_PROCESSED));		// stack events are acknowledged by TCPIPEventProcess(); 
}


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
eTCPIPEvent TCPIPEventGetPending(void)
{
	return _XtlEventsEth2Tcp(_TcpPendingEvents);
}

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
 *                  - The event notification system enables the user of the Tcp/Ip stack to call into the stack
 *                    for processing only when there are relevant events rather than being forced to periodically call
 *                    from within a loop at unknown moments.
 *                  - Without a notification handler the stack user can still call TCPIPEventGetPending() to see if processing by the stack needed.
 *                  - This is a default way of adding interrupt processing to the stack. The user can write a separate ISR to catch the ETHC
 *                    events and process accordingly. 
 ******************************************************************************/
void TCPIPEventSetNotifyHandler(pTCPIPEventF eventHandler)
{
	
	if(_TcpEnabledEvents!=0)
	{	// already have some active		
		INTEnable(INT_ETHERNET, INT_DISABLED);		// stop ints for a while

		_TcpNotifyFnc=eventHandler;		// set new handler
	
		INTClearFlag(INT_ETHERNET);
		INTEnable(INT_ETHERNET, INT_ENABLED);	// re-enable
	}
	else
	{
		_TcpNotifyFnc=eventHandler;		// set new handler
	}
}

/****************************************************************************
 * Function:        TCPIPEventProcess
 *
 * PreCondition:    TCPIPInit, TCPIPEventSetNotifyEvents should have been called.
 *
 * Input:           eventFlags - the events the stack that were asserted by calling the event notification handler
 *
 * Output:          TRUE if link up and processing ok,
 *                  FALSE otherwise
 *
 * Side Effects:    None
 *
 * Overview:        This function processes the events that have been reported by the stack (multiple events can be reported orr-ed together).
 *                  The processing is meant only for the normal transfer events: TCPIP_EV_TXDONE, TCPIP_EV_RXDONE and TCPIP_EV_TICK.
 *                  Other events are not processed by this call. They should be processed by the application.
 *                   
 *
 * Note:            - The call advances the internal TcpIp state machine. It's intended as a more efficient replacement
 *                    for the TCPIPProcess(). Using the event notification system the processing is done only when there's a need to do so.
 *                  - The TCPIPEventProcess() can be called even when notification is not enabled (TCPIPEventSetNotifyEvents() has not been called).
 *                    The call will behave the same as TCPIPProcess() and serves as an unique entry point.
 ******************************************************************************/
int TCPIPEventProcess(eTCPIPEvent eventFlags)
{

	int	linkUp;
	
	if(_TcpEnabledEvents==0)
	{
		return TCPIPProcess();		// fake all
	}

	
	// notification enabled
	// we don't use the user passed events that can be stale
	eTCPIPEvent procEvents=TCPIP_EV_NONE;
	linkUp=1;		
	
	if(_XtlEventsEth2Tcp(_TcpPendingEvents)&TCPIP_EV_RXDONE)
	{
		linkUp&=TCPIPProcessRx();
		procEvents|=TCPIP_EV_RXDONE;
	}

	if(_XtlEventsEth2Tcp(_TcpPendingEvents)&TCPIP_EV_TICK)
	{
		linkUp&=TCPIPProcessTick();
		procEvents|=TCPIP_EV_TICK;
	}

	if(_XtlEventsEth2Tcp(_TcpPendingEvents)&TCPIP_EV_TXDONE)
	{
		linkUp&=TCPIPProcessTx();	
		procEvents|=TCPIP_EV_TXDONE;
	}

	
	if(procEvents!=TCPIP_EV_NONE)
	{
		_TcpIpEventAck(procEvents);	// processed
	}

	return linkUp;	
}

/**************************************
 * local functions
 ****************************************/


/****************************************************************************
 * Function:        _TcpIpEventAck
 *
 * PreCondition:    TCPIPInit should have been called.
 *
 * Input:           eventFlags - the events that the user processed and need to be re-enabled
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Internal function to acknowledge and re-enable processed events.
 *                  Same as the interface one except it can clear any kind of events passed to it.
 *                  
 *
 * Note:            None
 ******************************************************************************/
static void _TcpIpEventAck(eTCPIPEvent eventFlags)
{
	if(_TcpEnabledEvents!=0)
	{	// already have some active		
		eEthEvents	ackEvents;

		ackEvents=_XtlEventsTcp2Eth(eventFlags);

		INTEnable(INT_ETHERNET, INT_DISABLED);		// stop ints for a while

		ackEvents&=_TcpPendingEvents;			// keep just the pending ones
		_TcpPendingEvents&=~ackEvents;			// no longer pending


		EthEventsClr(ackEvents);		// clear the old pending ones
		EthEventsEnableSet(ackEvents);		// re-enable the ack ones
		
		INTEnable(INT_ETHERNET, INT_ENABLED);	// re-enable
	}

}



/****************************************************************************
 * Function:        _TcpIpEthIsr
 *
 * PreCondition:    TCPIPInit, TCPIPEventSetNotifyEvents should have been called.
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function processes the Ethernet interrupts and reports the events back to the user.
 *
 * Note:            None
 ******************************************************************************/
void __attribute__((vector(_ETH_VECTOR), interrupt, nomips16, weak)) _TcpIpEthIsr(void)
{
	eEthEvents	currEvents;

	currEvents=EthEventsGet()&_TcpEnabledEvents;	// keep just those that are relevant
	_TcpPendingEvents|=currEvents;			// add the new events

	EthEventsEnableClr(currEvents);			// these will get reported; disable them until ack is received back
	
	EthEventsClr(currEvents);			// acknowledge the ETHC

	if(_TcpNotifyFnc)
	{
		(*_TcpNotifyFnc)(_XtlEventsEth2Tcp(_TcpPendingEvents));		// let the user know
	}

	INTClearFlag(INT_ETHERNET);			// acknowledge the INTC
}




#endif	// _EMBEDDED_ETHC

