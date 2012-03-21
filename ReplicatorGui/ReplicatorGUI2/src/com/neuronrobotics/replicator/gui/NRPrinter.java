package com.neuronrobotics.replicator.gui;

import java.io.InputStream;
import java.io.OutputStream;

import com.neuronrobotics.replicator.driver.GCodeParser;
import com.neuronrobotics.replicator.driver.StlSlicer;
import com.neuronrobotics.sdk.addons.kinematics.delta.DeltaRobotPrinterPrototype;
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
		return parser.print(gcode);
	}
	
	public boolean cancelPrint() {
		return parser.cancel();
	}
	public boolean isReady() {
		// TODO Auto-generated method stub
		return false;
	}
	
	public void addPrinterStatusListener(PrinterStatusListener l) {
		parser.addPrinterStatusListener(l);
	}
	public void removePrinterStatusListener(PrinterStatusListener l) {
		parser.removePrinterStatusListener(l);
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
