/* 
 * File:   main.c
 * Author: aim
 *
 * Created on July 27, 2012, 10:23 PM
 */

#include "main.h"
#include "GenericTypeDefs.h"
#include "plib.h"

#ifdef USB_A0_SILICON_WORK_AROUND
	#pragma config UPLLEN   = OFF       // USB PLL Enabled (A0 bit inverted)
#else
	#pragma config UPLLEN   = ON        // USB PLL Enabled
#endif

#pragma config FPLLMUL  = MUL_20        // PLL Multiplier
#pragma config UPLLIDIV = DIV_2         // USB PLL Input Divider
#pragma config FPLLIDIV = DIV_2         // PLL Input Divider
#pragma config FPLLODIV = DIV_1         // PLL Output Divider
#pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor

#pragma config FWDTEN   = OFF           // Watchdog Timer
//#pragma config FWDTEN   = ON          // Watchdog Timer

#pragma config WDTPS    = PS2048           // Watchdog Timer Postscale
#pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
#pragma config OSCIOFNC = OFF           // CLKO Enable
#pragma config POSCMOD  = EC            // Primary Oscillator
#pragma config IESO     = ON            // Internal/External Switch-over
#pragma config FSOSCEN  = ON            // Secondary Oscillator Enable (KLO was off)
#pragma config FNOSC    = PRIPLL        // Oscillator Selection
#pragma config CP       = OFF           // Code Protect
#pragma config BWP      = OFF           // Boot Flash Write Protect
#pragma config PWP      = OFF           // Program Flash Write Protect
#pragma config ICESEL   = ICS_PGx2      // ICE/ICD Comm Channel Select
#pragma config DEBUG    = OFF            // Background Debugger Enable

/*
 * 
 */



void main() {

    
    ATX_ENABLE(); // Turn on ATX Supply
    ENC_CSN_INIT(); // Set pin modes for CS pins

    OpenSPI1(CLK_POL_ACTIVE_LOW\
            |SPI_MODE8_ON|ENABLE_SDO_PIN|SLAVE_ENABLE_OFF|SPI_CKE_ON\
            |MASTER_ENABLE_ON|SEC_PRESCAL_8_1|PRI_PRESCAL_64_1, SPI_ENABLE);
BYTE i;
AS5055ReadPacket read;
AS5055CommandPacket cmd;

}


BYTE SPITransceve(BYTE b){
    SpiChnPutC(1, b);		// send data on the master channel, SPI1
    return SpiChnGetC(1);	// get the received data
}

void blink(){
        unsigned short int i,b;
    while(1){
        ENC2_CSN=CSN_Disabled;

        bDelay();bDelay();bDelay();bDelay();bDelay();bDelay();

        ENC2_CSN=CSN_Enabled;
        
        bDelay();bDelay();bDelay();bDelay();bDelay();bDelay();
    }
}