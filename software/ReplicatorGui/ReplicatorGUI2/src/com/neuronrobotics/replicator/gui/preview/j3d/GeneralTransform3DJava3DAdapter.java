package com.neuronrobotics.replicator.gui.preview.j3d;

import javax.media.j3d.Transform3D;

import com.neuronrobotics.replicator.gui.stl.GeneralTransform3D;

public class GeneralTransform3DJava3DAdapter extends Transform3D implements GeneralTransform3D {

	public GeneralTransform3DJava3DAdapter(Transform3D t){
		super(t); 
	}
	
	public GeneralTransform3DJava3DAdapter(){
		super();
	}

	/*public void transform(double[] p) {
		Point3d pt = new Point3d(p);
		this.transform(pt); 
		pt.get(p);
	}*/
	
	
	
}
