package com.neuronrobotics.replicator.gui.preview;

import java.awt.GridLayout;
import java.io.File;
import java.util.ArrayList;

import javax.swing.JPanel;
import javax.vecmath.Point3f;

public class STLPreviewTab extends JPanel {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -5559016123774970333L;

	//private STLPreviewTabListener theSTLPreviewContainer;
		
	private ArrayList<STLPreviewTabListener> theTabListeners;
	
	private boolean loaded, isDead;
	private File theSTLFile,theGCode;
	private Point3f workspaceDimensions;
	
	private SimpleLoadingScreen theLoadingScreen;
	private STLPreviewCanvas3D theSTLPreview;
	private LoadPreviewThread theLoadingThread;
	
	public STLPreviewTab(File stl, File gcode, Point3f workspaceDim){
		loaded = false;
		isDead = false;
		
		theTabListeners = new ArrayList<STLPreviewTabListener>();
		//theTabListeners.add(stlc);
		
		theSTLFile = stl;
		theGCode = gcode;
		workspaceDimensions = workspaceDim;
		theSTLPreview = null;
		theLoadingScreen = new SimpleLoadingScreen(stl.getName()+" preview loading...",true);		
		this.setLayout(new GridLayout(1,1));
		theLoadingThread = null;
	}
	
 	public STLPreviewTab(STLPreviewTabListener stlc, File stl, File gcode, Point3f workspaceDim){
		loaded = false;
		isDead = false;
		
		theTabListeners = new ArrayList<STLPreviewTabListener>();
		theTabListeners.add(stlc);
		
		theSTLFile = stl;
		theGCode = gcode;
		workspaceDimensions = workspaceDim;
		theSTLPreview = null;
		theLoadingScreen = new SimpleLoadingScreen(stl.getName()+" preview loading...",true);		
		this.setLayout(new GridLayout(1,1));
		theLoadingThread = null;
	}
	
	public void load(){
		if (!loaded) {
			this.removeAll();
			
			this.add(theLoadingScreen);
			
			if (theLoadingThread == null)
				theLoadingThread = new LoadPreviewThread(theLoadingScreen,
						theSTLFile, theGCode, workspaceDimensions);
			theLoadingThread.start();
		}
	}
	
	public void reload(){
		loaded = false;
		this.removeAll();
		this.add(theLoadingScreen);
		theLoadingThread = null;
		theSTLPreview= null;
		load();
	}

	private void alertPreviewLoaded(STLPreviewCanvas3D tempPreview) {
		this.removeAll();
		//this.remove(theLoadingScreen);
		theSTLPreview = tempPreview;
		this.add(theSTLPreview);
		loaded = true;
		
		STLPreviewMouseControls theMouseControls = new STLPreviewMouseControls(
				tempPreview);
		
		tempPreview.setMouseControls(theMouseControls);
		
		/*
			tempPreview.resetCamera(theSTLPreviewContainer.getCurrentSelectedCameraFocusMode());
			tempPreview.setOutlineVisibility(theSTLPreviewContainer.isOutlineSelected());

			//STLPreviewMouseControls theMouseControls = new STLPreviewMouseControls(
				//	tempPreview);
			theMouseControls.setMouseControlMode(theSTLPreviewContainer.getCurrentSelectedMouseMode());
			tempPreview.setMouseControls(theMouseControls);
		*/
		
		validate();
		
		for(STLPreviewTabListener sptl:theTabListeners) sptl.alertTabIsLoaded(this);
		
		theLoadingThread = null;
	}
			
	public STLPreviewCanvas3D getTheSTLPreview() {
		return theSTLPreview;
	}

	private void alertTabIsDead(Exception e){
		isDead = true;
		for(STLPreviewTabListener sptl:theTabListeners) sptl.alertTabIsDead(this);
	}
			
	public boolean isDead(){
		return isDead;
	}

	public boolean isLoaded() {
		return loaded;
	}

	public File getSTLFile() {	
		return theSTLFile;
	}
	
	public File getGCodeFile() {	
		return theGCode;
	}
	
	public void killTab(){
		isDead = true;
		theLoadingScreen = null;
		theLoadingThread = null;
		theSTLPreview.killPreview();
		theSTLPreview = null;
		this.theTabListeners = null;
		
		//theSTLPreviewContainer = null;
		
	}

	private class LoadPreviewThread extends Thread {

		//SimpleLoadingScreen theLoadingScreen;
		File stl, gcode;
		Point3f workspaceDimensions;

		public LoadPreviewThread(SimpleLoadingScreen sls, File stl, File gcode,
				Point3f workspaceDimensions) {
			super();
			//theLoadingScreen = sls;
			this.stl = stl;
			this.gcode = gcode;
			this.workspaceDimensions = workspaceDimensions;
			//currentlyLoading.add(stl);

		}

		@Override
		public void run() {
			
			try {
				STLPreviewCanvas3D tempPreview = new STLPreviewCanvas3D(stl, gcode,
						workspaceDimensions);
				tempPreview.inititalize();
				

				/*
				STLPreviewMouseControls theMouseControls = new STLPreviewMouseControls(
						tempPreview);
				theMouseControls.setMouseControlMode(theSTLPreviewContainer
						.getCurrentSelectedMouseMode());
				tempPreview.setMouseControls(theMouseControls);
				*/

				alertPreviewLoaded(tempPreview);
			} catch (Exception e) {
				e.printStackTrace();
				alertTabIsDead(e);
			}
		}

	}

}
