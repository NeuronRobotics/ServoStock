#include <plib.h>
#include "tcpip_bsd_config.h"
#include <TCPIP-BSD/tcpip_bsd.h>

#define initLed()		_TRISD0 = OUTPUT;_TRISD1 = OUTPUT;_TRISD2 = OUTPUT;
#define initButton() 	_TRISD6  = INPUT;_TRISD7  = INPUT;_TRISD13 = INPUT;CNPUESET=0x00098000;
#define isPressed()		( _RD6==0 || _RD7==0 || _RD13==0)
#define setLed(a,b,c) 	_RD0=a;_RD1=b;_RD2=c;

#if (( (__PIC32_FEATURE_SET__ < 500) || (__PIC32_FEATURE_SET__ > 799) || !defined (_ETH) || !defined(MAC_EMBEDDED_PIC32) ))
	#error "This demo is supossed to run on PIC32MX5-7 family with embedded Ethernet Controller!"
#endif

#if !defined (ETH_STARTER_KIT)
	#error "This demo is supposed to run on an Ethernet STarter Kit board. Define the ETH_STARTER_KIT symbol!"
#endif
#include "hardware_profile.h"
#include "system_services.h"
#include "Bowler/Bowler.h"

// notification function
void	TCPIPEventCB(eTCPIPEvent event);

void	ProcessTCPIPError(eTCPIPEvent errEvent);	
void	ProcessLinkError(void);

void setEthLEDs(int a, int b, int c);
BOOL isEthButtonPressed();

void InitializeEthernet();
BOOL RunEthernetServices(BowlerPacket * Packet);

void LoadCorePacket(BowlerPacket * Packet);
void push(BowlerPacket * Packet);
void pushEncoders(void);

