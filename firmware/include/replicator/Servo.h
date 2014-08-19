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

    boolean getRunPidIsr();
    
typedef enum _ServoState{
    LOW=0,
    PRETIME=1,
    TIME=2,
    FINISH=3
} ServoState;

    /*Stop the servo signals
     */
    void stopServos();

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
    void setServo(uint8_t PIN, uint8_t val,float time);

    /**
     * get the current position of the servo
     */
    uint8_t getServoPosition(uint8_t PIN);
   /**
    * private
    */
void runLinearInterpolationServo(uint8_t blockStart,uint8_t blockEnd);
uint8_t pinOn(uint8_t pin);
void pinOff(uint8_t pin);
void DelayPreServoPulse(void);


#ifdef	__cplusplus
}
#endif

#endif	/* SERVO_H */

