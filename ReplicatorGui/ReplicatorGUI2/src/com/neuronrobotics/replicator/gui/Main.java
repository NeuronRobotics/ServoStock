package com.neuronrobotics.replicator.gui;

import java.util.Vector;

import javax.media.j3d.*;

import com.neuronrobotics.replicator.driver.SliceStatusData;
import com.sun.j3d.utils.*;
import javax.vecmath.*;
import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.TextField;
import java.awt.event.*;
import java.awt.GraphicsConfiguration;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;

import com.sun.j3d.utils.applet.MainFrame;
import com.sun.j3d.utils.geometry.ColorCube;
import com.sun.j3d.utils.universe.*;


public class Main {

	public static void main(String[] argv) {
		DesktopApplet tapp = new DesktopApplet(new GUIDriver());
		Frame f = new MainFrame(tapp,1200,700);	
	}
}