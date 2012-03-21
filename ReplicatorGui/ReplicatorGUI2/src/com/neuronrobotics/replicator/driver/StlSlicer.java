package com.neuronrobotics.replicator.driver;

import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;

import com.neuronrobotics.replicator.gui.PrinterStatusListener;

public class StlSlicer {
	private ArrayList<PrinterStatusListener> listeners = new ArrayList<PrinterStatusListener>();
	public StlSlicer(MaterialData materialData) {
		//This is the stub class for the stl slicing system. 
	}

	public boolean slice(InputStream stl,OutputStream gcode) {
		
		return true;
	}
	
	private void fireStatus(SliceStatusData p) {
		for(PrinterStatusListener l: listeners) {
			l.sliceStatus(p);
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
}
