package com.neuronrobotics.replicator.gui.preview;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.media.j3d.BoundingSphere;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.STLLoader;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLTransformGroup;
import com.neuronrobotics.replicator.gui.stl.STLTransformGroupListener;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceBranchGroup;
import com.sun.j3d.utils.picking.PickResult;
import com.sun.j3d.utils.universe.SimpleUniverse;

public class STLPreviewCanvas3D extends Canvas3D implements STLTransformGroupListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = -45261396936364195L;

	// basic fields for creating java 3d scene
	private SimpleUniverse simpleU;
	private BranchGroup mainBranch;
	private BranchGroup modelBranch, workspaceBranch;

	// transform group for the stl model itself
	private STLTransformGroup currentSTLTransform;
	private ArrayList<STLTransformGroup> theSTLTransforms;
		
	// transform group that displays the area in which the printer can reliably print
	private STLWorkspaceBranchGroup theWorkspace;
	
	private DirectionalLight theLight;

	private Point3d cameraPosition, cameraDirection;
	private Vector3d cameraOrientation;
	
	private File theSTLFile, theGcode;
	private STLObject theSTLObject;

	private STLPreviewMouseControls theMouseControls;
	
	private boolean initialized;
	
	private boolean isDead;

	private ArrayList<STLPreviewCanvas3DListener> theListeners;

	private File theWorkspaceSTL;
	
	private boolean cameraPositionFixed;
	
	private STLPreviewCameraController theCameraController;
	
	public STLPreviewCanvas3D(){
		super(SimpleUniverse.getPreferredConfiguration());
		
		theListeners = new ArrayList<STLPreviewCanvas3DListener>();
		initialized = false;
		isDead = false;
		theCameraController = new STLPreviewCameraController(this);
		theSTLTransforms = new ArrayList<STLTransformGroup>();
		theWorkspaceSTL = null;
		theWorkspace = null;
		currentSTLTransform = null;
		cameraPositionFixed = false;
	}
	
	public STLPreviewCanvas3D(File workspaceSTL){
		super(SimpleUniverse.getPreferredConfiguration());
		
		theListeners = new ArrayList<STLPreviewCanvas3DListener>();
		
		initialized = false;
		isDead = false;

		theSTLTransforms = new ArrayList<STLTransformGroup>();
		theCameraController = new STLPreviewCameraController(this);
		currentSTLTransform = null;
		
		theWorkspaceSTL = workspaceSTL;
	}
	
	public STLPreviewCanvas3D(File stl, File gcode, File workspaceSTL) {
		super(SimpleUniverse.getPreferredConfiguration());
		
		theListeners = new ArrayList<STLPreviewCanvas3DListener>();
		
		initialized = false;
		isDead = false;

		theSTLTransforms = new ArrayList<STLTransformGroup>();

		theCameraController = new STLPreviewCameraController(this);

		this.theSTLFile = stl;
		this.theGcode = gcode;		
		currentSTLTransform = null;
		theWorkspaceSTL = workspaceSTL;

	}
	
	public void addListener(STLPreviewCanvas3DListener spcl){
		if(!theListeners.contains(spcl)) theListeners.add(spcl);
	}
	
	public void inititalize(){
		simpleU = new SimpleUniverse(this);
		mainBranch = new BranchGroup();
		
		modelBranch = new BranchGroup();
		workspaceBranch = new BranchGroup();
		// = simpleU.getLocale();
		
		mainBranch.setCapability(BranchGroup.ALLOW_CHILDREN_EXTEND);
		mainBranch.setCapability(BranchGroup.ALLOW_DETACH);
		mainBranch.setCapability(BranchGroup.ALLOW_CHILDREN_READ);
		mainBranch.setCapability(BranchGroup.ALLOW_CHILDREN_WRITE);
		
		modelBranch.setCapability(BranchGroup.ALLOW_CHILDREN_EXTEND);
		modelBranch.setCapability(BranchGroup.ALLOW_DETACH);
		modelBranch.setCapability(BranchGroup.ALLOW_CHILDREN_READ);
		modelBranch.setCapability(BranchGroup.ALLOW_CHILDREN_WRITE);
		modelBranch.setCapability(BranchGroup.ENABLE_PICK_REPORTING);
		modelBranch.setPickable(true);
		
		workspaceBranch.setCapability(BranchGroup.ALLOW_CHILDREN_EXTEND);
		workspaceBranch.setCapability(BranchGroup.ALLOW_DETACH);
		workspaceBranch.setCapability(BranchGroup.ALLOW_CHILDREN_READ);
		workspaceBranch.setCapability(BranchGroup.ALLOW_CHILDREN_WRITE);
		
		mainBranch.addChild(modelBranch);
		mainBranch.addChild(workspaceBranch);
		
		if(this.theSTLFile!=null){
			addModelToWorkspace(theSTLFile);
		}
		
		for (STLTransformGroup stlTransform : theSTLTransforms) {
			stlTransform.getModel().getAppearance()
					.setColoringAttributes(new ColoringAttributes());
			stlTransform.getModel().getAppearance().getColoringAttributes()
					.setCapability(ColoringAttributes.SHADE_GOURAUD);
			stlTransform.setCapability(TransformGroup.ENABLE_PICK_REPORTING);
			stlTransform.setPickable(true);
		}
		
		if(theWorkspaceSTL!=null){
			try{
				this.setWorkspace(theWorkspaceSTL);
			} catch (IOException e){
				theWorkspace = null;
				e.printStackTrace();
			}
			
		}
				
		theLight = new DirectionalLight();
		theLight.setInfluencingBounds(new BoundingSphere(new Point3d(0, 0, 0),
				900));
		
		theLight.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
		theLight.setCapability(DirectionalLight.ALLOW_COLOR_WRITE);
		mainBranch.addChild(theLight);

		updateIndicatorLightColor();

		// objects in the scene can be viewed.
		simpleU.addBranchGraph(mainBranch);

		//centerOnWorkspace();
		
		// Initialize camera position
		theCameraController.resetCamera();
		
		initialized = true;
	}
	
	public boolean isInitialized(){
		return initialized;
	}
	
	protected STLTransformGroup getCurrentSTLTransform(){
		return currentSTLTransform;
	}
	
	protected STLWorkspaceBranchGroup getTheWorkspaceTransform(){
		return theWorkspace;
	}

	// Camera functions

	public void setCamera(Point3d position, Point3d direction, Vector3d orient) {
		if (cameraPositionFixed && initialized)
			return;

		TransformGroup viewTransform = simpleU.getViewingPlatform()
				.getViewPlatformTransform();

		Transform3D t3d = new Transform3D();
		t3d.lookAt(position, direction,	orient);
		t3d.invert();
		viewTransform.setTransform(t3d);

		cameraPosition = position;
		cameraDirection = direction;
		cameraOrientation = orient;

		Vector3f lightDir = new Vector3f(cameraPosition);
		Vector3f temp = new Vector3f(cameraDirection);
		temp.sub(lightDir);

		theLight.setDirection(temp);

		for (STLPreviewCanvas3DListener spcl : theListeners) {
			spcl.alertCameraMoved(position, direction,orient);
		}
	}
	
	// light transform functions
	
	public void updateIndicatorLightColor() {
		if (modelIsInWorkspace())
			theLight.setColor(new Color3f(.0f, 5.5f, .0f));
		else
			theLight.setColor(new Color3f(5.5f, .0f, .0f));
	}
	
	public boolean modelIsInWorkspace() {
		
		if(theWorkspace==null) return false;
		
		Transform3D curr = currentSTLTransform.getTransform3D();
		
		if(curr!=null){
			return theWorkspace.stlIsContained(theSTLObject.getTransformedSTLObject(curr));
		}
		else{
			System.out.println("Yarp");
			return theWorkspace.stlIsContained(theSTLObject);
		}
		/*
		Point3f min = stlTransform.getCurrentMin();
		Point3f max = stlTransform.getCurrentMax();

		
		 * System.out.println(min); System.out.println(max);
		 */
		/*
		if (min.x < (0 - workspaceDimensions.x / 2))
			return false;
		if (min.y < (0 - workspaceDimensions.y / 2))
			return false;
		if (min.z < (0 - workspaceDimensions.z / 2))
			return false;
		if (max.x > workspaceDimensions.x / 2)
			return false;
		if (max.y > workspaceDimensions.y / 2)
			return false;
		if (max.z > workspaceDimensions.z / 2)
			return false;
			
		return true;
		*/
	}
		

	public void resetModelTransforms() {
		if(currentSTLTransform==null) return;
		Transform3D blank = new Transform3D();
		currentSTLTransform.setTransform(blank);
		
		//centerOnWorkspace();
		theCameraController.autoPan();
	}

	
		
	public void setOutlineVisibility(boolean vis) {
		for(STLTransformGroup st: theSTLTransforms){
			st.setOutlineVisibility(vis);
		}
	}
	
	public void setWorkspace(File newWorkspace) throws IOException{
		
		this.theWorkspaceSTL = newWorkspace;
		
		if(this.theWorkspace!=null){
			this.workspaceBranch.removeChild(theWorkspace);
		}
		
		theWorkspace = STLWorkspaceBranchGroup.getSTLWorkspaceBranchGroup(newWorkspace);
		
		if(theWorkspace!=null){
			this.workspaceBranch.addChild(theWorkspace);
		}
	}
	
	public void removeWorkspace(){
		if(this.theWorkspace!=null){
			this.workspaceBranch.removeChild(theWorkspace);
		}
		theWorkspace = null;
	}
	
	// Getters
	/*
	public STLObject getSTLObject() {
		return this.theSTLObject;
	}

	public File getSTLFile() {
		return theSTLFile;
	}

	public File getGCodeFile() {
		return theGcode;
	}

	/*
	public Point3f getWorkspaceDimensions() {
		return workspaceDimensions;
	}
	*/

	

	
	public void setMouseControls(STLPreviewMouseControls theMouseControls) {
		this.theMouseControls = theMouseControls;
	}
	

	public STLPreviewMouseControls getMouseControls() {
		return theMouseControls;
	}

	
	public void setMouseControlMode(STLPreviewMouseControls.MouseControlMode mc){
		if(theMouseControls!=null){
			theMouseControls.setMouseControlMode(mc); //TODO this ain't workin'
			if(mc==STLPreviewMouseControls.MouseControlMode.MODEL_TRANSLATE_XY){
				theCameraController.setCameraFocusMode(STLPreviewCameraController.CameraMode.AERIAL);
				theCameraController.resetCamera();
			} else theCameraController.setCameraFocusMode(STLPreviewCameraController.CameraMode.WORKSPACE_BASE); //TODO
			
		}
	}
	
	public void killPreview() {
		this.getView().removeAllCanvas3Ds();
		this.simpleU.removeAllLocales();
		isDead = true;
		//theLocale = null;
		mainBranch = null;
		this.theLight = null;
		simpleU.cleanup();
		simpleU = null;
	}
	
	public boolean isDead(){
		return isDead;
	}
	
	public Point3d getCameraPosition(){
		return cameraPosition;
	}
	
	public Point3d getCameraDirection(){
		return cameraDirection;
	}
	
	public Vector3d getCameraOrientation(){
		return cameraOrientation;
	}
	
	
	public void addModelToWorkspace(File stlFile){
		STLTransformGroup newTransform = null;
		
		try{
			newTransform = assembleSTLTransform(stlFile);
			
		} catch (IOException e){
			newTransform = null;
			e.printStackTrace();
		}
		
		if(newTransform!=null){
			BranchGroup newBranch = new BranchGroup();
			
			newTransform.setCapability(TransformGroup.ENABLE_PICK_REPORTING);
			newTransform.setPickable(true);
			
			newBranch.setCapability(BranchGroup.ENABLE_PICK_REPORTING);
			newBranch.setPickable(true);
			newBranch.setCapability(BranchGroup.ALLOW_DETACH);
			newBranch.addChild(newTransform);
			theSTLTransforms.add(newTransform);
			modelBranch.addChild(newBranch);
			currentSTLTransform = newTransform;
		}
	}
	
	
	private STLTransformGroup assembleSTLTransform(File f) throws IOException {
		// BranchGroup objRoot = new BranchGroup();

		STLTransformGroup stlTransform;

		theSTLObject = STLLoader.loadFile(f);

		stlTransform = STLLoader.createSTLTransform(theSTLObject, mainBranch);

		return stlTransform;
	}
	

	protected BranchGroup getMainBranch() {
		return this.modelBranch;
	}
	

	public void setCurrentPick(PickResult result) {
		if (result == null) {
			currentSTLTransform = null;
			return;
		}
		try {
			currentSTLTransform = (STLTransformGroup) result.getNode(PickResult.TRANSFORM_GROUP);
		} catch (ClassCastException e) {
			currentSTLTransform = null;
		}
	}

	
	public STLPreviewCameraController getTheCameraController(){
		return this.theCameraController;
	}
	
	public STLTransformGroup getcurrentSTLTransform(){
		return this.currentSTLTransform;
	}

	@Override
	public void alertSTLTransformMoved(STLTransformGroup gr) {
		this.theCameraController.autoPan();
		updateIndicatorLightColor();		
	}

	
	public STLPreviewCameraData getCameraData() {
		return new STLPreviewCameraData(cameraPosition,cameraDirection,cameraOrientation);
	}

	//TODO these all require new merging functionality still to be written
	public File getGCodeFile() {
		// TODO Auto-generated method stub
		return null;
	}

	public File getSTLFile() {
		// TODO Auto-generated method stub
		return null;
	}

	
	public STLObject getSTLObject() {
		// TODO Auto-generated method stub
		return null;
	}
}