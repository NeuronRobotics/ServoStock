package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class AccuracyTest {
	DeltaRobotPrinterPrototype deltaRobot;
	double x = 20;
	double y =20;
	double z = -85;
	TransformNR current[] = new TransformNR[]{
			new TransformNR(x,y,z,new RotationNR()),
			new TransformNR(x,-y,z,new RotationNR()),
			new TransformNR(-x,y,z,new RotationNR()),
			new TransformNR(-x,-y,z,new RotationNR()),
	};
	public AccuracyTest(){
		DyIO delt = new DyIO(new SerialConnection("/dev/DyIO0"));
		delt.connect();
		delt.enableBrownOutDetect(false);
		deltaRobot = new DeltaRobotPrinterPrototype(delt);
		Log.enableDebugPrint(false);
		deltaRobot.setCurrentPoseTarget(new TransformNR());
		while (delt.isAvailable() ) {
			for(int i=0;i<current.length;i++){
				try {
					System.out.println("Going to: "+current[i]);
					deltaRobot.setDesiredTaskSpaceTransform(current[i],.75);
					ThreadUtil.wait(2000);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
			//System.out.println("Took "+(System.currentTimeMillis()-time)+"ms");
		}
	}
	public static void main(String[] args) {
		new AccuracyTest();
	}
}
