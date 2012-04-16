package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematics;
import com.neuronrobotics.sdk.addons.kinematics.ITaskSpaceUpdateListener;
import com.neuronrobotics.sdk.addons.kinematics.TrobotKinematics;
import com.neuronrobotics.sdk.addons.kinematics.math.Rotation;
import com.neuronrobotics.sdk.addons.kinematics.math.Transform;
import com.neuronrobotics.sdk.common.BowlerAbstractConnection;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.ui.ConnectionDialog;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class DirectControl implements ITaskSpaceUpdateListener {
	TrobotKinematics model;
	DeltaRobotPrinterPrototype deltaRobot;
	Transform current = new Transform();
	public DirectControl() {
		
		/**
		 * First create the Bowler device connection
		 */
		BowlerAbstractConnection connection = new SerialConnection("/dev/DyIO1");
		DyIO.disableFWCheck();
		DyIO master = new DyIO(connection);
		if(!master.connect()){
			throw new RuntimeException("Not a bowler Device on connection: "+connection);
		}
		master.killAllPidGroups();
		model = new TrobotKinematics(master,"TrobotMaster.xml");
		
		model.addPoseUpdateListener(this);
		
		DyIO delt = new DyIO(new SerialConnection("/dev/DyIO0"));
		delt.connect();
		delt.enableBrownOutDetect(false);
		deltaRobot = new DeltaRobotPrinterPrototype(delt);
		Log.enableDebugPrint(false);
		deltaRobot.setCurrentPoseTarget(new Transform());
		while (delt.isAvailable() && master.isAvailable()) {
			//ThreadUtil.wait(30);
			long time = System.currentTimeMillis();
			try {
				deltaRobot.setDesiredTaskSpaceTransform(current,0);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.out.println("Took "+(System.currentTimeMillis()-time)+"ms");
		}
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		new DirectControl();
	}

	@Override
	public void onTaskSpaceUpdate(AbstractKinematics source, Transform pose) {
		current = new Transform(-pose.getX(),
				pose.getY(),
				-pose.getZ(),
				new Rotation());
		System.out.println("Current = "+pose);
	}

	@Override
	public void onTargetTaskSpaceUpdate(AbstractKinematics source,Transform pose) {
		// TODO Auto-generated method stub
		
	}

}
