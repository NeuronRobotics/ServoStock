package com.neuronrobotics.replicator.gui.preview;

import java.io.File;

import javax.swing.SwingWorker;
import javax.vecmath.Point3f;

public class PreviewLoadWorker extends SwingWorker<STLPreviewCanvas3D,Object>{
	
	private File theSTL, theGCode;
	private Point3f theWorkspaceDimensions;
	
	public PreviewLoadWorker(File stl,File Gcode, Point3f dimensions){
		theSTL = stl;
		theGCode = Gcode;
		theWorkspaceDimensions = dimensions;		
	}

	@Override
	protected STLPreviewCanvas3D doInBackground() throws Exception {
		STLPreviewCanvas3D tempPreview = new STLPreviewCanvas3D(theSTL, theGCode,
				theWorkspaceDimensions);
		return tempPreview;
	}

}
