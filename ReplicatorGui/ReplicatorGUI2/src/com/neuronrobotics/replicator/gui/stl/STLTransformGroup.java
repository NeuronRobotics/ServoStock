package com.neuronrobotics.replicator.gui.stl;

import java.awt.Color;
import java.util.ArrayList;
import java.util.Iterator;

import javax.media.j3d.Appearance;
import javax.media.j3d.Material;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.AxisAngle4f;
import javax.vecmath.Color3f;
import javax.vecmath.Matrix3f;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.preview.STLPreviewCanvas3D;
import com.sun.j3d.utils.picking.PickTool;

public class STLTransformGroup extends TransformGroup{
	
	// fields
	
	private STLObject theBaseSTLObject;
	private TransformableSTLObject theTransformableSTLObject;
	private Shape3D theModel, theFacetOutline;
	private ArrayList<STLTransformGroupListener> theListeners;
	
	private Iterator<STLFace> objectFaces;
	private Iterator<Vector3f> uniqueNormals;
	
	private STLFace currFace;
	
	private boolean isHilighted;
				
	// constructor(s)
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline){
		super();
		setModel(model);
		setOutline(outline);
		this.setOutlineVisibility(false);
		
		objectFaces = null;
		
		theBaseSTLObject = stlo;
		theTransformableSTLObject = new TransformableSTLObject(stlo);
		theListeners = new ArrayList<STLTransformGroupListener>();
		
		isHilighted = false;
						
	}
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline, STLWorkspaceBranchGroup workspace){
		this(stlo,model,outline);
		updateIndicatorLightBounds();
	}
	
	public void addListener(STLTransformGroupListener newListener){
		theListeners.add(newListener);
	}

	// private methods
	
	private void setModel(Shape3D newModel){
		if(theModel!=null) this.removeChild(theModel);
		this.theModel = newModel;
		
		Appearance app;	
		RenderingAttributes ra;
		if(theModel.getAppearance()==null) {
			app = new Appearance();
			theModel.setAppearance(app);
		}
		else app = theModel.getAppearance();
		if(theModel.getAppearance().getRenderingAttributes()==null) ra = new RenderingAttributes();
		else ra = theModel.getAppearance().getRenderingAttributes();
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_WRITE);
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ);
		app.setRenderingAttributes(ra);
		//theModel.setAppearance(app);
			
		Material mat = new Material();
		mat.setAmbientColor(new Color3f(Color.BLACK));
		mat.setDiffuseColor(new Color3f(0.1f,0.1f,0.1f));
		mat.setSpecularColor(new Color3f(0.5f,0.5f,0.5f));
		mat.setShininess(128);
		
		mat.setCapability(Material.ALLOW_COMPONENT_READ);
		mat.setCapability(Material.ALLOW_COMPONENT_WRITE);
		
		app.setMaterial(mat);
		
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
		if(theFacetOutline.getAppearance()==null){
			app = new Appearance();
			theFacetOutline.setAppearance(app);
		}
		else app = theFacetOutline.getAppearance();
		if(theFacetOutline.getAppearance().getRenderingAttributes()==null) ra = new RenderingAttributes();
		else ra = theFacetOutline.getAppearance().getRenderingAttributes();
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_WRITE);
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ);
		app.setRenderingAttributes(ra);
		//theFacetOutline.setAppearance(app);
				
		this.addChild(theFacetOutline);
		
	}
	
	private void updateIndicatorLightBounds() {
		//Point3d cent = new Point3d(this.getCurrentCenter());		
		//directionalLight1.setBounds(new BoundingSphere(cent,1));
		
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
		//this.transformedSTLObject=theBaseSTLObject.getTransformedSTLObject(new Transform3DAdapter(newTran));
		this.theTransformableSTLObject.setTransform(new Transform3DAdapter(newTran));
		this.alertListenersModelMoved(); //Shouldn't call this anywhere else
	}
	
	public Shape3D getModel(){		
		return theModel;
	}
	
	public Shape3D getOutline(){
		return theFacetOutline;
	}
	
	public STLObject getSTLObject(){
		return theBaseSTLObject;
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
		return theBaseSTLObject.getMax();
	}
	
	/**
	 * Returns base min of coordinates ignoring
	 * current transforms
	 * @return min
	 */
	public Point3f getBaseMin(){
		return theBaseSTLObject.getMin();
	}
		
	/**
	 * Returns current minima of coordinates given
	 * current transforms
	 * @return min
	 */
	public Point3f getCurrentMin() {
		//return this.transformedSTLObject.getMin();
		return this.theTransformableSTLObject.getMin();
	}
	
	/**
	 * Returns current maxima coordinates given
	 * current transforms
	 * @return max
	 */
	public Point3f getCurrentMax() {
		//return this.transformedSTLObject.getMax();	
		return this.theTransformableSTLObject.getMax();
	}
	
	/**
	 * Returns current average of coordinates given
	 * current transforms
	 * @return max
	 */
	public Point3f getCurrentCenter(){
		//return transformedSTLObject.getCenter();
		return this.theTransformableSTLObject.getCenter();
	}

	/**
	 * Returns average of coordinates as the center ignoring 
	 * any transforms
	 * @return center
	 */
	public Point3f getBaseCenter() {				
		return theBaseSTLObject.getCenter();
	}
	
	// Model transform functions
	
	public void rotateX(double rad) {
		Transform3D curr = new Transform3D();
		getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotX(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		//alertListenersModelMoved();
	}
	
	public void rotateY(double rad) {
		Transform3D curr = new Transform3D();
		getTransform(curr);
				
		Transform3D temp = new Transform3D();
				
		temp.rotY(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		//alertListenersModelMoved();
	}
	
	public void rotateZ(double rad) {
		
		Transform3D curr = new Transform3D();
		getTransform(curr);

		Transform3D temp = new Transform3D();
		temp.rotZ(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
		//alertListenersModelMoved();
		
	}

	public void rotateAroundUpVector(double rad){
		Transform3D curr = new Transform3D();
		getTransform(curr);

		Vector3f up;
		if(currFace!=null){
			up = currFace.getNormal();
		}else{ 
			up = new Vector3f(0,1,0);
		}
		
		Transform3D temp = new Transform3D();
		
		AxisAngle4f axAngRot = new AxisAngle4f(up, (float)rad);
		temp.setRotation(axAngRot);
		
		//temp.rotY(rad);
		curr.mul(temp);
		this.setTransform(curr);
		
	}

	public void resetModelTransforms() {
		Transform3D blank = new Transform3D();
		this.setTransform(blank);
		
		//centerOnWorkspace();

		//alertListenersModelMoved();
		
	}

	private void alertListenersModelMoved() {
			for(STLTransformGroupListener l:theListeners){
				l.alertSTLTransformMoved(this);
			}
	}

	public void centerOnWorkspace(STLWorkspaceObject theWorkspace) {
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
		
		//alertListenersModelMoved();
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
	
	public void setDiffuseLightColor(Color3f color3f) {
		Material mat = theModel.getAppearance().getMaterial();//.setDiffuseColor(color3f);
		mat.setAmbientColor(color3f);
	}
	
	public void setHighlighted(boolean hi){		
		isHilighted = hi;
		Color3f newColor = (hi) ? new Color3f(0.5f,0.5f,0.5f):new Color3f(0.1f,0.1f,0.1f);
		theModel.getAppearance().getMaterial().setDiffuseColor(newColor);
	}
	
	public STLObject getTransformedSTLObject() {
		Transform3D tran = new Transform3D();
		this.getTransform(tran);		
		return this.getSTLObject().getTransformedSTLObject(new Transform3DAdapter(tran));
		//return this.theTransformableSTLObject.getTransformedSTLObject();
	}

	public STLTransformGroup getDuplicate(boolean retainOrientation){
		STLObject stlClone = theBaseSTLObject.clone();
		if(retainOrientation){
			Transform3D tran = new Transform3D();
			this.getTransform(tran);
			Transform3D justOrient = new Transform3D();
			Matrix3f mat = new Matrix3f();
			tran.get(mat);
			justOrient.set(mat);
			stlClone = stlClone.getTransformedSTLObject(new Transform3DAdapter(justOrient));
		}		
		Shape3D dupModel = STLShape3DFactory.getModelShape3D(stlClone);
		Shape3D dupOutline = STLShape3DFactory.getFacetOutline(stlClone);
		return new STLTransformGroup(stlClone, dupModel, dupOutline);
	}
		
	public boolean isHilighted(){
		return isHilighted;
	}
	
	public void reorientToNextNormal(){
		if(uniqueNormals==null||!uniqueNormals.hasNext()){
			uniqueNormals = theBaseSTLObject.getNormalIterator();
		}
		Vector3f currNorm = uniqueNormals.next();
		AxisAngle4f rotAxAng = getRotationDown(currNorm);
		
		System.out.println("Curr norm: "+currNorm);
		System.out.println("RotAx: "+rotAxAng);
				
		Transform3D newt = new Transform3D();
		this.getTransform(newt);
		newt.setRotation(rotAxAng);
					
		this.setTransform(newt);		
	}
	
	public void reorientToNextFace(){
		do{
		if(objectFaces==null||!objectFaces.hasNext()){
			objectFaces = theBaseSTLObject.getFaceIterator();
		}
			
		currFace = objectFaces.next();
		AxisAngle4f rotAxAng = getRotationDown(currFace.getNormal());
		
		
		Transform3D newt = new Transform3D();
		this.getTransform(newt);
		newt.setRotation(rotAxAng);
					
		this.setTransform(newt);	
		Point3f facP = currFace.iterator().next().getVertex1();
		newt.transform(facP);
		if(facP.y<=this.getCurrentMin().y+0.0001f) break;
		}while(true);
	}
	
	public AxisAngle4f getRotationDown(Vector3f someNormal){
				
		float epsilon = 0.0001f;
		
		Vector3f curr = new Vector3f(someNormal);
		Vector3f down = new Vector3f(0,-1,0);
		curr.normalize();
		down.normalize();
		
		Vector3f up = new Vector3f(0,1,0);
		
		
		if(curr.epsilonEquals(down, epsilon)){
			return new AxisAngle4f();
		} else if(curr.epsilonEquals(up, epsilon)){
			return new AxisAngle4f(1f,0f,0f,(float)Math.PI);
		}
		
		Vector3f rotVec = new Vector3f();
		rotVec.cross(curr, down);
		rotVec.normalize();
		
		float angle = curr.angle(down);
		
		AxisAngle4f rotAxAng = new AxisAngle4f(rotVec.x,rotVec.y,rotVec.z,angle);
		
		if(Double.isNaN(rotVec.x)){
			System.out.println("Curr "+curr);
			System.out.println("down: "+down);
		}
		
		return rotAxAng;
	}
	
}
