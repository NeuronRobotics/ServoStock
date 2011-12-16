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

#ifndef RPC_PROCESS_H_
#define RPC_PROCESS_H_


float getLastPacketTime(void);
void Process_Self_Packet(BowlerPacket * Packet);
void StatRPCs(BowlerPacket * Packet);
void GetRPCs(BowlerPacket * Packet);
void PostRPCs(BowlerPacket * Packet);
void CriticalRPCs(BowlerPacket * Packet);

unsigned char UserGetRPCs(BowlerPacket * Packet);
unsigned char UserPostRPCs(BowlerPacket * Packet);
unsigned char UserCriticalRPCs(BowlerPacket * Packet);

void AddNamespace(unsigned char len, const unsigned char *  string);

#endif /* RPC_PROCESS_H_ */
