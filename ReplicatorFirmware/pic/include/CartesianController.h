/**
 * @file CartesianController.h
 *
 * Created on: Apr 28, 2011
 * @author hephaestus
 */

#ifndef CARTESIANCONTROLLER_H_
#define CARTESIANCONTROLLER_H_
//	typedef enum _CartesianAxis{
//		X=0,
//		Y,
//		Z,
//	}CartesianAxis;
#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 1
	typedef struct __attribute__((__packed__)) _CartesianAxisDescriptor
	{


	} CartesianAxisDescriptor;

	typedef struct __attribute__((__packed__)) _CartesianBox
	{
		int index;
		CartesianAxisDescriptor axis[3];

	} CartesianBox;
	/**
	 * Initialize the cartesian controller
	 */
	void CartesianControllerInit(void);
	/**
	 * Co-Operative process for cartesian controller
	 */
	void CartesianControllerCoOp(void);
	/**
	 * Packet Event for cartesian controller
	 */
	BOOL CartesianControllerGetPacket(BowlerPacket * Packet);
	/**
	 * Packet Event for cartesian controller
	 */
	BOOL CartesianControllerPostPacket(BowlerPacket * Packet);
	/**
	 * Packet Event for cartesian controller
	 */
	BOOL CartesianControllerCriticalPacket(BowlerPacket * Packet);
#endif /* CARTESIANCONTROLLER_H_ */
