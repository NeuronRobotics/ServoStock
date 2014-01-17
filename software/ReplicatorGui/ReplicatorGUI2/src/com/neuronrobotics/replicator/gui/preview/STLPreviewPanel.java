package com.neuronrobotics.replicator.gui.preview;

import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.dnd.DropTarget;
import java.awt.dnd.DropTargetDragEvent;
import java.awt.dnd.DropTargetDropEvent;
import java.awt.dnd.DropTargetEvent;
import java.awt.dnd.DropTargetListener;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Hashtable;
import java.util.List;

//import javax.media.j3d.Transform3D;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JLayeredPane;
import javax.swing.JTabbedPane;
import javax.swing.JToggleButton;
import javax.swing.JToolBar;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
//import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.GUIFrontendInterface;
//import com.neuronrobotics.replicator.gui.preview.STLPreviewCameraController.CameraMode;
import com.neuronrobotics.replicator.gui.preview.controller.STLPreviewMouseController.MouseControlMode;
//import com.neuronrobotics.replicator.gui.preview.j3d.GeneralTransform3DJava3DAdapter;
//import com.neuronrobotics.replicator.gui.preview.j3d.STLPreviewCanvas3D;
//import com.neuronrobotics.replicator.gui.preview.j3d.STLPreviewMouseControls;
//import com.neuronrobotics.replicator.gui.preview.j3d.STLPreviewMouseControls.MouseControlMode;
 
import com.neuronrobotics.replicator.gui.preview.view.STLWorkspaceViewListener;
//import com.neuronrobotics.replicator.gui.stl.GeneralTransform3D;
//import com.neuronrobotics.replicator.gui.stl.STLFacet;
//import com.neuronrobotics.replicator.gui.stl.STLObject;
//import com.neuronrobotics.replicator.gui.stl.STLObjectCalculationUtilities;
import com.neuronrobotics.replicator.gui.stl.STLLoader;

public class STLPreviewPanel extends JLayeredPane implements ActionListener,
		ChangeListener,STLPreviewTabListener, STLWorkspaceViewListener, DropTargetListener {

	/**
	 * 
	 */
	private static final long serialVersionUID = -5820208700200328570L;
	private JTabbedPane previewTabbedPane;
	private Hashtable<STLPreviewTab, STLPreviewTab> thePreviewTabs;

	private JComboBox<MouseControlMode> mouseModeMenu;
	//private JComboBox<STLPreviewCameraController.CameraMode> focusModeMenu;

	private JToolBar cameraControls;
	private JButton resetCamera, removePreview;// centerModel, forceReload;
	private JToggleButton toggleOutline;
		
	private GUIFrontendInterface theFrontend;
	
	//private JButton analyzePlacement;
	
	public STLPreviewPanel(GUIFrontendInterface front) {
		
		theFrontend = front;

		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();

		setFont(new Font("SansSerif", Font.PLAIN, 14));
		setLayout(gridbag);

		previewTabbedPane = new JTabbedPane();
		thePreviewTabs = new Hashtable<STLPreviewTab, STLPreviewTab>();
		cameraControls = new JToolBar();
		resetCamera = new JButton("Reset Camera");
	//	centerModel = new JButton("Reset STL");
		removePreview = new JButton("Remove current preview");
	//	forceReload = new JButton("Force Reload");
		//analyzePlacement = new JButton("Analyze");

		MouseControlMode[] mouseModes = MouseControlMode.getModes();
		//STLPreviewCameraController.CameraMode[] focusModes = STLPreviewCameraController.CameraMode.getModes();

		mouseModeMenu = new JComboBox<MouseControlMode>(
				mouseModes);
	//	focusModeMenu = new JComboBox<STLPreviewCameraController.CameraMode>(focusModes);

		toggleOutline = new JToggleButton("Outline: OFF", false);

		resetCamera.addActionListener(this);
		//centerModel.addActionListener(this);
		removePreview.addActionListener(this);

		toggleOutline.addActionListener(this);
		mouseModeMenu.addActionListener(this);
	//	focusModeMenu.addActionListener(this);

		//forceReload.addActionListener(this);
		//analyzePlacement.addActionListener(this);

		previewTabbedPane.addChangeListener(this);
		
		cameraControls.add(resetCamera);
		//cameraControls.add(centerModel);

		cameraControls.add(removePreview);

		cameraControls.add(toggleOutline);

		cameraControls.add(mouseModeMenu);
		//cameraControls.add(focusModeMenu);

		//cameraControls.add(forceReload);
		//cameraControls.add(analyzePlacement);
				
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
		
		DropTarget dt = new DropTarget(this,this);
		this.setDropTarget(dt);	
	}

	public void addEmptyWorkspace(String wsName, File workspaceSTL) {
		ImageIcon imageIcon = new ImageIcon("Images\\simpleCube.png");
		STLPreviewTab newTab = new STLPreviewTab(wsName,workspaceSTL);
		newTab.addTabListener(this);
		thePreviewTabs.put(newTab, newTab);
		//previewTabbedPane.add(newTab);
		previewTabbedPane.add(newTab, wsName);
		int tcount = previewTabbedPane.getTabCount();
		previewTabbedPane.setIconAt(tcount - 1, imageIcon);
		previewTabbedPane.setSelectedIndex(tcount - 1);
		newTab.load();
	}
	
	public boolean addPreview(File stl, File wstl)
			throws Exception {
		File gcode = new File(stl.getAbsolutePath() + ".gcode");
		return addPreview(stl, gcode, wstl);
	}

	public boolean addPreview(File stl, File gcode, File workspaceSTL)
			throws Exception {

		String name = "Workspace("+this.thePreviewTabs.size()+")";//stl.getName();
		ImageIcon imageIcon = new ImageIcon("Images\\simpleCube.png");

		if (!thePreviewTabs.containsKey(stl)) {
			STLPreviewTab newTab = new STLPreviewTab(this, stl,	workspaceSTL);
			thePreviewTabs.put(newTab, newTab);
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

	/*public STLPreviewCanvas3D getCurrentPreview() {
		if (thePreviewTabs.size() == 0)
			return null;
		STLPreviewTab currentTab = ((STLPreviewTab) previewTabbedPane
				.getSelectedComponent());
		if (currentTab.isLoaded())
			return currentTab.getTheSTLPreview();
		return null;
	}*/

	public boolean hasNoPreviews() {
		return previewTabbedPane.getTabCount() == 0;
	}

	@Override
	public void actionPerformed(ActionEvent event) {

		STLPreviewTab currentTab;
		//STLPreviewCanvas3D currentPreview;

		currentTab = ((STLPreviewTab) previewTabbedPane.getSelectedComponent());

		if (currentTab != null && currentTab.isLoaded() ) {

			//currentPreview = currentTab.getTheSTLPreview();
			
			//currentPreview.setOutlineVisibility(isOutlineSelected());
			//TODO no functionality for this yet in the new version
			
			/*if(event.getSource().equals(focusModeMenu)){
				currentPreview.getTheCameraController()
				.setCameraFocusMode(getCurrentSelectedCameraFocusMode());
			} else */if(event.getSource().equals(this.mouseModeMenu)){
				//currentPreview.getMouseControls().setMouseControlMode(getCurrentSelectedMouseMode());
				currentTab.getTheMotherFuckingController().getSTLPreviewMouseController().setCurrentMouseControlMode(getCurrentSelectedMouseMode());
				
			} else if (event.getSource().equals(resetCamera)) {
				//currentPreview.getTheCameraController().resetCamera();
				currentTab.getTheMotherFuckingController().getGeneralCameraController().setCamera(new double[]{100,100,100},new double[]{0,0,0});
				//TODO maybe a better way to reset the camera?
			} /*else if (event.getSource().equals(centerModel)) {
				currentPreview.resetModelTransforms();
								
				//currentPreview.centerOnWorkspace();
			}*/ else if (event.getSource().equals(toggleOutline)) {
				boolean onOff = isOutlineSelected();
				String newText = (onOff) ? "Outline:  ON" : "Outline: OFF";
				toggleOutline.setText(newText);
				//currentPreview.setOutlineVisibility(onOff);
			} /*else if (event.getSource().equals(forceReload)) {
				currentTab.reload();
			} else if (event.getSource().equals(analyzePlacement)){
				//TODO currently just for testing
				STLObject curr = this.getCurrentPreview().getMergedSTLObject();
				Transform3D t = new Transform3D();
				t.setTranslation(new Vector3f(0,-curr.getMin().y,0));
				GeneralTransform3D tran = new GeneralTransform3DJava3DAdapter(t);
								
				curr=curr.getTransformedSTLObject(tran);
				for(STLFacet fac:curr){
					System.out.println(fac.getMin());
				}
				//Scanner s = new Scanner(System.in);
				//s.next();
				
				System.out.println(STLObjectCalculationUtilities.approximateSupportVolume(curr, 10));
			}*/
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
					//currentTab.getTheSTLPreview().getMouseControls().setMouseControlMode(getCurrentSelectedMouseMode());
					
					currentTab.getTheMotherFuckingController().getSTLPreviewMouseController().setCurrentMouseControlMode(getCurrentSelectedMouseMode());
					
					//currentTab.getTheSTLPreview().getTheCameraController().setCameraFocusMode(getCurrentSelectedCameraFocusMode());
					//currentTab.getTheSTLPreview().setOutlineVisibility(isOutlineSelected());
				}
			} catch (ClassCastException e) {
				e.printStackTrace();
			}
		}
		this.theFrontend.requestValidate();
	}

	/*
	public CameraMode getCurrentSelectedCameraFocusMode() {
		return (CameraMode) this.focusModeMenu.getSelectedItem();
	}*/

	public MouseControlMode getCurrentSelectedMouseMode() {

		return (MouseControlMode) this.mouseModeMenu.getSelectedItem();

	}

	public void alertTabIsDead(STLPreviewTab deadTab) {
		theFrontend.errorDialog("Preview for " + deadTab.getName()
				+ " has met with an unexpected error");
		removeTab(deadTab);
	}

	public void alertTabIsLoaded(STLPreviewTab loadedTab){
		//loadedTab.getTheSTLPreview().getTheCameraController().setCameraFocusMode(getCurrentSelectedCameraFocusMode());
		//loadedTab.getTheSTLPreview().setOutlineVisibility(isOutlineSelected());
	
		//loadedTab.getTheSTLPreview().getMouseControls().setMouseControlMode(getCurrentSelectedMouseMode());
		loadedTab.getTheMotherFuckingController().getSTLPreviewMouseController().setCurrentMouseControlMode(getCurrentSelectedMouseMode());
		
		//loadedTab.getTheSTLPreview().getTheCameraController().resetCamera();
		
		//loadedTab.getTheSTLPreview().addListener(this);
		//TODO should add some types of listeners for new version perhaps?
				
		theFrontend.requestValidate();
	}
	
	public void removeTab(STLPreviewTab toRemove) {
		if (thePreviewTabs.contains(toRemove)) {
			thePreviewTabs.remove(toRemove);
			//thePreviewTabs.remove(toRemove.getSTLFile());
			previewTabbedPane.remove(toRemove);
		}		
				
		//STLPreviewCanvas3D curr = getCurrentPreview();
		
	//	if(curr!=null){
			//curr.getTheCameraController().rotateCameraXZ(6.28);
		//}
		
		theFrontend.requestValidate();
		
	}

	public boolean isOutlineSelected() {
		return toggleOutline.isSelected();
	}
	
	public STLPreviewTab getCurrentTab() {
		return (STLPreviewTab)previewTabbedPane.getSelectedComponent();
	}

	@Override
	public void dragEnter(DropTargetDragEvent arg0) {		
	}

	@Override
	public void dragExit(DropTargetEvent arg0) {
	}

	@Override
	public void dragOver(DropTargetDragEvent arg0) {		
	}

	@SuppressWarnings("unchecked")
	@Override
	public void drop(DropTargetDropEvent arg0) {
		if(arg0.getCurrentDataFlavorsAsList().contains(DataFlavor.javaFileListFlavor)){
			File newSTL;
			try {
				newSTL = ((List<File>)arg0.getTransferable().getTransferData(DataFlavor.javaFileListFlavor)).get(0);
			} catch (UnsupportedFlavorException | IOException e) {
				e.printStackTrace();
				return;
			}
						
			if(newSTL.getName().endsWith(".stl")){
				if(this.hasNoPreviews()){
					//this.addEmptyWorkspace("Untitled", workspaceSTL);
					//TODO
					return;
				}
				//this.getCurrentPreview().addModelToWorkspace(newSTL);
				try {
					this.getCurrentTab().getTheMotherFuckingModel().addSTLObject(STLLoader.loadFile(newSTL));
					this.getCurrentTab().alertSTLObjectAdded();
				} catch (IOException e) {
					this.theFrontend.errorDialog("IO Error loading STL");
					e.printStackTrace();
				}
				
			} 
		}
	}

	@Override
	public void dropActionChanged(DropTargetDragEvent arg0) {		
	}

	@Override
	public void alertCameraMoved(double[] position, double[] direction,	double[] orientation) {
		//Point3d pos = new Point3d(position);
		//Point3d dir = new Point3d(direction);
		//Vector3d or = new Vector3d(orientation);
		//this.alertCameraMoved(pos, dir, or);	
		//currently doesn't have to listen to this
		//TODO remove
	}
	
}
