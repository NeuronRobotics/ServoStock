package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.BowlerBoardDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class PrinterHardwareTest {
	
	
	public PrinterHardwareTest() throws Exception{
		BowlerBoardDevice delt = new BowlerBoardDevice();
		delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
		delt.connect();
		NRPrinter printer = new NRPrinter(delt);
		//NRPrinter printer = new NRPrinter(null);
		//Log.enableSystemPrint(false);
		int i=0;
		try {
			while(true){
				i++;
	//			int angle =(13*i)-20;
	//			double []jointSpaceVect = new double[]{angle,angle,angle,0,130};
	//			try {
	//				printer.getDevice().setDesiredJointSpaceVector(jointSpaceVect, 0);
	//				ThreadUtil.wait(1000);
	//				System.out.println("Target Angle: = "+angle+"\n"+printer.getDevice().getCurrentTaskSpaceTransform());
	//			} catch (Exception e) {
	//				// TODO Auto-generated catch block
	//				e.printStackTrace();
	//			}
				
				double z = 1*(i);
				TransformNR target = new TransformNR(0, 0, z, new RotationNR());
				printer.setDesiredTaskSpaceTransform(target, .2);
				ThreadUtil.wait(100);
				System.out.println("Target z = "+z+"\n"+printer.getCurrentTaskSpaceTransform());
			}
		}catch(Exception e){
			TransformNR target = new TransformNR(0, 0, 272.08, new RotationNR());
			printer.setDesiredTaskSpaceTransform(target, .2);
			System.exit(0);
		}
		
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			new PrinterHardwareTest();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.exit(0);
	}

}
