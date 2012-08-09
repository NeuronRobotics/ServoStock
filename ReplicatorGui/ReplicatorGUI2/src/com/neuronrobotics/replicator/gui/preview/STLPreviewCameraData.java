package com.neuronrobotics.replicator.gui.preview;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

public class STLPreviewCameraData {
	
	private Point3d position, direction;
	private Vector3d orientation;
	
	public STLPreviewCameraData(Point3d pos, Point3d dir, Vector3d orient){
		position = pos;
		direction = dir;
		orientation = orient;
	}
	
	public Point3d getCameraPosition(){
		return position;
	}
	
	public Point3d getCameraDirection(){
		return direction;
	}
	
	public Vector3d getCameraOrientation(){
		return orientation;
	}

}
