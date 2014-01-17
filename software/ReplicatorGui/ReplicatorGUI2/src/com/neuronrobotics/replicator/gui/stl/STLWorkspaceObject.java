package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Iterator;

import javax.vecmath.Vector3f;

public class STLWorkspaceObject extends STLObject {
	
	STLFace theSurface;
	double surfaceY;
	
	public STLWorkspaceObject(String name, ArrayList<STLFacet> facets) {
		super(name, facets);
		theSurface = null;
		surfaceY = Double.MAX_VALUE;
	}
	
	public STLWorkspaceObject(STLObject theSTLObject) {
		super(theSTLObject.getName(),theSTLObject.theFacets);
	}

	public STLFace getSurfaceFace(){
		
		if(theSurface!=null) return theSurface;
		
		double y = Double.MAX_VALUE;
		
		STLFace result = null;
		Vector3f down = new Vector3f(0,-1,0);
		
		Iterator<STLFace> theFaces = this.getFaceIterator();
		
		while(theFaces.hasNext()){
			STLFace face = theFaces.next();
			Vector3f currNorm = face.getNormal();
			currNorm.normalize();
			double currY = face.iterator().next().getVertex1().y;
			if(down.epsilonEquals(currNorm, 0.0001f)&&(y==Double.MAX_VALUE||currY<=y)){
				result = face;
				y=currY;
			}
		}
				
		theSurface = result;
		surfaceY = y;
		return result;
	}
	
	public double getSurfaceY(){
		if(theSurface==null) this.getSurfaceFace();
		if(surfaceY==Double.MAX_VALUE) return 0; //TODO bad practice
		return surfaceY;
	}

	public boolean stlIsInside(STLObject stlo){
		
		
		boolean intersect = STLObjectUtilities.objectsIntersect(this, stlo);
		if(intersect) return false;
		
		return STLObjectUtilities.isWithinBoundingBox(this, stlo);
		
		/*
		for(STLFacet facet:stlo){
			for (STLFacet workspaceFac:workspaceSTL){
				if(!isBehind(facet,workspaceFac)){
					//System.out.println("\n"+facet+"\n"+workspaceFac);
					return false;
				}
			}
		}
		return true;
		*/
	}
}
