package com.neuronrobotics.replicator.gui.preview;

import com.neuronrobotics.replicator.gui.stl.GeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;

public interface STLWorkspaceModelListener {
	
	public void alertSTLObjectAdded(STLObject newSTL, GeneralTransform3D transform);
	
	public void alertSTLObjectMoved(STLObject stl, GeneralTransform3D transform);
	
	public void alertSTLObjectRemoved(STLObject stl);
	
	public void alertSTLWorkspaceObjectChanged(STLWorkspaceObject newWorkspace);

}
