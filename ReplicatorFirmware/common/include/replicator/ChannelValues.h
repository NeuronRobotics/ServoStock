/*
 * ChannelValues.h
 *
 *  Created on: Jan 30, 2010
 *      Author: hephaestus
 */

#ifndef CHANNELVALUES_H_
#define CHANNELVALUES_H_
#include "Bowler/Bowler.h"
/**
 * Get/Set the pin state to/from a packet
 * @return if the operation was a success
 */
BOOL GetChannelValue(BowlerPacket * Packet);
BOOL SetChannelValue(BowlerPacket * Packet);
BOOL SetAllChannelValue(BowlerPacket * Packet);

/**
 * Retrieves the value of a channel
 * Internally checks the pin mode and calls the appropriate method to access it
 * @return the value of that channel
 */
UINT16 GetChanVal(BYTE pin);

/**
 * Sets the value of a channel(primitive only, no stream channels with this method)
 * @param pin the channel to be set
 * @param the value to set the mode to
 * @param time the time it takes for the transition (only valid with servo for now)
 * @return if it succeed
 */
BOOL SetChanVal(BYTE pin,INT32 bval, float time);

/**
 * Sets the value of a channel into non volatile storage
 */
BOOL SaveValue(BYTE pin,BYTE val);

#endif /* CHANNELVALUES_H_ */
