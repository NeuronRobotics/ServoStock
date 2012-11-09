package com.neuronrobotics.replicator.driver.interpreter;

import java.util.List;

/** 
 * Encapsulates a handler for a particular G or M code.
 * 
 * @author Jonathan D.K. Gibbons
 * @version 1
 */
public abstract class CodeHandler {
	
	/** 
	 * Execute the action associated with this handler.
	 * this <em>is permitted</em> to modify the values stored in line; prev should be considered immutable.
	 * 
	 * @param prev The register values for the previous line of G code. Contains such things as the last set position, for interpolation schemes.
	 * @param line The current set of register values for this line of G code.
	 * @throws Exception 
	 */
	public abstract void execute(GCodeLineData prev, GCodeLineData line) throws Exception;

	List<CodeHandler> subHandlers;
	public void setSubHandlers(List<CodeHandler> subHandlers) {
		this.subHandlers=subHandlers;
	}

	public void callSubMethods(GCodeLineData prev, GCodeLineData line) throws Exception {
		for(CodeHandler handler: subHandlers)
			handler.execute(prev, line);
	}
}

