package com.neuronrobotics.replicator.gui.preview;

public interface STLPreviewWorkspaceView {
	
	public void setWorkspaceModel(STLWorkspaceModel stlwm);
	
	public void setCamera(double[] position,double[] lookAt);
	
}
