/**
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

#ifndef DEBUG_H_
#define DEBUG_H_

void EnableDebugTerminal(void);
/**
 * enable printing (Defaults to enabled)
 */
void enableDebug(void);
/**
 * disable printing (Defaults to enabled)
 */
void disableDebug(void);
/**
 * print a given value as a 16 bit hex value
 */
#define prHEX(A) printfDEBUG_BYTE(GetHighNib(A>>8));printfDEBUG_BYTE(GetLowNib(A>>8));printfDEBUG_BYTE(GetHighNib(A&0x00ff));printfDEBUG_BYTE(GetLowNib(A&0x00ff))

/**
 * print the ascii of a float. No new line
 */
#define p_fl(A) printfDEBUG_FL(A)

/**
 * print the ascii of an unsigned long/int. No new line
 */
#define p_ul(A) printfDEBUG_UL(A)

/**
 * print the ascii of a signed long/int. No new line
 */
#define p_sl(A) printfDEBUG_SL(A)

/**
 * print the null terminated string with no new lines
 */
#define print(A) printfDEBUG_NNL(A)

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
#define println(A) printfDEBUG(A)

#define printStream(A,B) printByteArray(A,B);

/**
 * sends the charrector to the serial port if it is ascii, if it is not ascii, it is converted to a number then sent
 */
void printfDEBUG_BYTE(char b);

/**
 * print the null terminated string with a newline inserted at the begining of the string
 */
void printfDEBUG(const char *str);

/**
 * print the null terminated string with no new lines
 */
void printfDEBUG_NNL(const char *str);

/**
 * print the ascii of an unsigned long/int. No new line
 */
void printfDEBUG_UL(unsigned long val);

/**
 * print the ascii of a signed long/int. No new line
 */
void printfDEBUG_SL(long val);

/**
 * convert a long into an ascii string and place the string into the Buffer
 */
void ultoaMINE(unsigned long Value, unsigned char* Buffer);
/**
 * print all the bytes in a byte array. The legnth of the array must be correct
 */
void printByteArray(unsigned char * stream,unsigned short int len);
/**
 * convert a float into an ascii string and place the string into the outbuf
 */
void ftoa(float f, char * outbuf);
/**
 * print the ascii of a float. No new line
 */
void printfDEBUG_FL(float f);

/**
 * return the char of the hex value of the low 4 bits of the given byte
 */
char GetLowNib(unsigned char b);
/**
 * return the char of the hex value of the high 4 bits of the given byte
 */
char GetHighNib(unsigned char b);


//Bowler Stack Specific:
#if defined(BOWLERSTRUCTDEF_H_)
	#define printPacket printBowlerPacketDEBUG
	void printBowlerPacketDEBUG(BowlerPacket * packet);
	void printfDEBUG_BYTE(char b);
#endif
#endif /* DEBUG_H_ */
