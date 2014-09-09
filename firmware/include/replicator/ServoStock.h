/* 
 * File:   ReplicatorHeader.h
 * Author: hephaestus
 *
 * Created on July 29, 2012, 4:39 PM
 */

#ifndef REPLICATORHEADER_H
#define	REPLICATORHEADER_H
#include "arch/pic32/Compiler.h"
#include "main.h"
#ifdef	__cplusplus
extern "C" {
#endif

    // ATX MAcros and defines
#define     ATX_PWR_ON_TRIS    _TRISF0 // tris
#define     ATX_PWR_ON(s)      setPicIOPin(s, 'F',0)
#define     ATX_ENABLED        1

//#define     SPI_CLK_TRIS        _TRISG6 // tris
//#define     SPI_MISO_TRIS       _TRISG8 // tris
//#define     SPI_MOSI_TRIS       _TRISG7 // tris
#define     SPI_CLK_TRIS()        setPicIOTristateOutput('G',6) //_TRISG6 // tris
#define     SPI_MISO_TRIS()        setPicIOTristateInput('G',8)  //_TRISG8 // tris
#define     SPI_MOSI_TRIS()       setPicIOTristateOutput('G',7) //_TRISG7 // tris
#define     CloseSPIOpenCollector() mPORTGOpenDrainClose(BIT_6);\
                                        mPORTGOpenDrainClose(BIT_7);
#define     LED_RED_TRIS    setPicIOTristateOutput('D',10)
#define     LED_GRN_TRIS    setPicIOTristateOutput('D',11)
#define     LED_BLU_TRIS    setPicIOTristateOutput('D',0)


#define     initLEDs()      LED_RED_TRIS;LED_GRN_TRIS;LED_BLU_TRIS;
#define     setLED(r,g,b)   ioPortD(~r,10);ioPortD(~g,11);ioPortD(~b,0);


#define     resetButtionInit()      setPicIOTristateInput('F',5)//(_TRISF5)=INPUT; // for the reset sw
#define     getResetButton()        getPicIOPin('F',5)

#ifdef Rev4
    // eNCODER Connector macros and defines
    //PORT 0
#define     ENC0_CSN(s)          setPicIOPin(s, 'D',7)
#define     ENC0_CSN_TRIS      setPicIOTristateOutput('D',7)
#define     ENC0_SERVO_TRIS    setPicIOTristateOutput('B',15)
#define     ENC0_SERVO(s)        setPicIOPin(s, 'B',15)
    //PORT 1
#define     ENC1_CSN(s)          setPicIOPin(s, 'D',6)
#define     ENC1_CSN_TRIS      setPicIOTristateOutput('D',6)
#define     ENC1_SERVO_TRIS    setPicIOTristateOutput('B',14)
#define     ENC1_SERVO(s)        setPicIOPin(s, 'B',14)
    // Port 2
#define     ENC2_CSN(s)          setPicIOPin(s, 'D',5)
#define     ENC2_CSN_TRIS      setPicIOTristateOutput('D',5)
#define     ENC2_SERVO_TRIS    setPicIOTristateOutput('B',13)
#define     ENC2_SERVO(s)         setPicIOPin(s, 'B',13)
    // PORT 3
#define     ENC3_CSN(s)          setPicIOPin(s, 'D',4)
#define     ENC3_CSN_TRIS      setPicIOTristateOutput('D',4)
#define     ENC3_SERVO_TRIS    setPicIOTristateOutput('B',12)
#define     ENC3_SERVO(s)        setPicIOPin(s, 'B',12)
    // PORT 4
#define     ENC4_CSN(s)          setPicIOPin(s, 'E',5)
#define     ENC4_CSN_TRIS      setPicIOTristateOutput('E',5)
#define     ENC4_SERVO_TRIS    setPicIOTristateOutput('B',11)
#define     ENC4_SERVO(s)         setPicIOPin(s, 'B',11)
    // PORT 5
#define     ENC5_CSN(s)           setPicIOPin(s, 'E',6)
#define     ENC5_CSN_TRIS      setPicIOTristateOutput('E',6)
#define     ENC5_SERVO_TRIS    setPicIOTristateOutput('B',10)
#define     ENC5_SERVO(s)         setPicIOPin(s, 'B',10)
    //PORT 6
#define     ENC6_CSN(s)           setPicIOPin(s, 'E',7)
#define     ENC6_CSN_TRIS      setPicIOTristateOutput('E',7)
#define     ENC6_SERVO_TRIS    setPicIOTristateOutput('B',8)
#define     ENC6_SERVO(s)         setPicIOPin(s, 'B',8)
    //PORT 7
#define     ENC7_CSN(s)           setPicIOPin(s, 'G',9)
#define     ENC7_CSN_TRIS      setPicIOTristateOutput('G',9)
#define     ENC7_SERVO_TRIS    setPicIOTristateOutput('B',9)
#define     ENC7_SERVO(s)         setPicIOPin(s, 'B',9)


#define     setHeater0(s)         setPicIOPin(s, 'B',5)//
#define     HEATER_0_TRIS       setPicIOTristateOutput('B',5)

#define     setHeater1(s)        setPicIOPin(s, 'B',0)//
#define    HEATER_1_TRIS       setPicIOTristateOutput('B',0)

#define     setHeater2(s)        setPicIOPin(s, 'B',2)//
#define    HEATER_2_TRIS       setPicIOTristateOutput('B',2)

#define    HEATER_0_ADC         1
#define    HEATER_1_ADC         3
#define    HEATER_2_ADC         4

#elif defined( Rev3)
    // eNCODER Connector macros and defines
    //PORT 0
#define     ENC0_CSN(s)        setPicIOPin(s, 'E',7)//  setPicIOPin(s, 'E',7
#define     ENC0_CSN_TRIS      setPicIOTristateOutput('E',7)
#define     ENC0_SERVO_TRIS    setPicIOTristateOutput('B',12)
#define     ENC0_SERVO(s)      setPicIOPin(s, 'B',12)//  setPicIOPin(s, 'B',12
    //PORT 1
#define     ENC1_CSN(s)        setPicIOPin(s, 'D',7)//   setPicIOPin(s, 'D',7
#define     ENC1_CSN_TRIS      setPicIOTristateOutput('D',7)
#define     ENC1_SERVO_TRIS    setPicIOTristateOutput('B',10)
#define     ENC1_SERVO(s)      setPicIOPin(s, 'B',10)//setPicIOPin(s, 'B',10
    // Port 2
#define     ENC2_CSN(s)        setPicIOPin(s, 'G',9)//   setPicIOPin(s, 'G',9
#define     ENC2_CSN_TRIS      setPicIOTristateOutput('G',9)
#define     ENC2_SERVO_TRIS    setPicIOTristateOutput('B',15)
#define     ENC2_SERVO(s)      setPicIOPin(s, 'B',15)//setPicIOPin(s, 'B',15
    // PORT 3
#define     ENC3_CSN(s)        setPicIOPin(s, 'D',6)//    setPicIOPin(s, 'D',6
#define     ENC3_CSN_TRIS      setPicIOTristateOutput('D',6)
#define     ENC3_SERVO_TRIS    setPicIOTristateOutput('B',11)
#define     ENC3_SERVO(s)      setPicIOPin(s, 'B',11)//setPicIOPin(s, 'B',11
    // PORT 4
#define     ENC4_CSN(s)        setPicIOPin(s, 'E',5)//   setPicIOPin(s, 'E',5
#define     ENC4_CSN_TRIS      setPicIOTristateOutput('E',5)
#define     ENC4_SERVO_TRIS    setPicIOTristateOutput('B',14)
#define     ENC4_SERVO(s)      setPicIOPin(s, 'B',14)//setPicIOPin(s, 'B',14
    // PORT 5
#define     ENC5_CSN(s)        setPicIOPin(s, 'D',5)//    setPicIOPin(s, 'D',5
#define     ENC5_CSN_TRIS      setPicIOTristateOutput('D',5)
#define     ENC5_SERVO_TRIS    setPicIOTristateOutput('B',9)
#define     ENC5_SERVO(s)      setPicIOPin(s, 'B',9)//setPicIOPin(s, 'B',9
    //PORT 6
#define     ENC6_CSN(s)        setPicIOPin(s, 'E',6)//   setPicIOPin(s, 'E',6
#define     ENC6_CSN_TRIS      setPicIOTristateOutput('E',6)
#define     ENC6_SERVO_TRIS    setPicIOTristateOutput('B',13)
#define     ENC6_SERVO(s)      setPicIOPin(s, 'B',13)//setPicIOPin(s, 'B',13
    //PORT 7
#define     ENC7_CSN(s)        setPicIOPin(s, 'D',4)//   setPicIOPin(s, 'D',4
#define     ENC7_CSN_TRIS      setPicIOTristateOutput('D',4)
#define     ENC7_SERVO_TRIS    setPicIOTristateOutput('B',8)
#define     ENC7_SERVO(s)      setPicIOPin(s, 'B',8)//setPicIOPin(s, 'B',8

#define     setHeater0(s)      setPicIOPin(s, 'B',5)//
#define     HEATER_0_TRIS      setPicIOTristateOutput('B',5)

#define     setHeater1(s)      setPicIOPin(s, 'B',0)//
#define    HEATER_1_TRIS       setPicIOTristateOutput('B',0)

#define     setHeater2(s)      setPicIOPin(s, 'B',2)//
#define    HEATER_2_TRIS       setPicIOTristateOutput('B',2)

#define    HEATER_0_ADC         4
#define    HEATER_1_ADC         1
#define    HEATER_2_ADC         3
#else
#error No bowlerboard reveision defined
#endif
#define     CloseServoOpenCollector() 	mPORTBOpenDrainClose(BIT_12);\
                                                mPORTBOpenDrainClose(BIT_15);\
                                                mPORTBOpenDrainClose(BIT_11);\
                                                mPORTBOpenDrainClose(BIT_9);\
                                                mPORTBOpenDrainClose(BIT_12);\
                                                mPORTBOpenDrainClose(BIT_14);\
                                                mPORTBOpenDrainClose(BIT_13);\
                                                mPORTBOpenDrainClose(BIT_8);

#define     CloseSpiSSOpenCollector() 	mPORTEOpenDrainClose(BIT_7);\
                                                mPORTDOpenDrainClose(BIT_7);\
                                                mPORTGOpenDrainClose(BIT_9);\
                                                mPORTDOpenDrainClose(BIT_6);\
                                                mPORTEOpenDrainClose(BIT_5);\
                                                mPORTDOpenDrainClose(BIT_5);\
                                                mPORTEOpenDrainClose(BIT_6);\
                                                mPORTDOpenDrainClose(BIT_4);


#define     CSN_Enabled       0
#define     CSN_Disabled     1

#define     ENC_CSN_INIT()          CloseSpiSSOpenCollector();\
                                    ENC0_CSN_TRIS;ENC0_CSN(CSN_Disabled);\
                                    ENC1_CSN_TRIS;ENC1_CSN(CSN_Disabled);\
                                    ENC2_CSN_TRIS;ENC2_CSN(CSN_Disabled);\
                                    ENC3_CSN_TRIS;ENC3_CSN(CSN_Disabled);\
                                    ENC4_CSN_TRIS;ENC4_CSN(CSN_Disabled);\
                                    ENC5_CSN_TRIS;ENC5_CSN(CSN_Disabled);\
                                    ENC6_CSN_TRIS;ENC6_CSN(CSN_Disabled);\
                                    ENC7_CSN_TRIS;ENC7_CSN(CSN_Disabled);\
                                    mPMPClose();

#define     SERVO_HW_INIT()        CloseServoOpenCollector();\
                                    ENC7_SERVO_TRIS;\
                                    ENC6_SERVO_TRIS;\
                                    ENC5_SERVO_TRIS;\
                                    ENC4_SERVO_TRIS;\
                                    ENC3_SERVO_TRIS;\
                                    ENC2_SERVO_TRIS;\
                                    ENC1_SERVO_TRIS;\
                                    ENC0_SERVO_TRIS;
#define     ATX_ENABLE()       setPicIOTristateOutput('F', 0); ATX_PWR_ON(ATX_ENABLED);DelayMs(100); // set to output and pull low. This should probubly be an open collector pin.
#define     ATX_DISENABLE()    setPicIOTristateInput('F', 0); // dont want to DRIVE an io line that's pulled high. Set to input and let it get pulled up.

#define     bDelay()    i=2; while (i>1) i++;

    void initPIDLocal();
    void setPidIsr(boolean v);

#define numPidMotors 8

#define numPidHeater 3

#define numPidTotal (numPidMotors+numPidHeater)



    boolean isUpToTempreture();
    void HomeLinks();
    void startHomingLinks();


#define defaultMaxZ -289.5

#define ticksPerRev         (4096.0)
#define ticksPerDegree      (ticksPerRev/360.0)
#define pulleyDiameter      (20.4414) //(34)
#define mmPerTick           (pulleyDiameter *3.14159/ticksPerRev)
#define servoHomeValue      0

#if !defined(NUM_PID_GROUPS)
#define NUM_PID_GROUPS (numPidMotors)
#endif
    void LoadCorePacket(BowlerPacket * Packet);
    void setDebug(boolean d);

#ifdef	__cplusplus
}
#endif

#endif	/* REPLICATORHEADER_H */

