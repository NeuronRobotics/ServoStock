package com.neuronrobotics.replicator.gui.preview;

import java.awt.Container;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
//import java.awt.Image;
//import java.awt.LayoutManager;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.ArrayList;
import java.util.Hashtable;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JTabbedPane;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.vecmath.Point3f;

import com.neuronrobotics.replicator.gui.preview.STLPreviewMouseControls.MouseControlMode;

public class STLPreviewContainer extends Container implements ActionListener, ChangeListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5820208700200328570L;
	private JTabbedPane previewTabs;
	private Hashtable<File, STLPreview> thePreviews;
	private ArrayList<File> currentlyLoading;

	private JToolBar cameraControls;
	private JButton resetCamera,centerModel;
	//, zoomIn, zoomOut, rotateXZPlus, rotateXZMinus,
		//	rotateUp, rotateDown;
	private JToggleButton toggleOutline;
	//private JButton translateLeft, translateRight;
	//private JButton rotateModel;
	
	//Mouse control mode buttons
	private JToggleButton cameraMode, rotateXMode,rotateYMode,rotateZMode,translateXYMode,translateZYMode;
	
	public STLPreviewContainer() {

		// layoutSet = false;
		

		currentlyLoading = new ArrayList<File>();

		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("SansSerif", Font.PLAIN, 14));
		setLayout(gridbag);

		previewTabs = new JTabbedPane();
		thePreviews = new Hashtable<File, STLPreview>();
		cameraControls = new JToolBar();
		resetCamera = new JButton("Reset Camera");
		centerModel = new JButton("Reset STL");
		
		//zoomIn = new JButton("Zoom In");
		//zoomOut = new JButton("Zoom Out");
		//rotateXZPlus = new JButton("Camera Left");
		//rotateXZMinus = new JButton("Camera Right");
		//rotateUp = new JButton("Camera Up");
	//	rotateDown = new JButton("Camera Down");
		toggleOutline = new JToggleButton("Toggle Outline", true);
		//translateLeft = new JButton("Translate Left");
		//translateRight = new JButton("Translate Right");
		//rotateModel = new JButton("Rotate Model");
		cameraMode = new JToggleButton("Camera Mode");
		rotateXMode = new JToggleButton("Model RotateX");
		rotateYMode = new JToggleButton("Model RotateY");
		rotateZMode = new JToggleButton("Model RotateZ");
		translateXYMode = new JToggleButton("Model Translate XY");
		translateZYMode = new JToggleButton("Model Translate ZY");
		

		resetCamera.addActionListener(this);
		centerModel.addActionListener(this);
	//	zoomIn.addActionListener(this);
	//	zoomOut.addActionListener(this);
	//	rotateXZPlus.addActionListener(this);
	//	rotateXZMinus.addActionListener(this);
	//	rotateUp.addActionListener(this);
	//	rotateDown.addActionListener(this);
		toggleOutline.addActionListener(this);
	//	translateLeft.addActionListener(this);
	//	translateRight.addActionListener(this);
		//rotateModel.addActionListener(this);
		cameraMode.addActionListener(this);
		rotateXMode.addActionListener(this);
		rotateYMode.addActionListener(this);
		rotateZMode.addActionListener(this);
		translateXYMode.addActionListener(this);
		translateZYMode.addActionListener(this);
		
		
		previewTabs.addChangeListener(this);

		cameraControls.add(resetCamera);
		cameraControls.add(centerModel);
	//	cameraControls.add(zoomIn);
	//	cameraControls.add(zoomOut);
	//	cameraControls.add(rotateXZPlus);
	//	cameraControls.add(rotateXZMinus);
	//	cameraControls.add(rotateUp);
	//cameraControls.add(rotateDown);
		cameraControls.add(toggleOutline);
	//	cameraControls.add(translateLeft);
	//	cameraControls.add(translateRight);
	//	cameraControls.add(rotateModel);
		cameraControls.add(cameraMode);
		cameraControls.add(rotateXMode);
		cameraControls.add(rotateYMode);
		cameraControls.add(rotateZMode);
		cameraControls.add(translateXYMode);
		cameraControls.add(translateZYMode);
		
		cameraMode.setSelected(true);
		rotateXMode.setSelected(false);
		rotateYMode.setSelected(false);
		rotateZMode.setSelected(false);
		translateXYMode.setSelected(false);
		translateZYMode.setSelected(false);
			

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

	public boolean addPreview(File stl, Point3f workspaceDimensions)
			throws Exception {
		File gcode = new File(stl.getAbsolutePath() + ".gcode");
		return addPreview(stl, gcode, workspaceDimensions);
	}

	public boolean addPreview(File stl, File gcode, Point3f workspaceDimensions)
			throws Exception {
		if (!thePreviews.containsKey(stl) && !currentlyLoading.contains(stl)) {

			String name = stl.getName();

			SimpleLoadingScreen tempLoad = new SimpleLoadingScreen(name
					+ " preview is loading...", true);
			previewTabs.add("Loading: " + name, tempLoad);
			previewTabs.setSelectedComponent(tempLoad);

			this.update(this.getGraphics());

			AddPreviewThread apt = new AddPreviewThread(tempLoad, stl, gcode,
					workspaceDimensions);
			apt.start();

			return true;
		}
		if (!currentlyLoading.contains(stl)) {
			STLPreview tempPreview = thePreviews.get(stl);
			tempPreview.setOutlineVisibility(toggleOutline.isSelected());
			previewTabs.setSelectedComponent(tempPreview);
		} else {
			previewTabs.setSelectedIndex(previewTabs.indexOfTab("Loading: " + stl.getName()));
		}

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
		/*if (event.getSource().equals(zoomIn)) {
			current.zoom(current.getWorkspaceDimensions().x / 2);
		} else if (event.getSource().equals(zoomOut)) {
			current.zoom(-current.getWorkspaceDimensions().x / 2);
		} else if (event.getSource().equals(rotateXZPlus)) {
			current.rotateCameraXZ(.3);
		} else if (event.getSource().equals(rotateXZMinus)) {
			current.rotateCameraXZ(-.3);
		} else if (event.getSource().equals(rotateUp)) {
			current.rotateCameraUp(.15);
		} else if (event.getSource().equals(rotateDown)) {
			current.rotateCameraUp(-.15);
		} else if (event.getSource().equals(translateLeft)) {
			current.translateX(-.3);
		} else if (event.getSource().equals(translateRight)) {
			current.translateX(.3);
		} else if (event.getSource().equals(rotateModel)) {
			current.rotateY(.3);
		} else */if (event.getSource().equals(resetCamera)) {
			current.resetCamera();
		} else if(event.getSource().equals(centerModel)){
			current.pointNormalDown(null);
			//TODO current.resetModelTransforms();
			//current.centerOnWorkspace();
		}
		else if (event.getSource().equals(toggleOutline)) {
			current.setOutlineVisibility(!current.getOutlineVisibility());
		} else if (event.getSource().equals(cameraMode)){
			//selectOnly(cameraMode);
			cameraMode.setSelected(true); 
			rotateXMode.setSelected(false);
			rotateYMode.setSelected(false);
			rotateZMode.setSelected(false);
			translateXYMode.setSelected(false);
			translateZYMode.setSelected(false);
			current.getMouseControls().setMouseControlMode(MouseControlMode.CAMERA_ROTATE);
		
		} else if (event.getSource().equals(rotateXMode)){
			//selectOnly(rotateXMode);
			cameraMode.setSelected(false); 
			rotateXMode.setSelected(true);
			rotateYMode.setSelected(false);
			rotateZMode.setSelected(false);
			translateXYMode.setSelected(false);
			translateZYMode.setSelected(false);
			current.getMouseControls().setMouseControlMode(MouseControlMode.MODEL_ROTATE_X);
		
		} else if (event.getSource().equals(rotateYMode)){
			//selectOnly(rotateYMode);
			cameraMode.setSelected(false); 
			rotateXMode.setSelected(false);
			rotateYMode.setSelected(true);
			rotateZMode.setSelected(false);
			translateXYMode.setSelected(false);
			translateZYMode.setSelected(false);
			current.getMouseControls().setMouseControlMode(MouseControlMode.MODEL_ROTATE_Y);
		
		} else if (event.getSource().equals(rotateZMode)){
			//selectOnly(rotateZMode);
			cameraMode.setSelected(false); 
			rotateXMode.setSelected(false);
			rotateYMode.setSelected(false);
			rotateZMode.setSelected(true);
			translateXYMode.setSelected(false);
			translateZYMode.setSelected(false);
			current.getMouseControls().setMouseControlMode(MouseControlMode.MODEL_ROTATE_Z);	
		} else if (event.getSource().equals(translateXYMode)){
			//selectOnly(translateXYMode);
			cameraMode.setSelected(false); 
			rotateXMode.setSelected(false);
			rotateYMode.setSelected(false);
			rotateZMode.setSelected(false);
			translateXYMode.setSelected(true);
			translateZYMode.setSelected(false);
			current.getMouseControls().setMouseControlMode(MouseControlMode.MODEL_TRANSLATE_XY);
			
		} else if (event.getSource().equals(translateZYMode)){
			//selectOnly(translateZYMode);
			cameraMode.setSelected(false); 
			rotateXMode.setSelected(false);
			rotateYMode.setSelected(false);
			rotateZMode.setSelected(false);
			translateXYMode.setSelected(false);
			translateZYMode.setSelected(true);			
			current.getMouseControls().setMouseControlMode(MouseControlMode.MODEL_TRANSLATE_ZY);
		}

	}

	private class AddPreviewThread extends Thread {

		SimpleLoadingScreen theLoadingScreen;
		File stl, gcode;
		Point3f workspaceDimensions;

		public AddPreviewThread(SimpleLoadingScreen sls, File stl, File gcode,
				Point3f workspaceDimensions) {
			super();
			theLoadingScreen = sls;
			this.stl = stl;
			this.gcode = gcode;
			this.workspaceDimensions = workspaceDimensions;
			currentlyLoading.add(stl);

		}

		public void run() {

			STLPreview tempPreview = new STLPreview(stl, gcode,
					workspaceDimensions);
			String name = stl.getName();

			if (!tempPreview.getSTLObject().getName()
					.equalsIgnoreCase("Default"))
				name += " (" + tempPreview.getSTLObject().getName() + ")";

			int index = previewTabs.indexOfComponent(theLoadingScreen);
			ImageIcon imageIcon = new ImageIcon("Images\\simpleCube.png");
			previewTabs.insertTab(name, imageIcon, tempPreview, name, index);
			
			thePreviews.put(stl, tempPreview);
			// previewTabs.setSelectedComponent(tempPreview);

			previewTabs.remove(theLoadingScreen);

			STLPreviewMouseControls theMouseControls = new STLPreviewMouseControls(tempPreview);
			theMouseControls.setMouseControlMode(getCurrentSelectedMode());
			tempPreview.setMouseControls(theMouseControls);
			
			tempPreview.setOutlineVisibility(toggleOutline.isSelected());

			currentlyLoading.remove(stl);
		}

	}

	@Override
	public void stateChanged(ChangeEvent arg0) {
		if (!hasNoPreviews()){
			try{
			STLPreview current = ((STLPreview) previewTabs.getSelectedComponent());
			
			if(current.getMouseControls()!=null)
			current.getMouseControls().setMouseControlMode(getCurrentSelectedMode());
			}
			catch (ClassCastException e){
				//TODO
			}
		}
		this.repaint();		
	}

	public MouseControlMode getCurrentSelectedMode() {
		if(cameraMode.isSelected()) return MouseControlMode.CAMERA_ROTATE;
		else if(rotateXMode.isSelected()) return MouseControlMode.MODEL_ROTATE_X;
		else if(rotateYMode.isSelected()) return MouseControlMode.MODEL_ROTATE_Y;
		else if(rotateZMode.isSelected()) return MouseControlMode.MODEL_ROTATE_Z;
		else if(translateXYMode.isSelected()) return MouseControlMode.MODEL_TRANSLATE_XY;
		else if(translateZYMode.isSelected()) return MouseControlMode.MODEL_TRANSLATE_ZY;
		
		return MouseControlMode.CAMERA_ROTATE;
	}

	/*
	 * public void setLayout(LayoutManager lm){ if(!layoutSet){
	 * super.setLayout(lm); layoutSet = true; } }
	 */

}
