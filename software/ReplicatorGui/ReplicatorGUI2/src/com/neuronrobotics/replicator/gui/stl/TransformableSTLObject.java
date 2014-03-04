package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;

import com.neuronrobotics.replicator.gui.preview.TransformableSTLObjectListener;

public class TransformableSTLObject extends STLObject {

	private GeneralTransform3D currentTransform = new DefaultGeneralTransform3D(new double[]{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1});
	private STLObject baseSTLObject;
	private ArrayList<TransformableSTLObjectListener> theListeners = new ArrayList<TransformableSTLObjectListener>();
	
	public TransformableSTLObject(String name, ArrayList<STLFacet> facets) {
		this(new STLObject(name,facets));
	}
	
	public TransformableSTLObject(STLObject stlo){
		super(stlo.getName(),stlo.clone().theFacets);
		baseSTLObject = stlo;
	}
	
	public TransformableSTLObject(STLObject stlo, GeneralTransform3D currTransform){
		this(stlo);
		this.setTransform(currTransform);
	}
	
	public void setTransform(GeneralTransform3D newTransform){
		currentTransform = newTransform;
		for(STLFacet fac:this){
			if(!fac.acceptTransform(newTransform)){
				fac.setAllowTransforms(true);
				fac.acceptTransform(newTransform);
			}
		}
		this.calcMaxMin();
		
		fireTransformChanged();
	}
	
	public STLObject getBaseSTLOject(){
		return this.baseSTLObject;
	}
	
	public GeneralTransform3D getCurrentTransform(){
		return this.currentTransform;
	}
	
	public void addTransformableSTLObjectListener(TransformableSTLObjectListener newL){
		theListeners.add(newL);
	}
	
	public void removeTransformableSTLObjectListener(TransformableSTLObjectListener newL){
		theListeners.remove(newL);
	}
	
	private void fireTransformChanged(){
		for(TransformableSTLObjectListener l:theListeners){
			l.alertTransformChanged(baseSTLObject, currentTransform);
		}
	}
	
}
