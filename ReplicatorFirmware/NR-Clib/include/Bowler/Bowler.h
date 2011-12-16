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
#ifndef WASP_H_
#define WASP_H_

#include "Defines.h"
#include "Bowler_Struct_Def.h"
#include "Debug.h"
#include "Bowler_Helper.h"
#include "Bowler_Server.h"
#include "RPC_Process.h"
#include "Scheduler.h"
#include "AbstractPID.h"
#include "FIFO.h"
#include "BowlerTransport.h"
#include "namespace.h"
#include "BowlerRPCRegestration.h"


#if defined(__PIC32MX__)

	#if defined(__32MX795F512L__)
		#include "arch/pic32/EthHardware.h"
	#endif
	#if defined(__32MX460F512L__)
		#include "arch/pic32/Pizo.h"
	#endif
	#include "arch/pic32/BowlerConfig.h"

#elif defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__) || defined(__AVR_ATmega324P__)
	#include "arch/AVR/BowlerConfig.h"
#elif defined (__i386__) || defined (__ia64__) || defined (__amd64__)
	#include "arch/native/BowlerConfig.h"
#else
	#error Unknown archetecture!! See Bowler.h
#endif

#include "BowlerServerHardwareAbstraction.h"

void UserInit(void);
void UserRun(void);


#endif /* WASP_H_ */
