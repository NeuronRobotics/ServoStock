package com.neuronrobotics.replicator.driver.interpreter;
import java.util.Arrays;


/** 
 * Encapsulates the register information in a line of G code, stored as double-precision floating point values.
 *
 * @author Jonathan D.K. Gibbons
 * @version 1
 */
public class GCodeLineData {
	double lineValues[];

	/** 
	 * Construct a new object, initialized to zero.
	 */
	public GCodeLineData(){
		lineValues=new double[26];
	}

	/** 
	 * Copies a GCodeLineData object. By default, registers are copied between every line, such that a Y1.5 setting is kept if Y is not mentioned.
	 * @param toCopy Usually the data for the previous line of G code.
	 */
	public GCodeLineData(GCodeLineData toCopy) {
		lineValues=Arrays.copyOf(toCopy.lineValues,26);
	}
	
	/** 
	 * Set the value for register <tt>c</tt> in the line to <tt>val</tt>.
	 * @param c the register letter. May be upper or lower case.
	 * @param val the new value.
	 */
	public void storeWord(char c, double val) {
		int i=Character.toUpperCase(c)-'A';
		lineValues[i]=val;
	}
	
	/**
	 * Retrieve the value for register <tt>c</tt>.
	 * @param c the register letter. <em>must</em> be upper case.
	 * @return the value of the register for <tt>c</tt>
	 */
	public double getWord(char c) {
		return lineValues[c-'A'];
	}
	

	/** 
	 * Retrieve an array of values for the registers named in <tt>words</tt>.
	 * @param char words[] The register names must be upper case.
	 * @return the values of the registers in <tt>words</tt>
	 */
	public double[] getWords(char words[]) {
		double[] d=new double[words.length];
		for(int i=0; i<words.length; i++) {
			d[i]=lineValues[words[i]-'A'];
		}
		return d;
	}

	public String toString() {
		String str="GCodeLine: ";
		char c;
		for(c='A';c<='Z';c++)
			str=str+" "+c+getWord(c);
		return str;
	}
}
