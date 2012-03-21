package com.neuronrobotics.replicator.gui;
import java.applet.Applet;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Frame;
import java.awt.GraphicsConfiguration;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Iterator;
import java.util.Scanner;

import javax.media.j3d.*;
import javax.vecmath.*;

import com.neuronrobotics.replicator.common.STLLoader;
import com.neuronrobotics.replicator.common.STLObject;
import com.sun.j3d.utils.geometry.ColorCube;
import com.sun.j3d.utils.universe.SimpleUniverse;
import com.sun.j3d.utils.behaviors.mouse.*;

import org.j3d.loaders.InvalidFormatException;
import com.sun.j3d.utils.geometry.Sphere;

public class Preview3D extends Applet {

	private BranchGroup objRoot;
	private TransformGroup objRotate;
	private Transform3D rotate;
	private SimpleUniverse simpleU;
	private STLObject theSTL;
	//private Shape3D theModel;

	public Preview3D(File f) throws InvalidFormatException, IOException {

		setLayout(new BorderLayout());
		GraphicsConfiguration config = SimpleUniverse
				.getPreferredConfiguration();

		Canvas3D canvas3D = new Canvas3D(config);
		add("Center", canvas3D);
		

		// SimpleUniverse is a Convenience Utility class
		simpleU = new SimpleUniverse(canvas3D);
	
		
		//BranchGroup scene = 
		createSceneGraph(f);
		
		
		
		// objects in the scene can be viewed.
		simpleU.addBranchGraph(objRoot);
		
		////
		
		//TODO figure this shit out
		View v = new View();
		PhysicalBody pb = new PhysicalBody();
		PhysicalEnvironment pe = new PhysicalEnvironment();
		v.setPhysicalEnvironment(pe);
		v.setPhysicalBody(pb);
		//v.setFieldOfView(23);
		//v.addCanvas3D(canvas3D);
		v.attachViewPlatform(simpleU.getViewingPlatform().getViewPlatform());
		
		simpleU.getViewingPlatform().setNominalViewingTransform();
		
		
				
		//////
		
	}

	@SuppressWarnings("restriction")
	public BranchGroup createSceneGraph(final File f) throws InvalidFormatException,
			IOException {
		objRoot = new BranchGroup();
		
		//String dir = "C:\\Users\\Admin\\replicator\\ReplicatorGUI2\\";
		//File f = new File(dir+"spaceinvader.stl");
		
		//TODO removed to test something
		Thread STLLoadThread = new Thread(){
			@Override
			public void start(){
				try {
					theSTL = STLLoader.loadFile2(f);
					objRotate = STLLoader.getSTLTransform(theSTL,objRoot);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		};
		//objRotate = STLLoader.getSTLTransform(f,objRoot);
		STLLoadThread.start();
		objRoot.addChild(objRotate);
		
				
		AmbientLight lightA = new AmbientLight();
		lightA.setInfluencingBounds(new BoundingSphere());
		objRoot.addChild(lightA);
		
		DirectionalLight lightD1 = new DirectionalLight();
		lightD1.setInfluencingBounds(new BoundingSphere());
		// customize DirectionalLight object
		objRoot.addChild(lightD1);
				
		objRoot.compile();
				
		return objRoot;
	}
		
	public void setModel(File f) throws IOException{
		//TODO currently just adds in a model
		TransformGroup objRotate2 = STLLoader.getSTLTransform(f,objRoot);
			
		objRoot.compile();
	}
	
	public STLObject getSTLObject(){
		return theSTL;
	}
	
}
