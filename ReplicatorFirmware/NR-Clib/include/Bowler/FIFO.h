/**
 * @file FIFO.h
 *
 * Created on: May 27, 2010
 * @author hephaestus
 */

#ifndef FIFO_H_
#define FIFO_H_

#define FIFO_OK 			0
#define FIFO_FAILED_TO_SET	1
#define FIFO_FAILED_TO_GET	2
#define FIFO_OVERFLOW		3
#define FIFO_UNDERFLOW		4

typedef struct _BYTE_FIFO_STORAGE{
	UINT32 bufferSize;
	BYTE * buffer;
	UINT32 readPointer;
	UINT32 writePointer;
	UINT32 byteCount;
	BOOL   mutex;
}BYTE_FIFO_STORAGE;


void InitByteFifo(BYTE_FIFO_STORAGE * fifo,BYTE * buff,UINT32 size);

BYTE ReadFirstByte(BYTE_FIFO_STORAGE * fifo);

UINT32 FifoGetByteCount(BYTE_FIFO_STORAGE * fifo);

UINT32 FifoAddByte(BYTE_FIFO_STORAGE * fifo,BYTE b, BYTE * errorCode);

void printFiFoState(BYTE_FIFO_STORAGE * fifo, BYTE * buffer);

UINT32 FifoGetByteStream(BYTE_FIFO_STORAGE * fifo,BYTE *packet,UINT32 size);

UINT32 FifoReadByteStream(BYTE *packet,UINT32 size,BYTE_FIFO_STORAGE * fifo);

typedef struct _UINT32_FIFO_STORAGE{
	UINT32 bufferSize;
	UINT32 * buffer;
	UINT32 readPointer;
	UINT32 writePointer;
	UINT32 count;
}UINT32_FIFO_STORAGE;

void InitUINT32Fifo(UINT32_FIFO_STORAGE * fifo,UINT32 * buff,UINT32 size);

UINT32 FifoAddUINT32(UINT32_FIFO_STORAGE * fifo,UINT32 b);

UINT32 FifoGetUINT32Stream(UINT32_FIFO_STORAGE * fifo,UINT32 *packet,UINT32 size);

#endif /* FIFO_H_ */
