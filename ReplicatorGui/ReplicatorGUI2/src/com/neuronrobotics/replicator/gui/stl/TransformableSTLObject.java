package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Iterator;

import javax.vecmath.Point3f;

public class TransformableSTLObject extends STLObject {

	private GeneralTransform3D currentTransform = new Transform3DAdapter();
	private Point3f transformedMin=null, transformedMax=null, transformedCenter=null;
	
	public TransformableSTLObject(STLObject stlo, GeneralTransform3D currT){
		this(stlo);
		currentTransform=currT;
	}
	
	public TransformableSTLObject(String name, ArrayList<STLFacet> facets) {
		super(name, facets);
	}
	
	public TransformableSTLObject(STLObject stlO){
		super(stlO.getName(),stlO.theFacets);
	}
	
	public void setTransform(GeneralTransform3D gt){
		currentTransform = gt;
		transformedMin = transformedCenter = transformedMax = null;
	}
	
	@Override
	public Iterator<STLFacet> iterator() {
		return new Transformerator(super.iterator());
	}
	
	@Override
	public Point3f getMin() {
		if (this.transformedMin == null) {
			calcMaxMin();
		}
		return transformedMin;

	}

	@Override
	public Point3f getMax() {
		if (this.transformedMin == null) {
			calcMaxMin();
		}
		return transformedMax;

	}

	@Override
	public Point3f getCenter() {
		if (this.transformedMin == null) {
			calcMaxMin();
		}
		return transformedCenter;

	}
	
	private void calcMaxMin(){
		transformedCenter = null;
		transformedMin = null;
		transformedMax = null;
		for(STLFacet fac:this){
			Point3f facMin = fac.getMin();
			Point3f facMax = fac.getMax();
			if(transformedMin==null){
				transformedMin = new Point3f(facMin);
				transformedMax = new Point3f(facMax);
				continue;
			}
			if(facMin.x<transformedMin.x) transformedMin.x = facMin.x;
			if(facMin.y<transformedMin.y) transformedMin.y = facMin.y;
			if(facMin.z<transformedMin.z) transformedMin.z = facMin.z;
			if(facMax.x>transformedMax.x) transformedMax.x = facMax.x;
			if(facMax.y>transformedMax.y) transformedMax.y = facMax.y;
			if(facMax.z>transformedMax.z) transformedMax.z = facMax.z;
			transformedCenter = new Point3f(transformedMax);
			transformedCenter.add(transformedMin);
			transformedCenter.scale(0.5f);
		}
	}
	
	private class Transformerator implements Iterator<STLFacet>{

		Iterator<STLFacet> baseIterator;
		
		private Transformerator(Iterator<STLFacet> baseIt){
			baseIterator = baseIt;
		}
		
		@Override
		public boolean hasNext() {
			return baseIterator.hasNext();
		}

		@Override
		public STLFacet next() {
			STLFacet nxt = baseIterator.next();
			Point3f v1 = nxt.getVertex1(), v2 = nxt.getVertex2(), v3 = nxt.getVertex3();
			currentTransform.transform(v1);
			currentTransform.transform(v2);
			currentTransform.transform(v3);
			return new STLFacet(v1,v2,v3);
		}

		@Override
		public void remove() {
			baseIterator.remove();
		}
		
	}
	
	public STLObject getTransformedSTLObject() {
		return super.getTransformedSTLObject(currentTransform);
	}

	
}
