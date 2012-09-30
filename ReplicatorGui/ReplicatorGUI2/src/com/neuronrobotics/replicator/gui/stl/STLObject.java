package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import javax.vecmath.*;

public class STLObject implements Iterable<STLFacet> {

	private String name;
	protected ArrayList<STLFacet> theFacets;

	private Point3f center;
	private Point3f min, max;

	private ArrayList<STLFace> theFaces;
	private boolean facesAnalyzed;
	
	private ArrayList<Vector3f> uniqueNormals;
	
	public static STLObject getMergedSTLObject(String name,
			Collection<STLObject> theObjects) {
		ArrayList<STLFacet> newList = new ArrayList<STLFacet>();
		for(STLObject curr:theObjects){
			newList.addAll(curr.theFacets);
		}
		
		return new STLObject(name,newList);
	}
	
	public static STLObject getMergedSTLObject(String name, STLObject... theObjects){
		ArrayList<STLFacet> newList = new ArrayList<STLFacet>();
		for(STLObject curr:theObjects){
			newList.addAll(curr.theFacets);
		}
		
		return new STLObject(name,newList);
	}
	
	public STLObject(String name, ArrayList<STLFacet> facets) {
		this.name = name;
		this.theFacets = facets;
		this.center = null;
		this.min = null;
		this.max = null;
		this.theFaces = new ArrayList<STLFace>();
		uniqueNormals = null;
	}

	public int getFacetAmount() {
		return theFacets.size();
	}

	public Point3f getCenter() {
		if (center == null){
		int numVertices = theFacets.size() * 3;
		float xSum = 0, ySum = 0, zSum = 0;
		for (STLFacet sf : theFacets) {
			xSum += sf.getVertex1().x / numVertices;
			xSum += sf.getVertex2().x / numVertices;
			xSum += sf.getVertex3().x / numVertices;
			ySum += sf.getVertex1().y / numVertices;
			ySum += sf.getVertex2().y / numVertices;
			ySum += sf.getVertex3().y / numVertices;
			zSum += sf.getVertex1().z / numVertices;
			zSum += sf.getVertex2().z / numVertices;
			zSum += sf.getVertex3().z / numVertices;
		}
		center = new Point3f(xSum, ySum, zSum);
		}
		
		return new Point3f(center);
	}

	public float getXLength() {
		if (max == null || min == null)
			calcMaxMin();
		return max.x - min.x;
	}

	public float getYLength() {
		if (max == null || min == null)
			calcMaxMin();
		return max.y - min.y;
	}

	public float getZLength() {
		if (max == null || min == null)
			calcMaxMin();
		return max.z - min.z;
	}

	public String getName() {
		return name;
	}

	public Point3f getMax() {
		if (max == null)
			calcMaxMin();
		return new Point3f(max);
	}

	private void calcMaxMin() {
		
		max = null;
		min = null;
		for (STLFacet fac : this) {

			Point3f candMax = fac.getMax();
			Point3f candMin = fac.getMin();
			if (max != null) {
				max.set(Math.max(candMax.x, max.x), Math.max(candMax.y, max.y),
						Math.max(candMax.z, max.z));
				min.set(Math.min(candMin.x, min.x), Math.min(candMin.y, min.y),
						Math.min(candMin.z, min.z));
			} else {
				max = new Point3f(candMax);
				min = new Point3f(candMin);
			}
		}

	}

	public Point3f getMin() {
		if (min == null)
			calcMaxMin();
		return new Point3f(min);
	}

	@Override
	public String toString() {
		String res = "";
		res += "Name: " + this.name + "\n";
		return res;
	}

	@Override
	public Iterator<STLFacet> iterator() {
		return theFacets.iterator();
	}

	public Iterator<STLFace> getFaceIterator() {
		if (!facesAnalyzed)
			calculateFaces();
		return theFaces.iterator();
	}

	public STLObject getTransformedSTLObject(GeneralTransform3D tran) {

		String newName = this.name + "Transformed";

		ArrayList<STLFacet> newFacetList = new ArrayList<STLFacet>();
		for (STLFacet f : this) {
			Point3f temp1 = f.getVertex1();
			tran.transform(temp1);
			Point3f temp2 = f.getVertex2();
			tran.transform(temp2);
			Point3f temp3 = f.getVertex3();
			tran.transform(temp3);
			Vector3f newNormal = f.getNormal();
			tran.transform(newNormal);
			newFacetList.add(new STLFacet(temp1, temp2, temp3,newNormal));
		}
		
		return new STLObject(newName, newFacetList);
	}

	protected void calculateFaces() {
		theFaces = new ArrayList<STLFace>();
		theFaces.addAll(STLFace.generateSTLFaces(this));
		facesAnalyzed = true;
	}

	protected STLObject clone(){
		
		ArrayList<STLFacet> listCopy = new ArrayList<STLFacet>();
		for(STLFacet fac:theFacets){
			listCopy.add(new STLFacet(fac.getVertex1(),fac.getVertex2(),fac.getVertex3(),fac.getNormal()));
		}
		return new STLObject((name+""),listCopy);
	}

	private void findUniqueNormals(){
		
		float epsilon = 0.0001f;
		
		uniqueNormals = new ArrayList<Vector3f>();
		Vector3f currNorm = new Vector3f();
		for(STLFacet fac:this){
			currNorm= fac.getNormal();
			boolean match = false;
			for(Vector3f found:uniqueNormals){
				currNorm.normalize();
				found.normalize();
				if(currNorm.epsilonEquals(found, epsilon)) {
					match = true;
					break;
				}
			}
			if(!match) uniqueNormals.add(currNorm);
		}
	}
	
	public Iterator<Vector3f> getNormalIterator(){
		if (uniqueNormals==null) findUniqueNormals();
		System.out.println("Norms "+uniqueNormals);
		return uniqueNormals.iterator();
	}
}