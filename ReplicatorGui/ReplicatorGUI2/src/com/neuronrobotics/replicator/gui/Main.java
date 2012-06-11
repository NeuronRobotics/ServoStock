package com.neuronrobotics.replicator.gui;

import java.awt.Frame;
import java.nio.file.FileSystem;
import java.nio.file.FileSystems;

import javax.swing.ImageIcon;

import com.sun.j3d.utils.applet.MainFrame;

public class Main {

	public static void main(String[] argv) {
		
		ImageIcon imageIcon = new ImageIcon("Images\\hat.png");
		
		DesktopApplet tapp = new DesktopApplet(new GUIDriver());
		MainFrame f = new MainFrame(tapp, 1200, 700);
		f.setIconImage(imageIcon.getImage());
		f.setExtendedState(f.getExtendedState()|Frame.MAXIMIZED_BOTH);
		
	}
}
