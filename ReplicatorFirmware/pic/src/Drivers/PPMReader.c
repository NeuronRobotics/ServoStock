/**
 * @filePPMReader.c
 *
 *  Created on: Feb 18, 2011
 * @author Kevin Harrington
 */

#include "UserApp.h"
static BYTE ppmData[]={128,128,128,128,128,128};
static BYTE ppmLastSent[]={255,255,255,255,255,255};
static BYTE ppmLink[]={255,255,255,255,255,255};
static UINT32 ppmDataTmp[]={128,128,128,128,128,128};
static UINT32 ppmStart[NUM_PPM_CHAN];
static BYTE ppmIndex = 0;
static UINT32 bufferStart=0;
static UINT32 buffTime = (TICKS_PER_SECOND/1000)*6;

void configPin23Int();

typedef enum{
	START=0,
	WAIT_FOR_PULSE,
	PULSE_STARTED
}ppmState ;
static ppmState state;


void RunPPMCheck(void){
	if(GetChannelMode(23) != IS_PPM_IN){
		//setMode(23,IS_PPM_IN);
		return;
	}
	int i;
	BOOL up = FALSE;
	for(i=0;i<NUM_PPM_CHAN;i++){
		float fTime =MyTickConvertToMilliseconds(((float)ppmDataTmp[i])+(((float)TickGetUpper())*((float) 4294967295ul )));
		if(fTime>.9 && fTime<2.2){
			float fVal = (fTime-.99)*255;
			if(fVal>254)
				fVal=254;
			if(fVal<0)
				fVal=0;
			BYTE time =((BYTE) fVal);

			if((time>(ppmData[i]+3)) || (time<(ppmData[i]-3))){
				ppmData[i]=time;
				//setHeartBeatState( FALSE, 0);
				up=TRUE;
			}
		}
	}
	if(up){
		//push upstream
		pushPPMPacket();
		//print("\nUpdating ppm chan ");printStream(ppmData,NUM_PPM_CHAN);
		//print(" PPM cross link ");printStream(ppmLink,NUM_PPM_CHAN);
		for(i=0;i<NUM_PPM_CHAN;i++){
			if(ppmLink[i] != INVALID_PPM_LINK){
				if(ppmLastSent[i] != ppmData[i]){
					ppmLastSent[i] = ppmData[i];
					//unlockServos();
					SetChannelValueCoProc(ppmLink[i],ppmData[i]);
				}
			}
		}
	}
}

void runPPMEvent(void){
	BYTE pinState = CHAN3P1;
	UINT32 now = TickGet();
	if(pinState){
		mINT4SetEdgeMode(0);
	}else{
		mINT4SetEdgeMode(1);
	}

	switch(state){
	case START:
		if((bufferStart == 0) ||(pinState == 0 ))
			bufferStart = now;
		if((now>(bufferStart + buffTime))&&(pinState == 1)){
			state =  WAIT_FOR_PULSE;
		}
		break;
	case WAIT_FOR_PULSE:
		if(pinState == 0 ){
			ppmStart[ppmIndex]=now;
			state = PULSE_STARTED;
		}
		break;
	case PULSE_STARTED:
		if(pinState == 1 ){
			ppmDataTmp[ppmIndex] = (now-ppmStart[ppmIndex]);
			ppmIndex++;
			if(ppmIndex == NUM_PPM_CHAN){
				ppmIndex = 0;
				state = START;
			}else{
				state = WAIT_FOR_PULSE;
			}
		}
		break;
	}
}

void clearPPM(BYTE chan){
	if((chan == 23) && (GetChannelMode(23)==IS_PPM_IN)){
		CloseINT4();
		CHAN3P1_tris=INPUT;
	}
}

void startPPM(BYTE chan){
	int i;
	if(chan == 23){
//		ConfigINT4(EXT_INT_ENABLE | FALLING_EDGE_INT | EXT_INT_PRI_5);
//		CHAN3P1_tris=INPUT;
		configPin23Int();
		state = START;
		readPPMLink(ppmLink);
		for(i=0;i<NUM_PPM_CHAN;i++){
			if(ppmLink[i]>= NUM_PINS)
				ppmLink[i]=INVALID_PPM_LINK;
		}
		//println("Starting PPM reader");
	}
}

void GetPPMDataToPacket(BowlerPacket * Packet){
	//println("Getting PPM values");
	int i;
	LoadCorePacket(Packet);
	Packet->use.head.Method=BOWLER_POST;
	Packet->use.head.RPC=GetRPCValue("gchv");
	Packet->use.data[0]=23;
	for(i=0;i<NUM_PPM_CHAN;i++){
		Packet->use.data[1+i]=ppmData[i];
	}
	for(i=0;i<NUM_PPM_CHAN;i++){
		Packet->use.data[1+i+NUM_PPM_CHAN]=ppmLink[i];
	}
	Packet->use.head.DataLegnth=4+1+(NUM_PPM_CHAN*2);
	Packet->use.head.MessageID=0;
	SetCRC(Packet);
}
void ConfigPPM(BowlerPacket * Packet){
	int i;
	for(i=0;i<NUM_PPM_CHAN;i++){
		ppmLink[i]=Packet->use.data[i+1];
		if(ppmLink[i]>= NUM_PINS){
			ppmLink[i]=INVALID_PPM_LINK;
		}else{
			unlockServos();
		}
	}
	writePPMLink(ppmLink);
	READY(Packet,66,0);
}

void GetPPMDataToArray(BYTE * data){
	int i;
	for(i=0;i<NUM_PPM_CHAN;i++){
		data[i]=ppmData[i];
	}
}


