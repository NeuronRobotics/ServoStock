package com.neuronrobotics.replicator.gui.preview.view;

import java.awt.Color;
import java.awt.Component;
import java.util.ArrayList;
import java.util.Iterator;

import javax.media.j3d.AmbientLight;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.Node;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.preview.j3d.STLShape3DFactory;
import com.neuronrobotics.replicator.gui.preview.j3d.STLTransformGroup;
import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModel;
import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModelListener;
import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModel.PlacementStatus;
import com.neuronrobotics.replicator.gui.preview.view.STLWorkspaceView;
import com.neuronrobotics.replicator.gui.stl.DefaultGeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.GeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;
import com.sun.j3d.utils.picking.PickCanvas;
import com.sun.j3d.utils.picking.PickResult;
import com.sun.j3d.utils.universe.SimpleUniverse;

public class TestCanvas3D extends Canvas3D implements STLWorkspaceView, STLWorkspaceModelListener{

	/**
	 * 
	 */
	private static final long serialVersionUID = 7892972990572720591L;

	private PickCanvas thePickCanvas;
		
	private AmbientLight theAmbientLight;
	private DirectionalLight directionalLight1,directionalLight2;

	private SimpleUniverse simpleU;
	private BranchGroup mainBranch;
	private BranchGroup modelBranch;
	private BranchGroup workspaceBranch;

	private Point3d cameraPosition;
	private Point3d cameraDirection;

	private final Vector3d cameraOrientation = new Vector3d(0,1,0);

	private STLWorkspaceModel theWorkspaceModel;
		
	private ArrayList<STLObject> baseSTLs;
	private  ArrayList<BranchGroup> theBranchGroups;
	private ArrayList<STLTransformGroup> transformGroups;
	private STLTransformGroup currentPick;
	
	private ArrayList<STLWorkspaceViewListener> theListeners;

		
	
	public TestCanvas3D(STLWorkspaceModel stlwm) {
		super(SimpleUniverse.getPreferredConfiguration());
				
		baseSTLs = new ArrayList<STLObject>();
		transformGroups = new ArrayList<STLTransformGroup>();
		theBranchGroups = new ArrayList<BranchGroup>();
		theListeners = new ArrayList<STLWorkspaceViewListener>();
		currentPick = null;		
				
		theWorkspaceModel = stlwm;
		theWorkspaceModel.addSTLWorkspaceModelListener(this);
		
		initializeUniverse();	
		initializeView();		
		
	}

	private void initializeView() {
		this.workspaceBranch.removeAllChildren();
		this.modelBranch.removeAllChildren();
		
		baseSTLs = new ArrayList<STLObject>();
		transformGroups = new ArrayList<STLTransformGroup>();
		theBranchGroups = new ArrayList<BranchGroup>();
		currentPick = null;
		
		if(theWorkspaceModel.getWorkspaceObject()!=null){
			BranchGroup wsBG = new BranchGroup();
			wsBG.addChild(STLShape3DFactory.getWorkspaceShape3D(theWorkspaceModel.getWorkspaceObject()));
			workspaceBranch.addChild(wsBG);
		}
		
		Iterator<STLObject> theSTLObjects = theWorkspaceModel.getBaseSTLObjectIterator();
		Iterator<double[]> theTransforms = theWorkspaceModel.getTransformMatrixIterator();
				
		while(theSTLObjects.hasNext()){
			addSTLToModel(theSTLObjects.next(), new DefaultGeneralTransform3D(theTransforms.next()));			
		}
		
		updateIndicatorLights();
				
	}
	
	private void updateIndicatorLights() {
		for(int i=0;i<baseSTLs.size();i++){
			STLObject currSTL = baseSTLs.get(i);
			STLTransformGroup currSTG = transformGroups.get(i);
			
			currSTG.setDiffuseLightColor(getIndicatorColor(theWorkspaceModel.getPlacementStatus(currSTL)));
			currSTG.setHighlighted((currSTG==currentPick));
			
		}
	}
	
	private Color3f getIndicatorColor(PlacementStatus ps){
		
		Color3f color = null;
		
		switch (ps) {
			case UNKOWN:
				color = new Color3f(Color.gray);
				break;
			case VALID_PLACEMENT:
				color = new Color3f(Color.green);
				break;
			case MODEL_COLLISION:
				color = new Color3f(Color.red);
				break;
			case NOT_IN_WORKSPACE:
				color = new Color3f(Color.yellow);
				break;
			default:
				color = new Color3f(Color.white);
		}
		
		return color;
	}

	private void addSTLToModel(STLObject newSTL, GeneralTransform3D transform) {
		
		System.out.println("Adding model: " +newSTL.getName());
		System.out.println("Min/Max "+newSTL.getMin()+"/"+newSTL.getMax());
				
		BranchGroup newBG = new BranchGroup();
		newBG.setCapability(BranchGroup.ALLOW_DETACH);
		STLTransformGroup newTG = STLShape3DFactory.createSTLTransform(newSTL);
		newTG.setPickable(true);
		newTG.setCapability(Node.ALLOW_PICKABLE_READ);
		newTG.setCapability(TransformGroup.ENABLE_PICK_REPORTING);
		newBG.addChild(newTG);
		
		
		baseSTLs.add(newSTL);
		transformGroups.add(newTG);
		theBranchGroups.add(newBG);
		currentPick = null;
		
		this.modelBranch.addChild(newBG);
	}

	private void initializeUniverse() {
		simpleU = new SimpleUniverse(this);
		mainBranch = new BranchGroup();

		modelBranch = new BranchGroup();
		workspaceBranch = new BranchGroup();
		
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
		
		//ambient light
		theAmbientLight = new AmbientLight(new Color3f(Color.white));
		mainBranch.addChild(theAmbientLight);
		theAmbientLight.addScope(mainBranch);
		theAmbientLight.setInfluencingBounds(new BoundingSphere(new Point3d(0,0,0), 900));
		theAmbientLight.setCapability(AmbientLight.ALLOW_COLOR_WRITE);
		theAmbientLight.setCapability(AmbientLight.ALLOW_BOUNDS_WRITE);
		
		// directional light 1
		directionalLight1 = new DirectionalLight();// new AmbientLight();
		directionalLight1.setColor(new Color3f(Color.white));
		directionalLight1.setInfluencingBounds(new BoundingSphere(new Point3d(
				0, 0, 0), 900));

		directionalLight1.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
		directionalLight1.setCapability(DirectionalLight.ALLOW_COLOR_WRITE);
		directionalLight1.setCapability(DirectionalLight.ALLOW_BOUNDS_WRITE);
		mainBranch.addChild(directionalLight1);
		// directionalLight1.removeAllScopes();
		// directionalLight1.addScope(this);
		directionalLight1.setDirection(0, -1, 0);

		// directional light 2
		directionalLight2 = new DirectionalLight();// new AmbientLight();
		directionalLight2.setColor(new Color3f(Color.white.darker()));
		directionalLight2.setInfluencingBounds(new BoundingSphere(new Point3d(
				0, 0, 0), 900));

		directionalLight2.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
		directionalLight2.setCapability(DirectionalLight.ALLOW_COLOR_WRITE);
		directionalLight2.setCapability(DirectionalLight.ALLOW_BOUNDS_WRITE);
		directionalLight2.setCapability(DirectionalLight.ALLOW_STATE_WRITE);
		mainBranch.addChild(directionalLight2);
		// directionalLight2.removeAllScopes();
		// directionalLight2.addScope(this);
		directionalLight2.setDirection(0, -1, 0);
		
		thePickCanvas = new PickCanvas(this, modelBranch);
		thePickCanvas.setMode(PickCanvas.BOUNDS);
		
		this.setCamera(new double[]{120,120,120},new double[]{0,0,0});
				
		
		//mainBranch.compile();
		
		simpleU.addBranchGraph(mainBranch);
		simpleU.getViewer().getView().setBackClipDistance(900);
		
		
		//this.theCameraController.resetCamera();

	}

	// Camera functions
	private void setCamera(Point3d position, Point3d direction) {
		TransformGroup viewTransform = simpleU.getViewingPlatform()
				.getViewPlatformTransform();

		Transform3D t3d = new Transform3D();
		t3d.lookAt(position, direction, this.cameraOrientation);
		t3d.invert();
		viewTransform.setTransform(t3d);

		cameraPosition = position;
		cameraDirection = direction;

		Vector3f lightDir = new Vector3f(cameraPosition);
		Vector3f temp = new Vector3f(cameraDirection);
		temp.sub(lightDir);
		directionalLight1.setDirection(temp);
		Vector3f temp2 = new Vector3f(-temp.x, temp.y, -temp.z);
		temp2.normalize();
		if(!(temp2.epsilonEquals(temp, 0.001f)||(Math.abs(temp2.x)+Math.abs(temp2.z)<0.3))){
			directionalLight2.setDirection(temp2);
		} 
		
	}
	
	@Override
	public void setCamera(double[] position, double[] lookAt) {
		Point3d pos = new Point3d(position);
		Point3d dir = new Point3d(lookAt);
		setCamera(pos,dir);
		for(STLWorkspaceViewListener l:theListeners){
			l.alertCameraMoved(position, lookAt, new double[]{0,1,0});
		}
	}	
		
	@Override
	public void setWorkspaceModel(STLWorkspaceModel stlwm) {
		if(theWorkspaceModel!=null) theWorkspaceModel.removeListener(this);
		theWorkspaceModel = stlwm;
		theWorkspaceModel.addSTLWorkspaceModelListener(this);
		initializeView();
	}

	@Override
	public void getCameraData(double[] position, double[] lookAt) {
		this.cameraDirection.get(lookAt);
		this.cameraPosition.get(position);
	}

	@Override
	public STLObject getPick() {
		if(currentPick==null) return null;
		int index = this.transformGroups.indexOf(currentPick);
		if(index<0) return null;
		STLObject baseSTL = baseSTLs.get(index);
		return baseSTL;
	}
	
	public void setPickLocation(double x, double y){
		this.thePickCanvas.setShapeLocation((int)x, (int)y);
		if(!this.mainBranch.isLive()){
			currentPick = null;
			updateIndicatorLights();
			return;
		}
		
		PickResult pickResult = this.thePickCanvas.pickClosest();
		if(pickResult==null){
			currentPick = null;
			updateIndicatorLights();
			return;
		}
		
		STLTransformGroup node = (STLTransformGroup)pickResult.getNode(PickResult.TRANSFORM_GROUP);
		currentPick = node;
		updateIndicatorLights();
	}

	@Override
	public Component getComponent() {
		return this;
	}

	@Override
	public void alertSTLObjectAdded(STLObject newSTL,
			GeneralTransform3D transform) {
		addSTLToModel(newSTL,transform);		
	}

	@Override
	public void alertSTLObjectMoved(STLObject stl, GeneralTransform3D transform) {
		double[] dub = new double[16];
		transform.get(dub);
		int index = this.baseSTLs.indexOf(stl);
		this.transformGroups.get(index).setTransform(new Transform3D(dub));
	}

	@Override
	public void alertSTLObjectRemoved(STLObject stl) {
		int index = this.baseSTLs.indexOf(stl);
		TransformGroup theTG = this.transformGroups.get(index);
		BranchGroup theBG = this.theBranchGroups.get(index);
		
		System.out.println("This actually got called");
		this.modelBranch.removeChild(theBG);
		this.baseSTLs.remove(stl);
		this.transformGroups.remove(theTG);
		this.theBranchGroups.remove(theBG);
		if(currentPick==theTG) currentPick=null;
	}

	@Override
	public void alertSTLWorkspaceObjectChanged(STLWorkspaceObject newWorkspace) {
		this.workspaceBranch.removeAllChildren();
		this.workspaceBranch.addChild(STLShape3DFactory.getWorkspaceShape3D(newWorkspace));
	}

	@Override
	public void alertSTLPlacementStatusChanged(STLObject stl,
			PlacementStatus newStatus) {
		this.transformGroups.get(this.baseSTLs.indexOf(stl)).setDiffuseLightColor(this.getIndicatorColor(newStatus));
				
	}

	@Override
	public void addViewListener(STLWorkspaceViewListener newListener) {
		this.theListeners.add(newListener);		
	}	
	
}