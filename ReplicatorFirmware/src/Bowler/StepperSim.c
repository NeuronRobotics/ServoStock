#include "main.h"

int current = 0;

#define INT_PIN _RE8
#define DIR_PIN _RE0


void StartStepperSim(){
    _TRISE8 = INPUT;
    _TRISE0 = INPUT;
    ConfigINT1(EXT_INT_ENABLE | RISING_EDGE_INT | EXT_INT_PRI_1);
    pidReset(EXTRUDER0_INDEX,0);
}


void __ISR(_EXTERNAL_1_IRQ, ipl1) INT1_ISR(void){
	if(INT_PIN){
		mINT1SetEdgeMode(0);
		if (DIR_PIN)
			current++;
		else
			current--;
	}else{
		mINT1SetEdgeMode(1);
		if (!DIR_PIN)
			current++;
		else
			current--;
	}
        SetPID(EXTRUDER0_INDEX,-1*current);
	//Delay1us(3);//debounce
	mINT1ClearIntFlag();
}