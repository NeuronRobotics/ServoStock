/*
 * Kinematics.h
 *
 *  Created on: Feb 28, 2014
 *      Author: hephaestus
 */

#ifndef KINEMATICS_H_
#define KINEMATICS_H_
/**
 * Take the joint space positions and convert to a task space position
 * This should transform the output using the bed level calibration
 * Return 0 for success
 * Return error code for failure
 */
int forwardKinematics( float * currentJointPositions,
					   float * outputTaskSpacePositionMatrix
					);

/**
 * Take the task space position and convert to a set of joint space positions
 * This should transform the input through the bed level calibration
 * Return 0 for success
 * Return error code for failure
 */
int inverseKinematics( float * currentTaskSpacePosition,
					   float *  outputJointSpacePositionVector
					);


int servostock_calcInverse(float X, float Y, float Z, float * Alpha, float * Beta, float * Gama);
int servostock_calcForward(float Alpha, float Beta, float Gama, float * X, float *Y, float * Z);
int servostock_velInverse(float X, float Y, float Z, float Xd, float Yd, float Zd, float * Ad, float * Bd, float * Cd);
int servostock_velForward(float A, float B, float C, float Ad, float Bd, float Cd, float * Xd, float * Yd, float * Zd);


#endif /* KINEMATICS_H_ */
