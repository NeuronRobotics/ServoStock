package com.neuronrobotics.replicator.gui.preview;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

public interface STLPreviewCanvas3DListener {

	public void alertCameraMoved(Point3d position,Point3d direction,Vector3d orientation);
	
}
