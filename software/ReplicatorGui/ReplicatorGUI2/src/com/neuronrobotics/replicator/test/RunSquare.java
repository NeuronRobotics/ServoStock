package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.ui.ConnectionDialog;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class RunSquare {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		TransformNR current = new TransformNR();
		DeltaForgeDevice delt = new DeltaForgeDevice();
		ConnectionDialog.getBowlerDevice(delt);
		int delay = 1000;
		int rad = 50;
		for(int k=0;k<10;k++){
				for(int i=0;i<2;i++){
				for(int j=0;j<2;j++){
					current = new TransformNR(rad*i-rad/2, rad*j-rad/2,100, new RotationNR());
					System.out.println("Setting "+current);
					delt.sendLinearSection(current, 0, delay);
					//ThreadUtil.wait((int) (delay*1.2));
				}
			}
		}
		
		delt.disconnect();
		System.exit(0);
	}

}
