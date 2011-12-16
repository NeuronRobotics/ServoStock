/*
 * ChannelMode.h
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */

#ifndef CHANNELMODE_H_
#define CHANNELMODE_H_
/**
 * Initialize the internal data structures from the eeprom
 */
void InitPinModes(void);
void InitPinStates(void);

/**
 * Helper macro to return the mode with the async flag stripped off
 */
BYTE GetChannelMode(BYTE chan);

/**
 * Sets the modes from an incoming packet
 */
BOOL SetChannelMode(BowlerPacket * Packet);
BOOL SetAllChannelMode(BowlerPacket * Packet);



/**
 * Checks to see if the channel is set to async mode
 * @return if it is async
 */
BOOL IsAsync(BYTE channel);

/**
 * This Function is used to alter the mode of the pin (See DYIO_def.h for modes)
 * Setting the higest bit (|=0x80) will enable the mode as async
 *
 * @param pin The pin refers to the dyio channel to be altered
 * @param mode the mode to set the pin to
 * @return If the mode change was successfull
 */
BOOL setMode(BYTE pin,BYTE mode);


/**
 * Private method
 */
void configPinMode(BYTE pin,BYTE mode,BYTE tris,BYTE io);
#endif /* CHANNELMODE_H_ */
