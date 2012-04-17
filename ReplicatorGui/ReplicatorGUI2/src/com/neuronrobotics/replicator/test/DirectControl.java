package com.neuronrobotics.replicator.test;
import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.ITaskSpaceUpdateListenerNR;
import com.neuronrobotics.sdk.addons.kinematics.TrobotKinematics;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.serial.SerialConnection;
public class DirectControl implements ITaskSpaceUpdateListenerNR {
	TrobotKinematics model;
	DeltaRobotPrinterPrototype deltaRobot;
	TransformNR current = new TransformNR();
	public DirectControl() {
		DyIO.disableFWCheck();
		DyIO master = new DyIO(new SerialConnection("/dev/DyIO1"));
		if(!master.connect()){
			throw new RuntimeException("Not a bowler Device on connection: ");
		}
		master.killAllPidGroups();
		model = new TrobotKinematics(master,"TrobotMaster.xml");
		model.addPoseUpdateListener(this);
		DyIO delt = new DyIO(new SerialConnection("/dev/DyIO0"));
		delt.connect();
		delt.enableBrownOutDetect(false);
		deltaRobot = new DeltaRobotPrinterPrototype(delt);
		Log.enableDebugPrint(false);
		deltaRobot.setCurrentPoseTarget(new TransformNR());
		while (delt.isAvailable() && master.isAvailable()) {
			long time = System.currentTimeMillis();
			try {
				deltaRobot.setDesiredTaskSpaceTransform(current,0);
			} catch (Exception e) {
				e.printStackTrace();
			}
			System.out.println("Took "+(System.currentTimeMillis()-time)+"ms");
		}
	}
	public static void main(String[] args) {
		new DirectControl();
	}
	public void onTaskSpaceUpdate(AbstractKinematicsNR source, TransformNR pose) {
		current = new TransformNR(-pose.getX(),pose.getY(),-pose.getZ(),new RotationNR());
		//System.out.println("Current = "+pose);
	}
	public void onTargetTaskSpaceUpdate(AbstractKinematicsNR source,TransformNR pose) {}
}
