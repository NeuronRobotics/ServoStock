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

typedef enum _ServoState{
    LOW=0,
    PRETIME=1,
    TIME=2,
    FINISH=3
} ServoState;


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
   /**
    * private
    */
void runLinearInterpolationServo(BYTE blockStart,BYTE blockEnd);
BYTE pinOn(BYTE pin);
void pinOff(BYTE pin);
void DelayPreServoPulse(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

