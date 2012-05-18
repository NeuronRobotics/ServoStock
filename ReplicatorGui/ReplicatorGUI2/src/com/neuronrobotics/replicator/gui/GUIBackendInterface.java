package com.neuronrobotics.replicator.gui;

import java.io.File;

public interface GUIBackendInterface {
	
	public enum DriverState{NOT_READY,IDLE,SLICING,PRINTING,BOTH}
		
	public boolean connectPrinter();
	
	public void setFrontend(GUIFrontendInterface front);
	
	public boolean requestSlice(File stl, File GCode);
	
	public boolean requestPrint(File GCode);
	
	public boolean requestPrint(File stl, File GCode);
	
	public boolean requestCancel();
	
	public int getPrintProgress();
	
	public int getSliceProgress();
	
	public String getStatusString();
	
	public DriverState getCurrentDriverState();
	
}
