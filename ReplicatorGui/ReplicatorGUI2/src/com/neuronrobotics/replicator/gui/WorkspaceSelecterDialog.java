package com.neuronrobotics.replicator.gui;

import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.GridBagLayout;
import java.awt.Toolkit;
import java.awt.Window;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class WorkspaceSelecterDialog extends Dialog implements ActionListener, WindowListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1844314345543127648L;
	
	File theFile;
	JLabel label;
	JTextField selectedDirectory;
	JButton submit, browse;

	private String labelString;
	static boolean done;
		
	public static File directorySelectDialog(ImageIcon imageIcon,String title, String label, Frame theFrame){
		
		done = false;
		
		WorkspaceSelecterDialog theSelecter = new WorkspaceSelecterDialog(theFrame, title,label);
		theSelecter.addWindowListener(theSelecter);
		theSelecter.initialize();
		
		theSelecter.setIconImage(imageIcon.getImage());
		
		theSelecter.setAlwaysOnTop(true);
		theSelecter.setVisible(true);
		
		
		while(!done){}
		
		return theSelecter.theFile;
	}
	
	private static void allDone(){
		done = true;
	}
		
	
	private WorkspaceSelecterDialog(Frame frame, String string,String label) {
		super(frame,string);
		labelString = label;
	}

	private void initialize(){
				
		theFile = new File("DefaultWorkspaceFolder");
		
		this.setLayout(new GridBagLayout());
		
		Dimension screen = Toolkit.getDefaultToolkit().getScreenSize();
		int centX = screen.width/2;
		int centY = screen.height/2;
		
		this.setBounds(centX-325,centY-50,650,100);
		this.setResizable(false);
		
		label = new JLabel(labelString+" ");
		
		selectedDirectory = new JTextField(50);
		selectedDirectory.setText(theFile.getAbsolutePath());
		
		submit = new JButton("Submit");
		browse = new JButton("Browse");
		
		submit.addActionListener(this);
		browse.addActionListener(this);
		
		this.add(label);
		this.add(selectedDirectory);
		this.add(browse);
		this.add(submit);
		
		
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		if(arg0.getSource().equals(browse)){
			JFileChooser fileChooser = new JFileChooser();
			fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
			int returnVal = fileChooser.showOpenDialog(this);
			if (returnVal == JFileChooser.APPROVE_OPTION) {
				System.out.println("You chose to open this file: "
						+ fileChooser.getSelectedFile().getName());
				theFile = fileChooser.getSelectedFile();
				selectedDirectory.setText(theFile.getAbsolutePath());
			}
		
		} else if(arg0.getSource().equals(submit)){
			allDone();
			Window.getWindows()[0].dispose();
		}
		
		
	}


	
	@Override
	public void windowActivated(WindowEvent arg0) {
	}


	@Override
	public void windowClosed(WindowEvent arg0) {
	}


	@Override
	public void windowClosing(WindowEvent arg0) {
		arg0.getWindow().dispose();
		theFile = null;
		allDone();
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
		
	}
	
}