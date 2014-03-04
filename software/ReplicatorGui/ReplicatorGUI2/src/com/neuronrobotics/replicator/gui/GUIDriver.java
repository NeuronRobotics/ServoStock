package com.neuronrobotics.replicator.gui;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.LinkedList;

import com.neuronrobotics.replicator.driver.DeltaForgeDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.replicator.driver.PrinterStatus;
import com.neuronrobotics.replicator.driver.PrinterStatusListener;
import com.neuronrobotics.replicator.driver.SliceStatusData;
import com.neuronrobotics.sdk.ui.ConnectionDialog;

public class GUIDriver implements PrinterStatusListener, GUIBackendInterface {

	private DriverState currentDriverState;

	private NRPrinter thePrinter;

	private String statusString;

	private PrinterStatus currentPrinterStatus;
	private LinkedList<PrinterStatus> printStatusLog;

	private SliceStatusData currentSliceStatusData;
	private LinkedList<SliceStatusData> sliceStatusLog;

	private SliceAndPrintThread currentPrintThread;

	private GUIFrontendInterface theFrontend;

	private boolean cancelRequested;

	public GUIDriver() {
		currentPrinterStatus = null;
		currentSliceStatusData = null;
		statusString = "Welcome";
		currentDriverState = DriverState.NOT_READY;
		currentPrintThread = null;
		printStatusLog = new LinkedList<PrinterStatus>();
		sliceStatusLog = new LinkedList<SliceStatusData>();
		theFrontend = new EmptyFrontend();
	}

	public GUIDriver(GUIFrontendInterface front) {
		currentPrinterStatus = null;
		currentSliceStatusData = null;
		statusString = "Welcome";
		currentDriverState = DriverState.NOT_READY;
		currentPrintThread = null;
		printStatusLog = new LinkedList<PrinterStatus>();
		sliceStatusLog = new LinkedList<SliceStatusData>();
		theFrontend = front;
	}

	public void setFrontend(GUIFrontendInterface front) {
		theFrontend = front;
	}

	public boolean connectVirtualPrinter() {
		if (thePrinter != null) thePrinter.removePrinterStatusListener(this);
		thePrinter = new NRPrinter(null);
		thePrinter.addPrinterStatusListener(this);
		this.currentDriverState = DriverState.IDLE;
		statusString = "Connected to Virtual Printer";
		theFrontend.alertStatusUpdated();
		return true;
	}

	public boolean connectPrinter() {
		DeltaForgeDevice delt = new DeltaForgeDevice();
		if (!ConnectionDialog.getBowlerDevice(delt)) {
			System.out.println("Fail");
			return connectVirtualPrinter(); //TODO remove eventually
		}
		if (thePrinter != null) thePrinter.removePrinterStatusListener(this);
		this.thePrinter = new NRPrinter(delt);
		thePrinter.addPrinterStatusListener(this);
		if (thePrinter.isReady()) this.currentDriverState = DriverState.IDLE;
		statusString = "Printer Connected";
		theFrontend.alertStatusUpdated();
		return true;
	}

	public boolean requestPrint(File GCode) {
		System.out.println("Starting print...");
		if (this.currentDriverState != DriverState.IDLE)
			return false;
		try {
			PrintThread pt = new PrintThread(GCode);
			pt.start();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			theFrontend.errorDialog("Error: GCode File was Not Found");
			statusString = "Print Failed: GCode File Not Found";
			theFrontend.alertStatusUpdated();
			return false;
		}//TODO test
		return true;
	}

	public boolean requestPrint(File stl, File GCode) {
		System.out.println("Starting print...");
		if (this.currentDriverState == DriverState.PRINTING) {
			theFrontend.errorDialog("Already Printing!");
			return false;
		}
		if (this.currentDriverState == DriverState.NOT_READY) {
			boolean attemptFix = theFrontend.errorDialogWithFix("Printer not connected!","Connect Printer?");
			if(attemptFix){
				this.connectPrinter();
				return requestPrint(stl,GCode);
			}
			statusString = "Printer not connected!";
			theFrontend.alertStatusUpdated();
			return false;
		}
		
		currentPrintThread = new SliceAndPrintThread(theFrontend, stl, GCode);
		currentPrintThread.start();
		this.theFrontend.alertStatusUpdated();
		return true;
	}

	@Override
	public boolean requestSlice(File stl, File GCode) {
		// TODO
		return false;
	}

	@Override
	public boolean requestCancel() {
		cancelRequested = true;
		boolean result = thePrinter.cancelPrint();
		if (result) {
			statusString = "Print canceled";
			theFrontend.alertStatusUpdated();
		} else
			statusString = "No print to cancel";
		theFrontend.alertStatusUpdated();
		cancelRequested = false;
		return result;
	}

	@Override
	public com.neuronrobotics.replicator.gui.GUIBackendInterface.DriverState getCurrentDriverState() {
		return currentDriverState;
	}

	@Override
	public void printStatus(PrinterStatus psl) {
		printStatusLog.add(psl);
		currentPrinterStatus = psl;
		this.theFrontend.alertStatusUpdated();
	}

	@Override
	public void sliceStatus(SliceStatusData ssd) {
		sliceStatusLog.add(ssd);
		currentSliceStatusData = ssd;
		this.theFrontend.alertStatusUpdated();
	}

	private void setDriverState(DriverState st) {
		currentDriverState = st;
	}

	public String getStatusString() {
		return statusString;
	}

	private class SliceAndPrintThread extends Thread {

		private File stlFile;
		private File GCodeFile;
		private boolean printSuccess;
		private GUIFrontendInterface front;
		private LinkedList<String> sliceWarnings;
		private boolean done;
		private boolean sliceOnly;

		public SliceAndPrintThread(GUIFrontendInterface front, File stl,
				File GCode) {
			stlFile = stl;
			GCodeFile = GCode;
			printSuccess = false;
			this.front = front;
			sliceWarnings = new LinkedList<String>();
			done = false;
			sliceOnly = false;
		}

		public SliceAndPrintThread(GUIFrontendInterface front, File stl,
				File GCode, boolean sliceOnly) {
			stlFile = stl;
			GCodeFile = GCode;
			printSuccess = false;
			this.front = front;
			sliceWarnings = new LinkedList<String>();
			done = false;
			this.sliceOnly = sliceOnly;
		}

		public SliceAndPrintThread(File stl,File GCode){
			stlFile = stl;
			GCodeFile = GCode;
		}
		
		public boolean getPrintSuccess() {
			return printSuccess;
		}

		@Override
		public void run() {
			if (!done)
				done = true;
			else
				return; // TODO throw an exception here?
			try {
			
			/*if (currentDriverState != DriverState.IDLE) {
				String err = (currentDriverState == DriverState.NOT_READY) ? "Not connected"
						: "Drivers busy";
				front.errorDialog(err);
				statusString = err;
				theFrontend.alertStatusUpdated();
				return;
			}
			
			try {
			
				/*
				  InputStream stlIn = new FileInputStream(stlFile); if
				  (GCodeFile.exists()) GCodeFile.delete();
				  GCodeFile.createNewFile(); OutputStream gcodeOut = new
				  FileOutputStream(GCodeFile);
				  setDriverState(DriverState.SLICING); boolean goOn =
				  thePrinter.slice(stlIn, gcodeOut); gcodeOut.close(); if
				  (!goOn) { printSuccess = false;
				  front.errorDialog("Slice failed");
				  setDriverState(DriverState.IDLE); return; } for (String s :
				  sliceWarnings) { goOn =
				  front.userPrompt("Warning:\ns\n\nPrint anyway?"); if (!goOn)
				  { setDriverState(DriverState.IDLE); statusString =
				  "User aborted print"; return; } }
				 */
				// InputStream gcodeIn = new FileInputStream(GCodeFile);
				// TODO uncomment above, following for testing only
				
				setDriverState(DriverState.IDLE);
				InputStream gcodeIn = new FileInputStream("test.gcode"); // TODO
				setDriverState(DriverState.PRINTING);
				statusString = "Printing...";
				theFrontend.alertStatusUpdated();
				printSuccess = thePrinter.print(gcodeIn);
				if (!printSuccess) {
					setDriverState(DriverState.IDLE);
					if (!cancelRequested) {
						front.errorDialog("Print failed");
						statusString = "Print failed";
						theFrontend.alertStatusUpdated();
					}
					return;
				}
				statusString = "Print completed succssfully!";
				setDriverState(DriverState.IDLE);
				theFrontend.alertStatusUpdated();
				return;
			} catch (FileNotFoundException e) {
				front.errorDialog("File not found. Print aborted.");
				statusString = "Print aborted";
				e.printStackTrace();
				setDriverState(DriverState.IDLE);
				theFrontend.alertStatusUpdated();
				printSuccess = false;
				return;
			} catch (IOException e) {
				front.errorDialog("IO Exception. Print aborted.");
				statusString = "Print aborted";
				setDriverState(DriverState.IDLE);
				e.printStackTrace();
				printSuccess = false;
				theFrontend.alertStatusUpdated();
				return;
			}
			
				
		}

	}

	private class SliceThread extends Thread {

		InputStream stlStream;
		OutputStream gcodeStream;
		File gcodeFile;
		boolean done, sliceSuccess, printAfter;

		public SliceThread(File stl, File gcode, boolean printAfter) throws FileNotFoundException {
			stlStream = new FileInputStream(stl);
			gcodeFile = gcode;
			gcodeStream = new FileOutputStream(gcode);
			done = false;
			sliceSuccess = false;
			this.printAfter = printAfter;
		}

		public SliceThread(InputStream stlStream, OutputStream gcodeStream) {
			this.stlStream = stlStream;
			this.gcodeStream = gcodeStream;
			done = false;
			sliceSuccess = false;
		}

		public void run() {
			if (!done)
				done = true;
			else
				return; // TODO throw an exception here?
			if (currentDriverState != DriverState.IDLE) {
				String err = (currentDriverState == DriverState.NOT_READY) ? "Not connected"
						: "Drivers busy";
				theFrontend.errorDialog(err);
				return;
			}

			setDriverState(DriverState.SLICING);
			sliceSuccess = thePrinter.slice(stlStream, gcodeStream);
			try {
				gcodeStream.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			if (!sliceSuccess) {
				theFrontend.errorDialog("Slice failed!");
				statusString = "Slice failed";
				setDriverState(DriverState.IDLE);
				return;
			}
			setDriverState(DriverState.IDLE);
						
			return;

		}

	}

	private class PrintThread extends Thread {

		private InputStream gcodeStream;

		private boolean printSuccess;
		private boolean done;

		public PrintThread(File gcode) throws FileNotFoundException {

			gcodeStream = new FileInputStream(gcode);
			printSuccess = false;
			done = false;
		}

		public PrintThread(InputStream gcode) {
			gcodeStream = gcode;
			printSuccess = false;
			done = false;
		}

		public boolean getPrintSuccess() {
			return printSuccess;
		}

		@Override
		public void run() {
			System.out.println("In print thread");
			if (!done)
				done = true;
			else
				return; // TODO throw an exception here?
			if (currentDriverState != DriverState.IDLE) {
				String err = (currentDriverState == DriverState.NOT_READY) ? "Not connected"
						: "Drivers busy";
				theFrontend.errorDialog(err);
				return;
			}
			setDriverState(DriverState.PRINTING);
			statusString = "Printing...";
			theFrontend.alertStatusUpdated();
			printSuccess = thePrinter.print(gcodeStream);
			if (!printSuccess) {
				theFrontend.errorDialog("Print failed!");
				statusString = "Print failed!";
			} else
				statusString = "Print completed succssfully!";
			setDriverState(DriverState.IDLE);
			theFrontend.alertStatusUpdated();
			return;
		}

	}

	@Override
	public int getPrintProgress() {
		if (currentDriverState != DriverState.PRINTING
				&& currentDriverState != DriverState.BOTH) {
			return 0;
		} else if (currentPrinterStatus != null) {
			return currentPrinterStatus.getPrintProgress();
		}
		return 0;
	}

	@Override
	public int getSliceProgress() {
		if (currentDriverState != DriverState.SLICING
				&& currentDriverState != DriverState.BOTH) {
			return 0;
		} else if (currentSliceStatusData != null) {
			return currentSliceStatusData.getSliceProgress();
		}
		return 0;
	}

}
