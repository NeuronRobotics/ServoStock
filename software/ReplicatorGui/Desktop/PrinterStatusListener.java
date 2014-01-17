package com.neuronrobotics.replicator.gui;
import com.neuronrobotics.replicator.driver.PrinterStatus;



public interface PrinterStatusListener {
	
	public void statusChanged(PrinterStatus psl);
	
}
