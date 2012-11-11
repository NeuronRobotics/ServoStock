package com.neuronrobotics.replicator.test;

import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class PrinterHardwareTest {
	
	
	public PrinterHardwareTest(){
//		DeltaDoodle delt = new DeltaDoodle();
//		delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
//		delt.connect();
//		NRPrinter printer = new NRPrinter(delt);
		NRPrinter printer = new NRPrinter(null);
		
		for (int i=0;i<5;i++){
			int angle =(13*i)-20;
			double []jointSpaceVect = new double[]{angle,angle,angle,0,130};
			try {
				printer.getDevice().setDesiredJointSpaceVector(jointSpaceVect, 0);
				ThreadUtil.wait(1000);
				System.out.println("Target Angle: = "+angle+"\n"+printer.getDevice().getCurrentTaskSpaceTransform());
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		System.exit(0);
		
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new PrinterHardwareTest();
	}

}
