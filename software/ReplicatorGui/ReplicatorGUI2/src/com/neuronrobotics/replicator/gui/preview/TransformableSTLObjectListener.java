package com.neuronrobotics.replicator.gui.preview;

import com.neuronrobotics.replicator.gui.stl.GeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.STLObject;

public interface TransformableSTLObjectListener {
	
	public void alertTransformChanged(STLObject baseSTL, GeneralTransform3D newTransform);

}
