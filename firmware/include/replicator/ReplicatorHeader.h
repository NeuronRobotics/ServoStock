/* 
 * File:   ReplicatorHeader.h
 * Author: hephaestus
 *
 * Created on July 29, 2012, 4:39 PM
 */

#ifndef REPLICATORHEADER_H
#define	REPLICATORHEADER_H
#include "arch/pic32/Compiler.h"
#ifdef	__cplusplus
extern "C" {
#endif

    // ATX MAcros and defines
    #define     ATX_PWR_ON_TRIS    _TRISF0 // tris
    #define     ATX_PWR_ON         _RF0
    #define     ATX_ENABLED        1

    #define     SPI_CLK_TRIS        _TRISG6 // tris
    #define     SPI_MISO_TRIS       _TRISG8 // tris
    #define     SPI_MOSI_TRIS       _TRISG7 // tris
    #define     CloseSPIOpenCollector() mPORTGOpenDrainClose(BIT_6);\
                                        mPORTGOpenDrainClose(BIT_7);
    #define     LED_RED_TRIS    _TRISD10
    #define     LED_RED_PIN     _RD10
    #define     LED_GRN_TRIS    _TRISD11
    #define     LED_GRN_PIN     _RD11
    #define     LED_BLU_TRIS    _TRISD0
    #define     LED_BLU_PIN     _RD0

    #define     initLEDs()      LED_RED_TRIS=0;LED_GRN_TRIS=0;LED_BLU_TRIS=0;
    #define     setLED(r,g,b)   LED_RED_PIN=~r;LED_GRN_PIN=~g;LED_BLU_PIN=~b;
#define Rev4
#ifdef Rev4
 // eNCODER Connector macros and defines
	//PORT 0
    #define     ENC0_CSN           _RD7
    #define     ENC0_CSN_TRIS      _TRISD7
    #define     ENC0_SERVO_TRIS    _TRISB15
    #define     ENC0_SERVO         _RB15
	//PORT 1
    #define     ENC1_CSN           _RD6
    #define     ENC1_CSN_TRIS      _TRISD6
    #define     ENC1_SERVO_TRIS    _TRISB14
    #define     ENC1_SERVO         _RB14
	// Port 2
    #define     ENC2_CSN           _RD5
    #define     ENC2_CSN_TRIS      _TRISD5
    #define     ENC2_SERVO_TRIS    _TRISB13
    #define     ENC2_SERVO         _RB13
	// PORT 3
    #define     ENC3_CSN           _RD4
    #define     ENC3_CSN_TRIS      _TRISD4
    #define     ENC3_SERVO_TRIS    _TRISB12
    #define     ENC3_SERVO         _RB12
	// PORT 4
    #define     ENC4_CSN           _RE5
    #define     ENC4_CSN_TRIS      _TRISE5
    #define     ENC4_SERVO_TRIS    _TRISB11
    #define     ENC4_SERVO         _RB11
	// PORT 5
    #define     ENC5_CSN           _RE6
    #define     ENC5_CSN_TRIS      _TRISE6
    #define     ENC5_SERVO_TRIS    _TRISB10
    #define     ENC5_SERVO         _RB10
	//PORT 6
    #define     ENC6_CSN           _RE7
    #define     ENC6_CSN_TRIS      _TRISE7
    #define     ENC6_SERVO_TRIS    _TRISB8
    #define     ENC6_SERVO         _RB8
	//PORT 7
    #define     ENC7_CSN           _RG9
    #define     ENC7_CSN_TRIS      _TRISG9
    #define     ENC7_SERVO_TRIS    _TRISB9
    #define     ENC7_SERVO         _RB9

    #define    HEATER_0            _RB5
    #define    HEATER_0_TRIS       _TRISB5

    #define    HEATER_1            _RB0
    #define    HEATER_1_TRIS       _TRISB0

    #define    HEATER_2            _RB2
    #define    HEATER_2_TRIS       _TRISB2

#else
    // eNCODER Connector macros and defines
	//PORT 0
    #define     ENC0_CSN           _RE7
    #define     ENC0_CSN_TRIS      _TRISE7
    #define     ENC0_SERVO_TRIS    _TRISB12
    #define     ENC0_SERVO         _RB12
	//PORT 1
    #define     ENC1_CSN           _RD7
    #define     ENC1_CSN_TRIS      _TRISD7
    #define     ENC1_SERVO_TRIS    _TRISB10
    #define     ENC1_SERVO         _RB10
	// Port 2
    #define     ENC2_CSN           _RG9
    #define     ENC2_CSN_TRIS      _TRISG9
    #define     ENC2_SERVO_TRIS    _TRISB15
    #define     ENC2_SERVO         _RB15
	// PORT 3
    #define     ENC3_CSN           _RD6
    #define     ENC3_CSN_TRIS      _TRISD6
    #define     ENC3_SERVO_TRIS    _TRISB11
    #define     ENC3_SERVO         _RB11
	// PORT 4
    #define     ENC4_CSN           _RE5
    #define     ENC4_CSN_TRIS      _TRISE5
    #define     ENC4_SERVO_TRIS    _TRISB14
    #define     ENC4_SERVO         _RB14
	// PORT 5
    #define     ENC5_CSN           _RD5
    #define     ENC5_CSN_TRIS      _TRISD5
    #define     ENC5_SERVO_TRIS    _TRISB9
    #define     ENC5_SERVO         _RB9
	//PORT 6
    #define     ENC6_CSN           _RE6
    #define     ENC6_CSN_TRIS      _TRISE6
    #define     ENC6_SERVO_TRIS    _TRISB13
    #define     ENC6_SERVO         _RB13
	//PORT 7
    #define     ENC7_CSN           _RD4
    #define     ENC7_CSN_TRIS      _TRISD4
    #define     ENC7_SERVO_TRIS    _TRISB8
    #define     ENC7_SERVO         _RB8

    #define    HEATER_0            _RB5
    #define    HEATER_0_TRIS       _TRISB5

    #define    HEATER_1            _RB0
    #define    HEATER_1_TRIS       _TRISB0

    #define    HEATER_2            _RB2
    #define    HEATER_2_TRIS       _TRISB2

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
                                    ENC0_CSN_TRIS=0;ENC0_CSN=CSN_Disabled;\
                                    ENC1_CSN_TRIS=0;ENC1_CSN=CSN_Disabled;\
                                    ENC2_CSN_TRIS=0;ENC2_CSN=CSN_Disabled;\
                                    ENC3_CSN_TRIS=0;ENC3_CSN=CSN_Disabled;\
                                    ENC4_CSN_TRIS=0;ENC4_CSN=CSN_Disabled;\
                                    ENC5_CSN_TRIS=0;ENC5_CSN=CSN_Disabled;\
                                    ENC6_CSN_TRIS=0;ENC6_CSN=CSN_Disabled;\
                                    ENC7_CSN_TRIS=0;ENC7_CSN=CSN_Disabled;\
                                    mPMPClose();

#define     SERVO_HW_INIT()        CloseServoOpenCollector();\
                                    ENC7_SERVO_TRIS=0;\
                                    ENC6_SERVO_TRIS=0;\
                                    ENC5_SERVO_TRIS=0;\
                                    ENC4_SERVO_TRIS=0;\
                                    ENC3_SERVO_TRIS=0;\
                                    ENC2_SERVO_TRIS=0;\
                                    ENC1_SERVO_TRIS=0;\
                                    ENC0_SERVO_TRIS=0;
#define     ATX_ENABLE()       ATX_PWR_ON_TRIS = OUTPUT; ATX_PWR_ON = ATX_ENABLED;DelayMs(100); // set to output and pull low. This should probubly be an open collector pin.
#define     ATX_DISENABLE()    ATX_PWR_ON_TRIS = INPUT; // dont want to DRIVE an io line that's pulled high. Set to input and let it get pulled up.

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

