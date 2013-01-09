package com.neuronrobotics.replicator.test;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;
import com.neuronrobotics.replicator.driver.SliceStatusData;
import com.neuronrobotics.replicator.driver.interpreter.CodeHandler;
import com.neuronrobotics.replicator.driver.interpreter.GCodeInterpreter;
import com.neuronrobotics.replicator.driver.interpreter.GCodeLineData;
import com.neuronrobotics.replicator.gui.PrinterStatusListener;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.pid.VirtualGenericPIDDevice;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.ui.ConnectionDialog;

public class GcodeTest implements PrinterStatusListener {
	private GcodeTest(String filename) throws Exception {
//		DeltaForgeDevice delt = new DeltaForgeDevice();

//		delt.setConnection(new SerialConnection("/dev/DeltaDoodle0"));
//		delt.connect();
//		NRPrinter printer = new NRPrinter(delt);
		final PrintStream trace=new PrintStream(new FileOutputStream("trace.txt"));
		NRPrinter printer = new NRPrinter(null);
		printer.addPrinterStatusListener(this);
		//Log.enableDebugPrint(false);
//		File gcode = new File("cube.stl-dump.gcode");
		File gcode = new File(filename);
		try {
			//This is time consuming
			printer.slice(PrinterTest.class.getResourceAsStream("bottle.stl"),new FileOutputStream(gcode));
			//...
		//	if(printer.isReady())
//				printer.print(new FileInputStream(gcode));
			GCodeInterpreter interp=new GCodeInterpreter();
			int i;
			for(i=0;i<300;i++) {
				final int j=i;
				interp.setGHandler(j,new CodeHandler() {
				public void execute(GCodeLineData prev, GCodeLineData next) {
					trace.println("TRACE: G handler "+j);
					trace.println("PREV: "+prev);
					trace.println("NEXT: "+next);
					trace.println();
				}
				});
				interp.setMHandler(j,new CodeHandler() {
				public void execute(GCodeLineData prev, GCodeLineData next) {
					trace.println("TRACE: M handler "+j);
					trace.println("PREV: "+prev);
					trace.println("NEXT: "+next);
					trace.println();
				}
				});
			}
			interp.tryInterpretStream(new FileInputStream(gcode));
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		trace.close();
		System.exit(0);
	}
	GcodeTest() throws Exception {
		this("shotGlass.gcode");
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		try {
			if(args.length>1) {
				new GcodeTest(args[0]);
			} else {
				new GcodeTest();
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
