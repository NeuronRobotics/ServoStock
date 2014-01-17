package com.neuronrobotics.replicator.gui.preview.j3d;

import java.awt.Color;
import java.util.ArrayList;

import javax.media.j3d.Appearance;
import javax.media.j3d.Material;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Matrix3f;
import javax.vecmath.Point3f;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.TransformableSTLObject;
import com.sun.j3d.utils.picking.PickTool;

public class STLTransformGroup extends TransformGroup{
	
	// fields	
	private STLObject theBaseSTLObject;
	private TransformableSTLObject theTransformableSTLObject;
	private Shape3D theModel, theFacetOutline;
	private ArrayList<STLTransformGroupListener> theListeners;
		
	private boolean isHilighted;
				
	// constructor(s)
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline){
		super();
		setModel(model);
		setOutline(outline);
		this.setOutlineVisibility(false);
				
		theBaseSTLObject = stlo;
		theTransformableSTLObject = new TransformableSTLObject(stlo);
		theListeners = new ArrayList<STLTransformGroupListener>();
		
		isHilighted = false;
						
	}
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline, STLWorkspaceBranchGroup workspace){
		this(stlo,model,outline);
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
	
	//public methods
	
	public void setTransform(Transform3D newTran){
		super.setTransform(newTran);
		//this.transformedSTLObject=theBaseSTLObject.getTransformedSTLObject(new Transform3DAdapter(newTran));
		this.theTransformableSTLObject.setTransform(new GeneralTransform3DJava3DAdapter(newTran));
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
		return this.theTransformableSTLObject.getMin();
	}
	
	/**
	 * Returns current maxima coordinates given
	 * current transforms
	 * @return max
	 */
	public Point3f getCurrentMax() {	
		return this.theTransformableSTLObject.getMax();
	}
	
	/**
	 * Returns current average of coordinates given
	 * current transforms
	 * @return max
	 */
	public Point3f getCurrentCenter(){
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

	public void resetModelTransforms() {
		Transform3D blank = new Transform3D();
		this.setTransform(blank);		
	}

	private void alertListenersModelMoved() {
			for(STLTransformGroupListener l:theListeners){
				l.alertSTLTransformMoved(this);
			}
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
		return this.getSTLObject().getTransformedSTLObject(new GeneralTransform3DJava3DAdapter(tran));
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
			stlClone = stlClone.getTransformedSTLObject(new GeneralTransform3DJava3DAdapter(justOrient));
		}		
		Shape3D dupModel = STLShape3DFactory.getModelShape3D(stlClone);
		Shape3D dupOutline = STLShape3DFactory.getFacetOutline(stlClone);
		return new STLTransformGroup(stlClone, dupModel, dupOutline);
	}
		
	public boolean isHilighted(){
		return isHilighted;
	}
	
}
