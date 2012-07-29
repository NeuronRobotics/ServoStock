#include "main.h"

void initBackplaneHardware(){
    initBackplanePowerMgmnt(); // Init Power MGMNT subsystem
    ATX_ENABLE(); // Turn on ATX Supply
    ENC_CSN_INIT(); // Set pin modes for CS pins

    OpenSPI1(CLK_POL_ACTIVE_LOW\
            |SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON\
            |MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);
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