/*
 *
 * Copyright 2009 Neuron Robotics, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#ifndef SERVO_H_
#define SERVO_H_

#define BLOCK_SIZE 8

void SetPowerState0(BOOL railOk,BOOL regulated);
void SetPowerState1(BOOL railOk,BOOL regulated);
void setPowerOverride(BOOL set);
/**
 * SetServoPos
 * @param PIN the DyIO pin to use
 * @param val the position to set the servo to
 * @param time the time in Ms for the travil to take
 */
void SetServoPos(BYTE PIN,BYTE val,float time);
BYTE GetServoPos(BYTE PIN);
void RunServo(BYTE block);
void InitServo(BYTE pin);
void DelayPreServo(void);

#endif /* SERVO_H_ */
