package com.neuronrobotics.replicator.gui;


import java.awt.Container;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.Hashtable;

import javax.swing.JButton;
import javax.swing.JTabbedPane;
import javax.swing.JToolBar;
import javax.vecmath.Point3f;

public class STLPreviewContainer extends Container implements ActionListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5820208700200328570L;
	private JTabbedPane previewTabs;
	private Hashtable<File, STLPreview> thePreviews;

	private JToolBar cameraControls;
	private JButton resetCamera, zoomIn, zoomOut,rotateXZPlus,rotateXZMinus,rotateUp,rotateDown;
	
	private boolean layoutSet;

	public STLPreviewContainer() {
		
		layoutSet = false;
		
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("SansSerif", Font.PLAIN, 14));
		setLayout(gridbag);
		
		
		previewTabs = new JTabbedPane();
		thePreviews = new Hashtable<File, STLPreview>();
		cameraControls = new JToolBar();
		resetCamera = new JButton("Reset Camera");
		zoomIn = new JButton("Zoom In");
		zoomOut = new JButton("Zoom Out");
		rotateXZPlus = new JButton("Camera Left");
		rotateXZMinus = new JButton("Camera Right");
		rotateUp = new JButton("Camera Up");
		rotateDown = new JButton("Camera Down");

		resetCamera.addActionListener(this);
		zoomIn.addActionListener(this);
		zoomOut.addActionListener(this);
		rotateXZPlus.addActionListener(this);
		rotateXZMinus.addActionListener(this);
		rotateUp.addActionListener(this);
		rotateDown.addActionListener(this);		

		cameraControls.add(resetCamera);
		cameraControls.add(zoomIn);
		cameraControls.add(zoomOut);
		cameraControls.add(rotateXZPlus);
		cameraControls.add(rotateXZMinus);
		cameraControls.add(rotateUp);
		cameraControls.add(rotateDown);
		

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;

		c.gridwidth = GridBagConstraints.REMAINDER;
		c.gridheight = GridBagConstraints.RELATIVE;
		c.weighty = 1.0;

		gridbag.setConstraints(previewTabs, c);
		this.add(previewTabs);

		c.weighty = 0.0;
		c.gridheight = 1;

		gridbag.setConstraints(cameraControls, c);
		this.add(cameraControls);

	}

	public boolean addPreview(File stl, Point3f workspaceDimensions) {
		File gcode = new File(stl.getAbsolutePath() + ".gcode");
		return addPreview(stl, gcode, workspaceDimensions);
	}

	public boolean addPreview(File stl, File gcode, Point3f workspaceDimensions) {
		if (!thePreviews.containsKey(stl)) {
			STLPreview tempPreview = new STLPreview(stl, gcode,
					workspaceDimensions);
			String name = stl.getName();
			if(!tempPreview.getSTLObject().getName().equalsIgnoreCase("Default")) 
				name+="("+tempPreview.getSTLObject().getName()+")";
			previewTabs.add(name,tempPreview);
			thePreviews.put(stl, tempPreview);
			previewTabs.setSelectedComponent(tempPreview);
			return true;
		}
		previewTabs.setSelectedComponent(thePreviews.get(stl));
		return false;
	}

	public File getCurrentSTLFile() {
		if (thePreviews.size() == 0)
			return null;
		return ((STLPreview) previewTabs.getSelectedComponent()).getSTLFile();
	}

	public File getCurrentGCodeFile() {
		if (thePreviews.size() == 0)
			return null;
		return ((STLPreview) previewTabs.getSelectedComponent()).getGCodeFile();
	}

	public STLPreview getCurrentPreview() {
		if (thePreviews.size() == 0)
			return null;
		return (STLPreview) previewTabs.getSelectedComponent();
	}

	public boolean hasNoPreviews() {
		return thePreviews.size() == 0;
	}

	
	@Override
	public void actionPerformed(ActionEvent event) {
		if (hasNoPreviews())
			return;
		STLPreview current = ((STLPreview) previewTabs.getSelectedComponent());
		if (event.getSource().equals(zoomIn)) {
			current.zoom(3);
		} else if (event.getSource().equals(zoomOut)) {
			current.zoom(-3);
		} else if (event.getSource().equals(resetCamera)) {
			current.resetCamera();
		} else if (event.getSource().equals(rotateXZPlus)){
			current.rotateCameraXZ(.3);
		} else if (event.getSource().equals(rotateXZMinus)){
			current.rotateCameraXZ(-.3);
		} else if (event.getSource().equals(rotateUp)){
			current.rotateCameraUp(.15);
		} else if (event.getSource().equals(rotateDown)){
			current.rotateCameraUp(-.15);
		}

	}

	public void setLayout(LayoutManager lm){
		if(!layoutSet){
			super.setLayout(lm);
			layoutSet = true;
		}
	}
		
}
