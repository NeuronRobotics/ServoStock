package com.neuronrobotics.replicator.gui.preview.controller;

public interface GeneralSTLTransformHelper {
	
	public void rotateX(double angle);
	
	public void rotateY(double angle);
	
	public void rotateZ(double angle);
	
	public void translateLeftRight(double x);
	
	public void translateBackForth(double z);
	
	public void translateUpDown(double y);
	
	public void rotateAroundUpVector(double rad);
	
	public void placeOnWorkspace(double workspaceY, double currMin);
		
	public void setCurrentTransform(double[] mat4);	
	
	public void getCurrentTransform(double[] mat4);

	public void pointNormalDown(double[] normal);
	

}
