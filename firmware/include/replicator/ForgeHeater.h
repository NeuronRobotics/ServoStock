/* 
 * File:   ForgeHeater.h
 * Author: hephaestus
 *
 * Created on October 5, 2012, 1:48 PM
 */

#ifndef FORGEHEATER_H
#define	FORGEHEATER_H

#ifdef	__cplusplus
extern "C" {
#endif

   typedef struct {
        double a;
        double b;
        double c;
    } shh_coef;

    void initializeHeater();

    int resetHeater(int group, int current);

    float getHeaterTempreture(int group);

    void setHeater(int group, float v);

    boolean setSensorCoefs(BowlerPacket *Packet);
boolean PidRTDAsyncEventCallback(BowlerPacket * Packet, boolean(*pidAsyncCallbackPtr)(BowlerPacket *Packet));

#ifdef	__cplusplus
}
#endif

#endif	/* FORGEHEATER_H */

