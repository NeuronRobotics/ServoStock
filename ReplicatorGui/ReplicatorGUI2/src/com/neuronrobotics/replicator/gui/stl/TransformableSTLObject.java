package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Iterator;

import javax.vecmath.Point3f;

import com.neuronrobotics.replicator.gui.preview.j3d.GeneralTransform3DJava3DAdapter;

public class TransformableSTLObject extends STLObject {

	private GeneralTransform3D currentTransform = new GeneralTransform3DJava3DAdapter();
	private STLObject baseSTLObject;
	
	
	public TransformableSTLObject(String name, ArrayList<STLFacet> facets) {
		super(name, facets);
		baseSTLObject = this.clone();
	}
	
	public TransformableSTLObject(STLObject stlo){
		this(stlo.getName(),stlo.clone().theFacets);
		baseSTLObject = stlo;
	}
	
	public TransformableSTLObject(STLObject stlo, GeneralTransform3D currTransform){
		this(stlo);
		this.setTransform(currTransform);
	}
	
	public void setTransform(GeneralTransform3D newTransform){
		currentTransform = newTransform;
	}
	
	
	
}
