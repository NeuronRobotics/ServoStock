package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.BowlerBoardDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class AccuracyTest {
	NRPrinter deltaRobot;
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
		BowlerBoardDevice delt = new BowlerBoardDevice();
		delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
		delt.connect();
		deltaRobot = new NRPrinter(delt);
		Log.enableDebugPrint();
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
