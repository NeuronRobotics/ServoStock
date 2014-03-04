package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class RunSquare {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		TransformNR current = new TransformNR();
		DeltaForgeDevice delt = new DeltaForgeDevice();
		delt.setConnection(new SerialConnection("/dev/DeltaForge0"));
		delt.connect();
		ThreadUtil.wait(1000);
		for(int i=0;i<2;i++){
			for(int j=0;j<2;j++){
				current = new TransformNR(50*i, 50*j, 50, new RotationNR());
				System.out.println("Setting "+current);
				delt.sendLinearSection(current, 0, 0);
				ThreadUtil.wait(1000);
			}
		}
		
		delt.disconnect();
		System.exit(0);
	}

}
