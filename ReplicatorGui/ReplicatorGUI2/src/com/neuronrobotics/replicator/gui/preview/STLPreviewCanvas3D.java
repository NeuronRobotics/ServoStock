package com.neuronrobotics.replicator.gui.preview;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Map;

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
import com.neuronrobotics.replicator.gui.stl.STLObjectIntersectionUtilities;
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
	private ArrayList<ArrayList<Boolean>> collisionTable;
		
	// transform group that displays the area in which the printer can reliably print
	private STLWorkspaceBranchGroup theWorkspace;

	private Point3d cameraPosition, cameraDirection;
	private Vector3d cameraOrientation;
	
	//private File theSTLFile, theGcode;
	private STLObject theSTLObject;

	private STLPreviewMouseControls theMouseControls;
	
	private boolean initialized;
	
	private boolean isDead;

	private ArrayList<STLPreviewCanvas3DListener> theListeners;
	private ArrayList<File> toBeAdded;
	
	private File theWorkspaceSTL;
	
	private boolean cameraPositionFixed;
	
	private STLPreviewCameraController theCameraController;
	
	private enum PlacementStatus{
		UNKOWN {
			@Override
			Color3f getColor() {
				return new Color3f(.0f, 5.5f, .0f);
			}
		},NOT_IN_WORKSPACE {
			@Override
			Color3f getColor() {
				return new Color3f(5.5f, .0f, .0f);
			}
		},MODEL_COLLISION {
			@Override
			Color3f getColor() {
				return new Color3f(5.5f, 5.5f, 5.5f);
			}
		}, VALID_PLACEMENT {
			@Override
			Color3f getColor() {
				return new Color3f(.0f, 5.5f, .0f);
			}
		};
		
		abstract Color3f getColor();
	}
	
	private ArrayList<PlacementStatus> placementStatuses;
	
	public STLPreviewCanvas3D(){
		super(SimpleUniverse.getPreferredConfiguration());
		
		theListeners = new ArrayList<STLPreviewCanvas3DListener>();
		initialized = false;
		isDead = false;
		theCameraController = new STLPreviewCameraController(this);
		theSTLTransforms = new ArrayList<STLTransformGroup>();
		collisionTable = new ArrayList<ArrayList<Boolean>>();
		placementStatuses = new ArrayList<PlacementStatus>();
		theWorkspaceSTL = null;
		theWorkspace = null;
		currentSTLTransform = null;
		cameraPositionFixed = false;
		toBeAdded = new ArrayList<File>();
		intializeUniverse();
	}
	
	public STLPreviewCanvas3D(File workspaceSTL){
		this();
		theWorkspaceSTL = workspaceSTL;
	}
	
	public STLPreviewCanvas3D(File stl, File gcode, File workspaceSTL) {
		this(workspaceSTL);		
		toBeAdded.add(stl);
	}
	
	public void addListener(STLPreviewCanvas3DListener spcl){
		if(!theListeners.contains(spcl)) theListeners.add(spcl);
	}
	
	private void intializeUniverse(){
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
	}
	
	public void loadFromQueue(){
						
		for(File curr:toBeAdded){
			addModelToWorkspace(curr);
		}
		toBeAdded = new ArrayList<File>();
		
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
		
		if(theWorkspace!=null)
		for (STLTransformGroup stlTransform : theSTLTransforms) {
			stlTransform.centerOnWorkspace(theWorkspace);
		}
	
	
	//	mainBranch.addChild(theLight);

		
		
		updateIndicatorLights();

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

		for (STLPreviewCanvas3DListener spcl : theListeners) {
			spcl.alertCameraMoved(position, direction,orient);
		}
	}
	
	// light transform functions
	
	public void updateIndicatorLights() {
		
		int tot = this.theSTLTransforms.size();
		for(int i = 0;i<tot;i++){
			theSTLTransforms.get(i).setIndicatorLightColor(placementStatuses.get(i).getColor());
		}
		
		
		/*
		if(this.theWorkspace==null){
			for (STLTransformGroup stg:theSTLTransforms){
				stg.setIndicatorLightColor(new Color3f(5.5f,.0f,.0f));
			}
		}
				
		else {
			int ct = 0;
			for (STLTransformGroup stg:theSTLTransforms){
				Boolean curr = stg.modelIsInWorkspace(theWorkspace);
				System.out.println("Curr "+curr);
				if(curr){
					stg.setIndicatorLightColor(new Color3f(.0f, 5.5f, .0f));
				}
				else {
					stg.setIndicatorLightColor(new Color3f(5.5f, .0f, .0f));
				}
			}	
		}
		*/
		
	}
				
	public boolean modelIsInWorkspace(STLTransformGroup currTran) {
		
		if(theWorkspace==null) return false;
		
		Transform3D curr = new Transform3D();
		currTran.getTransform(curr);
				
		return theWorkspace.stlIsContained(currTran.getSTLObject().getTransformedSTLObject(curr));
	
	}

	public boolean modelsIntersect(STLTransformGroup m1, STLTransformGroup m2){
				
		Transform3D curr1 = new Transform3D(), curr2 = new Transform3D();
		m1.getTransform(curr1);
		m2.getTransform(curr2);
		
		
		
		STLObject stl1 = m1.getSTLObject().getTransformedSTLObject(curr1);
		STLObject stl2 = m2.getSTLObject().getTransformedSTLObject(curr2);
		
		return (STLObjectIntersectionUtilities.objectsIntersect(stl1, stl2));
		
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
		
		if(theWorkspace!=null)	this.workspaceBranch.addChild(theWorkspace);		
		
		updatePlacementStatus(false);
		updateIndicatorLights();
	} 
	
	
	public void removeWorkspace(){
		if(this.theWorkspace!=null){
			this.workspaceBranch.removeChild(theWorkspace);
		}
		theWorkspace = null;
		updatePlacementStatus(false);
	}
	
	// Getters
	
	public void setMouseControls(STLPreviewMouseControls theMouseControls) {
		this.theMouseControls = theMouseControls;
	}	

	public STLPreviewMouseControls getMouseControls() {
		return theMouseControls;
	}
	
	public void killPreview() {
		this.getView().removeAllCanvas3Ds();
		this.simpleU.removeAllLocales();
		isDead = true;
		//theLocale = null;
		mainBranch = null;
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
			currentSTLTransform.addListener(this);
			//Updating collision table
			ArrayList<Boolean> newCollisionList = new ArrayList<Boolean>();
			int ct=-1;
			boolean collisionFound = false;
			for(STLTransformGroup stg:theSTLTransforms){
				ct++;
				if(stg==newTransform) {
					newCollisionList.add(false);
					break;
				}
				if(this.modelsIntersect(stg, newTransform)){
					collisionFound = true;
					if (placementStatuses.get(ct) != PlacementStatus.NOT_IN_WORKSPACE){
						this.placementStatuses.set(ct,PlacementStatus.MODEL_COLLISION);
					}
					collisionTable.get(ct).add(true);
					newCollisionList.add(true);
				} else {
					collisionTable.get(ct).add(false);
					newCollisionList.add(false);
				}
			}
			boolean inWorkspace = true;
			if (theWorkspace!=null) inWorkspace = newTransform.modelIsInWorkspace(theWorkspace);
			
			if(theWorkspace==null) placementStatuses.add(PlacementStatus.UNKOWN);
			else if(!inWorkspace) placementStatuses.add(PlacementStatus.NOT_IN_WORKSPACE);
			else if(collisionFound) placementStatuses.add(PlacementStatus.MODEL_COLLISION);
			else placementStatuses.add(PlacementStatus.VALID_PLACEMENT);
			
			this.collisionTable.add(newCollisionList);
			System.out.println(collisionTable);
			System.out.println(placementStatuses);
			updateIndicatorLights();
			//alertSTLTransformMoved(currentSTLTransform);
			if(theWorkspace!=null) currentSTLTransform.centerOnWorkspace(theWorkspace);
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
	
	@Override
	public void alertSTLTransformMoved(STLTransformGroup gr) {
		if(this.cameraPosition!=null) this.theCameraController.autoPan();
		int index = theSTLTransforms.indexOf(gr);
		for(int i =0;i<theSTLTransforms.size();i++){
			
			STLTransformGroup curr = theSTLTransforms.get(i);
			if(curr==gr){
				System.out.println("GRRR");
				continue;
			}
			boolean collision = this.modelsIntersect(curr, gr);
			System.out.println(collision);
			collisionTable.get(index).set(i, collision);
			collisionTable.get(i).set(index, collision);
		}
		updatePlacementStatus(false);
		updateIndicatorLights();	
		
	}	
	
	private void updateCollisionTable(){
		//TODO
	}
	
	private void updatePlacementStatus(boolean updateCollisionTableFirst) {
		if(updateCollisionTableFirst){
			updateCollisionTable();
		} 
		
		for(int i =0;i<theSTLTransforms.size();i++){
			if(theWorkspace!=null&&!theSTLTransforms.get(i).modelIsInWorkspace(theWorkspace)){
				placementStatuses.set(i,PlacementStatus.NOT_IN_WORKSPACE);
				continue;
			}
			boolean collision = collisionTable.get(i).contains(true);
			if(collision){
				placementStatuses.set(i,PlacementStatus.MODEL_COLLISION);
			} else if(theWorkspace==null){
				placementStatuses.set(i,PlacementStatus.UNKOWN);
			} else {
				placementStatuses.set(i, PlacementStatus.VALID_PLACEMENT);
			}
			
		}
		System.out.println("Placement Statuses: "+placementStatuses);
		System.out.println("Collision Table\n");
		for(ArrayList<Boolean> ab:collisionTable) System.out.println(ab);
		System.out.println("End collision table");
	}

	public STLPreviewCameraData getCameraData() {
		return new STLPreviewCameraData(cameraPosition,cameraDirection,cameraOrientation);
	}
	
	public STLObject getMergedSTLObject() {
		ArrayList<STLObject> theObjects = new ArrayList<STLObject>();
		for(STLTransformGroup stg: this.theSTLTransforms){
			Transform3D currTran = new Transform3D();
			stg.getTransform(currTran);
			STLObject curr = stg.getSTLObject().getTransformedSTLObject(currTran);
			theObjects.add(curr);
		}
		return STLObject.getMergedSTLObject("MergedSTL", theObjects);
	}

	public void alertMouseControlModeChanged(STLPreviewMouseControls stlPreviewMouseControls) {
		if(stlPreviewMouseControls.getCurrentMode()==STLPreviewMouseControls.MouseControlMode.MODEL_TRANSLATE_XZ){
			this.theCameraController.setCameraFocusMode(STLPreviewCameraController.CameraMode.AERIAL);
		}
	}
}