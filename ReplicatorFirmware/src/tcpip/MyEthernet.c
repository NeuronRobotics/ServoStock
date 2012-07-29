#include "EthernetController.h"


volatile int	newStackEvent=0;	
volatile int	totStackEvents=0;	

//#define STACK_USE_POLLING
#define STACK_USE_DHCP

int		ethErrorEventCnt=0;			// number of errors that occurred
int     ethErrorEvent=0;            // the errors that occurred
int     ethRxOvflCnt=0;             // RX overflow count: the most important error; shows if the PIC32 system can keep up with the incoming data flow

int		ethLinkDownCnt=0;			// link down counter
int     ethLinkWasUp=0;             // flag to tell if the link was detected up (we might start with the link down or negotiation not performed)



IP_ADDR	curr_ip;
unsigned int 	sys_clk, pb_clk;

BOOL isEthButtonPressed(){
	_TRISD6  = 1;
	_TRISD7  = 1;
	_TRISD13 = 1;
	CNPUESET=0x00098000;
	if( _RD6==0 || _RD7==0 || _RD13==0)
		return TRUE;
	return FALSE;
}

void setEthLEDs(int a, int b, int c){
	_TRISD0 = 0;
	_TRISD1 = 0;
	_TRISD2 = 0;
	_RD0=a;
	_RD1=b;
	_RD2=c;
}

void InitializeEthernet(){
	sys_clk=GetSystemClock();
	pb_clk=SYSTEMConfigWaitStatesAndPB(sys_clk);
	// Turn on the interrupts
	INTEnableSystemMultiVectoredInt();

    //Turn ON the system clock
    SystemTickInit(sys_clk, TICKS_PER_SECOND);

    // Initialize the TCP/IP
	TCPIPSetDefaultAddr(DEFAULT_IP_ADDR, DEFAULT_IP_MASK, DEFAULT_IP_GATEWAY, DEFAULT_MAC_ADDR);
	if(!TCPIPInit(sys_clk)){
		//return 0;
	}
	
		
#if defined(STACK_USE_DHCP)
		DHCPInit();
#endif
	
	curr_ip.Val = 0;

#if !defined(STACK_USE_POLLING)
		TCPIPEventSetNotifyHandler(TCPIPEventCB);
		TCPIPEventSetNotifyEvents(TCPIP_EV_STACK_PROCESSED|TCPIP_EV_ERRORS);
#endif
	InitializeBowlerEthernetServer(1965);
}

BOOL RunEthernetServices(BowlerPacket * Packet){
        int linkUpdated=0;
        int	linkOk=0;
#if !defined(STACK_USE_POLLING)
        if(newStackEvent){
                eTCPIPEvent	activeEvent;
                newStackEvent = 0;
                activeEvent = TCPIPEventGetPending();
                if(activeEvent & TCPIP_EV_STACK_PROCESSED) {
                        linkOk = TCPIPEventProcess(activeEvent);
                        linkUpdated = 1;
                }
                if(activeEvent&TCPIP_EV_ERRORS){	// some error has occurred
                        ProcessTCPIPError(activeEvent);
                }

        }
#else
                linkOk=TCPIPEventProcess(0);
                linkUpdated=1;
#endif

        if(linkUpdated){
            if(linkOk){
                ethLinkWasUp=1;
            }
            else if(ethLinkWasUp){
                ProcessLinkError();     // link is actually down only if it was up before
            }
        }

#if defined(STACK_USE_DHCP)
        IP_ADDR ip;
        DHCPTask();

        if(curr_ip.Val != (ip.Val = TCPIPGetIPAddr())){   // board has changed the address
            curr_ip.Val = ip.Val;
        }
#endif
        return checkBowlerEthernetServer(Packet);
}


// TCPIP event notification handler
void TCPIPEventCB(eTCPIPEvent event)
{
	newStackEvent++;
	totStackEvents++;

}

void ProcessTCPIPError(eTCPIPEvent errEvent)
{
	// some error has occurred...
	// take a snapshot of the ETh Controller status
	
	sEthDcptQuery	rxQuery, txQuery;
	
	ethRxOvflCnt+=EthStatRxOvflCnt();
	
	EthDescriptorsQuery(ETH_DCPT_TYPE_RX, &rxQuery);
	EthDescriptorsQuery(ETH_DCPT_TYPE_TX, &txQuery);

	if(errEvent&TCPIP_EV_ERRORS){
            ethErrorEvent|=errEvent;
                    ethErrorEventCnt++;
            TCPIPEventAck(errEvent);
        }
        println_E("TCP Error!!");
}
	

void ProcessLinkError(void)
{
	// link is down...
	ethLinkDownCnt++;
	return;		// just ignore it for now
}


