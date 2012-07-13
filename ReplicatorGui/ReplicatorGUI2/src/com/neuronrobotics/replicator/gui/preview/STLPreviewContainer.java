package com.neuronrobotics.replicator.gui.preview;

import java.awt.Container;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.util.Hashtable;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JTabbedPane;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.vecmath.Point3f;

import com.neuronrobotics.replicator.gui.GUIFrontendInterface;
import com.neuronrobotics.replicator.gui.preview.STLPreviewCanvas3D.CameraFocusMode;
import com.neuronrobotics.replicator.gui.preview.STLPreviewMouseControls.MouseControlMode;

public class STLPreviewContainer extends Container implements ActionListener,
		ChangeListener,STLPreviewTabListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5820208700200328570L;
	private JTabbedPane previewTabbedPane;
	private Hashtable<File, STLPreviewTab> thePreviewTabs;

	private JComboBox<STLPreviewMouseControls.MouseControlMode> mouseModeMenu;
	private JComboBox<STLPreviewCanvas3D.CameraFocusMode> focusModeMenu;

	private JToolBar cameraControls;
	private JButton resetCamera, centerModel, removePreview, forceReload;
	private JToggleButton toggleOutline;
	
	//private STLPreviewTab workaroundTab;

	private GUIFrontendInterface theFrontend;

	public STLPreviewContainer(GUIFrontendInterface front) {

		//workaroundTab = null;
		
		theFrontend = front;

		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("SansSerif", Font.PLAIN, 14));
		setLayout(gridbag);

		previewTabbedPane = new JTabbedPane();
		thePreviewTabs = new Hashtable<File, STLPreviewTab>();
		cameraControls = new JToolBar();
		resetCamera = new JButton("Reset Camera");
		centerModel = new JButton("Reset STL");
		removePreview = new JButton("Remove current preview");
		forceReload = new JButton("Force Reload");

		STLPreviewMouseControls.MouseControlMode[] mouseModes = STLPreviewMouseControls.MouseControlMode
				.getModes();
		STLPreviewCanvas3D.CameraFocusMode[] focusModes = STLPreviewCanvas3D.CameraFocusMode
				.getModes();

		mouseModeMenu = new JComboBox<STLPreviewMouseControls.MouseControlMode>(
				mouseModes);
		focusModeMenu = new JComboBox<STLPreviewCanvas3D.CameraFocusMode>(focusModes);

		toggleOutline = new JToggleButton("Toggle Outline", true);

		resetCamera.addActionListener(this);
		centerModel.addActionListener(this);
		removePreview.addActionListener(this);

		toggleOutline.addActionListener(this);
		mouseModeMenu.addActionListener(this);
		focusModeMenu.addActionListener(this);

		forceReload.addActionListener(this);

		previewTabbedPane.addChangeListener(this);

		cameraControls.add(resetCamera);
		cameraControls.add(centerModel);

		cameraControls.add(removePreview);

		cameraControls.add(toggleOutline);

		cameraControls.add(mouseModeMenu);
		cameraControls.add(focusModeMenu);

		cameraControls.add(forceReload);

		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;

		c.gridwidth = GridBagConstraints.REMAINDER;
		c.gridheight = GridBagConstraints.RELATIVE;
		c.weighty = 1.0;

		gridbag.setConstraints(previewTabbedPane, c);
		this.add(previewTabbedPane);

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

		String name = stl.getName();
		ImageIcon imageIcon = new ImageIcon("Images\\simpleCube.png");

		if (!thePreviewTabs.containsKey(stl)) {
			STLPreviewTab newTab = new STLPreviewTab(this, stl, gcode,
					workspaceDimensions);
			thePreviewTabs.put(stl, newTab);
			previewTabbedPane.add(newTab);
			previewTabbedPane.add(newTab, name);
			int tcount = previewTabbedPane.getTabCount();
			previewTabbedPane.setIconAt(tcount - 1, imageIcon);
			previewTabbedPane.setSelectedIndex(tcount - 1);
			newTab.load();
			previewTabbedPane.validate();
			return true;
		} else {
			int index = previewTabbedPane.indexOfTab(name);
			if (index != -1)
				previewTabbedPane.setSelectedIndex(index);
			return false;
		}

	}

	public File getCurrentSTLFile() {
		if (thePreviewTabs.size() == 0)
			return null;
		STLPreviewTab currentTab = ((STLPreviewTab) previewTabbedPane
				.getSelectedComponent());
		if (currentTab.isLoaded())
			return currentTab.getTheSTLPreview().getSTLFile();
		return null;
	}

	public File getCurrentGCodeFile() {
		if (thePreviewTabs.size() == 0)
			return null;
		STLPreviewTab currentTab = ((STLPreviewTab) previewTabbedPane
				.getSelectedComponent());
		if (currentTab.isLoaded())
			return currentTab.getTheSTLPreview().getGCodeFile();
		return null;
	}

	public STLPreviewCanvas3D getCurrentPreview() {
		if (thePreviewTabs.size() == 0)
			return null;
		STLPreviewTab currentTab = ((STLPreviewTab) previewTabbedPane
				.getSelectedComponent());
		if (currentTab.isLoaded())
			return currentTab.getTheSTLPreview();
		return null;
	}

	public boolean hasNoPreviews() {
		return previewTabbedPane.getTabCount() == 0;
	}

	@Override
	public void actionPerformed(ActionEvent event) {

		STLPreviewTab currentTab;
		STLPreviewCanvas3D currentPreview;

		currentTab = ((STLPreviewTab) previewTabbedPane.getSelectedComponent());

		if (currentTab != null && currentTab.isLoaded() ) {

			currentPreview = currentTab.getTheSTLPreview();
			currentPreview.getMouseControls().setMouseControlMode(
					getCurrentSelectedMouseMode());
			currentPreview
					.setCameraFocusMode(getCurrentSelectedCameraFocusMode());
			currentPreview.setOutlineVisibility(isOutlineSelected());

			if (event.getSource().equals(resetCamera)) {
				currentPreview.resetCamera();
			} else if (event.getSource().equals(centerModel)) {
				currentPreview.resetModelTransforms();
				currentPreview.centerOnWorkspace();
			} else if (event.getSource().equals(toggleOutline)) {
				currentPreview.setOutlineVisibility(isOutlineSelected());
			}  else if (event.getSource().equals(forceReload)) {
				//currentPreview.getCanvas3D().invalidate();
				//validate();
				//theFrontend.requestValidate();
				currentTab.reload();
				//workAround();
			}
		}
		
		if (event.getSource().equals(removePreview)) {
			if (!hasNoPreviews()) {
				removeTab((STLPreviewTab) previewTabbedPane
						.getSelectedComponent());
			}
		}

	}

	@Override
	public void stateChanged(ChangeEvent arg0) {
		if (!hasNoPreviews()) {
			try {
				STLPreviewTab currentTab = ((STLPreviewTab) previewTabbedPane
						.getSelectedComponent());
				if (currentTab.isLoaded()) {
					currentTab.getTheSTLPreview().getMouseControls()
							.setMouseControlMode(getCurrentSelectedMouseMode());
					currentTab.getTheSTLPreview().setCameraFocusMode(
							getCurrentSelectedCameraFocusMode());
					currentTab.getTheSTLPreview().setOutlineVisibility(
							isOutlineSelected());
				}
			} catch (ClassCastException e) {
				e.printStackTrace();
			}
		}
		this.theFrontend.requestValidate();
	}

	public CameraFocusMode getCurrentSelectedCameraFocusMode() {
		return (CameraFocusMode) this.focusModeMenu.getSelectedItem();
	}

	public MouseControlMode getCurrentSelectedMouseMode() {

		return (MouseControlMode) this.mouseModeMenu.getSelectedItem();

	}

	public void alertTabIsDead(STLPreviewTab deadTab) {
		theFrontend.errorDialog("Preview for " + deadTab.getSTLFile().getName()
				+ " has met with an unexpected error");
		removeTab(deadTab);
	}

	public void alertTabIsLoaded(STLPreviewTab loadedTab){
		loadedTab.getTheSTLPreview().setCameraFocusMode(getCurrentSelectedCameraFocusMode());
		loadedTab.getTheSTLPreview().setOutlineVisibility(isOutlineSelected());
		loadedTab.getTheSTLPreview().getMouseControls().setMouseControlMode(getCurrentSelectedMouseMode());
		loadedTab.getTheSTLPreview().resetCamera();
	}

	public void removeTab(STLPreviewTab toRemove) {
		//toRemove.killTab();
		
		int index = previewTabbedPane.indexOfComponent(toRemove);
		
		if (thePreviewTabs.contains(toRemove)) {
			//if(!toRemove.isLoaded()) toRemove.stopLoading();
			thePreviewTabs.remove(toRemove.getSTLFile());
			previewTabbedPane.remove(toRemove);
		}		
		
		if(index==previewTabbedPane.getTabCount()&&index>0){
		//	workAround();
		}
		
	}

	public boolean isOutlineSelected() {
		return toggleOutline.isSelected();
	}

	
	public STLPreviewTab getCurrentTab() {
		return (STLPreviewTab)previewTabbedPane.getSelectedComponent();
	}
	
	/*
	private void workAround(){
		File blankSTL,blankGCode;
		
		try {
			blankSTL = File.createTempFile("blank", "stl");
			FileWriter fw = new FileWriter(blankSTL);
			fw.write("solid\nfacet\nouter loop\nvertex 0 0 0\nvertex 2 0 0\nvertex 2 3 0\nendloop\nendfacet\nfacet\nouter loop\nvertex 1 0 0\nvertex 2 2 0\nvertex 2 3 3\nendloop\nendfacet\nendsolid");	
			fw.close();
			fw = null;
			
			blankGCode = File.createTempFile("blank", "gcode");
			Point3f wdim  = new Point3f(1,1,1);	
			
			if(workaroundTab!=null &&previewTabbedPane.indexOfComponent(workaroundTab)!=-1) previewTabbedPane.remove(workaroundTab);

			workaroundTab = new STLPreviewTab(this, blankSTL, blankGCode, wdim);
			workaroundTab.load();			
			previewTabbedPane.add(workaroundTab);
			
			
			int index = previewTabbedPane.getSelectedIndex();
			
			previewTabbedPane.setSelectedComponent(workaroundTab);
			workaroundTab.getTheSTLPreview().getView().stopView();
			workaroundTab.getTheSTLPreview().getView().renderOnce();
			
			previewTabbedPane.setSelectedIndex(index);
			
			previewTabbedPane.getTabComponentAt(previewTabbedPane.getTabCount()-1).setVisible(false);
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
	*/
	
}
