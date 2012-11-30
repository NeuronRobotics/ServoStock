#include "main.h"
#define lowpasslen  1

int heaterDutty[] = {0,0,0,0};

float heaterLowpass[4][lowpasslen];
int heaterLowpassIndex;

int heaterIndex = 0;

void heaterPin(int index, int value){
    switch(index){
        case 0:
            HEATER_0 = value?1:0;
            break;
        case 1:
            HEATER_1 = value?1:0;
            break;
        case 2:
            HEATER_2 = value?1:0;
            break;
        case 3:
            HEATER_3 = value?1:0;
            break;
    }
}

int mapHeaterIndex(int group){
    switch(group){
        case 8:
            return 3;
        case 9:
            return 1;
        case 10:
            return 2;
        case 11:
            return 0;
    }
}

void initializeHeater(){
    int i;
    for(i=numPidMotors;i<numPidTotal;i++){
        InitADCHardware(mapHeaterIndex( i ));
    }
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, 300);
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_4);
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    println_I("Starting PID ISR");
    setPrintLevel(l);
    HEATER_0_TRIS=OUTPUT;
    HEATER_1_TRIS=OUTPUT;
    HEATER_2_TRIS=OUTPUT;
    HEATER_3_TRIS=OUTPUT;
    mPORTBSetPinsDigitalOut(BIT_4|BIT_5);

    // init lowpass
  
    heaterLowpassIndex=0;
    int j=0;
    for (i=0; i<4; i++){
        for(j=0; j<lowpasslen; j++)
            heaterLowpass[i][j]=0;
    }

    for(i=0;i<4;i++){
         heaterPin(i , 0);
         heaterDutty[i]=50;
    }
    
}

int resetHeater(int group, int current){

}


float getHeaterTempreture(int group){    
    float sum=getAdcVoltage(mapHeaterIndex(group),10);

    return       sum*65;
}

void setHeater(int group, float v){
//    v+=50;
//    if(v>99)
//        v=99;
    if(v<0)
        v=0;
    heaterDutty[group-numPidMotors]=(int)v;
}

void __ISR(_TIMER_3_VECTOR, ipl4) Timer3Handler(void){
    int i;
    for(i=0;i<4;i++){
        if(heaterIndex == heaterDutty[i]){
            heaterPin(i , 1);
        }
    }
    heaterIndex++;
    if(heaterIndex==100){
       heaterIndex=0;
       for(i=0;i<4;i++){
            heaterPin(i, 0);
        }
    }
    mT3ClearIntFlag();
}



