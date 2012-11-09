package com.neuronrobotics.replicator.driver.interpreter;

/** 
 * An empty code handler, for noting that "do nothing" is the correct action.
 * Presently used for absolute positioning and programming in mm, because those are the internal representations.
 * 
 * @author 
 * @version 
 */
public class EmptyCodeHandler extends CodeHandler {
	public void execute(GCodeLineData prev, GCodeLineData line) throws Exception {
	}
}

