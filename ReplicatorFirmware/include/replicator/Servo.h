/* 
 * File:   Servo.h
 * Author: hephaestus
 *
 * Created on August 7, 2012, 4:58 PM
 */

#ifndef SERVO_H
#define	SERVO_H

#ifdef	__cplusplus
extern "C" {
#endif
    /**
     * Start the servo hardware
     */
    void initServos();

    /**
     * Run the pulse for all pins
     */
    void runServos();

    /**
     * Set a setpoint for a servo with an intrerpolated time
     */
    void setServo(BYTE PIN, BYTE val,float time);

    /**
     * get the current position of the servo
     */
    BYTE getServoPosition(BYTE PIN);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

