package com.neuronrobotics.replicator.driver;

import java.io.InputStream;
import java.io.OutputStream;

import com.neuronrobotics.replicator.gui.PrinterStatusListener;
import com.neuronrobotics.sdk.dyio.DyIO;

public class NRPrinter {
	DeltaRobotPrinterPrototype device;
	private GCodeParser parser;
	private StlSlicer slicer;
	
	
	public NRPrinter(DyIO d) {
		device = new DeltaRobotPrinterPrototype(d);
		setParser(new GCodeParser(device));
		setSlicer(new StlSlicer(device.getMaterialData()));
	}
	/**
	 * 
	 * @param stl the input stream
	 * @param gcode the gcode to be written to
	 * @return
	 */
	public boolean slice(InputStream stl,OutputStream gcode) {
		return getSlicer().slice(stl, gcode);
	}
	
	/**
	 * 
	 * @param gcode the gcode to be sent to the printer
	 * @return
	 */
	public boolean print(InputStream gcode) {
		System.out.println("Printing now.");
		return getParser().print(gcode);
	}
	
	public boolean cancelPrint() {
		return getParser().cancel();
	}
	public boolean isReady() {
		// TODO Auto-generated method stub
		return getParser().isReady();
	}
	
	public void addPrinterStatusListener(PrinterStatusListener l) {
		getParser().addPrinterStatusListener(l);
		getSlicer().addPrinterStatusListener(l);
	}
	public void removePrinterStatusListener(PrinterStatusListener l) {
		getParser().removePrinterStatusListener(l);
		getSlicer().removePrinterStatusListener(l);
	}
	private void setSlicer(StlSlicer slicer) {
		this.slicer = slicer;
	}
	public StlSlicer getSlicer() {
		return slicer;
	}
	private void setParser(GCodeParser parser) {
		this.parser = parser;
	}
	public GCodeParser getParser() {
		return parser;
	}
	
}
