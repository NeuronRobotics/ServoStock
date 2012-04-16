package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematics;
import com.neuronrobotics.sdk.addons.kinematics.ITaskSpaceUpdateListener;
import com.neuronrobotics.sdk.addons.kinematics.TrobotKinematics;
import com.neuronrobotics.sdk.addons.kinematics.math.Transform;
import com.neuronrobotics.sdk.common.BowlerAbstractConnection;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.ui.ConnectionDialog;

public class DirectControl implements ITaskSpaceUpdateListener {
	TrobotKinematics model;
	DeltaRobotPrinterPrototype device;
	public DirectControl() {
		
		/**
		 * First create the Bowler device connection
		 */
		BowlerAbstractConnection connection = ConnectionDialog.promptConnection();
		DyIO.disableFWCheck();
		DyIO master = new DyIO(connection);
		if(!master.connect()){
			throw new RuntimeException("Not a bowler Device on connection: "+connection);
		}
		master.killAllPidGroups();
		model = new TrobotKinematics(master,"TrobotMaster.xml");
		
		model.addPoseUpdateListener(this);
		
		DyIO delt = new DyIO(ConnectionDialog.promptConnection());
		delt.connect();
		delt.enableBrownOutDetect(false);
		device = new DeltaRobotPrinterPrototype(delt);
		
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {


	}

	@Override
	public void onTaskSpaceUpdate(AbstractKinematics source, Transform pose) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onTargetTaskSpaceUpdate(AbstractKinematics source,
			Transform pose) {
		// TODO Auto-generated method stub
		
	}

}
