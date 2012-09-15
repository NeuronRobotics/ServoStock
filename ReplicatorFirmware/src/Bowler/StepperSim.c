#include "main.h"

int current = 0;

#define INT_PIN _RA15
#define DIR_PIN _RE0


void StartStepperSim(){
    _TRISA15 = INPUT;
    _TRISE0 = INPUT;
    ConfigINT4(EXT_INT_ENABLE | RISING_EDGE_INT | EXT_INT_PRI_1);
}

int getStepperSimCurrent(){
    return current;
}

void __ISR(_EXTERNAL_4_IRQ, ipl1) INT1_ISR(void){
	if(INT_PIN){
		mINT4SetEdgeMode(0);
		if (DIR_PIN)
			current++;
		else
			current--;
	}else{
		mINT4SetEdgeMode(1);
		if (!DIR_PIN)
			current++;
		else
			current--;
	}
	Delay1us(3);//debounce
	mINT4ClearIntFlag();
}