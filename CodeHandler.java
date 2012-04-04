

/** 
 * Encapsulates a handler for a particular G or M code.
 * 
 * @author Jonathan D.K. Gibbons
 * @version 1
 */
public interface CodeHandler {
	
	/** 
	 * Execute the action associated with this handler.
	 * this <em>is permitted</em> to modify the values stored in line; prev should be considered immutable.
	 * 
	 * @param prev The register values for the previous line of G code. Contains such things as the last set position, for interpolation schemes.
	 * @param line The current set of register values for this line of G code.
	 * @throws Exception 
	 */
	public void execute(GCodeLineData prev, GCodeLineData line) throws Exception;
}

