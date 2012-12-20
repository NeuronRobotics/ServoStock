package com.neuronrobotics.replicator.driver;

import java.io.InputStream;
import java.io.OutputStream;

import com.neuronrobotics.replicator.gui.PrinterStatusListener;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class NRPrinter {
	private DeltaRobotPrinterPrototype device;
	private GCodeParser parser;
	private StlSlicer slicer;
	
	
	public NRPrinter(DeltaForgeDevice d) {
		Log.enableDebugPrint(true);
		
		setDevice(new DeltaRobotPrinterPrototype(d));
		setParser(new GCodeParser(getDevice()));
//		setSlicer(new StlSlicer(getDevice().getMaterialData()));
		setSlicer(new MiracleGrue(getDevice().getMaterialData()));
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
		cancelPrint();
		ThreadUtil.wait(5000);
		long start = System.currentTimeMillis();
		boolean b = getParser().print(gcode);
		System.out.println("Print Done, took "+((((double)(System.currentTimeMillis()-start))/1000.0)/60.0)+" minutes");
		cancelPrint();
		return b;
	}
	
	public boolean cancelPrint() {
		getDevice().cancelRunningPrint();
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
	public DeltaRobotPrinterPrototype getDevice() {
		return device;
	}
	public void setDevice(DeltaRobotPrinterPrototype device) {
		this.device = device;
	}
	
}
