package com.neuronrobotics.replicator.driver;

import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.commands.cartesian.LinearInterpolationCommand;
import com.neuronrobotics.sdk.common.BowlerDatagram;
import com.neuronrobotics.sdk.common.ByteList;
import com.neuronrobotics.sdk.genericdevice.GenericPIDDevice;

public class DeltaDoodle extends GenericPIDDevice {
	
	/**
	 * This function will set up a multi-dimentional send for position and interpolation
	 * @param x new x position
	 * @param y new y position
	 * @param z new z position
	 * @param mmOfFiliment new target for mm of filiment
	 * @param ms time in MS
	 * @return true is there is space for more packets in the buffer
	 */
	boolean sendLinearSection(TransformNR taskSpaceTransform, double mmOfFiliment, int ms) {
		
		
		
		BowlerDatagram dg = send(new LinearInterpolationCommand(taskSpaceTransform, mmOfFiliment, ms));
		
		int numSpaceRemaining = ByteList.convertToInt(dg.getData().getBytes(	0,//Starting index
																				4),//number of bytes
																				false);//True for signed data
		System.out.println("Running line x="+taskSpaceTransform.getX()+" y="+taskSpaceTransform.getY()+" z="+taskSpaceTransform.getZ()+" num spaces="+numSpaceRemaining);
		return numSpaceRemaining>0;
	}
	
}
