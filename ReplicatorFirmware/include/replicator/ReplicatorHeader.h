/* 
 * File:   ReplicatorHeader.h
 * Author: hephaestus
 *
 * Created on July 29, 2012, 4:39 PM
 */

#ifndef REPLICATORHEADER_H
#define	REPLICATORHEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

// ATX MAcros and defines
#define     ATX_PWR_ON_TRIS    _TRISD5 // tris
#define     ATX_PWR_ON         _RD5
#define     ATX_ENABLED        0

#define     ATX_ENABLE()       ATX_PWR_ON_TRIS = 0; ATX_PWR_ON = ATX_ENABLED;DelayMs(100); // set to output and pull low. This should probubly be an open collector pin.
#define     ATX_DISENABLE()    ATX_PWR_ON_TRIS = 1; // dont want to DRIVE an io line that's pulled high. Set to input and let it get pulled up.

// eNCODER Connector macros and defines
#define     ENC0_CSN           _RA0
#define     ENC0_CSN_TRIS      _TRISA0
#define     ENC0_SERVO_TRIS    _TRISC13
#define     ENC0_SERVO         _RC13

#define     ENC1_CSN           _RA1
#define     ENC1_CSN_TRIS      _TRISA1
#define     ENC1_SERVO_TRIS    _TRISC14
#define     ENC1_SERVO         _RC14

#define     ENC2_CSN           _RB13
#define     ENC2_CSN_TRIS      _TRISB13
#define     ENC2_SERVO_TRIS    _TRISF2
#define     ENC2_SERVO         _RF2

#define     ENC3_CSN           _RA3
#define     ENC3_CSN_TRIS      _TRISA3
#define     ENC3_SERVO_TRIS    _TRISF8
#define     ENC3_SERVO         _RF8

#define     ENC4_CSN           _RA9
#define     ENC4_CSN_TRIS      _TRISA9
#define     ENC4_SERVO_TRIS    _TRISD1
#define     ENC4_SERVO         _RD1

#define     ENC5_CSN           _RB14
#define     ENC5_CSN_TRIS      _TRISB14
#define     ENC5_SERVO_TRIS    _TRISD2
#define     ENC5_SERVO         _RD2
    
#define     ENC6_CSN           _RA6
#define     ENC6_CSN_TRIS      _TRISA6
#define     ENC6_SERVO_TRIS    _TRISD3
#define     ENC6_SERVO         _RD3

#define     ENC7_CSN           _RA7
#define     ENC7_CSN_TRIS      _TRISA7
#define     ENC7_SERVO_TRIS    _TRISD4
#define     ENC7_SERVO         _RD4

#define    HEATER_0            _RG7
#define    HEATER_0_TRIS       _TRISG7

#define    HEATER_1            _RB4
#define    HEATER_1_TRIS       _TRISB4

#define    HEATER_2            _RG13
#define    HEATER_2_TRIS       _TRISG13

#define    HEATER_3            _RB5
#define    HEATER_3_TRIS       _TRISB5

#define     CloseServoOpenCollector() mPORTCOpenDrainClose(BIT_13);\
                                    mPORTCOpenDrainClose(BIT_14);\
                                    mPORTFOpenDrainClose(BIT_2);\
                                    mPORTFOpenDrainClose(BIT_8);\
                                    mPORTDOpenDrainClose(BIT_1);\
                                    mPORTDOpenDrainClose(BIT_2);\
                                    mPORTDOpenDrainClose(BIT_3);\
                                    mPORTDOpenDrainClose(BIT_4);
#define     CloseSpiSSOpenCollector() mPORTAOpenDrainClose(BIT_0);\
                                    mPORTAOpenDrainClose(BIT_1);\
                                    mPORTBOpenDrainClose(BIT_13);\
                                    mPORTAOpenDrainClose(BIT_3);\
                                    mPORTAOpenDrainClose(BIT_9);\
                                    mPORTBOpenDrainClose(BIT_14);\
                                    mPORTAOpenDrainClose(BIT_6);\
                                    mPORTAOpenDrainClose(BIT_7);

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
                                    ENC7_CSN_TRIS=0;ENC7_CSN=CSN_Disabled;

#define     SERVO_HW_INIT()        CloseServoOpenCollector();\
                                    ENC7_SERVO_TRIS=0;\
                                    ENC6_SERVO_TRIS=0;\
                                    ENC5_SERVO_TRIS=0;\
                                    ENC4_SERVO_TRIS=0;\
                                    ENC3_SERVO_TRIS=0;\
                                    ENC2_SERVO_TRIS=0;\
                                    ENC1_SERVO_TRIS=0;\
                                    ENC0_SERVO_TRIS=0;


#define     bDelay()    i=2; while (i>1) i++;

void initPIDLocal();
void setPidIsr(BOOL v);

#define numPidMotors 8

#define numPidHeater 4

#define numPidTotal (numPidMotors+numPidHeater)

#define EXTRUDER0_INDEX 0
#define HEATER0_INDEX   11
#define LINK0_INDEX 6
#define LINK1_INDEX 7
#define LINK2_INDEX 4

BOOL isUpToTempreture();


#define defaultMaxZ -289.5

#define servoCalebrateValue 121
#define ticksPerRev         (4096.0)
#define ticksPerDegree      (ticksPerRev/360.0)
#define gearRatio           (7.0)
#define calibrationAngle    (27.0)
#define servoHomeValue      (ticksPerDegree*calibrationAngle*gearRatio)

#if !defined(NUM_PID_GROUPS)
	#define NUM_PID_GROUPS (8)
#endif
void LoadCorePacket(BowlerPacket * Packet);
void setDebug(BOOL d);

#ifdef	__cplusplus
}
#endif

#endif	/* REPLICATORHEADER_H */

