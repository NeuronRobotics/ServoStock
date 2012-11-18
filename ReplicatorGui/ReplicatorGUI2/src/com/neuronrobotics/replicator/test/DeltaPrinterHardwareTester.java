package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;
import com.neuronrobotics.replicator.driver.SliceStatusData;
import com.neuronrobotics.replicator.gui.PrinterStatusListener;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.serial.SerialConnection;

public class DeltaPrinterHardwareTester implements PrinterStatusListener {
	public DeltaPrinterHardwareTester() {
		DeltaForgeDevice delt = new DeltaForgeDevice();
		delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
		delt.connect();
		NRPrinter printer = new NRPrinter(delt);
		//printer.addPrinterStatusListener(this);
		System.out.println("Starting");
		Log.enableSystemPrint(false);
		try {
			for(int i=0;i<5;i++) {
				double angle = i*14-20;
				double [] joints = new double[] {angle,angle,angle,0,130};
				printer.getDevice().setDesiredJointSpaceVector(joints, 0);
				TransformNR pose = printer.getDevice().getCurrentPoseTarget();
				System.out.println(pose);
				Thread.sleep(1000);
			}
			
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.exit(0);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new DeltaPrinterHardwareTester();
	}
	@Override
	public void sliceStatus(SliceStatusData ssd) {
		// TODO Auto-generated method stub
		
	}
	@Override
	public void printStatus(PrinterStatus psl) {
		// TODO Auto-generated method stub
		
	}

}
