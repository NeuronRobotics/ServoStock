package com.neuronrobotics.replicator.test;

import java.util.List;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class RetractPrint {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		boolean done=true;
		DeltaForgeDevice delt=null;
		while(done) {
			try {
				List<String> s =SerialConnection.getAvailableSerialPorts();
				boolean exists=false;
				for(String str:s) {
					if(str.contains("DeltaDoodle0")) {
						exists=true;
					}
				}
				if(exists) {
					delt = new DeltaForgeDevice();
					delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
					delt.connect();
					done=false;
				}else {
					ThreadUtil.wait(60000);
				}
			}catch (Exception ex) {
				//ex.printStackTrace();
				ThreadUtil.wait(60000);
			}
		}
		delt.sendLinearSection(new TransformNR(0, 0, 0, new RotationNR()), 0, 0);
		delt.disconnect();
		System.exit(0);
	}

}
