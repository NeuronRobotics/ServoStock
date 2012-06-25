package com.neuronrobotics.replicator.gui.preview;

import java.awt.Font;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;

public class SimpleLoadingScreen extends JPanel{
	
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -431112182662775252L;

	
	private JProgressBar theProgressBar;
	private JLabel theText;
	
	//private final ImageIcon imageIcon = new ImageIcon("Images\\hat.png");
		
	
	public SimpleLoadingScreen(String text,boolean indeterminate){
		theProgressBar = new JProgressBar();
		theProgressBar.setIndeterminate(indeterminate);
		theText = new JLabel(text);
			
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		setFont(new Font("Helvetica", Font.PLAIN, 72));
		setLayout(gridbag);
		
		c.gridwidth = GridBagConstraints.REMAINDER;
		
		gridbag.setConstraints(theText, c);
		add(theText);
		theText.setFont(new Font("Helvetica", Font.PLAIN, 32));
		
		c.fill = GridBagConstraints.HORIZONTAL;
		gridbag.setConstraints(theProgressBar, c);
		add(theProgressBar);
		
	}
	
	/**
	 * Sets the main text to argument passed in
	 * @param newText
	 */
	public void setText(String newText){
		this.theText.setText(newText);
	}
		
	/**
	 * Takes in an int to set the current level of progress for the progress bar
	 * @param prog
	 */
	public void setProgress(int prog){
		if(!theProgressBar.isIndeterminate()) theProgressBar.setOrientation(prog);
	}
	
	

}
