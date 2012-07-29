#include "main.h"

UINT8   AS5055CalculateParity(UINT16 data){
    UINT8 bits,shift;
    for (shift=0; shift<16; shift++){
        if ((data >>  shift)&0x0001) bits++;
    }
    if (bits % 2) return 1; 
    return 0;
}
