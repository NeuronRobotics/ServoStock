package com.neuronrobotics.replicator.gui.preview;

import java.awt.Container;
import java.io.File;

import javax.swing.ImageIcon;
import javax.vecmath.Point3f;

public class STLPreviewTab extends Container{
	
	private STLPreviewContainer theSTLPreviewContainer;
	
	private boolean loaded;
	private File theSTLFile,theGCode;
	private Point3f workspaceDimensions;
	
	private SimpleLoadingScreen theLoadingScreen;
	private STLPreview theSTLPreview;
	
	public STLPreviewTab(STLPreviewContainer stlc, File stl, File gcode, Point3f workspaceDim){
		loaded = false;
		theSTLFile = stl;
		theGCode = gcode;
		workspaceDimensions = workspaceDim;
		theSTLPreviewContainer = stlc;
		theSTLPreview = null;
		theLoadingScreen = new SimpleLoadingScreen(stl.getName()+" preview loading...",true);		
	}
	
	public void load(){
		
	}
	
	/*
	
	
	private class AddPreviewThread extends Thread {

		SimpleLoadingScreen theLoadingScreen;
		File stl, gcode;
		Point3f workspaceDimensions;

		public AddPreviewThread(SimpleLoadingScreen sls, File stl, File gcode,
				Point3f workspaceDimensions) {
			super();
			theLoadingScreen = sls;
			this.stl = stl;
			this.gcode = gcode;
			this.workspaceDimensions = workspaceDimensions;
			//currentlyLoading.add(stl);

		}

		public void run() {

			STLPreview tempPreview = new STLPreview(stl, gcode,
					workspaceDimensions);
			String name = stl.getName();

			if (!tempPreview.getSTLObject().getName()
					.equalsIgnoreCase("Default"))
				name += " (" + tempPreview.getSTLObject().getName() + ")";

			int index = previewTabs.indexOfComponent(theLoadingScreen);
			ImageIcon imageIcon = new ImageIcon("Images\\simpleCube.png");
			previewTabs.insertTab(name, imageIcon, tempPreview, name, index);
			
			thePreviews.put(stl, tempPreview);
			// previewTabs.setSelectedComponent(tempPreview);

			previewTabs.remove(theLoadingScreen);

			STLPreviewMouseControls theMouseControls = new STLPreviewMouseControls(tempPreview);
			theMouseControls.setMouseControlMode(getCurrentSelectedMode());
			tempPreview.setMouseControls(theMouseControls);
			
			tempPreview.setOutlineVisibility(toggleOutline.isSelected());

			currentlyLoading.remove(stl);
		}

	}*/

	

}
