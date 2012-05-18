package com.neuronrobotics.replicator.gui.stl;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.ArrayList;
import java.util.IllegalFormatException;
import java.util.Iterator;
import java.util.Scanner;
import java.util.StringTokenizer;

import javax.media.j3d.*;
import javax.vecmath.*;

//import org.j3d.loaders.InvalidFormatException;

public class STLObject implements Iterable<STLFacet>{

	private String name;
	private ArrayList<STLFacet> facets;
	private Point3f center;
	private Point3f min, max;
	

	public STLObject(String name, ArrayList<STLFacet> facets,
			Point3f center, Point3f min, Point3f max) {
		this.name = name;
		this.facets=facets;
		this.center = center;
		this.min = min;
		this.max = max;
	}
	
	public Iterable<STLFacet> getFacetIterable(){
		return (Iterable<STLFacet>)facets;
	}

	public int getFacetAmount() {
		return facets.size();
	}


	public Point3f getCenter() {
		if (center != null)
			return center;
		int numVertices = facets.size() * 3;
		float xSum = 0, ySum = 0, zSum = 0;
		for (STLFacet sf : facets) {
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
		return center;
	}

	public float getXDistance() {
		return max.x - min.x;
	}

	public float getYDistance() {
		return max.y - min.y;
	}

	public float getZDistance() {
		return max.z - min.z;
	}
	

	public String getName() {
		return name;
	}
	
	public Point3f getMax(){
		return max;
	}
	
	public Point3f getMin(){
		return min;
	}
	
	@Override
	public String toString(){
		String res = "";
		res+="Name: "+this.name+"\n";		
		return res;
	}

	@Override
	public Iterator<STLFacet> iterator() {
		return facets.iterator();
	}

}