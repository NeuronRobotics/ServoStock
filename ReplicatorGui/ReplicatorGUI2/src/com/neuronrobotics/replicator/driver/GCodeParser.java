package com.neuronrobotics.replicator.driver;
import com.neuronrobotics.replicator.driver.interpreter.*;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.concurrent.locks.ReentrantLock;
import com.neuronrobotics.replicator.gui.PrinterStatusListener;

public class GCodeParser {
	private ArrayList<PrinterStatusListener> listeners = new ArrayList<PrinterStatusListener>();
	private GenericKinematicsGCodeInterpreter interp;
	DeltaRobotPrinterPrototype device;

	public GCodeParser(DeltaRobotPrinterPrototype device) {
		// TODO Auto-generated constructor stub
		this.device=device;
	}

	public boolean print(InputStream gcode) {
		//this should be a thread that takes the gcode and sends it to the printer
		interp=new GenericKinematicsGCodeInterpreter(device); // Could reuse.
		System.out.println("Reached print.");
		try {
			interp.tryInterpretStream(gcode);
			return true;
		} catch (Exception e) { 
			// um... this is bad. Ideally, the kinematics methods probably shouldn't through Exception, but we'll just catch it here for now.
			System.err.println(e);
			e.printStackTrace();
		}
		return false;
	}

	public boolean cancel() {
		if(interp!=null) {
			return interp.cancel();
		}
		return false;
	}
	
	private void fireStatus(PrinterStatus p) {
		for(PrinterStatusListener l: listeners) {
			l.printStatus(p);
		}
	}

	public void addPrinterStatusListener(PrinterStatusListener l) {
		if(!listeners.contains(l))
			listeners.add(l);
	}

	public void removePrinterStatusListener(PrinterStatusListener l) {
		if(listeners.contains(l))
			listeners.remove(l);
	}

	public boolean isReady() {
		// TODO Auto-generated method stub
//		return false;
		return true;
	}
	
}
