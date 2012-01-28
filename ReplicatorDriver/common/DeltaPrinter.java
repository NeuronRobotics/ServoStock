package com.neuronrobotics.replicator.driver;

import com.neuronrobotics.sdk.common.BowlerAbstractDevice;
import com.neuronrobotics.sdk.common.BowlerAbstractConnection;

public class DeltaPrinter extends GenericPIDDevice{
	
	//Object to simplify passing around descriptions of the Printer's Status
	private PrinterStatus theStatus;
	
	/**
	 * Basic constructor
	 */
	public DeltaPrinter(){
		super();
		//TODO
	}
	
	/**
	 * Constructor that accepts connection
	 * @param connection:  
	 */
	public DeltaPrinter(BowlerAbstractConnection connection){
		super(connection);
		//TODO
	}
	
	/**
	 * Takes in the STLFile and slices that mother up into 
	 * a SlicedObject, passes along PrinterStatus object if necessary
	 * @param stl: STLFile containing model to be sliced
	 * @return true if 
	 */
	public boolean slice(STLObject stl){
		//TODO
	}
	
	/**
	 * Takes in the sliced model and begins to print
	 * @param s: SlicedModel object which holds the sliced data
	 * @return true if print is started, false otherwise
	 */
	public boolean print(SlicedObject so){
		//TODO
	}
	
	/**
	 * 
	 * @return true if there is a print to cancel and it is canceled, false otherwise
	 */
	public boolean cancel(){
		//TODO
	}
	
	public PrinterStatus getPrinterStatus(){
		return theStatus;
	}

}
