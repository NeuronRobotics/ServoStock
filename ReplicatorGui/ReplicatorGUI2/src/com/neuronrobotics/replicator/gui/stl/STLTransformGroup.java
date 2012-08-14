package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;

import javax.media.j3d.Appearance;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;

import com.neuronrobotics.replicator.gui.preview.STLPreviewCameraData;
import com.neuronrobotics.replicator.gui.preview.STLPreviewCanvas3D;
import com.sun.j3d.utils.picking.PickTool;

public class STLTransformGroup extends TransformGroup{
	
	private STLObject theSTLObject;
	
	private Shape3D theModel, theFacetOutline;
	
	private ArrayList<STLTransformGroupListener> theListeners;
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline){
		super();
		//this.setCapability(ALLOW_CHILDREN_EXTEND); TODO add children on the fly?
		setModel(model);
		setOutline(outline);
		theSTLObject = stlo;
		theListeners = new ArrayList<STLTransformGroupListener>();
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
	
	/*
	private void setModel(STLObject theSTL, Shape3D newModel, Shape3D newOutline){
		
		theSTLObject = theSTL;
		setModel(newModel);
		setOutline(newOutline);
		
	}*/
	
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

	public Point3f getBaseMax(){
		return theSTLObject.getMax();
	}
	
	public Point3f getBaseMin(){
		return theSTLObject.getMin();
	}
	
	@Override
	public void setTransform(Transform3D transform){
		super.setTransform(transform);
	}
	
	public Point3f getCurrentMin() {
		
		//TODO this is probably wrong
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
	}
	
	public Point3f getCurrentMax() {
		
		//TODO this is wrong
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		
		Point3f currMax = null;
		
		for(STLFacet fac:theSTLObject){
			Point3f candidate = fac.getMax();
			temp.transform(candidate);
			if(currMax==null) currMax = candidate;
			else currMax.set(Math.max(currMax.x,candidate.x),Math.max(currMax.y,candidate.y),Math.max(currMax.z,candidate.z));			
		}					
		
		return currMax;
	}
	
	public Point3f getCurrentCenter(){
				
		Point3f center = getBaseCenter();
		Point3f cent2 = new Point3f();
		cent2.add(center);
		
		
		Transform3D temp = new Transform3D();
		this.getTransform(temp);
		temp.transform(cent2);	
						
		return cent2;
	}

	public Point3f getBaseCenter() {				
		return theSTLObject.getCenter();
	}

	public boolean modelIsInWorkspace(STLWorkspaceBranchGroup theWorkspace) {
		
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
		Transform3D curr = getTransform3D();

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
		Transform3D curr = this.getTransform3D();

		Transform3D temp = new Transform3D();
		temp.rotX(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		alertListenersModelMoved();
	}

	
	public void rotateY(double rad) {
		Transform3D curr = getTransform3D();

		Transform3D temp = new Transform3D();
		temp.rotY(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		alertListenersModelMoved();
	}

	
	public void rotateZ(double rad) {
		
		Transform3D curr = getTransform3D();

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
		
		translateY(transY);
	}

	public void translate(Vector3d tran) {
		Transform3D temp = new Transform3D();
		Transform3D temp2 = new Transform3D();
		
		this.getTransform(temp2);
		
		temp.setTranslation(tran);
		temp2.mul(temp);// TODO
		this.setTransform(temp2);
		
		alertListenersModelMoved();
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

		//Vector3d camVec = new Vector3d(camD.getCameraPosition());
		//camVec.sub(camD.getCameraDirection());
		//camVec.cross(camVec, camD.getCameraOrientation()); //TODO test

		// curr.invert();
		//curr.transform(camVec);
		//camVec.normalize();

		tran.scale(d);
		//camVec.scale(-d);
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

	public void translateLateral(double d, STLPreviewCanvas3D prev) {

		Transform3D curr = this.getTransform3D();

		Vector3d camVec = new Vector3d(prev.getCameraPosition());
		camVec.sub(prev.getCameraDirection());
		camVec.cross(camVec, prev.getCameraOrientation()); //TODO test

		curr.invert();
		curr.transform(camVec);
		camVec.normalize();

		camVec.scale(-d);

		translate(camVec);

	}

	public Transform3D getTransform3D() {
		Transform3D tran = new Transform3D();
		this.getTransform(tran);
		return tran;
	}
	
}
