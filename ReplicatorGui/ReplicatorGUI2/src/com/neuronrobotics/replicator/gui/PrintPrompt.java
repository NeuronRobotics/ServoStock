package com.neuronrobotics.replicator.gui;

import java.awt.Dialog;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.JCheckBox;

//import javax.swing.JDialog;

public class PrintPrompt extends Dialog{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1861518105140997973L;
	
	private JCheckBox reslice,rewriteSTL;
					
	private PrintPrompt(Frame owner){
		super(owner,"Print Options");
		FlowLayout theLayout = new FlowLayout();
		theLayout.setAlignment(FlowLayout.CENTER);
		this.setLayout(theLayout);
		
		reslice = new JCheckBox("Force Reslice");
		rewriteSTL = new JCheckBox("Use Transformed STL");
		
		this.add(reslice);
		this.add(rewriteSTL);
		
		
		this.addWindowListener(new WindowListener(){

			@Override
			public void windowActivated(WindowEvent arg0) {				
			}

			@Override
			public void windowClosed(WindowEvent arg0) {
				
			}

			@Override
			public void windowClosing(WindowEvent arg0) {
				arg0.getWindow().dispose();
				System.exit(0);
			}

			@Override
			public void windowDeactivated(WindowEvent arg0) {
			}

			@Override
			public void windowDeiconified(WindowEvent arg0) {
			}

			@Override
			public void windowIconified(WindowEvent arg0) {
			}

			@Override
			public void windowOpened(WindowEvent arg0) {
			}});
		
	}
		
	public static PrintOptions promptUser(Frame owner){
		PrintPrompt thePrompt = new PrintPrompt(owner);
		thePrompt.setVisible(true);
		
		
		return new PrintOptions(true,true);
	}

}
