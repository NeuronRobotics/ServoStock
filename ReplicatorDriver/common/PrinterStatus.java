package com.neuronrobotics.replicator.driver;

import java.util.ArrayList;

import javax.vecmath.*;

public class PrinterStatus {
	
	public enum DriverState{NOT_READY,READY,PRINTING,PRINTER_ERROR,PROCESSING_ERROR}
	
	private DriverState theDriverState;
	
	private Point3f headLocation;
	
	private int printProgress;
	
	private ArrayList<PrinterStatusListener> listeners;
	
	public PrinterStatus(){
		headLocation = new Point3f();
		theDriverState = DriverState.NOT_READY;
		printProgress = 0;
		listeners = new ArrayList<PrinterStatusListener>();
	}
	
	public void setDriverState(DriverState dstate){
		theDriverState = dstate;
	}
	
	public DriverState getDriverState(){
		return theDriverState;
	}
	
	public void setHeadLocation(Point3f hl){
		headLocation = hl;
	}
	
	public Point3f getHeadLocation(){
		return headLocation;
	}
	
	public void setPrintProgress(int pp){
		printProgress = pp;
	}
	
	public int getPrintProgress(){
		return printProgress;
	}

	public void addListener(PrinterStatusListener psl){
		listeners.add(psl);
	}
	
	private void notifyStatusListeners(){
		for(PrinterStatusListener l:listeners) l.statusChanged(this); 
	}
	
}
