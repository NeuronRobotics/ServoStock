package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

public class STLFace implements Iterable<STLFacet>{
	
	private static float EPSILON = 0.0001f;
	
	private ArrayList<STLFacet> theFacets;
	private ArrayList<Point3f> theVertices;
	
	private Vector3f normal;
	private float originDistance;
	
	//Main Static factory methods that ensure valid STLFace creation
			
	public static Collection<STLFace> generateSTLFaces(STLObject stlo){
		ArrayList<STLFace> theFaces = new ArrayList<STLFace>();
		
		for (STLFacet currFacet:stlo){
			int index = indexOfMatchingFace(currFacet, theFaces);
			if(index==-1){
				theFaces.add(new STLFace(currFacet));
			} else {
				theFaces.get(index).addFacet(currFacet);
			}
		}	
		
		return theFaces;
	}

	//static utilities
	
	private static int indexOfMatchingFace(STLFacet facet, Collection<STLFace> col){
				
		int ct = 0;
		
		Vector3f facetNormal = new Vector3f(facet.getNormal());
		facetNormal.normalize();
		
		for(STLFace face:col){
			Vector3f faceNormal = new Vector3f(face.getNormal());
			faceNormal.normalize();
			
			if((facetNormal.epsilonEquals(faceNormal, EPSILON))&&floatEpsilonEquals(face.originDistance,facet.originToPlaneDistance())){
				return ct;
			}
			ct++;
		}		
		return -1;
	}
	
	private static boolean floatEpsilonEquals(float originDistance2,float originToPlaneDistance) {
		float diff = originDistance2 - originToPlaneDistance;
		return diff>=-EPSILON&&diff<=EPSILON;
	}
	
	//Private methods to allow static factory methods to ensure valid face creation
	
	private STLFace(STLFacet f){
		theFacets = new ArrayList<STLFacet>();
		theFacets.add(f);
		normal = f.getNormal();

		theVertices = new ArrayList<Point3f>();
		theVertices.add(f.getVertex1());
		theVertices.add(f.getVertex2());
		theVertices.add(f.getVertex3());
		
		originDistance = f.originToPlaneDistance();
		
	}
	
	private boolean addFacet(STLFacet fac){
		theVertices.add(fac.getVertex1());
		theVertices.add(fac.getVertex2());
		theVertices.add(fac.getVertex3());
		return theFacets.add(fac);
	}
	
	//Public Getters
	
	public Collection<? extends STLFacet> getFacets() {
		return theFacets;
	}
	
	public Vector3f getNormal(){
		return normal;
	}
	
	public Point3f getCenter(){
		//TODO want to make sure point is on plane
		//this seems easier to solve after rotations
		//are better figured out
		Point3f center = new Point3f(0,0,0);
		
		Point3f max = new Point3f(0,0,0), min = new Point3f(0,0,0);
		
		for(STLFacet fac:this){
			max.x = Math.max(max.x, fac.getMax().x);
			max.y = Math.max(max.y, fac.getMax().y);
			max.z = Math.max(max.z, fac.getMax().z);
			
			min.x = Math.min(min.x, fac.getMax().x);
			min.y = Math.min(min.y, fac.getMax().y);
			min.z = Math.min(min.z, fac.getMax().z);
			
		}
		center = new Point3f(((max.x-min.x)/2),((max.y-min.y)/2),((max.z-min.z)/2));
		return center;
	}

	public float getDistanceToOrigin(){
		return originDistance;
	}
		
	@Override
	public Iterator<STLFacet> iterator() {
		return theFacets.iterator();
	}
		
}
