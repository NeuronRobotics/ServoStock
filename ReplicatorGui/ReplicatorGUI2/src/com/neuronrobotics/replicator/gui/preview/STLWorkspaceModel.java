package com.neuronrobotics.replicator.gui.preview;

import java.util.Iterator;

import javax.vecmath.Color3f;

import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;

public interface STLWorkspaceModel{
	
	public enum PlacementStatus {
		UNKOWN {
			@Override
			Color3f getBaseColor() {
				return new Color3f(.0f, .0f, .0f);
			}

		},
		NOT_IN_WORKSPACE {
			@Override
			Color3f getBaseColor() {
				return new Color3f(.4f, .0f, .0f);
			}

			
		},
		MODEL_COLLISION {
			@Override
			Color3f getBaseColor() {
				return new Color3f(.0f, .0f, .4f);
			}

		},
		VALID_PLACEMENT {
			@Override
			Color3f getBaseColor() {
				return new Color3f(0,0.4f,0);
			}

		};

		abstract Color3f getBaseColor();

	}
	
	public void addSTLWorkspaceModelListener(STLWorkspaceModelListener stlwml);

	public boolean addSTLObject(STLObject stl);
		
	public boolean removeSTLObject(int index);
	
	public boolean removeSTLObject(STLObject toRemove);
	
	public void setWorkspace(STLWorkspaceObject theW);
	
	public STLWorkspaceObject getWorkspaceObject();
	
	public boolean getTransformMatrix(int index, double[] result);
	
	public boolean getTransformMatrix(STLObject stl, double[] result);
		
	public boolean setTransformMatrix(int index, double[] mat4);
	
	public boolean setTransformMatrix(STLObject obj, double[] mat4);
	
	public boolean isWorkspacePlacementValid();
	
	public PlacementStatus getPlacementStatus(int index);
	
	public PlacementStatus getPlacementStatus(STLObject obj);
	
	public Iterator<STLObject> getBaseSTLObjectIterator();
	
	public Iterator<double[]> getTransformMatrixIterator();
	
}
