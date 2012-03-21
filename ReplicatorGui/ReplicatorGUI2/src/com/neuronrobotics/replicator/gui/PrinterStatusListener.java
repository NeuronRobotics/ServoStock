package com.neuronrobotics.replicator.gui;
import com.neuronrobotics.replicator.driver.PrinterStatus;
import com.neuronrobotics.replicator.driver.SliceStatusData;



public interface PrinterStatusListener {
	
	public void sliceStatus(SliceStatusData ssd);
	
	public void statusChanged(PrinterStatus psl);
	
}
