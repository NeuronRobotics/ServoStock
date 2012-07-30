#include "main.h"

UINT8   AS5055CalculateParity(UINT16 data){
    UINT8 bits=0;
    UINT8 shift=0;
    for (shift=1; shift<16; shift++){
        if ((data >>  shift)&0x0001)
            bits++;
    }
    if (bits % 2)
        return 1;
    return 0;
}

UINT16 AS5055reset(BYTE index){
    EncoderSS(index,CSN_Enabled);
    AS5055CommandPacket cmd;
    AS5055ReadPacket read;

    cmd.regs.Address=AS5055REG_SoftwareReset;
    cmd.regs.RWn=AS5055_WRITE;
    cmd.regs.PAR=AS5055CalculateParity(cmd.uint0_15);

    SPITransceve(cmd.bytes.ubyte8_15);
    SPITransceve(cmd.bytes.ubyte0_7);
    EncoderSS(index,CSN_Disabled);
    EncoderSS(index,CSN_Enabled);
    SPITransceve(0);
    SPITransceve(0);
    EncoderSS(index,CSN_Disabled);
    
    return read.uint0_15;
}

UINT16 AS5055ResetErrorFlag(BYTE index){
    AS5055CommandPacket cmd;
    AS5055ReadPacket read;
    EncoderSS(index,CSN_Enabled);
    cmd.regs.Address=AS5055REG_ClearErrorFlagReset;
    cmd.regs.RWn=AS5055_READ;
    cmd.regs.PAR=AS5055CalculateParity(cmd.uint0_15);

    SPITransceve(cmd.bytes.ubyte8_15);
    SPITransceve(cmd.bytes.ubyte0_7);
    EncoderSS(index,CSN_Disabled);
    
    return read.regs.Data;
}

void printSystemConfig(BYTE index){
    AS5055CommandPacket cmd;
    AS5055SystemConfigPacket read;
    EncoderSS(index,CSN_Enabled);
    cmd.regs.Address=AS5055REG_SystemConfig1;
    cmd.regs.RWn=AS5055_READ;
    cmd.regs.PAR=AS5055CalculateParity(cmd.uint0_15);

    SPITransceve(cmd.bytes.ubyte8_15);
    SPITransceve(cmd.bytes.ubyte0_7);
    EncoderSS(index,CSN_Disabled);
    EncoderSS(index,CSN_Enabled);
    read.bytes.ubyte8_15=SPITransceve(0);
    read.bytes.ubyte0_7=SPITransceve(0);
    EncoderSS(index,CSN_Disabled);
    println_I("System config: ");       prHEX16(read.uint0_15,INFO_PRINT);
    println_I("\tResolution: ");        p_sl(read.regs.resolution,INFO_PRINT);
    println_I("\tchip ID: ");           p_sl(read.regs.id,INFO_PRINT);
    println_I("\tinvert_spinning: ");   p_sl(read.regs.invert,INFO_PRINT);
    println_I("\tFE_bw_setting: ");     p_sl(read.regs.bw,INFO_PRINT);
    println_I("\tFE_gain_setting: ");   p_sl(read.regs.gain,INFO_PRINT);
    println_I("\tbreak_AGC_loop: ");    p_sl(read.regs.break_loop,INFO_PRINT);
}

UINT16 AS5055readAngle(BYTE index){
    AS5055CommandPacket cmd;
    AS5055AngularDataPacket read;
    EncoderSS(index,CSN_Enabled);
    cmd.regs.Address=AS5055REG_AngularData;
    cmd.regs.RWn=AS5055_READ;
    cmd.regs.PAR=AS5055CalculateParity(cmd.uint0_15);

    SPITransceve(cmd.bytes.ubyte8_15);
    SPITransceve(cmd.bytes.ubyte0_7);
    EncoderSS(index,CSN_Disabled);
    EncoderSS(index,CSN_Enabled);
    read.bytes.ubyte8_15=SPITransceve(0);
    read.bytes.ubyte0_7=SPITransceve(0);
    EncoderSS(index,CSN_Disabled);
    if(read.regs.EF){
        //AS5055ResetErrorFlag(index);
        //println_E("**Error flag on data read!");
        if(read.regs.AlarmHI == 1 && read.regs.AlarmLO == 0){
            //println_E("Alarm bit indicating a too high magnetic field");
        }else if(read.regs.AlarmHI == 0 && read.regs.AlarmLO == 1){
            //println_E("Alarm bit indicating a too low magnetic field");
        }else{
          printSystemConfig(index);
        }
        
    }
    return read.regs.Data;
}

void EncoderSS(BYTE index, BYTE state){
    switch(index){
        case 2:
            ENC2_CSN=state;
            break;
        case 3:
            ENC3_CSN=state;
            break;
    }
    if(state==CSN_Disabled){
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
    }
}

