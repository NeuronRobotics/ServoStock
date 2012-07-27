package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.*;

public class STLFacet {

	private Point3f vertex1, vertex2, vertex3;
	private Vector3f normal;
		
	public STLFacet(Point3f a, Point3f b, Point3f c){
		vertex1 = a;
		vertex2 = b;
		vertex3 = c;
		calculateNormal(a,b,c);
	}
	
	public STLFacet(Point3f a, Point3f b, Point3f c, Vector3f norm){
		vertex1 = a;
		vertex2 = b;
		vertex3 = c;
		normal = norm;
	}
	
	//TODO need to test, unsure the logic is sound
	public boolean pointIsWithin(Point3f a){
		
		float epsilon = 0.0001f; //TODO might need to leave at 0 to prevent slicer exceptions
		
		Vector3f temp = new Vector3f(normal);
		Vector3f temp2 = new Vector3f(a);
				
		return temp2.dot(temp)<=(this.originToPlaneDistance()+epsilon);
		
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
		return normal;
	}

	public Point3f getVertex1() {
		return vertex1;
	}
	
	public Point3f getVertex2() {
		return vertex2;
	}
	
	public Point3f getVertex3() {
		return vertex3;
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
	
	//TODO need to test, but this should work
	public float originToPlaneDistance(){
		Vector3f temp = this.getNormal();
		float dist = -temp.dot(new Vector3f(vertex1));
		return dist;
	}
		
	public String toString(){
		return "Normal: "+normal+"\nVertices: "+vertex1+""+vertex2+""+vertex3;
	}
	
}
