package com.neuronrobotics.replicator.gui.preview.view;

import java.awt.Component;

import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModel;
import com.neuronrobotics.replicator.gui.stl.STLObject;

public interface STLWorkspaceView {
	
	public void setWorkspaceModel(STLWorkspaceModel stlwm);
	
	public void setCamera(double[] position,double[] lookAt);
	
	public void getCameraData(double[] position,double[] lookAt);
	
	public STLObject getPick();
	
	public void addViewListener(STLWorkspaceViewListener newListener);
	
	//TODO: is this general enough to allow most pick interfaces to work with this, given camera data is known?
	public void setPickLocation(double x, double y);

	public Component getComponent();
	
}
