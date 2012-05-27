package com.neuronrobotics.replicator.gui.stl;

import javax.media.j3d.Appearance;
import javax.media.j3d.RenderingAttributes;
import javax.media.j3d.Shape3D;
import javax.media.j3d.TransformGroup;

public class STLTransformGroup extends TransformGroup{
	
	private Shape3D theModel, theOutline;
	
	public STLTransformGroup(){
		super();
		//this.setCapability(ALLOW_CHILDREN_EXTEND); TODO add children on the fly?
		theModel = null;
		theOutline = null;
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
	}
	
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

}
