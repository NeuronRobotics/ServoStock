package com.neuronrobotics.replicator.gui.stl;

import javax.media.j3d.Transform3D;

public class Transform3DAdapter extends Transform3D implements GeneralTransform3D {

	public Transform3DAdapter(Transform3D t){
		super(t);
	}
	
	public Transform3DAdapter(){
		super();
	}
	
}
