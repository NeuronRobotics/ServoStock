package com.neuronrobotics.replicator.gui.stl;

import javax.vecmath.Point3d;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

public interface GeneralTransform3D {
	
	public void transform(Point3f p);
	
	public void transform(Point3d p);
	
	public void transform(Vector3f v);
	
	public void transform(Vector3d p);
	
}
