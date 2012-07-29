#include "main.h"

void initBackplaneHardware(){
    initBackplanePowerMgmnt(); // Init Power MGMNT subsystem
    ATX_ENABLE(); // Turn on ATX Supply
    ENC_CSN_INIT(); // Set pin modes for CS pins
}
void initBackplanePowerMgmnt(){
        // Configure Relay IO
	Relay5_GPIO_TRIS = 0;
	Relay12_GPIO_TRIS = 0;
	Relay48_GPIO_TRIS = 0;

    Relay5v=Disengaged;
    Relay12v=Disengaged;
    Relay48v=Disengaged;
}

void initBackplaneVoltageSenseRelays(){
 
}

UINT16 Get5vRailVoltage(){

}

UINT16 Get12vRailVoltage(){

}

UINT16 Get48vRailVoltage(){

}