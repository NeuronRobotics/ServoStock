package com.neuronrobotics.replicator.gui;

public class PrintOptions {
	
	private boolean ApplyTransformToSTL;
	
	public PrintOptions(boolean applyTransform){
		ApplyTransformToSTL = applyTransform;
	}
	
	public boolean getApplyTransform(){
		return ApplyTransformToSTL;
	}

}
