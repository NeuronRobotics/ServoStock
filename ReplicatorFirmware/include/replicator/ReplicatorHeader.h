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
#define     ATX_DISABLED       1

#define     ATX_ENABLE()       ATX_PWR_ON_TRIS = 0; ATX_PWR_ON = ATX_ENABLED; // set to output and pull low. This should probubly be an open collector pin.
#define     ATX_DISENABLE()    ATX_PWR_ON_TRIS = 1; // dont want to DRIVE an io line that's pulled high. Set to input and let it get pulled up.

// eNCODER Connector macros and defines
#define     ENC0_CSN           _RA0
#define     ENC0_CSN_TRIS      _TRISA0
#define     ENC0_SERVO_TRIS    _TRISC13
#define     ENC0_SERVO         _RC13

#define     ENC1_CSN           _RA1
#define     ENC1_CSN_TRIS      _TRISA1
#define     ENC1_SERVO_TRIS    _TRIC14
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

#define     CSN_Enabled       0
#define     CSN_Disabled     1

#define     ENC_CSN_INIT()       ENC2_CSN_TRIS=0;ENC2_CSN=CSN_Disabled;ENC3_CSN_TRIS=0;ENC3_CSN=CSN_Disabled
#define     ENC_SERVO_INIT()     ENC7_SERVO_TRIS=0;ENC6_SERVO_TRIS=0;ENC5_SERVO_TRIS=0;ENC4_SERVO_TRIS=0;ENC3_SERVO_TRIS=0;ENC2_SERVO_TRIS=0;ENC1_SERVO_TRIS=0;ENC0_SERVO_TRIS=0;


#define     bDelay()    i=2; while (i>1) i++;

void initPIDLocal();

#define numPidMotor 8

#ifdef	__cplusplus
}
#endif

#endif	/* REPLICATORHEADER_H */

