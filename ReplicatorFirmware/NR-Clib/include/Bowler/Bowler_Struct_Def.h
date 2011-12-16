/**
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef BOWLERSTRUCTDEF_H_
#define BOWLERSTRUCTDEF_H_

	typedef union _RPC_VALUE {
		  unsigned char ASCII[4];
		  UINT32		   value;
	}RPC_VALUE;
#if !defined(__STACK_TSK_H) && !defined(_SOCKET_H_)
	typedef union __attribute__((__packed__)) _MAC_ADDR
	{
		struct{
			unsigned char v[6];
		};
	} MAC_ADDR;
#endif
	typedef struct __attribute__((__packed__)) _HEADER
	{
		unsigned char		ProtocolRevision;
		MAC_ADDR			MAC;				// The MAC address of the packet
		unsigned char       Method;				// The method type
		unsigned			MessageID    :7;			// Semi unique Transaction ID
		unsigned    		ResponseFlag :1;		// Is this packet a response packet
		unsigned char		DataLegnth;			// Length of data to come
		unsigned char		CRC;				// CRC for packet
		UINT32				RPC;				// 4 byte RPC stored as a 32 bit int for single compare;
	} HEADER;
#define FullPacketDataSize 251
	typedef union __attribute__((__packed__)) _BowlerPacket{
		unsigned char stream[FullPacketDataSize+sizeof(HEADER)];
		struct
		{
			HEADER head;
			unsigned char data[FullPacketDataSize];
		} use;
	}BowlerPacket;
#define MiniPacketDataSize 105
	typedef union __attribute__((__packed__)) _BowlerPacketMini{
		unsigned char stream[MiniPacketDataSize+sizeof(HEADER)];
		struct
		{
			HEADER head;
			unsigned char data[MiniPacketDataSize];
		} use;
	}BowlerPacketMini;




#endif /* WASPSTRUCTDEF_H_ */
