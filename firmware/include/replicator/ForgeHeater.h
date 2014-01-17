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

    void initializeHeater();

    int resetHeater(int group, int current);

    float getHeaterTempreture(int group);

    void setHeater(int group, float v);



#ifdef	__cplusplus
}
#endif

#endif	/* FORGEHEATER_H */

