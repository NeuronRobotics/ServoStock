/* 
 * File:   servoCalibration.h
 * Author: hephaestus
 *
 * Created on May 20, 2013, 10:40 AM
 */

#ifndef SERVOCALIBRATION_H
#define	SERVOCALIBRATION_H

#ifdef	__cplusplus
extern "C" {
#endif
/**This is a blocking fenction to set up a servo calibration wehn used with a PID controller. 
 */
    void runServoCalibration(int group);

    int getUpperServoHistoresis(int gtoup);
    int getLowerServoHistoresis(int gtoup);
    int getServoStop(int gtoup);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVOCALIBRATION_H */

