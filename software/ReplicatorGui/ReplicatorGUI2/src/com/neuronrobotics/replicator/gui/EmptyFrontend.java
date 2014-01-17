package com.neuronrobotics.replicator.gui;


public class EmptyFrontend implements GUIFrontendInterface {

	@Override
	public boolean userPrompt(String prompt) {
		return true;
	}

	@Override
	public void errorDialog(String errorMessage) {
		System.out.println(errorMessage);	
	}

	@Override
	public void alertStatusUpdated() {
		
	}

	@Override
	public boolean errorDialogWithFix(String errorMessage, String fixPrompt) {
		return true;
	}

	@Override
	public void requestValidate() {		
	}

}
