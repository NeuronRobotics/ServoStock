package com.neuronrobotics.replicator.test;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;
import com.neuronrobotics.replicator.driver.SliceStatusData;
import com.neuronrobotics.replicator.gui.PrinterStatusListener;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.ui.ConnectionDialog;

public class PrinterTest implements PrinterStatusListener {
	private PrinterTest(String filename) {
		DeltaForgeDevice delt = new DeltaForgeDevice();

		delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
		delt.connect();
		NRPrinter printer = new NRPrinter(delt);
//	NRPrinter printer = new NRPrinter(null);
		printer.addPrinterStatusListener(this);
		//Log.enableDebugPrint(false);
//		File gcode = new File("cube.stl-dump.gcode");
		File gcode = new File(filename);
		try {
			//This is time consuming
//			printer.slice(PrinterTest.class.getResourceAsStream("bottle.stl"),new FileOutputStream(gcode));
			//...
			if(printer.isReady())
				printer.print(new FileInputStream(gcode));
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		System.exit(0);
	}
	PrinterTest() {
		this("shotGlass.gcode");
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			if(args.length>1) {
				new PrinterTest(args[0]);
			} else {
				new PrinterTest();
			}
		}catch (Exception ex) {
			ex.printStackTrace();
			System.exit(1);
		}
	}
	@Override
	public void printStatus(PrinterStatus psl) {
		//System.out.println("Printer status: "+psl);
	}
	@Override
	public void sliceStatus(SliceStatusData ssd) {
		//System.out.println("Printer status: "+ssd);
	}

}
