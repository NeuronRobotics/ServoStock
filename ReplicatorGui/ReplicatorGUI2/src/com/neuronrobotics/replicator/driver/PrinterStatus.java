package com.neuronrobotics.replicator.driver;

import java.util.ArrayList;

import javax.vecmath.*;

import com.neuronrobotics.replicator.gui.PrinterStatusListener;

public class PrinterStatus {
	
	/**
	 * This enum should be used to indicate current printer status
	 * NOT_READY indicates that the printer is not ready to print
	 * READY indicates the printer is idle and ready to receive a print job
	 * PRINTING indicates the printer is currently working
	 * ERROR indicates that an error has occurred and the print has been terminated
	 * WARNING_PRINTNIG indicates that something may be wrong but the print has not been terminated
	 * WARNING_DONE indicates that something may be wrong and the print has finished
	 * SUCCESS indicates the print has finished with no new warnings
	 * NOTE: optional message should be set for errors and warnings
	 * SUCCESS should not be taken to mean there were no warnings during the print
	 * just that there are no new warnings at the end of the print
	 */
	public enum PrinterState {
		NOT_READY, READY, PRINTING, ERROR, WARNING_PRINTING,WARNING_DONE, SUCCESS;

		private String message;

		public String getMessage() {
			return message;
		}

		private void setMessage(String m) {
			message = m;
		}
		
		public boolean hasMessage(){
			return message!=null;
		}
		
	}
	
	private PrinterState thePrinterState;
	
	private Point3f headLocation;
	
	private int printProgress;
		
	public PrinterStatus(Point3f headLocation, int printProgress, PrinterState thePrinterState){
		this.headLocation = headLocation;
		this.printProgress = printProgress;
		this.thePrinterState = thePrinterState;
	}
	
	public PrinterStatus(Point3f headLocation, int printProgress, PrinterState thePrinterState, String stateMessage){
		this.headLocation = headLocation;
		this.printProgress = printProgress;
		this.thePrinterState = thePrinterState;
		this.thePrinterState.setMessage(stateMessage);
	}
	
	public PrinterState getDriverState(){
		return thePrinterState;
	}
	
	public Point3f getHeadLocation(){
		return headLocation;
	}
	
	public int getPrintProgress(){
		return printProgress;
	}
	
}
