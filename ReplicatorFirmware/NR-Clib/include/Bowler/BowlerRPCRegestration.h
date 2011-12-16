/*
 * BowlerRPCRegestration.h
 *
 *  Created on: Sep 29, 2010
 *      Author: hephaestus
 */

#ifndef BOWLERRPCREGESTRATION_H_
#define BOWLERRPCREGESTRATION_H_

#define MAX_NUM_RPC 15
BYTE addRPC(BYTE method,const char * rpc,void( *_callback)(BowlerPacket*));
BYTE setMethodCallback(BYTE method,BYTE( *_callback)(BowlerPacket*));

typedef void rpcCallback(BowlerPacket *);

typedef struct __attribute__((__packed__)) _RPC_HANDLER{
		unsigned long rpc;
		rpcCallback * callback;
} RPC_HANDLER;


typedef struct __attribute__((__packed__)) _RPC_HANDLER_SET{
		unsigned char numRPC;
		RPC_HANDLER handlers[MAX_NUM_RPC];
} RPC_HANDLER_SET;


typedef BYTE methodCallback(BowlerPacket *);

typedef struct __attribute__((__packed__)) _METHOD_HANDLER{
		unsigned char set;
		methodCallback * callback;
} METHOD_HANDLER;

#endif /* BOWLERRPCREGESTRATION_H_ */
