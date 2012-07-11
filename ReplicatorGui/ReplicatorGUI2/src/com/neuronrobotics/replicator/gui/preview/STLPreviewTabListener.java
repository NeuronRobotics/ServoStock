package com.neuronrobotics.replicator.gui.preview;

public interface STLPreviewTabListener {
	
	public void alertTabIsDead(STLPreviewTab deadTab);
	
	public void alertTabIsLoaded(STLPreviewTab loadedTab);
}
