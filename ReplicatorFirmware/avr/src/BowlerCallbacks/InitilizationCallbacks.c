/*
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

#include "UserApp.h"
const char startmessage[] = "###Starting AVR In Debug Mode\n";
void UserInit(void){
	enableDebug();
#if defined(DEBUG)
	ConfigureUART(115200);
	if(GetChannelMode(16)!=IS_UART_TX)
		setMode(16,IS_UART_TX);
#endif
	//println("Starting User initialization");
	InitFlagPins();
	InitBankLEDs();
	SetPowerState0(0,0);
	SetPowerState1(0,0);
	InitPins();

	//_delay_ms(1);

#if defined(WPIRBE)
	SPISlaveInit();
#endif

	setMethodCallback(BOWLER_GET,UserGetRPCs);
	setMethodCallback(BOWLER_POST,UserPostRPCs);
	setMethodCallback(BOWLER_CRIT,UserCriticalRPCs);

	enableDebug();
	//SetPinTris(0,OUTPUT);
	//SetDIO(0,OFF);

#if defined(USE_AS_LIBRARY)
	InitializeUserCode();
#endif
	printfDEBUG(startmessage);// All printfDEBUG functions do not need to be removed from code if debug is disabled
}


