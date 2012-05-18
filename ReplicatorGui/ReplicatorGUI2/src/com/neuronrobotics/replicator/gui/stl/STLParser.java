package com.neuronrobotics.replicator.gui.stl;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;


public abstract class STLParser {

	protected InputStream stream;
	protected String name;
		
	public static STLParser getParser(InputStream is){
		byte[] b = new byte[80];
		try {
			is.read(b, 0, 1);
			int ct = 1;
			while(b[ct-1]==' '&&ct<80){
				is.read(b, ct, 1);
				ct++;
			}
			String str = "";
			if (ct<80){
				is.read(b,1,4);
				for(int i=0;i<5;i++){
				str+=((char)b[i]);
				ct+=4;
			}
			}
			if(str.equalsIgnoreCase("solid")) return new ASCIISTLParser(is);
			return new BinarySTLParser(is,ct,b);
		} catch (IOException e) {
			e.printStackTrace();
		}
		return null; //Should use an exception here
	}

	/** 
	 * 
	 * @return next facet is returned as STLFacet object
	 */
	public abstract STLFacet nextFacet() throws Exception; //TODO use more appropriate Exception(s)
	
	/**
	 * 
	 * @return name of solid, if none given, returns "default"
	 * @throws IOException 
	 */
	public abstract String getName() throws IOException;
	
	//TODO implementing these might be more trouble than they are worth
	//public abstract int getObjectCount(); 	
	//public abstract int getFacetCount(int i);

	/**
	 * 
	 * @return true if facets left, false otherwise
	 */
	public abstract boolean hasNextFacet();
	
	
}
