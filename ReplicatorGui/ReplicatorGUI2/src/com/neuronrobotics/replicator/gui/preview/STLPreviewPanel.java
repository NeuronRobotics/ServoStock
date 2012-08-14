package com.neuronrobotics.replicator.gui.preview;

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
import javax.swing.JLayeredPane;
import javax.swing.JTabbedPane;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import com.neuronrobotics.replicator.gui.GUIFrontendInterface;
import com.neuronrobotics.replicator.gui.preview.STLPreviewCameraController.CameraMode;
import com.neuronrobotics.replicator.gui.preview.STLPreviewMouseControls.MouseControlMode;

public class STLPreviewPanel extends JLayeredPane implements ActionListener,
		ChangeListener,STLPreviewTabListener, STLPreviewCanvas3DListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5820208700200328570L;
	private JTabbedPane previewTabbedPane;
	private Hashtable<File, STLPreviewTab> thePreviewTabs;

	private JComboBox<STLPreviewMouseControls.MouseControlMode> mouseModeMenu;
	private JComboBox<STLPreviewCameraController.CameraMode> focusModeMenu;

	private JToolBar cameraControls;
	private JButton resetCamera, centerModel, removePreview, forceReload;
	private JToggleButton toggleOutline;
		
	private GUIFrontendInterface theFrontend;
	
	private OrientationIndicatorCanvas3D orientationIndicator;
	
	public STLPreviewPanel(GUIFrontendInterface front) {

		//workaroundTab = null;
		
		orientationIndicator = new OrientationIndicatorCanvas3D();
		
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
		STLPreviewCameraController.CameraMode[] focusModes = STLPreviewCameraController.CameraMode
				.getModes();

		mouseModeMenu = new JComboBox<STLPreviewMouseControls.MouseControlMode>(
				mouseModes);
		focusModeMenu = new JComboBox<STLPreviewCameraController.CameraMode>(focusModes);

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
		
		cameraControls.add(orientationIndicator);
		
		c.fill = GridBagConstraints.BOTH;
		c.weightx = 1.0;

		c.gridwidth = GridBagConstraints.REMAINDER;
		c.gridheight = GridBagConstraints.RELATIVE;
		c.weighty = 1.0;

		gridbag.setConstraints(previewTabbedPane, c);
		this.setLayer(previewTabbedPane, DEFAULT_LAYER, -1);
		this.add(previewTabbedPane);

		c.weighty = 0.0;
		c.gridheight = 1;

		gridbag.setConstraints(cameraControls, c);
		this.setLayer(cameraControls, DEFAULT_LAYER, 0);
		this.add(cameraControls);
		
				
	}

	public boolean addPreview(File stl, File wstl)
			throws Exception {
		File gcode = new File(stl.getAbsolutePath() + ".gcode");
		return addPreview(stl, gcode, wstl);
	}

	public boolean addPreview(File stl, File gcode, File workspaceSTL)
			throws Exception {

		String name = stl.getName();
		ImageIcon imageIcon = new ImageIcon("Images\\simpleCube.png");

		if (!thePreviewTabs.containsKey(stl)) {
			STLPreviewTab newTab = new STLPreviewTab(this, stl, gcode,
					workspaceSTL);
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
			return currentTab.getTheSTLPreview().getMergedSTLFile();
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
			currentPreview.getTheCameraController()
					.setCameraFocusMode(getCurrentSelectedCameraFocusMode());
			currentPreview.setOutlineVisibility(isOutlineSelected());

			if (event.getSource().equals(resetCamera)) {
				currentPreview.getTheCameraController().resetCamera();
			} else if (event.getSource().equals(centerModel)) {
				currentPreview.resetModelTransforms();
				//currentPreview.centerOnWorkspace();
			} else if (event.getSource().equals(toggleOutline)) {
				currentPreview.setOutlineVisibility(isOutlineSelected());
			} else if (event.getSource().equals(forceReload)) {
				currentTab.reload();
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
					currentTab.getTheSTLPreview().getTheCameraController().setCameraFocusMode(
							getCurrentSelectedCameraFocusMode());
					currentTab.getTheSTLPreview().setOutlineVisibility(
							isOutlineSelected());
					updateOrientationIndicator(false);
				}
			} catch (ClassCastException e) {
				e.printStackTrace();
			}
		}
		this.theFrontend.requestValidate();
	}

	public CameraMode getCurrentSelectedCameraFocusMode() {
		return (CameraMode) this.focusModeMenu.getSelectedItem();
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
		loadedTab.getTheSTLPreview().getTheCameraController().setCameraFocusMode(getCurrentSelectedCameraFocusMode());
		loadedTab.getTheSTLPreview().setOutlineVisibility(isOutlineSelected());
		loadedTab.getTheSTLPreview().getMouseControls().setMouseControlMode(getCurrentSelectedMouseMode());
		loadedTab.getTheSTLPreview().getTheCameraController().resetCamera();
		
		loadedTab.getTheSTLPreview().addListener(this);
		
		updateOrientationIndicator(true);
		
		theFrontend.requestValidate();
	}
	
	private void updateOrientationIndicator(boolean reload) {
		
		if (reload) {
			cameraControls.remove(orientationIndicator);
			orientationIndicator = new OrientationIndicatorCanvas3D();
			cameraControls.add(orientationIndicator);
		}
		
		STLPreviewCanvas3D curr = getCurrentPreview();
		if(curr!=null){
			orientationIndicator.setCamera(curr.getCameraPosition(), curr.getCameraDirection(), curr.getCameraOrientation());
		}
	}

	public void removeTab(STLPreviewTab toRemove) {
		
		int index = previewTabbedPane.indexOfComponent(toRemove);
		
		if (thePreviewTabs.contains(toRemove)) {
			thePreviewTabs.remove(toRemove.getSTLFile());
			previewTabbedPane.remove(toRemove);
		}		
				
		if(index==previewTabbedPane.getTabCount()) updateOrientationIndicator(true);
		else updateOrientationIndicator(false);
		
		STLPreviewCanvas3D curr = getCurrentPreview();
		
		if(curr!=null){
			curr.getTheCameraController().rotateCameraXZ(6.28);
			updateOrientationIndicator(false);
		}
		
		theFrontend.requestValidate();
		
	}

	public boolean isOutlineSelected() {
		return toggleOutline.isSelected();
	}
	
	public STLPreviewTab getCurrentTab() {
		return (STLPreviewTab)previewTabbedPane.getSelectedComponent();
	}

	@Override
	public void alertCameraMoved(Point3d position, Point3d direction,
			Vector3d orientation) {
		updateOrientationIndicator(false);		
	}
	
}
