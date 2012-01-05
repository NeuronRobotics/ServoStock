/*
 * Counter.c
 *
 *  Created on: Feb 7, 2010
 *      Author: hephaestus
 */

#include "UserApp.h"

#define ENCIPL ipl1
#define INTPRI EXT_INT_PRI_1
//#define USE_INT_DISABLE

/**
 * this is the storage variable for the counter groups
 */
COUNTER Counter[NUM_COUNTER_GROUPS];
/**
 * This is the mapping between a counter group and its associated DyIO channels
 */
COUNTER_PINS pinmap[]={ {{17,16,3}},{{19,18,2}},{{21,20,1}},{{23,22,0}}  };

void RunCounter(void){
	BYTE iIndex;
	//printfDEBUG("Running counter");
	for (iIndex=0;iIndex<NUM_COUNTER_GROUPS;iIndex++){
		 runCounterGroup(iIndex);
	}
}

void InitCounterPins(void){
	BYTE i;
	for (i=0;i<NUM_PINS;i++){
		 ClearCounter(i);
	}
	for (i=0;i<NUM_COUNTER_GROUPS;i++){
		 Counter[i].CURRENT=0;
		 Counter[i].SETPOINT=0;
	}
	OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, (0x1000/10 ));
	ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_5);
	INTEnableSystemMultiVectoredInt();
    printfDEBUG("Initialized the Counter module");
}
void ClearCounter(BYTE chan){
	BYTE group = channelToCounterGroup(chan);
	switch ( GetChannelMode(chan)){
		case IS_COUNTER_INPUT_INT:
		case IS_COUNTER_INPUT_DIR:
		case IS_COUNTER_INPUT_HOME:
		case IS_COUNTER_OUTPUT_INT:
		case IS_COUNTER_OUTPUT_DIR:
		case IS_COUNTER_OUTPUT_HOME:
			println("Mode was counter, clearing");
			SetCoProcMode(pinmap[group].DIR,IS_DI);
			SetCoProcMode(pinmap[group].INT,IS_DI);
			SetCoProcMode(pinmap[group].HOME,IS_DI);
			break;
		default:
			return;
	}
	if (group > 3)
		return;
	printfDEBUG("Clearing counter channel:");
	printfDEBUG_UL(group);

	//Counter[chan].CURRENT=0;
	//Counter[chan].SETPOINT=0;
	Counter[group].STEP_INDEX=0;
	Counter[group].TimeOffset=0;
	Counter[group].TimeStep=0;
	Counter[group].OutputEnabled=FALSE;
	Counter[group].Homed=FALSE;

	switch (group){
	case 0:
		CHAN0P0_tris=INPUT;
		CHAN0P1_tris=INPUT;
		CloseINT1();
		break;
	case 1:
		CHAN1P0_tris=INPUT;
		CHAN1P1_tris=INPUT;
		CloseINT2();
		break;
	case 2:
		CHAN2P0_tris=INPUT;
		CHAN2P1_tris=INPUT;
		CloseINT3();
		break;
	case 3:
		CHAN3P0_tris=INPUT;
		CHAN3P1_tris=INPUT;
		CloseINT4();
		break;
	}

}

void configPin23Int(){
	CHAN3P0_tris=INPUT;
	CHAN3P1_tris=INPUT;
	ConfigINT4(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
	INTEnableSystemMultiVectoredInt();
}

BOOL StartCounterInput(BYTE chan){

	BYTE group = channelToCounterGroup(chan);
	LONG count = GetCounterByGroup(group);
	printfDEBUG("Enabeling counter input channel:");
	printfDEBUG_UL(group);
	Counter[group].OutputEnabled=FALSE;
	if (group > 3)
		return FALSE;
	println("Setting counter output modes");
	if(GetChannelMode(pinmap[group].DIR)!=IS_COUNTER_INPUT_DIR)
		SetCoProcMode(pinmap[group].DIR,IS_COUNTER_INPUT_DIR);
	if(GetChannelMode(pinmap[group].INT)!=IS_COUNTER_INPUT_INT)
		SetCoProcMode(pinmap[group].INT,IS_COUNTER_INPUT_INT);
	if(GetChannelMode(pinmap[group].HOME)!=IS_COUNTER_INPUT_HOME)
		SetCoProcMode(pinmap[group].HOME ,IS_COUNTER_INPUT_HOME);
	initCounterAsync(group, count);
	switch (group){
	case 0:
		CHAN0P0_tris=INPUT;
		CHAN0P1_tris=INPUT;
		ConfigINT1(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
		INTEnableSystemMultiVectoredInt();
		break;
	case 1:
		CHAN1P0_tris=INPUT;
		CHAN1P1_tris=INPUT;
		ConfigINT2(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
		INTEnableSystemMultiVectoredInt();
		break;
	case 2:
		CHAN2P0_tris=INPUT;
		CHAN2P1_tris=INPUT;
		ConfigINT3(EXT_INT_ENABLE | RISING_EDGE_INT | INTPRI);
		INTEnableSystemMultiVectoredInt();
		break;
	case 3:
		configPin23Int();
		break;
	default:
		return FALSE;
	}
	//This ensures that re-enabeling the interupts doesnt currupt the count
	Counter[group].CURRENT = count;
	Counter[group].Homed=FALSE;

	return TRUE;
}
BOOL StartCounterOutput(BYTE chan){
	BYTE group = channelToCounterGroup(chan);


	if (group > 3)
		return FALSE;
	printfDEBUG("Enabeling counter output channel: ");
	printfDEBUG_UL(group);
	printfDEBUG("Setting counter input modes");
	if(GetChannelMode(pinmap[group].DIR)!=IS_COUNTER_OUTPUT_DIR)
		SetCoProcMode(pinmap[group].DIR,IS_COUNTER_OUTPUT_DIR);
	if(GetChannelMode(pinmap[group].INT)!=IS_COUNTER_OUTPUT_INT)
		SetCoProcMode(pinmap[group].INT,IS_COUNTER_OUTPUT_INT);
	if(GetChannelMode(pinmap[group].HOME)!=IS_COUNTER_OUTPUT_HOME)
		SetCoProcMode(pinmap[group].HOME ,IS_COUNTER_OUTPUT_HOME);

	Counter[group].OutputEnabled=TRUE;
	//Counter[chan].SETPOINT= 1000;
	switch (group){
	case 0:
		mPORTEOpenDrainOpen(BIT_7);
		mPORTDOpenDrainOpen(BIT_8);
		CHAN0P0=OFF;
		CHAN0P1=OFF;
		break;
	case 1:
		mPORTEOpenDrainOpen(BIT_6);
		mPORTDOpenDrainOpen(BIT_9);
		CHAN1P0=OFF;
		CHAN1P1=OFF;
		break;
	case 2:
		mPORTEOpenDrainOpen(BIT_5);
		mPORTDOpenDrainOpen(BIT_10);
		CHAN2P0=OFF;
		CHAN2P1=OFF;
		break;
	case 3:
		mPORTEOpenDrainOpen(BIT_4);
		mPORTDOpenDrainOpen(BIT_11);
		CHAN3P0=OFF;
		CHAN3P1=OFF;
		break;
	}
	Counter[group].Homed=FALSE;
	return TRUE;
}

void runCounterOutputStep(BYTE group){
	if (group > 3)
		return;

	if(Counter[group].SETPOINT == Counter[group].CURRENT ){
		return;
	}
	//print("Step");
	if (Counter[group].SETPOINT > Counter[group].CURRENT ){
		switch (Counter[group].STEP_INDEX){
		case 0:
			setPinsByGroup(group,ON,ON);
			break;
		case 1:
			setPinsByGroup(group,OFF,ON);
			break;
		case 2:
			setPinsByGroup(group,OFF,OFF);
			break;
		case 3:
			setPinsByGroup(group,ON,OFF);
			break;

		}
		Counter[group].STEP_INDEX +=1;
		if (Counter[group].STEP_INDEX == 4){
			Counter[group].STEP_INDEX = 0;
			Counter[group].CURRENT +=1;
		}

	}else if (Counter[group].SETPOINT < Counter[group].CURRENT ){
		switch (Counter[group].STEP_INDEX){
		case 0:
			setPinsByGroup(group,ON,OFF);
			break;
		case 1:
			setPinsByGroup(group,OFF,OFF);
			break;
		case 2:
			setPinsByGroup(group,OFF,ON);
			break;
		case 3:
			setPinsByGroup(group,ON,ON);
			break;
		}
		Counter[group].STEP_INDEX +=1;
		if (Counter[group].STEP_INDEX == 4){
			Counter[group].STEP_INDEX = 0;
			Counter[group].CURRENT -=1;
		}
	}

	if (Counter[group].TimeStep >= Counter[group].TimeOffset ){
		Counter[group].TimeStep = 0;
	}
	if (Counter[group].STEP_INDEX!=3){
		Counter[group].TimeStep +=1;
	}
}

void runCounterGroup(BYTE group){
	if (group > 3)
		return;
	switch(GetChannelMode(pinmap[group].INT)){
	case IS_COUNTER_INPUT_INT:
	case IS_COUNTER_OUTPUT_INT:
		break;
	default:
		return;
	}

	//extern BYTE DIG_val[];

	if ( Counter[group].OutputEnabled == FALSE){
			if ((GetDigitalValFromAsync(pinmap[group].HOME)==0) ){
				if(Counter[group].Homed ==FALSE){
					print("\nHoming INput group: ");p_ul(group);print(" based on DyIO input: ");p_ul(pinmap[group].HOME);
					Counter[group].Homed=TRUE;
					if(GetPIDGroup(pinmap[group].INT) != NOT_USED_IN_PID ){
						println("Used in PID, pushing async limit event");
						BYTE g = GetPIDGroup(pinmap[group].INT);
						//SetPID(g,Counter[group].CURRENT);
						trigerPIDLimit(g,INDEXEVENT,Counter[group].CURRENT);
						//Counter[group].SETPOINT=Counter[group].CURRENT;
					}else{
						Counter[group].CURRENT=0;
						Counter[group].SETPOINT=0;
					}
				}

			}else{
				Counter[group].Homed=FALSE;
			}
	}else{
		if(Counter[group].STEP_INDEX==0){
			if(Counter[group].interpolate.setTime>0)
				Counter[group].SETPOINT = interpolate(&Counter[group].interpolate,getMs());
			else{
				Counter[group].SETPOINT=Counter[group].interpolate.set;
			}

			if ((GetDigitalValFromAsync(pinmap[group].HOME)==0) ){
				if(Counter[group].Homed == FALSE){
					print("\nHoming OUTput group: ");p_ul(group);print(" based on DyIO input: ");p_ul(pinmap[group].HOME);
					Counter[group].Homed=TRUE;
					Counter[group].CURRENT=0;
					Counter[group].SETPOINT=0;
					Counter[group].interpolate.set=(float)0;
					Counter[group].interpolate.setTime=0;
					Counter[group].interpolate.start=0;
					Counter[group].interpolate.startTime=getMs();
				}
			}else{
				Counter[group].Homed=FALSE;
			}
		}
		runCounterOutputStep(group);
	}
}

void setPinsByGroup(BYTE group,BYTE pin1,BYTE pin2){
	switch (group){
	case 0:
		CHAN0P0=pin1;
		CHAN0P1=pin2;
		break;
	case 1:
		CHAN1P0=pin1;
		CHAN1P1=pin2;
		break;
	case 2:
		CHAN2P0=pin1;
		CHAN2P1=pin2;
		break;
	case 3:
		CHAN3P0=pin1;
		CHAN3P1=pin2;
		break;
	}
}
LONG GetCounterByGroup(BYTE group){
	return Counter[group].CURRENT;
}
LONG GetCounterByChannel(BYTE channel){
	return GetCounterByGroup(channelToCounterGroup(channel));
}
LONG GetCounterOutput(BYTE chan){
	return Counter[channelToCounterGroup(chan)].CURRENT;
}

BOOL SetCounterOutput(BYTE chan,LONG val, UINT32 ms){
	BYTE group =channelToCounterGroup(chan);

	//Counter[group].SETPOINT=val;
	Counter[group].interpolate.set=(float)val;
	Counter[group].interpolate.setTime=ms;
	Counter[group].interpolate.start=Counter[group].CURRENT;
	Counter[group].interpolate.startTime=getMs();

	return TRUE;
}
BOOL SetCounterInput(BYTE chan,LONG val){
	Counter[channelToCounterGroup(chan)].CURRENT=val;
	return TRUE;
}

BYTE channelToCounterGroup(BYTE chan){
	BYTE i;
	for(i=0;i<NUM_COUNTER_GROUPS;i++){
		if(pinmap[i].INT == chan || pinmap[i].DIR == chan ||pinmap[i].HOME == chan )
			return i;
	}
	return 0xff;
}

BYTE getCounterIntChannnel(BYTE group){
	return pinmap[group].INT;
}
BYTE getCounterDirChannnel(BYTE group){
	return pinmap[group].DIR;
}
BYTE getCounterHomeChannnel(BYTE group){
	return pinmap[group].HOME;
}

void __ISR(_EXTERNAL_1_IRQ, ENCIPL) INT1_ISR(void){
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN0P1){
		mINT1SetEdgeMode(0);
		//ConfigINT4(EXT_INT_ENABLE | FALLING_EDGE_INT | EXT_INT_PRI_5);
		if (CHAN0P0)
			Counter[0].CURRENT++;
		else
			Counter[0].CURRENT--;
	}else{
		mINT1SetEdgeMode(1);
		//ConfigINT4(EXT_INT_ENABLE | RISING_EDGE_INT | EXT_INT_PRI_5);
		if (!CHAN0P0)
			Counter[0].CURRENT++;
		else
			Counter[0].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT1ClearIntFlag();
#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}

void __ISR(_EXTERNAL_2_IRQ, ENCIPL) INT2_ISR(void){
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN1P1){
		mINT2SetEdgeMode(0);
		if (CHAN1P0)
			Counter[1].CURRENT++;
		else
			Counter[1].CURRENT--;
	}else{
		mINT2SetEdgeMode(1);
		if (!CHAN1P0)
			Counter[1].CURRENT++;
		else
			Counter[1].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT2ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}
void __ISR(_EXTERNAL_3_IRQ, ENCIPL) INT3_ISR(void){
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN2P1){
		mINT3SetEdgeMode(0);
		if (CHAN2P0)
			Counter[2].CURRENT++;
		else
			Counter[2].CURRENT--;
	}else{
		mINT3SetEdgeMode(1);
		if (!CHAN2P0)
			Counter[2].CURRENT++;
		else
			Counter[2].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT3ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}
void __ISR(_EXTERNAL_4_IRQ, ENCIPL) INT4_ISR(void){


	if(GetChannelMode(23)==IS_PPM_IN){
		runPPMEvent();
		mINT4ClearIntFlag();
		return;
	}
#if defined(USE_INT_DISABLE)
	StartCritical();
#endif
	if(CHAN3P1){
		mINT4SetEdgeMode(0);
		if (CHAN3P0)
			Counter[3].CURRENT++;
		else
			Counter[3].CURRENT--;
	}else{
		mINT4SetEdgeMode(1);
		if (!CHAN3P0)
			Counter[3].CURRENT++;
		else
			Counter[3].CURRENT--;
	}
	//Delay1us(3);//debounce
	mINT4ClearIntFlag();

#if defined(USE_INT_DISABLE)
	EndCritical();
#endif
}

void __ISR(_TIMER_3_VECTOR, ipl5) _Timer3Handler(void)
{
	//StartCritical();
	ConfigIntTimer3(T3_INT_OFF);
	mT3ClearIntFlag();
	RunCounter();
	ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_5);
	//EndCritical();
}



