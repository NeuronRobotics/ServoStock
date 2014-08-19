/*
 * SPIClient.c
 *
 *  Created on: Dec 9, 2010
 *      Author: hephaestus
 */
#include "main.h"

uint8_t SPITransceve(uint8_t b){
    SpiChnPutC(2, b);		// send data on the master channel, SPI1
    Delay1us(10);
    return SpiChnGetC(2);	// get the received data
}
uint8_t get(uint8_t b){
	uint8_t back = SPITransceve(b);
        //Delay10us(60);
	return back;
}


