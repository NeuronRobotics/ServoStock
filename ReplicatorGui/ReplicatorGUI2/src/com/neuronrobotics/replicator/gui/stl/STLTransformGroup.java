package com.neuronrobotics.replicator.gui.stl;

import javax.media.j3d.Appearance;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Point3f;

public class STLTransformGroup extends TransformGroup{
	
	private STLObject theSTLObject;
	
	private Shape3D theModel, theFacetOutline;
	
	public STLTransformGroup(STLObject stlo, Shape3D model, Shape3D outline){
		super();
		//this.setCapability(ALLOW_CHILDREN_EXTEND); TODO add children on the fly?
		setModel(model);
		setOutline(outline);
		theSTLObject = stlo;
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
	
	public void setModel(STLObject theSTL, Shape3D newModel, Shape3D newOutline){
		
		theSTLObject = theSTL;
		setModel(newModel);
		setOutline(newOutline);
		
	}
	
	public Shape3D getModel(){		
		return theModel;
	}
	
	public Shape3D getOutline(){
		return theFacetOutline;
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


}
