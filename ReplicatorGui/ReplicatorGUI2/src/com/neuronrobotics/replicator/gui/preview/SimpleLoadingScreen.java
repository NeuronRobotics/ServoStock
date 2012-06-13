package com.neuronrobotics.replicator.gui.preview;

//import java.awt.Container;
//import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
//import java.awt.Image;
//import java.awt.image.BufferedImage;
//import java.awt.image.ImageObserver;
//import java.io.File;
//import java.io.IOException;

//import javax.imageio.ImageIO;
//import javax.swing.ImageIcon;
//import javax.swing.JFrame;
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
	
	
	public void paint(Graphics g){
		super.paint(g);
		/*
		Image image = imageIcon.getImage();
		Image currImage = image.getScaledInstance(400,400,Image.SCALE_DEFAULT);//this.getWidth()-20, this.getHeight()-20, Image.SCALE_FAST);
			
		System.out.println("currImage Width" + image.getWidth(this));
		
		g.drawImage(currImage, 0,0, this);
			
		//g.drawImage(currImage, (this.getWidth()/2)-currImage.getWidth(this)/2, this.getHeight()/2-currImage.getHeight(this)/2, this);
		*/
	}
	
	
			
	public void setProgress(int prog){
		if(!theProgressBar.isIndeterminate()) theProgressBar.setOrientation(prog);
	}
	
	

}
