/*
 * FlashStorage.h
 *
 *  Created on: Jul 15, 2010
 *      Author: hephaestus
 */

#ifndef FLASHSTORAGE_H_
#define FLASHSTORAGE_H_

#define FLASH_PAGE_SIZE 				0x1000
#define StartStorePhysical			0x1D009000
#define EndStorePhysical			0x1D00A000

#define StartStoreVirtual			0x9D009000

#define LOCKBYTE					37

#define FLASHSTORE					20

typedef union __attribute__((__packed__)) _FLASH
{
	UINT32 stream[FLASHSTORE];
	struct
	{
		BYTE   mac [6];
		char   name[17];
		BYTE   lock;
		BYTE   blSet;
		BYTE   fwSet;
		BYTE   bl[3];
		BYTE   fw[3];
		BYTE   pad [(FLASHSTORE*4)-6-17-1-1-1-3-3];
	} data;

} FLASH_STORE;

BYTE FlashSetMac(BYTE * mac);
void FlashSetName(char * name);
void FlashGetMac(BYTE * mac);
void FlashGetName(char * name);

BYTE FlashSetBlRev(BYTE * mac);
void FlashGetBlRev(BYTE * mac);
BYTE FlashSetFwRev(BYTE * mac);
void FlashGetFwRev(BYTE * mac);

#endif /* FLASHSTORAGE_H_ */
