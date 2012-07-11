package com.neuronrobotics.replicator.gui;

import java.awt.Frame;
import java.io.File;

import javax.swing.ImageIcon;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

import com.sun.j3d.utils.applet.MainFrame;

public class Main {
	
	private static ImageIcon imageIcon = new ImageIcon("Images\\hat.png");

	public static void main(String[] argv) {
		
		//Setting look and Feel
		String lookAndFeel = UIManager.getSystemLookAndFeelClassName();
		try {
			UIManager.setLookAndFeel(lookAndFeel);
		} catch (ClassNotFoundException e1) {
			e1.printStackTrace();
		} catch (InstantiationException e1) {
			e1.printStackTrace();
		} catch (IllegalAccessException e1) {
			e1.printStackTrace();
		} catch (UnsupportedLookAndFeelException e1) {
			e1.printStackTrace();
		}
		
		File fd = WorkspaceSelecterDialog.directorySelectDialog(imageIcon,"Select Workspace","Workspace:",new Frame());
		
		if(fd!=null){
			startGUI(fd);
		} else {
			System.exit(0);
		}
		
	}
	
	private static void startGUI(File directory){
		
		DesktopApplet tapp;
		if(!directory.exists()||!directory.isDirectory()) tapp = new DesktopApplet(new GUIDriver());
		else tapp = new DesktopApplet(new GUIDriver(),directory);
				
		MainFrame f = new MainFrame(tapp, 1200, 700);
		f.setIconImage(imageIcon.getImage());
		f.setExtendedState(f.getExtendedState()|Frame.MAXIMIZED_BOTH);
		
	}
	
	
}
