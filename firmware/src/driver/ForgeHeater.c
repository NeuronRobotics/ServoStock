#include "main.h"
#define lowpasslen  1

int heaterDutty[] = {0,0,0,0};

float heaterLowpass[4][lowpasslen];
int heaterLowpassIndex;

int heaterIndex = 0;

void heaterPin(int index, int value){

    // THis needs to be toggel pins only
    
//    switch(index){
//        case 0:
//             setHeater0(1);
//            break;
//        case 1:
//            setHeater1(1);
//            break;
//        case 2:
//            setHeater2(1);
//            break;
//    }
}

int mapHeaterIndex(int group){
    switch(group){
        case 8:
            return HEATER_0_ADC;
        case 9:
            return HEATER_1_ADC;
        case 10:
            return HEATER_2_ADC;

    }
    return 0;
}

void initializeHeater(){
    int i;
    // did this on bootup
    //for(i=numPidMotors;i<numPidTotal;i++){
   //     InitADCHardware(mapHeaterIndex( i ));
    //}
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_256, 300);
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_4);
    Print_Level l = getPrintLevel();
    setPrintLevelInfoPrint();
    println_I("Starting PID ISR");
    setPrintLevel(l);
    HEATER_0_TRIS=OUTPUT;
    HEATER_1_TRIS=OUTPUT;
    HEATER_2_TRIS=OUTPUT;
    
    setHeater0(0);
    setHeater1(0);
    setHeater2(0);

    // init lowpass
  
    heaterLowpassIndex=0;
    int j=0;
    for (i=0; i<4; i++){
        for(j=0; j<lowpasslen; j++)
            heaterLowpass[i][j]=0;
    }

    for(i=0;i<4;i++){
         heaterPin(i , 0);
         heaterDutty[i]=0;
    }
    
}

int resetHeater(int group, int current){
    return 0;
}

// these 3 coefs charecterize a sensor
// each sesnor should be able to have it's own set of coefs. this should be an array.
double SH_A=0.0007229943855,SH_B=0.00021619777,SH_C=0.000000093022549; //celcius

// Resistance (ohms) to temperature (kelvin)
float steinhart_RtoK(float r,double a,double b,double c){

    //Print_Level l = getPrintLevel();
            //setPrintLevelInfoPrint();
    double k = 1.0/(a + (b*log(r)) + (c*pow(3.0,log(r)))  );
    //int i=0;
    //for(i=0; i<600; i++)print_I("\b");

    //println_I("steinhart_RtoK:");
    //print_I("\tohms=");p_fl_I(r);print_I("\tk=");p_fl_I((float)k);println_I("");
    //print_I("\ta=");p_fl_I((float)a);print_I("\tb=");p_fl_I((float)b);print_I("\tc=");p_fl_I((float)c);println_I("");
    //setPrintLevel(l);
    return k;
}

// temperature(kelvin) to resistance(ohms)
float steinhart_KtoR(float t , double a,double b,double c){
    float y = (a-(1.0/t))/2.0*c;
    float x = sqrt(   (pow(3.0,b/(3.0*c))) + (pow(2.0,y) ));
    float r = cbrt(x-y)-cbrt(x+y);
    return r;
}

    #define pullupRes 10000.0
// get heater temperature in celcius
float getHeaterTempreture(int group){    
    float adcVolts=getAdcVoltage(mapHeaterIndex(group),10);
        
    // we should run ADC from the pic's 3.3v supply
    float  rtdOhms= ((3.4/adcVolts)-1)*pullupRes; // convert voltage to ohms of thermistor

    float temp = steinhart_RtoK(rtdOhms,SH_A,SH_B,SH_C); // convert to kelvin/celcius from ohms using thermistor coefs

    return       temp; // return temp in celcius.
}


// set heater temperature
void setHeater(int group, float v){
    //float kelvin=v+273.15;
    //float rtdOhms = steinhart_KtoR(kelvin,SH_A,SH_B,SH_C);
    //float volt = 10000.0/(10000.0+rtdOhms)
//    v+=50;
//    if(v>99)
//        v=99;
    if(v<0){
        v=0;
        setLED(0,0,1);
    } else {

        setLED(1,0,0);
    }
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


shh_coef coefs[]={
    {0.0007229943855,0.00021619777,0.000000093022549},
    {0.0007229943855,0.00021619777,0.000000093022549},
    {0.0007229943855,0.00021619777,0.000000093022549}
};

boolean setSensorCoefs(BowlerPacket *Packet){
    uint8_t chan= Packet->use.data[0];   // heater channel
    float a=get32bit(Packet, 1);            // desired a
    float b=get32bit(Packet, 5);            // desired b
    float c=get32bit(Packet, 9);            // desired c
    if (chan<sizeof(coefs)){
        coefs[chan].a=a;
        coefs[chan].b=b;
        coefs[chan].c=c;
    } else {
        return false;
    }
    return true;
}

boolean PidRTDAsyncEventCallback(BowlerPacket * Packet, boolean(*pidAsyncCallbackPtr)(BowlerPacket *Packet)) {
    //println_E("PidRTDAsyncEventCallback");
    return false;
}