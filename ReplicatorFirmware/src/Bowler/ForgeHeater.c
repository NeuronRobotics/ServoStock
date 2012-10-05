#include "main.h"


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
}

int resetHeater(int group, int current){

}


float getHeaterTempreture(int group){
    
    return getAdcVoltage(mapHeaterIndex( group));
}

void setHeater(int group, float v){

}

