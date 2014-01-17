/*
 * SPIClient.c
 *
 *  Created on: Dec 9, 2010
 *      Author: hephaestus
 */
#include "main.h"

BYTE SPITransceve(BYTE b){
    SpiChnPutC(2, b);		// send data on the master channel, SPI1
    Delay1us(10);
    return SpiChnGetC(2);	// get the received data
}
BYTE get(BYTE b){
	BYTE back = SPITransceve(b);
        //Delay10us(60);
	return back;
}


