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
import javax.vecmath.Tuple3d;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.STLLoader;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLTransformGroup;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceBranchGroup;
import com.sun.j3d.utils.universe.SimpleUniverse;

public class STLPreviewCanvas3D extends Canvas3D {

	/**
	 * 
	 */
	private static final long serialVersionUID = -45261396936364195L;

	// basic fields for creating java 3d scene
	private SimpleUniverse simpleU;
	private BranchGroup mainBranch;

	// transform group for the stl model itself
	private STLTransformGroup stlTransform;

	// transform group that displays the area in which the printer can reliably print
	private STLWorkspaceBranchGroup theWorkspace;

	private DirectionalLight theLight;

	private Point3d cameraPosition, cameraDirection;

	// allowing this to be anything else doesn't add much value and complicates
	// otherwise simple math so I've elected to make it a constant
	private static final Vector3d CAMERA_ORIENTATION = new Vector3d(0, 1, 0);

	private File theSTLFile, theGcode;
	private STLObject theSTLObject;

	private STLPreviewMouseControls theMouseControls;
	
	private boolean initialized;
	
	private CameraFocusMode currentCameraFocusMode;

	private boolean isDead;

	private ArrayList<STLPreviewCanvas3DListener> theListeners;

	private File theWorkspaceSTL;

	/**
	 * enum for encapsulating camera focus methods currently 
	 * provides simple methods for getting current point to focus on
	 * as well as the base camera position, both of which may be dependent
	 * on selected mode
	 *
	 */
	public enum CameraFocusMode {
		WORKSPACE_BASE {

			@Override
			public Point3d getFocus(STLPreviewCanvas3D sp) {
				return new Point3d(0, 0, 0);
			}

			@Override
			public Point3d getBaseCameraPosition(STLPreviewCanvas3D sp) {
				double m = Math.max(60,Math.max(60,60)); //TODO get from STLWorkspaceBranchGroup
				return new Point3d(2 * m, 2 * m, 2 * m);
			}

			public String toString(){
				return "Focus Camera on Workspace";
			}
		},
		STL_CENTER {

			@Override
			public Point3d getFocus(STLPreviewCanvas3D sp) {
				Point3d newFocus = new Point3d(sp.stlTransform.getCurrentCenter());
				
				/*
				System.out.println("Current center "+newFocus);
				
				System.out.println("Base Min (STLTransform)"+ sp.stlTransform.getBaseCenter());
				System.out.println("Base min (STLObject)"+ sp.theSTLObject.getCenter());
				System.out.println();
				*/
				
				return new Point3d(newFocus);
			}

			@Override
			public Point3d getBaseCameraPosition(STLPreviewCanvas3D sp) {
				double m = Math.max(sp.theSTLObject.getXLength(), Math.max(
						sp.theSTLObject.getYLength(),
						sp.theSTLObject.getZLength()));
				Point3d basePos = new Point3d(2 * m, 2 * m, 2 * m);
				basePos.add(this.getFocus(sp));
				System.out.println("Base camera position "+basePos);
				return basePos;
			}
		
			public String toString(){
				return "Focus Camera on STL";
			}
		};

		public abstract Point3d getFocus(STLPreviewCanvas3D sp);

		public abstract Point3d getBaseCameraPosition(STLPreviewCanvas3D sp);

		public static CameraFocusMode[] getModes() {
				return new CameraFocusMode[]{WORKSPACE_BASE,STL_CENTER};
		}

	};

	public STLPreviewCanvas3D(File stl, File gcode, File workspaceSTL) {
		super(SimpleUniverse.getPreferredConfiguration());
		
		theListeners = new ArrayList<STLPreviewCanvas3DListener>();
		
		initialized = false;
		isDead = false;
		
		currentCameraFocusMode = CameraFocusMode.STL_CENTER;

		//theCanvas3D = new Canvas3D(SimpleUniverse.getPreferredConfiguration());

		//this.setLayout(new GridLayout(1, 1));
		//this.add(theCanvas3D);

		this.theSTLFile = stl;
		this.theGcode = gcode;
		
		theWorkspaceSTL = workspaceSTL;

	}
	
	public void addListener(STLPreviewCanvas3DListener spcl){
		if(!theListeners.contains(spcl)) theListeners.add(spcl);
	}
	
	public void inititalize(){
		simpleU = new SimpleUniverse(this);
		mainBranch = new BranchGroup();
		// = simpleU.getLocale();
				
		mainBranch.setCapability(BranchGroup.ALLOW_CHILDREN_EXTEND);
		mainBranch.setCapability(BranchGroup.ALLOW_DETACH);
		mainBranch.setCapability(BranchGroup.ALLOW_CHILDREN_READ);
		mainBranch.setCapability(BranchGroup.ALLOW_CHILDREN_WRITE);
		
		
		try {
			this.assembleSTLTransform(theSTLFile);
			mainBranch.addChild(stlTransform);
		} catch (IOException e) {
			e.printStackTrace();
		}

		stlTransform.getModel().getAppearance()
				.setColoringAttributes(new ColoringAttributes());
		stlTransform.getModel().getAppearance().getColoringAttributes()
				.setCapability(ColoringAttributes.SHADE_GOURAUD);

		try {
			theWorkspace = STLWorkspaceBranchGroup.STLWorkspaceBranchGroupFactory(theWorkspaceSTL);
		} catch (IOException e) {
			//TODO notify of exception
			theWorkspace = null; //TODO Change to NullSTLWorkspaceBranchGroup object?
			e.printStackTrace();
		}

		if(theWorkspace!=null)mainBranch.addChild(theWorkspace);
		
		theLight = new DirectionalLight();
		theLight.setInfluencingBounds(new BoundingSphere(new Point3d(0, 0, 0),
				900));
		
		theLight.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
		theLight.setCapability(DirectionalLight.ALLOW_COLOR_WRITE);
		mainBranch.addChild(theLight);

		updateIndicatorLightColor();

		// objects in the scene can be viewed.
		simpleU.addBranchGraph(mainBranch);

		centerOnWorkspace();
		
		// Initialize camera position
		resetCamera();
		
		initialized = true;
	}
	
	public boolean isInitialized(){
		return initialized;
	}
		
	public void setCamera(Point3d position, Point3d lookAt) {
				
		TransformGroup viewTransform = simpleU.getViewingPlatform()
				.getViewPlatformTransform();

		Transform3D t3d = new Transform3D();
		t3d.lookAt(position, lookAt, CAMERA_ORIENTATION);
		t3d.invert();
		viewTransform.setTransform(t3d);

		cameraPosition = position;
		cameraDirection = lookAt;

		Vector3f lightDir = new Vector3f(cameraPosition);
		Vector3f temp = new Vector3f(cameraDirection);
		temp.sub(lightDir);

		theLight.setDirection(temp);
		
		for(STLPreviewCanvas3DListener spcl:theListeners){
			spcl.alertCameraMoved(position, lookAt, CAMERA_ORIENTATION);
		}

	}

	private STLTransformGroup assembleSTLTransform(File f) throws IOException {
		// BranchGroup objRoot = new BranchGroup();

		try {
			theSTLObject = STLLoader.loadFile(f);

			stlTransform = STLLoader.createSTLTransform(theSTLObject,
					mainBranch);
		} catch (IOException e) {
			e.printStackTrace();
		}

		return stlTransform;
	}

	// Camera functions
	public void zoom(double d) {
		Vector3d dirVector = new Vector3d();
		dirVector.add(cameraDirection);
		dirVector.sub(cameraPosition);
		dirVector.normalize();
		dirVector.scale(d);
		// System.out.println(dirVector);

		// Prevents zooming past focal point
		if (d <= cameraPosition.distance(cameraDirection))
			cameraPosition.add(dirVector);

		setCamera(cameraPosition, cameraDirection);
	}

	public void panX(double d) {
		cameraPosition.add(new Point3d(0, 0, d));
		cameraDirection.add(new Point3d(0, 0, d));
		setCamera(cameraPosition, cameraDirection);
	}

	public void panY(double d) {
		cameraPosition.add(new Point3d(0, d, 0));
		cameraDirection.add(new Point3d(0, d, 0));
		setCamera(cameraPosition, cameraDirection);
	}

	public void panZ(double d) {
		cameraPosition.add(new Point3d(d, 0, 0));
		cameraDirection.add(new Point3d(d, 0, 0));
		setCamera(cameraPosition, cameraDirection);
	}

	public void panTo(Tuple3d focus){
		
		if(cameraPosition==null||cameraDirection==null){
			resetCamera();
		}
		
		Vector3d newPos = new Vector3d(0,0,0);
		newPos.add(cameraPosition);
		newPos.sub(cameraDirection);
		newPos.add(focus);
		
		cameraDirection = new Point3d(focus);		
		cameraPosition = new Point3d(newPos);	
		
		setCamera(cameraPosition, cameraDirection);
 	}
	
	public void resetCamera() {
				
		cameraPosition = currentCameraFocusMode.getBaseCameraPosition(this);
		cameraDirection = currentCameraFocusMode.getFocus(this);
		setCamera(cameraPosition, cameraDirection);
		
		double clipDist = cameraPosition.distance(new Point3d(this.stlTransform.getCurrentCenter()));
		clipDist+=Math.max(Math.max(this.theSTLObject.getXLength(), this.theSTLObject.getYLength()),this.theSTLObject.getZLength());
		this.getView().setBackClipDistance(clipDist);
			
	}

	public void resetCamera(CameraFocusMode newMode) {
		currentCameraFocusMode = newMode;
		resetCamera();
	}
	
	public void setCameraFocusMode(CameraFocusMode newMode){
		currentCameraFocusMode = newMode;
		cameraDirection = currentCameraFocusMode.getFocus(this);
		autoPan();
	}

	public void rotateCameraXZ(double rot) {
		
		Vector3d vec = new Vector3d();
		vec.add(cameraPosition);
		vec.sub(cameraDirection);

		double radius = Math.sqrt((vec.x * vec.x) + (vec.z * vec.z));

		double currentAngle = Math.acos(vec.x / radius);
		if (vec.z < 0)
			currentAngle = (2 * Math.PI) - currentAngle;

		double newAngle = currentAngle + rot;
		double newX = radius * Math.cos(newAngle)+cameraDirection.x;
		double newZ = radius * Math.sin(newAngle)+cameraDirection.z;

		/*
		 * System.out.println("Radius: "+radius);
		 * System.out.println("Initial Angle: "+currentAngle);
		 * System.out.println("Delta Angle: "+rot);
		 * System.out.println("Final Angle:" + newAngle);
		 * System.out.println("Initial position: "+cameraPosition);
		 */
		cameraPosition = new Point3d(newX, cameraPosition.y, newZ);
		/*
		 * System.out.println("Final position: "+cameraPosition);
		 * System.out.println("//////////////");
		 */

		setCamera(cameraPosition, cameraDirection);
	}
	
	public void rotateCameraUp(double rot) {
		
		Vector3d positionVector = new Vector3d();
		positionVector.add(cameraPosition);
		positionVector.sub(cameraDirection);

		double radius = positionVector.length();

		double currentAngle = Math.asin(positionVector.y / radius);

		double newAngle = rot + currentAngle;

		double newY = Math.sin(newAngle) * radius;

		double t = positionVector.x / positionVector.z;

		double newZ = Math.sqrt(((radius * radius) - (newY * newY))
				/ ((t * t) + 1));

		if (positionVector.z < 0)
			newZ *= -1;

		double newX = newZ * t;
		
		newY+=cameraDirection.y;
		newZ+=cameraDirection.z;
		newX+=cameraDirection.x;

		cameraPosition = new Point3d(newX, newY, newZ);

		setCamera(cameraPosition, cameraDirection);
	}

	private void autoPan(){
		panTo(this.currentCameraFocusMode.getFocus(this));
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
		
		Transform3D curr = this.getTransform3D();
		
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

	// TODO currently tries to erase rotations without erasing translations
	public void pointNormalDown(Vector3d normal) {
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);

		Vector3d pointInDir = new Vector3d(0, -1, 0);

		if (normal == null) {
			normal = new Vector3d(1, 0, 1);

		}

		// if(normal.equals(new Vector3d(0,0,0))) return;

		normal.normalize();

		curr.transform(normal);

		Vector3d noX = new Vector3d(0, normal.y, normal.z);
		Vector3d noZ = new Vector3d(normal.x, normal.y, 0);
		Vector3d noY = new Vector3d(normal.x, 0, normal.z);

		// Quat4d noRot = new Quat4d(1,0,0,1);
		// noRot.inverse();
		// curr.setRotation(noRot);

		/*
		 * double zAngle; if(normal.y!=0) { zAngle =
		 * Math.atan(normal.x/normal.y); } else if(normal.x!=0) zAngle =
		 * Math.PI/2; else zAngle = 0;
		 * 
		 * double xAngle; if(normal.y!=0){ xAngle =
		 * Math.atan(normal.z/normal.y); } else if(normal.z!=0) xAngle =
		 * Math.PI/2; else xAngle = 0;
		 * 
		 * double zRotate = -(Math.PI - zAngle); double xRotate = -(Math.PI -
		 * xAngle);
		 */

		Double xRotate = pointInDir.angle(noX);
		Double zRotate = pointInDir.angle(noZ);
		Double yRotate = pointInDir.angle(noY);// TODO?

		if (xRotate.isNaN())
			xRotate = 0.0;// Math.PI;
		if (zRotate.isNaN())
			zRotate = 0.0;// Math.PI;
		if (yRotate.isNaN())
			yRotate = 0.0;

		// curr.rotX(xRotate);
		// curr.rotY(0);
		// curr.rotZ(zRotate);
		System.out.println(xRotate + " " + zRotate);
		this.rotateX(xRotate);
		this.rotateZ(zRotate);

		// stlTransform.setTransform(curr);
		System.out.println(stlTransform.getCurrentMax());

		updateIndicatorLightColor();
	}

	
	// Model transform functions
	
	public void rotateX(double rad) {
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotX(rad);
		curr.mul(temp);
		stlTransform.setTransform(curr);
		
		autoPan();
		updateIndicatorLightColor();
	}

	public void rotateY(double rad) {
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotY(rad);
		curr.mul(temp);
		stlTransform.setTransform(curr);
		
		autoPan();
		updateIndicatorLightColor();
	}

	public void rotateZ(double rad) {
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotZ(rad);
		curr.mul(temp);
		stlTransform.setTransform(curr);
		
		autoPan();
		updateIndicatorLightColor();
	}

	// TODO this is a bit more complicated than originally thought
	// Need to correct for both camera angle as well as previous transforms
	// hopefully should be as simple as offsetting currentAngle variable
	public void rotateUpDown(double rad) {
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);

		double radZ = 0, radX = 0;

		Vector3d vec = new Vector3d();
		vec.add(cameraPosition);
		vec.sub(cameraDirection);

		double radius = Math.sqrt((vec.x * vec.x) + (vec.z * vec.z));

		double currentAngle = Math.acos(vec.x / radius);
		if (vec.z < 0)
			currentAngle = (2 * Math.PI) - currentAngle;

		// TODO

		radZ = rad * Math.cos(currentAngle);
		radX = rad * Math.sin(currentAngle);

		rotateZ(radZ);
		rotateX(radX);

		// /////
		/*
		 * Transform3D temp = new Transform3D(); temp.rotZ(radZ);
		 * temp.rotX(radX); curr.mul(temp); stlTransform.setTransform(curr);
		 */
		updateIndicatorLightColor();
	}

	public void resetModelTransforms() {
		Transform3D blank = new Transform3D();
		stlTransform.setTransform(blank);
		
		centerOnWorkspace();
		autoPan();
	}

	public void centerOnWorkspace() {
		/*
		// Point3f cent = stlTransform.getCurrentCenter();
		Point3f cent = theSTLObject.getCenter();
		System.out.println(cent);
		System.out.println(theSTLObject.getCenter());
		double xTrans = -cent.x;
		double zTrans = -cent.z;
		double yTrans = -theSTLObject.getMin().y - (workspaceDimensions.y / 2);
		Vector3d tran = new Vector3d(xTrans, yTrans, zTrans);
		Transform3D centerTransform = new Transform3D();
		stlTransform.getTransform(centerTransform);
		centerTransform.setTranslation(tran);
		// translate(tran);
		stlTransform.setTransform(centerTransform);

		updateIndicatorLightColor();
		autoPan();
		*/ //TODO
	}

	public void translate(Vector3d tran) {
		Transform3D temp = new Transform3D();
		Transform3D temp2 = new Transform3D();
		stlTransform.getTransform(temp2);
		temp.setTranslation(tran);
		temp2.mul(temp);// TODO
		stlTransform.setTransform(temp2);
		
		autoPan();
		updateIndicatorLightColor();
	}

	public void translateX(double x) {
		Vector3d tran = new Vector3d(x, 0, 0);
		translate(tran);
	}

	public void translateY(double y) {
		Vector3d tran = new Vector3d(0, y, 0);
		translate(tran);
	}

	public void translateZ(double z) {
		Vector3d tran = new Vector3d(0, 0, z);
		translate(tran);
	}

	public void translateLeftRight(double d) {
		Vector3d tran = new Vector3d(1, 0, 0);
		Transform3D curr = this.getTransform3D();
		// curr.setTranslation(new Vector3d(0,0,0));
		curr.invert();
		curr.transform(tran);
		tran.normalize();

		Vector3d camVec = new Vector3d(cameraPosition);
		camVec.sub(cameraDirection);
		camVec.cross(camVec, CAMERA_ORIENTATION);

		// curr.invert();
		curr.transform(camVec);
		camVec.normalize();

		tran.scale(d);
		camVec.scale(-d);
		// System.out.println(tran);
		translate(tran);
		// translate(camVec);
	}

	public void translateUpDown(double d) {
		Vector3d tran = new Vector3d(0, -1, 0); // For some reason -1 makes this
												// work
		Transform3D curr = this.getTransform3D();
		// curr.setTranslation(new Vector3d(0,0,0));
		curr.invert();
		curr.transform(tran);
		tran.normalize();
		tran.scale(d);
		// System.out.println(tran);
		translate(tran);
	}

	public void translateBackForth(double d) {
		Vector3d tran = new Vector3d(0, 0, 1);
		Transform3D curr = this.getTransform3D();
		// curr.setTranslation(new Vector3d(0,0,0));
		curr.invert(); // THis works but I really don't know why
		curr.transform(tran);
		tran.normalize();
		tran.scale(d);
		// System.out.println(tran);
		translate(tran);
	}

	public void translateLateral(double d) {

		Transform3D curr = this.getTransform3D();

		Vector3d camVec = new Vector3d(cameraPosition);
		camVec.sub(cameraDirection);
		camVec.cross(camVec, CAMERA_ORIENTATION);

		curr.invert();
		curr.transform(camVec);
		camVec.normalize();

		camVec.scale(-d);

		translate(camVec);

	}

	public void setOutlineVisibility(boolean vis) {
		stlTransform.setOutlineVisibility(vis);
	}

	public void setModelVisibility(boolean vis) {
		stlTransform.setModelVisibility(vis);
	}

	public void setWorkspace(File newWorkspace) throws IOException{
		this.theWorkspaceSTL = newWorkspace;
		
		if(this.theWorkspace!=null){
			this.mainBranch.removeChild(theWorkspace);
		}
		
		theWorkspace = STLWorkspaceBranchGroup.STLWorkspaceBranchGroupFactory(newWorkspace);
		
	}
	
	public void removeWorkspace(){
		if(this.theWorkspace!=null){
			this.mainBranch.removeChild(theWorkspace);
		}
		theWorkspace = null;
	}
	
	// Getters
	
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
	}*/

	public boolean getOutlineVisibility() {
		return stlTransform.getOutlineVisibility();
	}

	public boolean getModelVisibility() {
		return stlTransform.getModelVisibility();
	}

	public Transform3D getTransform3D() {
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);
		return curr;
	}

	public Canvas3D getCanvas3D() {
		return this;
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
		return CAMERA_ORIENTATION;
	}
	
}