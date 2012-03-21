package com.neuronrobotics.replicator.driver;

import java.io.InputStream;
import java.util.ArrayList;

import com.neuronrobotics.replicator.gui.PrinterStatusListener;

public class GCodeParser {
	private ArrayList<PrinterStatusListener> listeners = new ArrayList<PrinterStatusListener>();
	
	public GCodeParser(DeltaRobotPrinterPrototype device) {
		// TODO Auto-generated constructor stub
	}

	public boolean print(InputStream gcode) {
		//this should be a thread that takes the gcode and sends it to the printer
		return false;
	}

	public boolean cancel() {
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
		return false;
	}
	
}
