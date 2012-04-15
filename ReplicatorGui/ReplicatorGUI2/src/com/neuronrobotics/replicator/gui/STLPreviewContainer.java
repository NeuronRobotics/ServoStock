package com.neuronrobotics.replicator.gui;

import java.io.File;

public class STLPreviewContainer {
	
	private File theSTLFile;
	private File theGCodeFile;
	private Preview3D thePreview;
	
	public STLPreviewContainer(File stl,File gCode,Preview3D preview){
		this.theSTLFile = stl;
		this.theGCodeFile = gCode;
		this.thePreview = preview;
	}
	
	public File getSTL(){
		return theSTLFile;
	}
	
	public File getGCode(){
		return theGCodeFile;
	}
	
	public Preview3D getPreview(){
		return thePreview;
		
	}
	
	public String toString(){
		if(theSTLFile!=null) return theSTLFile.getName();
		else if (theGCodeFile!=null) return theGCodeFile.getName();
		else if (thePreview!=null) return thePreview.getName();
		return "Null Object";
	}
	

}
