/* 
 * File:   delta.h
 * Author: hephaestus
 *
 * Created on November 12, 2012, 2:42 PM
 */

#ifndef DELTA_H
#define	DELTA_H

#ifdef	__cplusplus
extern "C" {
#endif


void initializeDelta();

void setConfigurations(float endEffector,float base, float driven, float free, float zOffsetValue);

int delta_calcForward(float theta1, float theta2, float theta3, float * x0, float *y0, float * z0);

int delta_calcInverse(float x0, float y0, float z0, float *theta1, float *theta2, float *theta3);

#ifdef	__cplusplus
}
#endif

#endif	/* DELTA_H */

