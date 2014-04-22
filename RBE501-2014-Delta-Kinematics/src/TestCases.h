/*
 * TestCases.h
 *
 *  Created on: Apr 13, 2014
 *      Author: bill
 */

#ifndef TESTCASES_H_
#define TESTCASES_H_

int twoDSquare ( int sideLength, float * initialPosition);
int twoDDiamondWorkspace (int sideLength);
int threeDTestCase (int positionCount, const float desiredPositions[][3], float calculatedJoints[][3], float calculatedPositions[][3]);
void define2DCircle (int radius, int stepCount, float * origin, float dataPoints[][3]);
void twoDTriangle (int length, float * origin, float dataPoints[][3]);
int inverseVelocity (float * taskPosition, float * desiredTaskVelocity);
int forwardVelocity (float * jointPosition, float * desiredJointVelocity);
int wrapInverseVelocity (float * taskPosition, float * desiredTaskVelocity);

#endif /* TESTCASES_H_ */
