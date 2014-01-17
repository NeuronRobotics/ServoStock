package com.neuronrobotics.replicator.gui.preview.model;

import java.util.Iterator;

import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;

public interface STLWorkspaceModel {
	
	/**
	 * UNKOWN: placement status is not clear. Either necessary collision detections have not been done
	 * or possibly no collision has been detected but a workspace model has not been specified
	 * NOT_IN_WORKSPACE: object is not in workspace but is also not colliding with any other objects 
	 * MODEL_COLLISION: two objects are colliding. Assumed to take precedence over other invalid placement statuses
	 * VALID_PLACEMENT: no object collisions, everything contained within the workspace
	 */
	public enum PlacementStatus {
		UNKOWN, 
		NOT_IN_WORKSPACE,
		MODEL_COLLISION,
		VALID_PLACEMENT;
	}
	
	public void addSTLWorkspaceModelListener(STLWorkspaceModelListener stlwml);
	
	public void removeListener(STLWorkspaceModelListener stlwml);

	public boolean addSTLObject(STLObject stl);
			
	public boolean removeSTLObject(STLObject toRemove);
	
	public void setWorkspace(STLWorkspaceObject theW);
	
	public STLWorkspaceObject getWorkspaceObject();	
	
	public boolean getTransformMatrix(STLObject stl, double[] result);
	
	public boolean setTransformMatrix(STLObject obj, double[] mat4);
		
	public PlacementStatus getPlacementStatus(int index);
	
	public PlacementStatus getPlacementStatus(STLObject obj);
	
	public Iterator<STLObject> getBaseSTLObjectIterator();
	
	public Iterator<double[]> getTransformMatrixIterator();

	public boolean isWorkspacePlacementValid();
	
	public void getCurrMins(STLObject baseObj,double[] result);
	
	public void getCurrMaxes(STLObject baseObj,double[] result);

	public STLObject getMergedSTLObject();
	
	
}
