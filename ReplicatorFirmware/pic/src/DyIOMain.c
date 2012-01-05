
#include "Bowler/Bowler.h"
#include "DyIO/DyIO_def.h"

void buttonCheck(BYTE code){
//	StartCritical();
//	EndCritical();
	if (_RB0==1){
		p_ul(code);print(" Reset Button Pressed from loop");
		SetColor(1,1,1);
		U1CON = 0x0000;
		DelayMs(100);
		Reset();
	}
}
void runDyIOMain(void){
#if defined(__AVR_ATmega324P__)
	static BowlerPacketMini Packet;
#else
	static BowlerPacket Packet;
#endif
	Bowler_Init();// Com Stack Init. Sets up timeout timer, uart 0 and if debug enabled, uart 1
	UserInit();// User code init
	//U1IE=0;// Mask all USB interrupts
	while (1){
		//USBDeviceTasks();
		UserRun();
		Bowler_Server((BowlerPacket *) &Packet, FALSE);
		buttonCheck(0);
	}
}


