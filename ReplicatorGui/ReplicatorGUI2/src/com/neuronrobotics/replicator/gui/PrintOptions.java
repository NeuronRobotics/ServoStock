package com.neuronrobotics.replicator.gui;

public class PrintOptions {
	
	private boolean forceReslice, useTransformedSTL;
	
	public PrintOptions(boolean reslice, boolean applyTransform){
		useTransformedSTL = applyTransform;
		forceReslice = reslice;
	}

	public boolean isForceReslice() {
		return forceReslice;
	}

	public boolean isUseTransformedSTL() {
		return useTransformedSTL;
	}

}
