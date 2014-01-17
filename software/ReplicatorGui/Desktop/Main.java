package com.neuronrobotics.replicator.gui;

import java.util.Vector;

import javax.media.j3d.*;

import com.neuronrobotics.replicator.driver.DeltaPrinter;
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
		
		TestApplet tapp = new TestApplet();
		Frame f = new MainFrame(tapp,1200,700);
		
		/*
		MainApplet gui;
		
		try {
		
		DeltaPrinter thePrinter = new DeltaPrinter();
		
		gui = new MainApplet(thePrinter);		
		
		Frame f = new MainFrame(gui,1200,700);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		*/
		//preview.setSize(200,234);		
	}
}