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


#define     ATX_PWR_ON_TRIS    _TRISD5 // tris
#define     ATX_PWR_ON         _RD5
#define     ATX_ENABLED        0
#define     ATX_DISABLED       1

#define     ATX_ENABLE()       ATX_PWR_ON_TRIS = 0; ATX_PWR_ON = ATX_ENABLED; // set to output and pull low. This should probubly be an open collector pin.
#define     ATX_DISENABLE()    ATX_PWR_ON_TRIS = 1; // dont want to DRIVE an io line that's pulled high. Set to input and let it get pulled up.


#define     ENC2_CSN           _RB13
#define     ENC2_CSN_TRIS      _TRISB13
#define     ENC3_CSN           _RA3
#define     ENC3_CSN_TRIS      _TRISA3

#define     CSN_Enabled       0
#define     CSN_Disabled     1

#define     ENC_CSN_INIT()       ENC2_CSN_TRIS=0;ENC2_CSN=CSN_Disabled;ENC3_CSN_TRIS=0;ENC3_CSN=CSN_Disabled

#define     bDelay()    i=2; while (i>1) i++;

UINT8   AS5055CalculateParity(UINT16 data);

#define numPidMotor 8

#ifdef	__cplusplus
}
#endif

#endif	/* REPLICATORHEADER_H */

