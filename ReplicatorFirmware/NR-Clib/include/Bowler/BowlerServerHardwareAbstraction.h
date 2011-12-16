/**
 * @file BowlerHardwareAbstraction.h
 *
 * Created on: May 27, 2010
 * @author hephaestus
 *
 * This header defines the FIFO's for the bowler server.
 */

#ifndef BOWLERHARDWAREABSTRACTION_H_
#define BOWLERHARDWAREABSTRACTION_H_


/**
 * @return returns the number of bytes in the fifo
 */
UINT16 getNumBytes(BYTE_FIFO_STORAGE * fifo);
/**
 * get a stream of this legnth from the connection
 */
UINT16 getStream(BYTE *,UINT16,BYTE_FIFO_STORAGE * fifo);
/**
 * send the array out the connection
 */
UINT16 putStream(BYTE *,UINT16);
/**
 * get the time in ms
 */
float getMs(void);

/**
 * send this char to the print terminal
 */
void putCharDebug(char c);
/**
 * Start the scheduler
 */
void startScheduler(void);


#endif /* BOWLERHARDWAREABSTRACTION_H_ */
