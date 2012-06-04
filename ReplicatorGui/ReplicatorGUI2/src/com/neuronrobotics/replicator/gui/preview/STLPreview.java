package com.neuronrobotics.replicator.gui.preview;

//import java.awt.Color;
import java.awt.GraphicsConfiguration;
import java.io.File;
import java.io.IOException;
//import java.util.Dictionary;
//import java.util.Hashtable;

import javax.media.j3d.AmbientLight;
import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingSphere;
//import javax.media.j3d.Bounds;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.GeometryArray;
import javax.media.j3d.IndexedLineArray;
//import javax.media.j3d.IndexedQuadArray;
//import javax.media.j3d.J3DGraphics2D;
import javax.media.j3d.LineArray;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.ASCIISTLWriter;
import com.neuronrobotics.replicator.gui.stl.STLLoader;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLTransformGroup;
//import com.sun.j3d.utils.geometry.ColorCube;
import com.sun.j3d.utils.universe.SimpleUniverse;

public class STLPreview extends Canvas3D {
	

	
	/**
	 * 
	 */
	private static final long serialVersionUID = -45261396936364195L;
	private SimpleUniverse simpleU;
	private BranchGroup mainBranch;
	private STLTransformGroup stlTransform;
	private TransformGroup theWorkspace;
	
	private DirectionalLight theLight;
	
	//private Shape3D stlModel,facetOutline;
	
	private Point3d cameraPosition,cameraDirection;
	private static final Vector3d CAMERA_ORIENTATION = new Vector3d(0,1,0);
	
	private File theSTLFile, theGcode;
	private STLObject theSTLObject;
		
	private Point3f workspaceDimensions;
			
	public STLPreview(File stl, File gcode, Point3f workspaceDim){
		super(SimpleUniverse.getPreferredConfiguration());
		
		this.theSTLFile = stl;
		this.theGcode = gcode;
		System.out.println(theGcode.getName());
		
		workspaceDimensions = workspaceDim;
	
		simpleU = new SimpleUniverse(this);
		mainBranch = new BranchGroup();

		try {
			this.assembleSTLTransform(stl);
			mainBranch.addChild(stlTransform);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		stlTransform.getModel().getAppearance().setColoringAttributes(new ColoringAttributes());
		stlTransform.getModel().getAppearance().getColoringAttributes().setCapability(ColoringAttributes.SHADE_GOURAUD);
		
		theWorkspace = RectangularWorkspace(new Point3f(0, 0, 0),
				workspaceDimensions);
		
		mainBranch.addChild(theWorkspace);
		// ////////
		AmbientLight lightA = new AmbientLight();
		lightA.setInfluencingBounds(new BoundingSphere());
		mainBranch.addChild(lightA);
		
		theLight = new DirectionalLight();
		theLight.setInfluencingBounds(new BoundingSphere(new Point3d(0,0,0),900));
		//theLight.setDirection(-1,-1,-1);
		theLight.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
		theLight.setCapability(DirectionalLight.ALLOW_COLOR_WRITE);
		//theLight.setColor(new Color3f(.2f,.4f,.8f));
		// customize DirectionalLight object		
		mainBranch.addChild(theLight);
		
		updateIndicatorLightColor();
		
		// objects in the scene can be viewed.
		simpleU.addBranchGraph(mainBranch);
		
	
		//Initialize camera position
		resetCamera();
		
		this.getView().setBackClipDistance(1000); //TODO do this dynamically?
		
		centerOnWorkspace();
		
	}

	private STLPreview(GraphicsConfiguration arg0) {
		super(arg0);
	}

	private TransformGroup RectangularWorkspace(Point3f center,
			Point3f dimensions) {
		TransformGroup workspaceGroup = new TransformGroup();

		IndexedLineArray axisLines = new IndexedLineArray(8,
				GeometryArray.COORDINATES, 24);

		axisLines.setCoordinate(0, new Point3f(center.x - dimensions.x / 2,
				center.y - dimensions.y / 2, center.z - dimensions.z / 2));
		axisLines.setCoordinate(1, new Point3f(center.x - dimensions.x / 2,
				center.y + dimensions.y / 2, center.z - dimensions.z / 2));
		axisLines.setCoordinate(2, new Point3f(center.x + dimensions.x / 2,
				center.y - dimensions.y / 2, center.z - dimensions.z / 2));
		axisLines.setCoordinate(3, new Point3f(center.x + dimensions.x / 2,
				center.y + dimensions.y / 2, center.z - dimensions.z / 2));
		axisLines.setCoordinate(4, new Point3f(center.x - dimensions.x / 2,
				center.y - dimensions.y / 2, center.z + dimensions.z / 2));
		axisLines.setCoordinate(5, new Point3f(center.x - dimensions.x / 2,
				center.y + dimensions.y / 2, center.z + dimensions.z / 2));
		axisLines.setCoordinate(6, new Point3f(center.x + dimensions.x / 2,
				center.y - dimensions.y / 2, center.z + dimensions.z / 2));
		axisLines.setCoordinate(7, new Point3f(center.x + dimensions.x / 2,
				center.y + dimensions.y / 2, center.z + dimensions.z / 2));

		axisLines.setCoordinateIndex(0, 0);
		axisLines.setCoordinateIndex(1, 1);
		axisLines.setCoordinateIndex(2, 0);
		axisLines.setCoordinateIndex(3, 2);
		axisLines.setCoordinateIndex(4, 0);
		axisLines.setCoordinateIndex(5, 4);
		axisLines.setCoordinateIndex(6, 7);
		axisLines.setCoordinateIndex(7, 3);
		axisLines.setCoordinateIndex(8, 7);
		axisLines.setCoordinateIndex(9, 5);
		axisLines.setCoordinateIndex(10, 7);
		axisLines.setCoordinateIndex(11, 6);
		axisLines.setCoordinateIndex(12, 2);
		axisLines.setCoordinateIndex(13, 3);
		axisLines.setCoordinateIndex(14, 2);
		axisLines.setCoordinateIndex(15, 6);
		axisLines.setCoordinateIndex(16, 6);
		axisLines.setCoordinateIndex(17, 4);
		axisLines.setCoordinateIndex(18, 5);
		axisLines.setCoordinateIndex(19, 4);
		axisLines.setCoordinateIndex(20, 5);
		axisLines.setCoordinateIndex(21, 1);
		axisLines.setCoordinateIndex(22, 1);
		axisLines.setCoordinateIndex(23, 3);

		Shape3D workArea = new Shape3D();
		workArea.setGeometry(axisLines);
		workspaceGroup.addChild(workArea);

		// Work surface
		LineArray surfaceLines = new LineArray(12,GeometryArray.COORDINATES);
		
		
		float xDelta = dimensions.x/4.0f;
		float zDelta = dimensions.z/4.0f;
		Point3f backLeft = new Point3f(center.x-dimensions.x
				/2, center.y - dimensions.y / 2, center.z - dimensions.z
				/ 2);
		
		int vt = 0;
		
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+xDelta,backLeft.y,backLeft.z));
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+xDelta,backLeft.y,backLeft.z+dimensions.z));
		
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+(2*xDelta),backLeft.y,backLeft.z));
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+(2*xDelta),backLeft.y,backLeft.z+dimensions.z));
		
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+(3*xDelta),backLeft.y,backLeft.z));
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+(3*xDelta),backLeft.y,backLeft.z+dimensions.z));
		
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x,backLeft.y,backLeft.z+zDelta));
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+dimensions.x,backLeft.y,backLeft.z+zDelta));
		
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x,backLeft.y,backLeft.z+(2*zDelta)));
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+dimensions.x,backLeft.y,backLeft.z+(2*zDelta)));
		
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x,backLeft.y,backLeft.z+(3*zDelta)));
		surfaceLines.setCoordinate(vt++, new Point3d(backLeft.x+dimensions.x,backLeft.y,backLeft.z+(3*zDelta)));
		
		
		
		
		Shape3D workspaceSurface = new Shape3D();
		workspaceSurface.setGeometry(surfaceLines);

		Appearance app = new Appearance();
		ColoringAttributes ca = new ColoringAttributes();
		Color3f a = new Color3f(.25f, .25f, .25f);
		a.add(new Color3f(.5f, .5f, .5f));
		ca.setColor(a);
		app.setColoringAttributes(ca);

		workspaceSurface.setAppearance(app);

		workspaceGroup.addChild(workspaceSurface);
		
		

		return workspaceGroup;
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
		
		
	}

	private STLTransformGroup assembleSTLTransform(File f) throws IOException {
		// BranchGroup objRoot = new BranchGroup();

		try {
			theSTLObject = STLLoader.loadFile(f);
			
			boolean debug = true;
			if (debug) {
				ASCIISTLWriter aw = new ASCIISTLWriter(theSTLObject);
				aw.writeSTLToFile(new File("writerTest.stl"));
				System.out.println(theSTLObject);
				System.out.println(theSTLObject.getCenter());
				System.out.println(theSTLObject.getMax());
				System.out.println(theSTLObject.getMin());
				System.out.println(theSTLObject.getXDistance());
				System.out.println(theSTLObject.getYDistance());
				System.out.println(theSTLObject.getZDistance());
			}
			stlTransform = STLLoader.createSTLTransform(theSTLObject, mainBranch);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		return stlTransform;
	}
	
	//Camera functions
	public void zoom(double d){		
		Vector3d dirVector = new Vector3d();
		dirVector.add(cameraDirection);
		dirVector.sub(cameraPosition);
		dirVector.normalize();
		dirVector.scale(d);
		//System.out.println(dirVector);
		
		//Prevents zooming pest focal point
		if(d<=cameraPosition.distance(cameraDirection))
		cameraPosition.add(dirVector);
		
		setCamera(cameraPosition,cameraDirection);	
	}

	public void panX(double d){
		cameraPosition.add(new Point3d(0,0,d));
		cameraDirection.add(new Point3d(0,0,d));
		setCamera(cameraPosition,cameraDirection);
	}
	
	public void panY(double d){
		cameraPosition.add(new Point3d(0,d,0));
		cameraDirection.add(new Point3d(0,d,0));
		setCamera(cameraPosition,cameraDirection);
	}
	
	public void panZ(double d){
		cameraPosition.add(new Point3d(d,0,0));
		cameraDirection.add(new Point3d(d,0,0));
		setCamera(cameraPosition,cameraDirection);
	}
	
	public void resetCamera(){
		double m = Math.max(this.workspaceDimensions.z,Math.max(this.workspaceDimensions.x,this.workspaceDimensions.y));
		cameraPosition = new Point3d(2*m,2*m,2*m);
		cameraDirection = new Point3d(0,0,0); 
		//TODO will need to switch between focusing on workspace and model
		setCamera(cameraPosition,cameraDirection);
		
			
	}
	
	public void rotateCameraXZ(double rot){
		Vector3d vec = new Vector3d();
		vec.add(cameraPosition);
		vec.sub(cameraDirection);
		
		double radius = Math.sqrt((vec.x*vec.x)+(vec.z*vec.z));
		
		double currentAngle = Math.acos(vec.x/radius);
		if(vec.z<0) currentAngle=(2*Math.PI)-currentAngle;
				
		double newAngle = currentAngle+rot;
		double newX = radius*Math.cos(newAngle);
		double newZ = radius*Math.sin(newAngle);
		

		
		
		System.out.println("Radius: "+radius);
		System.out.println("Initial Angle: "+currentAngle);
		System.out.println("Delta Angle: "+rot);
		System.out.println("Final Angle:" + newAngle);
		System.out.println("Initial position: "+cameraPosition);
		
		cameraPosition = new Point3d(newX,cameraPosition.y,newZ);
		
		System.out.println("Final position: "+cameraPosition);
		System.out.println("//////////////");
		
		
		
		
		
		setCamera(cameraPosition,cameraDirection);
	}
	
	public void rotateCameraXY(double rot){
		Vector3d vec = new Vector3d();
		vec.add(cameraPosition);
		vec.sub(cameraDirection);
		
		double radius = Math.sqrt((vec.x*vec.x)+(vec.y*vec.y));
		
		double currentAngle = Math.acos(vec.x/radius);
		if(vec.y<0) currentAngle=(2*Math.PI)-currentAngle;
				
		double newAngle = currentAngle+rot;
		double newX = radius*Math.cos(newAngle);
		double newY = radius*Math.sin(newAngle);
		
		
		/*
		System.out.println("Radius: "+radius);
		System.out.println("Initial Angle: "+currentAngle);
		System.out.println("Delta Angle: "+rot);
		System.out.println("Final Angle:" + newAngle);
		System.out.println("Initial position: "+cameraPosition);
		*/
		
		cameraPosition = new Point3d(newX,newY,cameraPosition.z);
		
		//System.out.println("Final position: "+cameraPosition);
		
		setCamera(cameraPosition,cameraDirection);
	}
	
	public void rotateCameraUp(double rot){		
		Vector3d positionVector = new Vector3d();
		positionVector.add(cameraPosition);
		positionVector.sub(cameraDirection);
		
		double radius = positionVector.length();
		
		double currentAngle=Math.asin(positionVector.y/radius);
		
		double newAngle = rot+currentAngle;
							
		double newY = Math.sin(newAngle)*radius;
		
		double t = positionVector.x/positionVector.z;
		
		double newZ = Math.sqrt(((radius*radius)-(newY*newY))/((t*t)+1));
		
		if(positionVector.z<0) newZ*=-1;
		
		double newX = newZ*t;
		
		cameraPosition = new Point3d(newX,newY,newZ);		
				
		setCamera(cameraPosition, cameraDirection);		
	}
	
	//light transform functions
	public void updateIndicatorLightColor(){
		if(modelInWorkspace()) theLight.setColor(new Color3f(.0f,5.5f,.0f));
		else theLight.setColor(new Color3f(5.5f,.0f,.0f));
	}
	
	public boolean modelInWorkspace(){
		
		Point3f min = stlTransform.getCurrentMin();
		Point3f max = stlTransform.getCurrentMax();
		
		System.out.println(min);
		System.out.println(max);
		
		if(min.x<(0-workspaceDimensions.x/2)) return false;
		if(min.y<(0-workspaceDimensions.y/2)) return false;
		if(min.z<(0-workspaceDimensions.z/2)) return false;
		if(max.x>workspaceDimensions.x/2) return false;
		if(max.y>workspaceDimensions.y/2) return false;
		if(max.z>workspaceDimensions.z/2) return false;
				
		return true;
	}
		
	//Model transform functions
	public void rotateX(double rad){
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);
		
		Transform3D temp = new Transform3D();
		temp.rotX(rad);
		curr.mul(temp);
		stlTransform.setTransform(curr);
		updateIndicatorLightColor();
	}
	
	public void rotateY(double rad){
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);
		
		Transform3D temp = new Transform3D();
		temp.rotY(rad);
		curr.mul(temp);
		stlTransform.setTransform(curr);
		updateIndicatorLightColor();
	}
	
	public void rotateZ(double rad){
		Transform3D curr = new Transform3D();
		stlTransform.getTransform(curr);
		
		Transform3D temp = new Transform3D();
		temp.rotZ(rad);
		curr.mul(temp);
		stlTransform.setTransform(curr);
		updateIndicatorLightColor();
	}
	
	public void centerOnWorkspace(){
		//Point3f cent = stlTransform.getCurrentCenter();
		//Point3f cent = theSTLObject.getCenter();
		double xTrans = 0;//-cent.x;
		double zTrans = 0;//-cent.z;
		double yTrans = -stlTransform.getBaseMin().y-(workspaceDimensions.y/2);
		Vector3d tran = new Vector3d(xTrans,yTrans,zTrans);
		translate(tran);
		updateIndicatorLightColor();
	}
	
	public void translate(Vector3d tran){
		Transform3D temp = new Transform3D();
		Transform3D temp2 = new Transform3D();
		stlTransform.getTransform(temp2);
		temp.setTranslation(tran);
		temp2.mul(temp);
		stlTransform.setTransform(temp2);
		updateIndicatorLightColor();
	}

	public void translateX(double x){
		Vector3d tran = new Vector3d(x,0,0);
		translate(tran);
	}
	
	public void translateY(double y){
		Vector3d tran = new Vector3d(0,y,0);
		translate(tran);
	}
	
	public void translateZ(double z){
		Vector3d tran = new Vector3d(0,0,z);
		translate(tran);
	}
	
	public void setOutlineVisibility(boolean vis){
		stlTransform.setOutlineVisibility(vis);
	}
	
	public void setModelVisibility(boolean vis){
		stlTransform.setModelVisibility(vis);
	}
	
	//Getters
	public STLObject getSTLObject(){
		return this.theSTLObject;
	}
	
	public File getSTLFile(){
		return theSTLFile;
	}
	
	public File getGCodeFile(){
		return theGcode;
	}
	
	public Point3f getWorkspaceDimensions(){
		return workspaceDimensions;
	}

	
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

}
