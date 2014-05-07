/*
 * Kinematics.h
 *
 *  Created on: Feb 28, 2014
 *      Author: hephaestus
 */

#ifndef KINEMATICS_H_
#define KINEMATICS_H_

int forwardKinematics( float * currentJointPositions,
					   float * outputTaskSpacePositionMatrix
					);
int inverseKinematics( float * currentTaskSpacePosition,
					   float *  outputJointSpacePositionVector
					);
int calculateJointSpaceVelocities(	float * currentTaskSpacePosition,
									float * desiredTaskSpaceVelocities,
									float * outputJointSpaceVelocities
								);
int calculateTaskSpaceVelocities(	float * currentJointSpacePosition,
									float * desiredJointSpaceVelocities,
									float * outputTaskSpaceVelocity
							);


int servostock_calcInverse(float X, float Y, float Z, float * Alpha, float * Beta, float * Gama);
int servostock_calcForward(float Alpha, float Beta, float Gama, float * X, float *Y, float * Z);
int servostock_velInverse(float X, float Y, float Z, float Xd, float Yd, float Zd, float * Ad, float * Bd, float * Cd);
int servostock_velForward(float A, float B, float C, float Ad, float Bd, float Cd, float * Xd, float * Yd, float * Zd);


#endif /* KINEMATICS_H_ */
