package com.neuronrobotics.replicator.gui;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.LinkedList;
import java.util.Queue;

import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;
import com.neuronrobotics.replicator.driver.SliceStatusData;
import com.neuronrobotics.replicator.driver.SliceStatusData.SlicerState;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.ui.ConnectionDialog;

public class GUIDriver implements PrinterStatusListener{

	private enum DriverState{NOT_READY,IDLE,SLICING,PRINTING}
	
	private File tempGCodeFile;
	
	private DriverState currentDriverState;
	
	private NRPrinter thePrinter;
	
	private String statusString;
	
	private PrinterStatus currentPrinterStatus;

	private SliceStatusData currentSliceStatusData;
	
	private PrintThread currentPrintThread;
	
	public GUIDriver(){
		currentPrinterStatus = null;
		currentSliceStatusData = null;
		statusString = "Test Status String";
		currentDriverState = DriverState.NOT_READY;
		currentPrintThread = null;
	}

	public boolean connectPrinter() {
		DyIO dyio = new DyIO();
		if(!ConnectionDialog.getBowlerDevice(dyio)) {
			System.out.println("Fail");
			//System.exit(1);
			return false;
		}
		this.thePrinter = new NRPrinter(dyio);
		thePrinter.addPrinterStatusListener(this);
		if(thePrinter.isReady()) this.currentDriverState=DriverState.IDLE;
		return true;
	}
	
	public boolean requestPrint(File GCode){
		if(this.currentDriverState!=DriverState.IDLE) return false;
		
		
		return true;
	}
	
	public boolean requestPrint(File stl, File GCode){
		
		if(this.currentDriverState!=DriverState.IDLE){
			//TODO error dialog
			return false;
		}		
		currentPrintThread = new PrintThread(stl,GCode);
		return true;
	}
		
	public boolean requestCancel(){
		//TODO
		return false;
	}

	@Override
	public void sliceStatus(SliceStatusData ssd) {
		
	}

	@Override
	public void printStatus(PrinterStatus psl) {
		//TODO	
	}
	
	private void setDriverState(DriverState st){
		currentDriverState = st;
	}
	
	
	public String getStatusString(){
		return statusString;
	}
	
	private class PrintThread extends Thread{
		
		private File stlFile;
		private File GCodeFile;
		private boolean printSuccess;
		
		public PrintThread(File stl, File GCode){
			stlFile=stl;
			GCodeFile=GCode;
			printSuccess=false;
		}
		
		public boolean getPrintSuccess(){
			return printSuccess;
		}
		
		@Override
		public void start(){
			try {
				InputStream stlIn = new FileInputStream(stlFile);
				if(GCodeFile.exists()) GCodeFile.delete();
				GCodeFile.createNewFile();
				OutputStream gcodeOut = new FileOutputStream(GCodeFile);
				setDriverState(DriverState.SLICING);
				boolean goOn = thePrinter.slice(stlIn, gcodeOut);
				gcodeOut.close();
				//TODO prompt user if there are warnings
				if(!goOn){
					printSuccess=false;
					setDriverState(DriverState.IDLE);
					return;
				}
				InputStream gcodeIn = new FileInputStream(GCodeFile);
				setDriverState(DriverState.PRINTING);
				printSuccess = thePrinter.print(gcodeIn);
				setDriverState(DriverState.IDLE);
				return;
			} catch (FileNotFoundException e) {
				// TODO error dialog
				statusString = "";
				e.printStackTrace();
				setDriverState(DriverState.IDLE);
				printSuccess=false;
				return;
			} catch (IOException e) {
				// TODO error dialog
				setDriverState(DriverState.IDLE);
				e.printStackTrace();
				printSuccess=false;
				return;
			}
		}
		
	}
	
}
