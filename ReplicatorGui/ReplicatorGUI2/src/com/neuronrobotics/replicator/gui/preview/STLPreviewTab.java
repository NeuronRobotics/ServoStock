package com.neuronrobotics.replicator.gui.preview;

import java.awt.Color;
import java.awt.Container;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentListener;
import java.io.File;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import com.neuronrobotics.replicator.gui.preview.j3d.OrientationIndicatorCanvas3D;
import com.neuronrobotics.replicator.gui.preview.j3d.STLPreviewCanvas3D;
import com.neuronrobotics.replicator.gui.preview.j3d.STLPreviewMouseControls;

public class STLPreviewTab extends JLayeredPane{
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -5559016123774970333L;

	private ArrayList<STLPreviewTabListener> theTabListeners;
	
	private boolean loaded, isDead;
	private File theSTLFile;
	
	private SimpleLoadingScreen theLoadingScreen;
	private STLPreviewCanvas3D theSTLPreview;
	private LoadPreviewThread theLoadingThread;
	
	private JPanel indicatorPanel;
	//private JButton testButton, testButton2;
	
	private final JPanel canvasLayer = new JPanel(), loadingScreenLayer = new JPanel();
		
	private File theWorkspaceSTLFile;
		
	public STLPreviewTab(String name, File wstl){
		loaded = false;
		isDead = false;
		
		theTabListeners = new ArrayList<STLPreviewTabListener>();
		theWorkspaceSTLFile = wstl;		
		theSTLFile = null;
		theSTLPreview = null;
		theLoadingScreen = new SimpleLoadingScreen(name+" preview loading...",true);		
		//this.setLayout(new GridLayout(1,1));
		theLoadingThread = null;
				
		this.setName(name);
		
		loadingScreenLayer.setLayout(new GridLayout(1,1));
		//overlayLayer.setLayout(new GridLayout(1,1));
		canvasLayer.setLayout(new GridLayout(1,1));
		
		//this.add
		
		this.add(loadingScreenLayer);
		//this.add(overlayLayer,150);
		this.add(canvasLayer);
	}
		
	public STLPreviewTab(File stl, File wstl){
		this(stl.getName(),wstl);
		theSTLFile = stl;
		theSTLPreview = null;
	}
	
 	public STLPreviewTab(STLPreviewTabListener stlc, File stl, File wstl){
		this(stl,wstl);
		theTabListeners.add(stlc);
	}
 	
 	public void addTabListener(STLPreviewTabListener sptl){
 		this.theTabListeners.add(sptl);
 	}
	
	public void load(){
		if (!loaded) {
			loadingScreenLayer.setSize(this.getSize());
			canvasLayer.setSize(this.getSize());
			//this.removeAll();
			
			//this.add(theLoadingScreen);
			loadingScreenLayer.add(theLoadingScreen);
			loadingScreenLayer.setVisible(true);
			
			if (theLoadingThread == null){
					theLoadingThread = new LoadPreviewThread(theLoadingScreen,theSTLFile, theWorkspaceSTLFile);
			}
			
			theLoadingThread.start();
		}
	}
	
	public void reload(){
		loaded = false;
		this.removeAll();
		//this.add(theLoadingScreen);
		loadingScreenLayer.setVisible(true);
		theLoadingThread = null;
		theSTLPreview= null;
		load();
	}

	private void alertPreviewLoaded(STLPreviewCanvas3D tempPreview) {
		loadingScreenLayer.setVisible(false);
		theSTLPreview = tempPreview;
		canvasLayer.add(tempPreview);
		loaded = true;
		
		STLPreviewMouseControls theMouseControls = new STLPreviewMouseControls(tempPreview);
		tempPreview.setMouseControls(theMouseControls);
				
		final OrientationIndicatorCanvas3D theind = new OrientationIndicatorCanvas3D();
		tempPreview.addListener(new STLPreviewWorkspaceViewListener() {
					
			@Override
			public void alertCameraMoved(double[] position, double[] direction,
					double[] orientation) {
				theind.setCamera(new Point3d(position),new Point3d(direction), new Vector3d(orientation));
				
			}
		});
		
		//theind.setSize(90,90);
		//theind.setLocation(0, 0);
		
		indicatorPanel = new JPanel();
		indicatorPanel.setSize(100,100);
		//indicatorPanel.setLocation(5,5);
		indicatorPanel.setLayout(new GridLayout(1,1));		
		indicatorPanel.setBorder(BorderFactory.createLineBorder(Color.gray));
		
		/*
		testButton = new JButton();
		testButton.setText("Test");
		testButton.setSize(45, 45);
		//testButton.setLocation(5, 110);
		testButton.setBackground(Color.black);
		testButton.setForeground(Color.black);
		testButton.setBorder(BorderFactory.createLineBorder(Color.gray));
		testButton.setIcon(new ImageIcon("Images\\logo.png"));
		
		testButton2 = new JButton();
		testButton2.setText("Test");
		testButton2.setSize(45, 45);
		//testButton2.setLocation(60, 110);
		testButton2.setBackground(Color.black);
		testButton2.setBorder(BorderFactory.createLineBorder(Color.gray));
							
		*/
		
		indicatorPanel.add(theind);
		this.add(indicatorPanel,0);
		//this.add(testButton);//TODO
		//this.add(testButton2);
		this.moveToFront(tempPreview);
		this.moveToFront(theind);
		//this.moveToFront(testButton);
		//this.moveToFront(testButton2);	
		
		layoutControlLayer();
		
		this.addComponentListener(new ComponentListener(){

			@Override
			public void componentHidden(ComponentEvent arg0) {				
			}

			@Override
			public void componentMoved(ComponentEvent arg0) {				
			}

			@Override
			public void componentResized(ComponentEvent arg0) {
				 layoutControlLayer();
			}

			@Override
			public void componentShown(ComponentEvent arg0) {
			}});
						
		validate();
						
		for(STLPreviewTabListener sptl:theTabListeners) sptl.alertTabIsLoaded(this);
		
		theLoadingThread = null;
	}
	
	private void layoutControlLayer(){
		int xS = getSize().width,yS=getSize().height;
		indicatorPanel.setLocation(5,yS-105);
		//testButton.setLocation(5, indicatorPanel.getY()-50);
		//testButton2.setLocation(60, indicatorPanel.getY()-50);
	}
			
	public STLPreviewCanvas3D getTheSTLPreview() {
		return theSTLPreview;
	}

	private void alertTabIsDead(Exception e){
		isDead = true;
		for(STLPreviewTabListener sptl:theTabListeners) sptl.alertTabIsDead(this);
	}
			
	public boolean isDead(){
		return isDead;
	}

	public boolean isLoaded() {
		return loaded;
	}
	
	public void killTab(){
		isDead = true;
		theLoadingScreen = null;
		theLoadingThread = null;
		theSTLPreview.killPreview();
		theSTLPreview = null;
		this.theTabListeners = null;
		
		//theSTLPreviewContainer = null;
		
	}

	private class LoadPreviewThread extends Thread {

		//SimpleLoadingScreen theLoadingScreen;
		File stl;
		File workspaceSTL;

		public LoadPreviewThread(SimpleLoadingScreen sls, File stl, 
				File wstl) {
			super();
			//theLoadingScreen = sls;
			this.stl = stl;
			this.workspaceSTL = wstl;
			//currentlyLoading.add(stl);

		}

		@Override
		public void run() {
			
			try {
				STLPreviewCanvas3D tempPreview;
				if (stl != null) tempPreview = new STLPreviewCanvas3D(stl, workspaceSTL);
				 else tempPreview = new STLPreviewCanvas3D(workspaceSTL);
				
				tempPreview.loadFromQueue();

				alertPreviewLoaded(tempPreview);
			} catch (Exception e) {
				e.printStackTrace();
				alertTabIsDead(e);
			}
		}

	}


}
