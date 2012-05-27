package com.neuronrobotics.replicator.gui.stl;

import javax.media.j3d.Appearance;
import javax.media.j3d.GeometryArray;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Point3f;

public class STLTransformGroup extends TransformGroup{
	
	private Shape3D theModel, theOutline;
	
	private Point3f max, min;
	
	public STLTransformGroup(){
		super();
		//this.setCapability(ALLOW_CHILDREN_EXTEND); TODO add children on the fly?
		theModel = null;
		theOutline = null;
		max = null;
		min = null;
	}

	public void setModel(Shape3D newModel){
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
		
		max = null;
		min = null;
	}
	
	//TODO should combine with above
	public void setOutline(Shape3D newOutline){
		if(theOutline!=null) this.removeChild(theOutline);
		this.theOutline = newOutline;
		
		Appearance app;	
		RenderingAttributes ra;
		if(theOutline.getAppearance()==null) app = new Appearance();
		else app = theOutline.getAppearance();
		if(theOutline.getAppearance().getRenderingAttributes()==null) ra = new RenderingAttributes();
		else ra = theOutline.getAppearance().getRenderingAttributes();
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_WRITE);
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ);
		app.setRenderingAttributes(ra);
		theOutline.setAppearance(app);
				
		this.addChild(theOutline);
		
		max = null;
		min = null;
	}
	
	
	
	public Shape3D getModel(){		
		return theModel;
	}
	
	public Shape3D getOutline(){
		return theOutline;
	}
	
	public void setModelVisibility(boolean visible){
		theModel.getAppearance().getRenderingAttributes().setVisible(visible);
	}
	
	public void setOutlineVisibility(boolean visible){
		theOutline.getAppearance().getRenderingAttributes().setVisible(visible);	
	}
	
	public boolean getModelVisibility(){
		return theModel.getAppearance().getRenderingAttributes().getVisible();
	}
	
	public boolean getOutlineVisibility(){
		return theOutline.getAppearance().getRenderingAttributes().getVisible();
	}

	public Point3f getBaseMax(){
		if (max!=null) return max;
		max = new Point3f(0f,0f,0f);
		GeometryArray ga = (GeometryArray)(theModel.getGeometry());
		int vc = ga.getVertexCount();
		Point3f tempCoord = new Point3f(0f,0f,0f);
		for(int i=0;i<vc;i++){
			ga.getCoordinate(i,tempCoord);
			if(tempCoord.x>max.x) max.set(tempCoord.x,max.y,max.z);
			if(tempCoord.y>max.y) max.set(max.x,tempCoord.y,max.z);
			if(tempCoord.z>max.z) max.set(max.x,max.y,tempCoord.z);
		}
		return max;
	}
	
	public Point3f getBaseMin(){
		if (min!=null) return min;
		min = new Point3f(0f,0f,0f);
		GeometryArray ga = (GeometryArray)(theModel.getGeometry());
		int vc = ga.getVertexCount();
		Point3f tempCoord = new Point3f(0f,0f,0f);
		for(int i=0;i<vc;i++){
			ga.getCoordinate(i,tempCoord);
			if(tempCoord.x<min.x) min.set(tempCoord.x,min.y,min.z);
			if(tempCoord.y<min.y) min.set(min.x,tempCoord.y,min.z);
			if(tempCoord.z<min.z) min.set(min.x,min.y,tempCoord.z);
		}
		return min;
	}
	
	@Override
	public void setTransform(Transform3D transform){
		super.setTransform(transform);
	}
	
	public Point3f getCurrentMin() {

		if (min == null)
			this.getBaseMin();

		Transform3D currT = new Transform3D();
		this.getTransform(currT);

		Point3f currMin = new Point3f(min);
		currT.transform(currMin); //TODO have to actually go through everything again

		return currMin;
	}
	
	public Point3f getCurrentMax() {

		if (max == null)
			this.getBaseMax();

		Transform3D currT = new Transform3D();
		this.getTransform(currT);

		Point3f currMax = new Point3f(max);
		currT.transform(currMax);
		
		return currMax;
	}
	
	public Point3f getCurrentCenter(){
				
		Point3f currMin = getCurrentMin();
		Point3f currMax = getCurrentMax();
		
		float x = (currMax.x-currMin.x)/2;
		float y = (currMax.y-currMin.y)/2;
		float z = (currMax.z-currMin.z)/2;
		
		
		return new Point3f(x,y,z);
	}

	public Point3f getBaseCenter() {
		Point3f baseMin = getBaseMin();
		Point3f baseMax = getBaseMax();
		
		float x = (baseMax.x-baseMin.x)/2;
		float y = (baseMax.y-baseMin.y)/2;
		float z = (baseMax.z-baseMin.z)/2;
		
		
		return new Point3f(x,y,z);
	}
	

}
