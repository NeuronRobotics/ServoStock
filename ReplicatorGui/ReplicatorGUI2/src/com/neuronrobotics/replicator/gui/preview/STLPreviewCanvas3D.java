package com.neuronrobotics.replicator.gui.preview;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import javax.media.j3d.AmbientLight;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.STLLoader;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLObjectCalculationUtilities;
import com.neuronrobotics.replicator.gui.stl.STLTransformGroup;
import com.neuronrobotics.replicator.gui.stl.STLTransformGroupListener;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceBranchGroup;
import com.sun.j3d.utils.picking.PickResult;
import com.sun.j3d.utils.universe.SimpleUniverse;

public class STLPreviewCanvas3D extends Canvas3D implements
		STLTransformGroupListener{

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

	// transform group that displays the area in which the printer can reliably
	// print
	private STLWorkspaceBranchGroup theWorkspace;

	private Point3d cameraPosition, cameraDirection;
	private Vector3d cameraOrientation;

	// private File theSTLFile, theGcode;
	//private STLObject theSTLObject;

	private STLPreviewMouseControls theMouseControls;

	private boolean initialized;

	private boolean isDead;

	private ArrayList<STLPreviewCanvas3DListener> theListeners;
	private ArrayList<File> toBeAdded;

	private File theWorkspaceSTL;

	private boolean cameraPositionFixed;

	private STLPreviewCameraController theCameraController;
	
	private AmbientLight theAmbientLight;
	private DirectionalLight directionalLight1,directionalLight2;

	private enum PlacementStatus {
		UNKOWN {
			@Override
			Color3f getBaseColor() {
				return new Color3f(.0f, .0f, .0f);
			}

		},
		NOT_IN_WORKSPACE {
			@Override
			Color3f getBaseColor() {
				return new Color3f(.4f, .0f, .0f);
			}

			
		},
		MODEL_COLLISION {
			@Override
			Color3f getBaseColor() {
				return new Color3f(.0f, .0f, .4f);
			}

		},
		VALID_PLACEMENT {
			@Override
			Color3f getBaseColor() {
				return new Color3f(0,0.4f,0);
			}

		};

		abstract Color3f getBaseColor();

	}

	private ArrayList<PlacementStatus> placementStatuses;

	public STLPreviewCanvas3D() {
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

	public STLPreviewCanvas3D(File workspaceSTL) {
		this();
		theWorkspaceSTL = workspaceSTL;
	}

	public STLPreviewCanvas3D(File stl, File workspaceSTL) {
		this(workspaceSTL);
		toBeAdded.add(stl);
	}

	public void addListener(STLPreviewCanvas3DListener spcl) {
		if (!theListeners.contains(spcl))
			theListeners.add(spcl);
	}

	private void intializeUniverse() {
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
		
		this.theCameraController.resetCamera();

	}

	public void loadFromQueue() {

		for (File curr : toBeAdded) {
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

		if (theWorkspaceSTL != null) {
			try {
				this.setWorkspace(theWorkspaceSTL);
			} catch (IOException e) {
				theWorkspace = null;
				e.printStackTrace();
			}

		}

		if (theWorkspace != null)
			for (STLTransformGroup stlTransform : theSTLTransforms) {
				stlTransform.centerOnWorkspace(theWorkspace
						.getWorkspaceSTLObject());
			}

		// mainBranch.addChild(theLight);

		updateIndicatorLights();

		// objects in the scene can be viewed.
		simpleU.addBranchGraph(mainBranch);

		// centerOnWorkspace();

		// Initialize camera position
		theCameraController.resetCamera();

		initialized = true;
	}

	public boolean isInitialized() {
		return initialized;
	}

	protected STLTransformGroup getCurrentSTLTransform() {
		return currentSTLTransform;
	}

	protected STLWorkspaceBranchGroup getTheWorkspaceTransform() {
		return theWorkspace;
	}
	
	// Camera functions

	public void setCamera(Point3d position, Point3d direction, Vector3d orient) {
		if (cameraPositionFixed && initialized)
			return;

		TransformGroup viewTransform = simpleU.getViewingPlatform()
				.getViewPlatformTransform();

		Transform3D t3d = new Transform3D();
		t3d.lookAt(position, direction, orient);
		t3d.invert();
		viewTransform.setTransform(t3d);

		cameraPosition = position;
		cameraDirection = direction;
		cameraOrientation = orient;

		Vector3f lightDir = new Vector3f(cameraPosition);
		Vector3f temp = new Vector3f(cameraDirection);
		temp.sub(lightDir);
		directionalLight1.setDirection(temp);
		Vector3f temp2 = new Vector3f(-temp.x, temp.y, -temp.z);
		temp2.normalize();
		if(!(temp2.epsilonEquals(temp, 0.001f)||(Math.abs(temp2.x)+Math.abs(temp2.z)<0.3))){
			directionalLight2.setDirection(temp2);
		} 
		

		for (STLPreviewCanvas3DListener spcl : theListeners) {
			spcl.alertCameraMoved(position, direction, orient);
		}
		updateIndicatorLights();
	}
	
	// light transform functions
	
	public void updateIndicatorLights() {

		int tot = this.theSTLTransforms.size();
		for (int i = 0; i < tot; i++) {
			STLTransformGroup stg = theSTLTransforms.get(i);

			Color3f col = placementStatuses.get(i).getBaseColor();
			stg.setDiffuseLightColor(col);
			
			stg.setHighlighted(stg == currentSTLTransform);
			
			if(cameraDirection!=null){
				Vector3d camDir = new Vector3d(0,0,0);
				camDir.add(this.cameraDirection);
				camDir.sub(this.cameraPosition);
			}
		}

	}

	public boolean modelIsInWorkspace(STLTransformGroup currTran) {

		if (theWorkspace == null)
			return false;

		return theWorkspace.stlIsInside(currTran.getTransformedSTLObject());

	}

	public boolean modelsIntersect(STLTransformGroup m1, STLTransformGroup m2) {

		STLObject stl1 = m1.getTransformedSTLObject();
		STLObject stl2 = m2.getTransformedSTLObject();

		return (STLObjectCalculationUtilities.objectsIntersect(stl1, stl2));
	}

	public void resetModelTransforms() {
		if (currentSTLTransform == null)
			return;
		Transform3D blank = new Transform3D();
		currentSTLTransform.setTransform(blank);

		// centerOnWorkspace();
		theCameraController.autoPan();
	}

	public void setOutlineVisibility(boolean vis) {
		for (STLTransformGroup st : theSTLTransforms) {
			st.setOutlineVisibility(vis);
		}
	}

	public void setWorkspace(File newWorkspace) throws IOException {

		this.theWorkspaceSTL = newWorkspace;

		if (this.theWorkspace != null) {
			this.workspaceBranch.removeChild(theWorkspace);
		}

		theWorkspace = STLWorkspaceBranchGroup
				.getSTLWorkspaceBranchGroup(newWorkspace);

		if (theWorkspace != null)
			this.workspaceBranch.addChild(theWorkspace);

		updatePlacementStatus(false);
		updateIndicatorLights();
	}

	public void removeWorkspace() {
		if (this.theWorkspace != null) {
			this.workspaceBranch.removeChild(theWorkspace);
		}
		theWorkspace = null;
		updatePlacementStatus(false);
	}

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
		// theLocale = null;
		mainBranch = null;
		simpleU.cleanup();
		simpleU = null;
	}

	public boolean isDead() {
		return isDead;
	}

	public Point3d getCameraPosition() {
		return cameraPosition;
	}

	public Point3d getCameraDirection() {
		return cameraDirection;
	}

	public Vector3d getCameraOrientation() {
		return cameraOrientation;
	}

	public void addModelToWorkspace(File stlFile) {
		STLTransformGroup newTransform = null;

		try {
			newTransform = assembleSTLTransform(stlFile);

		} catch (IOException e) {
			newTransform = null;
			e.printStackTrace();
		}

		addModelToWorkspace(newTransform);

	}

	private void addModelToWorkspace(STLTransformGroup newTransform) {
		if (newTransform != null) {
			
			BranchGroup newBranch = new BranchGroup();
			
			newTransform.setCapability(TransformGroup.ENABLE_PICK_REPORTING);
			newTransform.setPickable(true);
			
			newTransform.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
			newTransform.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);

			newBranch.setCapability(BranchGroup.ENABLE_PICK_REPORTING);
			newBranch.setPickable(true);
			newBranch.setCapability(BranchGroup.ALLOW_DETACH);
			newBranch.addChild(newTransform);
			theSTLTransforms.add(newTransform);
			modelBranch.addChild(newBranch);
			currentSTLTransform = newTransform;
			currentSTLTransform.addListener(this);

			// Updating collision table
			ArrayList<Boolean> newCollisionList = new ArrayList<Boolean>();
			int ct = -1;
			boolean collisionFound = false;
			for (STLTransformGroup stg : theSTLTransforms) {
				ct++;
				if (stg == newTransform) {
					newCollisionList.add(false);
					break;
				}
				if (this.modelsIntersect(stg, newTransform)) {
					collisionFound = true;
					if (placementStatuses.get(ct) != PlacementStatus.NOT_IN_WORKSPACE) {
						this.placementStatuses.set(ct,
								PlacementStatus.MODEL_COLLISION);
					}
					collisionTable.get(ct).add(true);
					newCollisionList.add(true);
				} else {
					collisionTable.get(ct).add(false);
					newCollisionList.add(false);
				}
			}
			boolean inWorkspace = true;
			if (theWorkspace != null)
				theWorkspace
						.stlIsInside(newTransform.getTransformedSTLObject());

			if (theWorkspace == null)
				placementStatuses.add(PlacementStatus.UNKOWN);
			else if (!inWorkspace)
				placementStatuses.add(PlacementStatus.NOT_IN_WORKSPACE);
			else if (collisionFound)
				placementStatuses.add(PlacementStatus.MODEL_COLLISION);
			else
				placementStatuses.add(PlacementStatus.VALID_PLACEMENT);

			this.collisionTable.add(newCollisionList);
			System.out.println(collisionTable);
			System.out.println(placementStatuses);
			updateIndicatorLights();
			// alertSTLTransformMoved(currentSTLTransform);
			if (theWorkspace != null)
				currentSTLTransform.centerOnWorkspace(theWorkspace
						.getWorkspaceSTLObject());
		}
	}

	public void removeCurrentModel() {

		if (currentSTLTransform == null) {
			System.out.println("Nothing to remove");
			return;
		}

		int index = theSTLTransforms.indexOf(currentSTLTransform);
		BranchGroup currBranch = (BranchGroup) currentSTLTransform.getParent();
		this.modelBranch.removeChild(currBranch);
		theSTLTransforms.remove(index);
		for (ArrayList<Boolean> al : this.collisionTable) {
			al.remove(index);
		}
		collisionTable.remove(index);
		this.placementStatuses.remove(index);
		currentSTLTransform = null;
		updatePlacementStatus(false);
		updateIndicatorLights();

	}

	private STLTransformGroup assembleSTLTransform(File f) throws IOException {
		// BranchGroup objRoot = new BranchGroup();

		STLTransformGroup stlTransform;

		STLObject theSTLObject = STLLoader.loadFile(f);

		stlTransform = STLLoader.createSTLTransform(theSTLObject);

		return stlTransform;
	}

	protected BranchGroup getMainBranch() {
		return this.modelBranch;
	}

	public void setCurrentPick(PickResult result) {
		if (result == null) {
			currentSTLTransform = null;
		} else {
			try {
				currentSTLTransform = (STLTransformGroup) result
						.getNode(PickResult.TRANSFORM_GROUP);
			} catch (ClassCastException e) {
				currentSTLTransform = null;
			}
		}
		updateIndicatorLights();

	}

	public STLPreviewCameraController getTheCameraController() {
		return this.theCameraController;
	}

	@Override
	public void alertSTLTransformMoved(STLTransformGroup gr) {
		if (this.cameraPosition != null)
			this.theCameraController.autoPan();
		int index = theSTLTransforms.indexOf(gr);
		for (int i = 0; i < theSTLTransforms.size(); i++) {

			STLTransformGroup curr = theSTLTransforms.get(i);
			if (curr == gr)
				continue;

			boolean collision = this.modelsIntersect(curr, gr);
			System.out.println(collision);
			collisionTable.get(index).set(i, collision);
			collisionTable.get(i).set(index, collision);
		}
		updatePlacementStatus(false);
		updateIndicatorLights();
	}

	private void updateCollisionTable() {
		int size = theSTLTransforms.size();
		for (int i = 0; i < size; i++) {
			STLTransformGroup stgA = theSTLTransforms.get(i);
			for (int j = i + 1; j < size; j++) {
				STLTransformGroup stgB = theSTLTransforms.get(j);
				boolean coll = STLObjectCalculationUtilities.objectsIntersect(
						stgA.getSTLObject(), stgB.getSTLObject());
				collisionTable.get(j).set(i, coll);
				collisionTable.get(i).set(j, coll);
			}
		}

	}

	private void updatePlacementStatus(boolean updateCollisionTableFirst) {
		if (updateCollisionTableFirst) {
			updateCollisionTable();
		}

		for (int i = 0; i < theSTLTransforms.size(); i++) {
			if (theWorkspace != null
					&& !theWorkspace.stlIsInside(theSTLTransforms.get(i)
							.getTransformedSTLObject())) {
				placementStatuses.set(i, PlacementStatus.NOT_IN_WORKSPACE);
				continue;
			}
			boolean collision = collisionTable.get(i).contains(true);
			if (collision) {
				placementStatuses.set(i, PlacementStatus.MODEL_COLLISION);
			} else if (theWorkspace == null) {
				placementStatuses.set(i, PlacementStatus.UNKOWN);
			} else {
				placementStatuses.set(i, PlacementStatus.VALID_PLACEMENT);
			}

		}
		System.out.println("Placement Statuses: " + placementStatuses);
		System.out.println("Collision Table\n");
		for (ArrayList<Boolean> ab : collisionTable)
			System.out.println(ab);
		System.out.println("End collision table");
	}
	
	public STLPreviewCameraData getCameraData() {
		return new STLPreviewCameraData(cameraPosition, cameraDirection,
				cameraOrientation);
	}

	public STLObject getMergedSTLObject() {
		ArrayList<STLObject> theObjects = new ArrayList<STLObject>();
		for (STLTransformGroup stg : this.theSTLTransforms) {
			Transform3D currTran = new Transform3D();
			stg.getTransform(currTran);
			STLObject curr = stg.getTransformedSTLObject();
			theObjects.add(curr);
		}
		return STLObject.getMergedSTLObject("MergedSTL", theObjects);
	}

	public void alertMouseControlModeChanged(
			STLPreviewMouseControls stlPreviewMouseControls) {
		if (stlPreviewMouseControls.getCurrentMode() == STLPreviewMouseControls.MouseControlMode.MODEL_TRANSLATE_XZ) {
			this.theCameraController
					.setCameraFocusMode(STLPreviewCameraController.CameraMode.AERIAL);
		}
	}

	public void alertRightClick(int x, int y) {

		JPopupMenu popup = new JPopupMenu();

		if (currentSTLTransform == null) {
			popup.add(new JMenuItem("Basic"));
			// .out.println("Basic popup menu");
		} else {

			JMenuItem remove = new JMenuItem("Remove");
			remove.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent arg0) {
					removeCurrentModel();
				}
			});
			popup.add(remove);
			JMenuItem duplicate = new JMenuItem("Duplicate");
			duplicate.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					duplicateCurrentModel();
				}
			});
			popup.add(duplicate);

			JMenuItem resetTransforms = new JMenuItem("Reset Transforms");
			resetTransforms.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					resetCurrentModel();
				}
			});
			popup.add(resetTransforms);
			
			JMenuItem reorient = new JMenuItem("Reorient");
			reorient.addActionListener(new ActionListener() {

				@Override
				public void actionPerformed(ActionEvent e) {
					orientNextFace();
				}

				
			});
			popup.add(reorient);
			
			
			
			//Vector v = (this->cross(vector)).normalize();
			//return Quaternion(v, acos(a.dot(b)));	

			// System.out.println("Transform specific pop up menu");
		}
		popup.show(this, x, y);
	}
	
	protected void orientNextFace() {

		if (currentSTLTransform != null) {

			currentSTLTransform.reorientToNextFace();

			Point3f min = currentSTLTransform.getCurrentMin();
			Double y = this.theWorkspace.getWorkspaceSTLObject().getSurfaceY();
			if(!y.isNaN()) currentSTLTransform.translateUpDown(min.y - y-.0001f);
		}
	}
	
	protected void resetCurrentModel() {
		if (currentSTLTransform == null) {
			System.out.println("No model to reset");
			return;
		}
		currentSTLTransform.resetModelTransforms();
		currentSTLTransform.centerOnWorkspace(theWorkspace
				.getWorkspaceSTLObject());
	}

	protected void duplicateCurrentModel() {
		if (currentSTLTransform == null) {
			System.out.println("Nothing to duplicate");
			return;
		}

		STLTransformGroup newTransform = currentSTLTransform.getDuplicate(true);

		this.addModelToWorkspace(newTransform);

	}

	public int getModelCount(){
		return this.theSTLTransforms.size();
	}	
	
}