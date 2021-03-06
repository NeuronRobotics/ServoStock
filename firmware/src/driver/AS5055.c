#include "main.h"


int64_t overflow[numPidTotal];
//int64_t offset[numPidTotal];
int64_t raw[numPidTotal];
int64_t recent[numPidTotal];
boolean initialized = false;
boolean busy = 0;
#define jump 3700
void encoderSPIInit();
void AS5055ResetErrorFlag(uint8_t index);
void printSystemConfig(uint8_t index);
uint16_t AS5055send(uint8_t index, uint16_t data);

boolean enableWrapping = true;

void disableWrapping() {
    enableWrapping = false;
}

void initializeEncoders() {
    DelayMs(200);
    int8_t i;
//    println_I("Starting SPI");
    encoderSPIInit();
    // AC: Do we still need this?
    mJTAGPortEnable(0); // Disable JTAG and free up channels 0 and 1
    ENC_CSN_INIT(); // Set pin modes for CS pins
    for (i = 0; i < numPidTotal; i++) {
//        println_I("Encoder ");
//        p_int_I(i);
        AS5055reset(i);
//        print_I(" | reset ");
        overflow[i] = 0;
        //offset[i]=0;
        recent[i] = 0;
        raw[i] = AS5055readAngle(i);
        Delay10us(50); // Delay for the encoders to perform read
        raw[i] = AS5055readAngle(i);
    }
}

int64_t readEncoderWithoutOffset(uint8_t index) {
    int64_t tmp = 0;
    int64_t diff = 0;
    if (!busy) {
        busy = 1;
        tmp = AS5055readAngle(index);
        diff = raw[index] - tmp;
        //        print_E(" diff : ");
        //        p_int_E(diff);
        raw[index] = tmp;
        busy = 0;
    } else {
        diff = 0;
    }
    int64_t oflw = 0;
    if (enableWrapping) {
        if (diff > jump || diff < (-1 * jump)) {
            if (diff > 0)
                overflow[index]++;
            else
                overflow[index]--;
        }
        oflw = (4096 * overflow[index]);
    }
    //    print_W(" overflow Index : ");
    //    p_int_W(overflow[index]);
    //    print_E(" overflow adjustment  : ");
    //    p_fl_E(oflw);


    int64_t ret = ( tmp + oflw);
    //    print_W(" Return value : ");
    //    p_fl_W(ret);
    return ret;
}

float getRecentEncoderReading(int index) {
    float value = (float)recent[index];
    return value;
}

void updateAllEncoders() {
    int i,j;
    int mask = 0x3;// Mask off the last 2 bits for rounding noise error correction;
    for (i = 0; i < numPidMotors; i++) {

        recent[i] = 0;
    }
    for (j=0;j<encoderIntegralSize;j++){
        for (i = 0; i < numPidMotors; i++) {
            // Set the read command to the chip
            AS5055readAngle(i);
        }
        Delay10us(50); // Delay for the encoders to perform read
        for (i = 0; i < numPidMotors; i++) {
            // Take a reading after waiting
            //        println_I("RAW Data:  ");p_int_I(i);
            recent[i] += readEncoderWithoutOffset(i) ^ mask;
            //        print_I(" raw : ");p_int_I( raw[i]);
            //        print_I(" val: ");p_int_I( recent[i]);
            //        print_I(" Done\r\n");
            //AS5055reset(i);
            AS5055ResetErrorFlag(i);
        }
    }

    for (i = 0; i < numPidMotors; i++) {

        recent[i] = (recent[i]/encoderIntegralSize) ^ mask;
    }
 
}

//float readEncoder(uint8_t index){
//    float size=1;
//    float ret=0;
//    int64_t i;
//    for(i=0;i<size;i++)
//        ret += (readEncoderWithoutOffset(index));
//    recent[index]=ret/size;
//    return getRecentEncoderReading(index);
//}

void encoderSPIInit() {
    SPI_CLK_TRIS();
    SPI_MISO_TRIS();
    SPI_MOSI_TRIS();
    if (initialized)
        return;
    initialized = true;
#if defined(__32MX795F512L__)
    OpenSPI1(CLK_POL_ACTIVE_HIGH\
 | SPI_MODE8_ON | ENABLE_SDO_PIN | SLAVE_ENABLE_OFF | SPI_CKE_OFF\
 | MASTER_ENABLE_ON | SEC_PRESCAL_3_1 | PRI_PRESCAL_4_1
            , SPI_ENABLE);
#elif defined(__32MX440F128H__)
    OpenSPI2(CLK_POL_ACTIVE_HIGH\
 | SPI_MODE8_ON | ENABLE_SDO_PIN | SLAVE_ENABLE_OFF | SPI_CKE_OFF\
 | MASTER_ENABLE_ON | SEC_PRESCAL_3_1 | PRI_PRESCAL_4_1
            , SPI_ENABLE);
#endif
}

uint8_t AS5055CalculateParity(uint16_t data) {
    uint8_t bits = 0;
    uint8_t shift = 0;
    for (shift = 1; shift < 16; shift++) {
        if ((data >> shift)&0x0001)
            bits++;
    }
    if (bits % 2)
        return 1;
    return 0;
}

uint16_t AS5055reset(uint8_t index) {
    //println_I("[AS5055] Resetting ");p_int_I(index);
    AS5055CommandPacket cmd;
    AS5055ReadPacket read;

    cmd.regs.Address = AS5055REG_SoftwareReset;
    cmd.regs.RWn = AS5055_WRITE;
    cmd.regs.PAR = AS5055CalculateParity(cmd.uint0_15);

    AS5055send(index, cmd.uint0_15);

    return read.uint0_15;
}

void AS5055ResetErrorFlag(uint8_t index) {
    //println_I("[AS5055send] Clear Error Flags");
    AS5055CommandPacket cmd;

    cmd.regs.Address = AS5055REG_MasterReset;
    cmd.regs.RWn = AS5055_READ;
    cmd.regs.PAR = AS5055CalculateParity(cmd.uint0_15);

    AS5055send(index, cmd.uint0_15);

}

void printSystemConfig(uint8_t index) {
    AS5055CommandPacket cmd;
    AS5055SystemConfigPacket read;
    cmd.regs.Address = AS5055REG_SystemConfig1;
    cmd.regs.RWn = AS5055_READ;
    cmd.regs.PAR = AS5055CalculateParity(cmd.uint0_15);

    read.uint0_15 = AS5055send(index, cmd.uint0_15);
    Print_Level l = getPrintLevel();
    if (l != NO_PRINT) {
//        println_I("System config: ");
//        prHEX16(read.uint0_15, INFO_PRINT);
//        println_I("\tResolution: ");
//        p_int(read.regs.resolution, INFO_PRINT);
//        println_I("\tchip ID: ");
//        p_int(read.regs.id, INFO_PRINT);
//        println_I("\tinvert_spinning: ");
//        p_int(read.regs.invert, INFO_PRINT);
//        println_I("\tFE_bw_setting: ");
//        p_int(read.regs.bw, INFO_PRINT);
//        println_I("\tFE_gain_setting: ");
//        p_int(read.regs.gain, INFO_PRINT);
//        println_I("\tbreak_AGC_loop: ");
//        p_int(read.regs.break_loop, INFO_PRINT);
    }
    setPrintLevel(l);
}

uint16_t AS5055readAngle(uint8_t index) {
    Print_Level l = getPrintLevel();

    AS5055AngularDataPacket read;

    int64_t tmp = AS5055send(index, 0xffff);
    read.uint0_15 = tmp;


    setPrintLevel(l);
    return read.regs.Data ;
}

uint8_t lock = false;

uint16_t AS5055send(uint8_t index, uint16_t data) {
    if (lock)
        return 0xffff;
    lock = true;
    UINT16_UNION tmp;
    UINT16_UNION back;
    if (data == 0)
        data = 0xffff;
    tmp.Val = data;
    EncoderSS(index, CSN_Enabled);
    //println_I("[AS5055send] Sending data: ");prHEX8(tmp.byte.SB,INFO_PRINT);prHEX8(tmp.byte.LB,INFO_PRINT);println_I("");
    back.byte.SB = SPITransceve(tmp.byte.SB);
    back.byte.LB = SPITransceve(tmp.byte.LB);
    EncoderSS(index, CSN_Disabled);
    //    Delay10us(50);
    //    EncoderSS(index,CSN_Enabled);
    //   // AC: This gives you the response from the previous command. You need to send outa nop to get the response for this command
    //    back.byte.SB = SPITransceve(0);
    //    back.byte.LB = SPITransceve(0);
    //    EncoderSS(index,CSN_Disabled);
    //println_I("[AS5055send] Got data: ");prHEX8(back.byte.SB,INFO_PRINT);prHEX8(back.byte.LB,INFO_PRINT);println_I("");

    lock = false;
    //print_I("`");
    return back.Val;
}

void EncoderSS(uint8_t index, uint8_t state) {
    if (state == CSN_Enabled) {
        encoderSPIInit();
    } else {
        Delay10us(1);
    }
    switch (index) {
        case 0:
            ENC0_CSN(state);
            break;
        case 1:
            ENC1_CSN(state);
            break;
        case 2:
            ENC2_CSN(state);
            break;
        case 3:
            ENC3_CSN(state);
            break;
        case 4:
            ENC4_CSN(state);
            break;
        case 5:
            ENC5_CSN(state);
            break;
        case 6:
            ENC6_CSN(state);
            break;
        case 7:
            ENC7_CSN(state);
            break;
    }
    if (state == CSN_Enabled)
        Delay10us(1);
}

