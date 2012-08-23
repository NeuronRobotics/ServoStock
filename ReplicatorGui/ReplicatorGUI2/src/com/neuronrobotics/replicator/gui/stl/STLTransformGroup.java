package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;

import javax.media.j3d.AmbientLight;
import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Point3d;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;

import com.neuronrobotics.replicator.gui.preview.STLPreviewCanvas3D;
import com.sun.j3d.utils.picking.PickTool;

public class STLTransformGroup extends TransformGroup{
	
	// fields
	
	private STLObject theSTLObject;
	private Shape3D theModel, theFacetOutline;
	private AmbientLight indicatorLight;
	private STLWorkspaceBranchGroup theWorkspace;
	private ArrayList<STLTransformGroupListener> theListeners;
	
	
	// constructor(s)
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline){
		super();
		setModel(model);
		setOutline(outline);
		
		theSTLObject = stlo;
		theListeners = new ArrayList<STLTransformGroupListener>();
		
		theWorkspace = null;
		
		indicatorLight = new AmbientLight();
		indicatorLight.setInfluencingBounds(new BoundingSphere(new Point3d(0, 0, 0),
				900));
				
		indicatorLight.setCapability(DirectionalLight.ALLOW_DIRECTION_WRITE);
		indicatorLight.setCapability(DirectionalLight.ALLOW_COLOR_WRITE);
		indicatorLight.setCapability(ALLOW_BOUNDS_WRITE);
		this.addChild(indicatorLight);
		indicatorLight.removeAllScopes();
		indicatorLight.addScope(this);
		updateIndicatorLightBounds();
				
	}
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline, STLWorkspaceBranchGroup workspace){
		this(stlo,model,outline);
		theWorkspace = workspace;
		updateIndicatorLightBounds();
	}

	// private methods
	
	public void setWorkspace(STLWorkspaceBranchGroup newWorkspace){
		this.theWorkspace = newWorkspace;
	}
	
	public void addListener(STLTransformGroupListener newListener){
		theListeners.add(newListener);
	}
	
	private void setModel(Shape3D newModel){
		if(theModel!=null) this.removeChild(theModel);
		this.theModel = newModel;
		
		Appearance app;	
		RenderingAttributes ra;
		if(theModel.getAppearance()==null) app = new Appearance();
		else app = theModel.getAppearance();
		if(theModel.getAppearance().getRenderingAttributes()==null) ra = new RenderingAttributes();
		else ra = theModel.getAppearance().getRenderingAttributes();
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_WRITE);
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ);
		app.setRenderingAttributes(ra);
		theModel.setAppearance(app);
			
		theModel.setPickable(true);
		theModel.setCapability(ENABLE_PICK_REPORTING);
		PickTool.setCapabilities(theModel, PickTool.INTERSECT_FULL);
		
		this.addChild(theModel);
		
	}
	
	private void setOutline(Shape3D newOutline){
		if(theFacetOutline!=null) this.removeChild(theFacetOutline);
		this.theFacetOutline = newOutline;
		
		Appearance app;	
		RenderingAttributes ra;
		if(theFacetOutline.getAppearance()==null) app = new Appearance();
		else app = theFacetOutline.getAppearance();
		if(theFacetOutline.getAppearance().getRenderingAttributes()==null) ra = new RenderingAttributes();
		else ra = theFacetOutline.getAppearance().getRenderingAttributes();
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_WRITE);
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ);
		app.setRenderingAttributes(ra);
		theFacetOutline.setAppearance(app);
				
		this.addChild(theFacetOutline);
		
	}
	
	private void updateIndicatorLightBounds() {
		Point3d cent = new Point3d(this.getCurrentCenter());		
		indicatorLight.setBounds(new BoundingSphere(cent,1));
		
		/*
		if(theWorkspace!=null&&this.modelIsInWorkspace(theWorkspace)){
			indicatorLight.setColor(new Color3f(.0f, 5.5f, .0f));
		} else {
			indicatorLight.setColor(new Color3f(5.5f, .0f, .0f));
		}*/
	}
	
	//public methods
	
	public void setTransform(Transform3D newTran){
		super.setTransform(newTran);
		updateIndicatorLightBounds();
		for(STLTransformGroupListener stgl:this.theListeners){
			stgl.alertSTLTransformMoved(this);
		}
	}
	
	public Shape3D getModel(){		
		return theModel;
	}
	
	public Shape3D getOutline(){
		return theFacetOutline;
	}
	
	public STLObject getSTLObject(){
		return theSTLObject;
	}

	public void setModelVisibility(boolean visible){
		theModel.getAppearance().getRenderingAttributes().setVisible(visible);
	}
	
	public void setOutlineVisibility(boolean visible){
		theFacetOutline.getAppearance().getRenderingAttributes().setVisible(visible);	
	}
	
	public boolean getModelVisibility(){
		return theModel.getAppearance().getRenderingAttributes().getVisible();
	}
	
	public boolean getOutlineVisibility(){
		return theFacetOutline.getAppearance().getRenderingAttributes().getVisible();
	}

	/**
	 * Returns base max of coordinates ignoring
	 * current transforms
	 * @return max
	 */
	public Point3f getBaseMax(){
		return theSTLObject.getMax();
	}
	
	/**
	 * Returns base min of coordinates ignoring
	 * current transforms
	 * @return min
	 */
	public Point3f getBaseMin(){
		return theSTLObject.getMin();
	}
		
	/**
	 * Returns current minima of coordinates given
	 * current transforms
	 * @return min
	 */
	public Point3f getCurrentMin() {
		
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		
		//Point3f currMax = null;
		
		STLObject transformedObj = theSTLObject.getTransformedSTLObject(temp);
		return transformedObj.getMin();
		/*
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		
		Point3f currMin = null;
		
		for(STLFacet fac:theSTLObject){
			Point3f candidate = fac.getMin();
			temp.transform(candidate);
			
			if(currMin==null) currMin = candidate;
			else currMin.set(Math.min(currMin.x,candidate.x),Math.min(currMin.y,candidate.y),Math.min(currMin.z,candidate.z));			
		}					
		
		return currMin;
	*/
	}
	
	/**
	 * Returns current maxima coordinates given
	 * current transforms
	 * @return max
	 */
	public Point3f getCurrentMax() {
		//This and current min should now be correct iff 
		//STLObject getMin/getMax functions work
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		
		//Point3f currMax = null;
		
		STLObject transformedObj = theSTLObject.getTransformedSTLObject(temp);
		return transformedObj.getMax();
		
		/*
		for(STLFacet fac:theSTLObject){
			Point3f candidate = fac.getMax();
			temp.transform(candidate);
			if(currMax==null) currMax = candidate;
			else currMax.set(Math.max(currMax.x,candidate.x),Math.max(currMax.y,candidate.y),Math.max(currMax.z,candidate.z));			
		}					
		
		return currMax;*/
	}
	
	/**
	 * Returns current average of coordinates given
	 * current transforms
	 * @return max
	 */
	public Point3f getCurrentCenter(){
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		
		//Point3f currMax = null;
		System.out.println(theSTLObject);
		STLObject transformedObj = theSTLObject.getTransformedSTLObject(temp);
		return transformedObj.getCenter();
		/*
		Point3f center = getBaseCenter();
		Point3f cent2 = new Point3f();
		cent2.add(center);
		
		
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		temp.transform(cent2);	
						
		return cent2;
		*/
	}

	/**
	 * Returns average of coordinates as the center ignoring 
	 * any transforms
	 * @return center
	 */
	public Point3f getBaseCenter() {				
		return theSTLObject.getCenter();
	}

	/**
	 * Determines whether model is contained completely inside given 
	 * workspace
	 * @param theWorkspace
	 * @return 
	 */
	public boolean modelIsInWorkspace(STLWorkspaceBranchGroup theWorkspace) {
		
		if(theWorkspace==null) return false;
		
		Transform3D curr = new Transform3D();
		getTransform(curr);
			
		return theWorkspace.stlIsContained(theSTLObject.getTransformedSTLObject(curr));
		
	}

	// TODO currently tries to erase rotations without erasing translations
	public void pointNormalDown(Vector3d normal) {
		Transform3D curr = new Transform3D();
		getTransform(curr);

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
		System.out.println(getCurrentMax());

		alertListenersModelMoved();
	}
	
	// Model transform functions
	
	public void rotateX(double rad) {
		Transform3D curr = new Transform3D();
		getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotX(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		alertListenersModelMoved();
	}
	
	public void rotateY(double rad) {
		Transform3D curr = new Transform3D();
		getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotY(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		alertListenersModelMoved();
	}
	
	public void rotateZ(double rad) {
		
		Transform3D curr = new Transform3D();
		getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotZ(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		alertListenersModelMoved();
		
	}

	/*
	// TODO this is a bit more complicated than originally thought
	// Need to correct for both camera angle as well as previous transforms
	// hopefully should be as simple as offsetting currentAngle variable
	public void rotateUpDown(double rad) {
		
		Transform3D curr = this.getTransform3D();

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
		 
		updateIndicatorLightColor();
	}
	*/

	public void resetModelTransforms() {
		Transform3D blank = new Transform3D();
		this.setTransform(blank);
		
		//centerOnWorkspace();

		alertListenersModelMoved();
		
	}

	private void alertListenersModelMoved() {
			for(STLTransformGroupListener l:theListeners){
				l.alertSTLTransformMoved(this);
			}
	}

	public void centerOnWorkspace(STLWorkspaceBranchGroup theWorkspace) {
		double transY = theWorkspace.getSurfaceY()-this.getCurrentMin().y;
		

		System.out.println("Trans Y "+transY);
		System.out.println("Curr min "+this.getCurrentMin());
		System.out.println("Surface y: "+theWorkspace.getSurfaceY());
		
		translate(new  Vector3d(0,transY,0));
	}

	public void translate(Vector3d tran) {
		Transform3D temp = new Transform3D();
		Transform3D temp2 = new Transform3D();
		
		this.getTransform(temp2);
		
		temp.setTranslation(tran);
		temp2.mul(temp);
		this.setTransform(temp2);
		
		alertListenersModelMoved();
	}
	
	/**
	 * Translates group along x-axis while correcting for
	 * possible rotations that may have been previously applied 
	 * @param dist
	 */
	public void translateLeftRight(double dist) {
				
		Vector3d tran = new Vector3d(1, 0, 0);
		Transform3D curr = new Transform3D();
		getTransform(curr);
		// curr.setTranslation(new Vector3d(0,0,0));
		curr.invert();
		curr.transform(tran);
		tran.normalize();

		//Vector3d camVec = new Vector3d(camD.getCameraPosition());
		//camVec.sub(camD.getCameraDirection());
		//camVec.cross(camVec, camD.getCameraOrientation());

		// curr.invert();
		//curr.transform(camVec);
		//camVec.normalize();

		tran.scale(dist);
		//camVec.scale(-d);
		// System.out.println(tran);
		translate(tran);
		// translate(camVec);
	}

	/**
	 * Translates group along y-axis while correcting for
	 * possible rotations that may have been previously applied 
	 * @param dist
	 */
	public void translateUpDown(double dist) {
		Vector3d tran = new Vector3d(0, -1, 0); // For some reason -1 makes this
												// work
		Transform3D curr = new Transform3D();
		getTransform(curr);
		// curr.setTranslation(new Vector3d(0,0,0));
		curr.invert();
		curr.transform(tran);
		tran.normalize();
		tran.scale(dist);
		// System.out.println(tran);
		translate(tran);
	}

	/**
	 * Translates group along z-axis while correcting for
	 * possible rotations that may have been previously applied 
	 * @param dist
	 */
	public void translateBackForth(double dist) {
		Vector3d tran = new Vector3d(0, 0, 1);
		Transform3D curr = new Transform3D();
		getTransform(curr);
		// curr.setTranslation(new Vector3d(0,0,0));
		curr.invert(); // THis works but I really don't know why
		curr.transform(tran);
		tran.normalize();
		tran.scale(dist);
		// System.out.println(tran);
		translate(tran);
	}

	/**
	 * Translates group laterally in direction orthogonal to 
	 * camera direction and orientation
	 * @param dist
	 * @param prev
	 */
	public void translateLateral(double dist, STLPreviewCanvas3D prev) {

		Transform3D curr = new Transform3D();
		getTransform(curr);

		Vector3d camVec = new Vector3d(prev.getCameraPosition());
		camVec.sub(prev.getCameraDirection());
		camVec.cross(camVec, prev.getCameraOrientation()); 
		
		curr.invert();
		curr.transform(camVec);
		camVec.normalize();

		camVec.scale(-dist);

		translate(camVec);

	}

	
	public void setIndicatorLightColor(Color3f color3f) {
		indicatorLight.setColor(color3f);
	}

	

}
