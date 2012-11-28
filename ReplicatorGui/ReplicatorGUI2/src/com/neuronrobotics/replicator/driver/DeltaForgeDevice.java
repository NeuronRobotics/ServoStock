package com.neuronrobotics.replicator.driver;

import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.commands.cartesian.CancelPrintCommand;
import com.neuronrobotics.sdk.commands.cartesian.LinearInterpolationCommand;
import com.neuronrobotics.sdk.common.BowlerDatagram;
import com.neuronrobotics.sdk.common.ByteList;
import com.neuronrobotics.sdk.genericdevice.GenericPIDDevice;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class DeltaForgeDevice extends GenericPIDDevice {
	
	private int numSpacesRemaining = 1;
	
	/**
	 * This function will set up a multi-dimentional send for position and interpolation
	 * @param x new x position
	 * @param y new y position
	 * @param z new z position
	 * @param mmOfFiliment new target for mm of filiment
	 * @param ms time in MS
	 * @return number of spaces in the buffer
	 */
	public int sendLinearSection(TransformNR taskSpaceTransform, double mmOfFiliment, int ms) {
		RuntimeException e= new RuntimeException("There is no more room left");;
		if(numSpacesRemaining == 0 ) {
			throw e;
		}
		
		BowlerDatagram dg = send(new LinearInterpolationCommand(taskSpaceTransform, mmOfFiliment, ms));
		if(dg.getRPC().equalsIgnoreCase("_err")) {
			throw e;
		}
		
		numSpacesRemaining = ByteList.convertToInt(dg.getData().getBytes(	0,//Starting index
																				4),//number of bytes
																				false);//True for signed data
		System.out.println("Running line x="+taskSpaceTransform.getX()+" y="+taskSpaceTransform.getY()+" z="+taskSpaceTransform.getZ()+" num spaces="+numSpacesRemaining);

		return numSpacesRemaining;
	}
	
	public void cancelRunningPrint() {
		send(new CancelPrintCommand());
		
	}
	
	@Override
	public void onAsyncResponse(BowlerDatagram data) {
		super.onAsyncResponse(data);
		if(data.getRPC().equalsIgnoreCase("_sli")) {
			//System.out.println(data);
			numSpacesRemaining = ByteList.convertToInt(data.getData().getBytes(	0,//Starting index
																				4),//number of bytes
																				false);//True for signed data
		}
	}

	public int getNumberOfSpacesInBuffer() {
		return numSpacesRemaining;
	}
	
}
