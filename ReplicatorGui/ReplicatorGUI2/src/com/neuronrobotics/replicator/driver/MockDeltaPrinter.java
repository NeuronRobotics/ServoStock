package com.neuronrobotics.replicator.driver;

import java.io.InputStream;

import com.neuronrobotics.replicator.common.STLObject;

//import com.neuronrobotics.sdk.common.BowlerAbstractDevice;
//import com.neuronrobotics.sdk.common.BowlerAbstractConnection;

public class MockDeltaPrinter extends DeltaPrinter{
	
	//Object to simplify passing around descriptions of the Printer's Status
	private PrinterStatus theStatus;
	
	/**
	 * Basic constructor
	 */
	public MockDeltaPrinter(){
		super();
		//TODO
	}
	
	/**
	 * Constructor that accepts connection
	 * @param connection:  
	 */
	public MockDeltaPrinter(BowlerAbstractConnection connection){
		super(connection);
		//TODO
	}
	
	/**
	 * Takes in the STLFile and slices that mother up into 
	 * a SlicedObject, passes along PrinterStatus object if necessary
	 * @param stl: STLFile containing model to be sliced
	 * @return true if 
	 */
	public boolean slice(InputStream stl){
		
		
		return true;
		//TODO
	}
	
	/**
	 * Takes in the sliced model and begins to print
	 * @param s: SlicedModel object which holds the sliced data
	 * @return true if print is started, false otherwise
	 */
	public boolean print(InputStream so){
		return true;
		//TODO
	}
	
	/**
	 * 
	 * @return true if there is a print to cancel and it is canceled, false otherwise
	 */
	public boolean cancel(){
		return true;
		//TODO
	}
	
	public PrinterStatus getPrinterStatus(){
		return theStatus;
	}

}
