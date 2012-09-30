package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Iterator;


public abstract class STLWriter {
	
	
	STLObject theSTL;
	
	public STLWriter(STLObject stl){
		theSTL = stl;
	}
	
	public void writeSTLToFile(File f) throws IOException{
		FileWriter fw = new FileWriter(f);
		writeHeader(fw);
		
		Iterator<STLFacet> theFacets = theSTL.iterator();
		if(theFacets.hasNext()){
		STLFacet fac = theFacets.next();
		while (theFacets.hasNext()){
			writeFacet(fac,fw);
		}
		}
		writeFooter(fw);
		fw.close();
	}
	
	public abstract void writeHeader(FileWriter fw) throws IOException;
	
	public abstract void writeFacet(STLFacet fac, FileWriter fw) throws IOException;
	
	public abstract void writeFooter(FileWriter fw) throws IOException;
		
	
}
