package com.neuronrobotics.replicator.driver;

import java.io.InputStream;
import java.io.OutputStream;

import com.neuronrobotics.replicator.common.STLObject;
import com.neuronrobotics.replicator.driver.PrinterStatus.DriverState;

//import com.neuronrobotics.sdk.common.BowlerAbstractDevice;
//import com.neuronrobotics.sdk.common.BowlerAbstractConnection;

public class DeltaPrinter extends GenericPIDDevice{
	
	//Object to simplify passing around descriptions of the Printer's Status
	private PrinterStatus theStatus;
	
	/**
	 * Basic constructor
	 */
	public DeltaPrinter(){
		super();
		theStatus = new PrinterStatus();
		//TODO
	}
	
	/**
	 * Constructor that accepts connection
	 * @param connection:  
	 */
	public DeltaPrinter(BowlerAbstractConnection connection){
		super(connection);
		theStatus = new PrinterStatus();
		//TODO
	}
	
	/**
	 * Takes in the STLFile and slices that mother up into 
	 * a sliced format and outputs to given output stream
	 * @param stlInput: input stream containing model to be sliced
	 * @return true if 
	 */
	public boolean slice(InputStream stlInput, OutputStream slicedOutput){
		return true;
		//
	}
	
	/**
	 * Takes in the sliced model and begins to print
	 * @param slicedInput: input stream which holds the sliced data
	 * @return true if print is started, false otherwise
	 */
	public boolean print(InputStream slicedInput){
		if(theStatus.getDriverState()==DriverState.PRINTING) return false;
		return true;
		//TODO
	}
	
	/**
	 * 
	 * @return true if there is a print to cancel and it is canceled, false otherwise
	 */
	public boolean cancel(){
		return false;
		//TODO
	}
	
	public PrinterStatus getPrinterStatus(){
		return theStatus;
	}

}
