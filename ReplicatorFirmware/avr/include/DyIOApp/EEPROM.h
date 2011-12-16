/*
 * EEPROM.h
 *
 *  Created on: Feb 17, 2010
 *      Author: hephaestus
 */

#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/eeprom.h>
void EEInitMAC(void);
BOOL ProvisionMAC(BYTE * m);

void EEWriteMode(BYTE pin,BYTE mode);
void EEWriteValue(UINT16 pin,BYTE value);
BYTE EEReadValue(UINT16 pin);
BYTE EEReadMode(BYTE pin);

UINT32 EEReadBaud(void);
void EEWriteBaud(UINT32 val);
void EEWriteData(UINT16 addr,BYTE data);
BYTE EEReadData(UINT16 addr);

#endif /* EEPROM_H_ */
