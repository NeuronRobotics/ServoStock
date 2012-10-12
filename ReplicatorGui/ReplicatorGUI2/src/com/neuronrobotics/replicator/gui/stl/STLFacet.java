package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.*;

public class STLFacet {

	private Point3f vertex1, vertex2, vertex3;
	private Vector3f normal;
	private float surfaceArea, volumeUnder,projectedArea,originToPlaneDistance;
			
	public STLFacet(Point3f a, Point3f b, Point3f c){
		vertex1 = a;
		vertex2 = b;
		vertex3 = c;
		calculateNormal(a,b,c);
		this.calculateMetaInformation();
	}
	
	public STLFacet(Point3f a, Point3f b, Point3f c, Vector3f norm){
		vertex1 = a;
		vertex2 = b;
		vertex3 = c;
		normal = norm;
		this.calculateMetaInformation();
	}
		
	public boolean pointIsWithin(Point3f a){
		
		float epsilon = 0.0001f; //TODO might need to leave at 0 to prevent slicer exceptions
		
		Vector3f temp = new Vector3f(getNormal());
		Vector3f temp2 = new Vector3f(a);
		Vector3f temp3 = new Vector3f(vertex1);
		
		float dist = temp.dot(temp3);
		float d2 = temp.dot(temp2);
		if(dist>=0){
			return d2<=(dist+epsilon);
		} else {
			return d2>=(dist-epsilon);
		}
		//return temp.dot(temp2)<=(this.originToPlaneDistance()+epsilon);
		
	}
	
	private boolean isBetween(float monkey, float a,float b){
		return ((monkey>=a&&monkey<=b)||(monkey<=a&&monkey>=b));
	}
		
	private void calculateNormal(Point3f a, Point3f b, Point3f c){
		
		Vector3f v1 = new Vector3f();
		v1.add(a);
		v1.sub(b);
		
		Vector3f v2 = new Vector3f();
		v2.add(a);
		v2.sub(c);
		 		
		if(normal==null) normal = new Vector3f();
		normal.cross(v1,v2);
	}
	
	public Vector3f getNormal(){
		return new Vector3f(normal);
	}

	public Point3f getVertex1() {
		return new Point3f(vertex1);
	}
	
	public Point3f getVertex2() {
		return new Point3f(vertex2);
	}
	
	public Point3f getVertex3() {
		return new Point3f(vertex3);
	}
	
	public Point3f getCenter(){
		
		float x = (vertex1.x+vertex2.x+vertex3.x)/3;
		float y = (vertex1.y+vertex2.y+vertex3.y)/3;
		float z = (vertex1.z+vertex2.z+vertex3.z)/3;
		
		return new Point3f(x,y,z);
	}
	
	public Point3f getMax(){
		float x,y,z;
		x = Math.max(Math.max(vertex1.x,vertex2.x), vertex3.x);
		y = Math.max(Math.max(vertex1.y,vertex2.y), vertex3.y);
		z = Math.max(Math.max(vertex1.z,vertex2.z), vertex3.z);
		return new Point3f(x,y,z);
	}
	
	public Point3f getMin(){
		float x,y,z;
		x = Math.min(Math.min(vertex1.x,vertex2.x), vertex3.x);
		y = Math.min(Math.min(vertex1.y,vertex2.y), vertex3.y);
		z = Math.min(Math.min(vertex1.z,vertex2.z), vertex3.z);
		return new Point3f(x,y,z);
	}
	
	public float getTriangleArea() {
		return surfaceArea;
	}
	
	public float volumeUnderTriangle(){
		return volumeUnder;
	}
	
	private float projectedTriangleArea() {
		return projectedArea;
	}
		
	public float originToPlaneDistance(){
		return originToPlaneDistance;
	}
	
	private void calculateMetaInformation(){
		//private float surfaceArea, volumeUnder,projectedArea,originToPlaneDistance;
		
		//calculating plane distance from origin
		Vector3f temp = this.getNormal();
		temp.normalize();
		originToPlaneDistance = temp.dot(new Vector3f(vertex1));
		
		//calculating surface area
		Vector3f v = new Vector3f(this.vertex2), w = new Vector3f(this.vertex3);
		Vector3f v0 = new Vector3f(vertex1);
		v.sub(v0);
		w.sub(v0);
		Vector3f cr = new Vector3f();
		cr.cross(v, w);
		surfaceArea = (float) Math.abs(cr.length() / 2.0);

		//calculating projected area
		v.y=0;
		w.y=0;
		cr.cross(v, w);
		projectedArea = (float) Math.abs(cr.length() / 2.0);
		
		//calculating volume under 
		volumeUnder = (float)((vertex1.y+vertex2.y+vertex3.y)/3.0)*projectedArea;
		
	}	
			
	public String toString(){
		return "Normal: "+normal+"\n"+
				"Vertices: "+vertex1+""+vertex2+""+vertex3;
	}
	
	public String metaInformation(){
		return "Surface Area: "+this.surfaceArea+"\n"+
				"Projeced Area: "+projectedArea+"\n"+
				"Volume Under: "+volumeUnder+"\n"+
				"Origin to plane distance: "+originToPlaneDistance;
	}
	
}
