package com.neuronrobotics.replicator.gui;

public interface GUIFrontendInterface {
	
	public boolean userPrompt(String prompt);
	
	public void errorDialog(String errorMessage);
		
	public boolean errorDialogWithFix(String errorMessage, String fixPrompt);
	
	public void alertStatusUpdated();

}
