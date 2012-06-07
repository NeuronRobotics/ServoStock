package com.neuronrobotics.replicator.gui.navigator;

import java.io.File;

public class WorkspaceFolderNodeObject {
	
	private File theDirectory;
	
	public WorkspaceFolderNodeObject(File dir) {//throws Exception{
	//	if(dir==null||!dir.isDirectory()) throw new Exception();
		theDirectory = dir;
	}
	
	public File getTheDirectory(){
		return theDirectory;
	}
	
	public String toString(){
		return theDirectory.getName();
	}
	
}
