/*
 * namespace.h
 *
 *  Created on: Aug 15, 2010
 *      Author: hephaestus
 */

#ifndef NAMESPACE_H_
#define NAMESPACE_H_

//bcs.core
#define _ERR					0x7272655f // '_err'  The Error RPC
#define _RDY					0x7964725f // '_rdy'  The ready RPC
#define _PNG					0x676E705F // '_png'  Generic ping
#define _NMS					0x736d6e5f // '_nms'  Namespace RPC
//bcs.safe
#define SAFE					0x65666173 // 'safe'  Get/Set the safe-mode parameters

typedef struct __attribute__((__packed__)) _NAMESPACE{
		unsigned char len;
		const unsigned char * name;
} NAMESPACE;

typedef struct __attribute__((__packed__)) _NAMESPACE_SET{
		unsigned char numNamespaces;
		NAMESPACE  names[8];
} NAMESPACE_SET;

#endif /* NAMESPACE_H_ */
