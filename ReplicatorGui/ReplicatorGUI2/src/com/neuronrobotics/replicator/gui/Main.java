package com.neuronrobotics.replicator.gui;

import java.awt.Frame;

import com.sun.j3d.utils.applet.MainFrame;

public class Main {

	public static void main(String[] argv) {

		DesktopApplet tapp = new DesktopApplet(new GUIDriver());
		MainFrame f = new MainFrame(tapp, 1200, 700);
		f.setExtendedState(f.getExtendedState()|Frame.MAXIMIZED_BOTH);
		
	}
}
