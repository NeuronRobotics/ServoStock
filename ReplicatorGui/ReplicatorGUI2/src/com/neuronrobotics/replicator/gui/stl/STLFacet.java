package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.*;

public class STLFacet {

	private Point3f vertex1, vertex2, vertex3;
	private Vector3f normal;
	
	public STLFacet(){
		
	}
	
	public STLFacet(Point3f a, Point3f b, Point3f c){
		vertex1 = a;
		vertex2 = b;
		vertex3 = c;
		setNormal(a,b,c);
	}
	
	public void setNormal(Vector3f n){
		normal = n;
	}
	
	private void setNormal(Point3f a, Point3f b, Point3f c){
		Vector3f v1 = new Vector3f();
		v1.add(a);
		v1.sub(b);
		
		Vector3f v2 = new Vector3f();
		v2.add(a);
		v2.sub(c);
		
		if(normal==null) normal = new Vector3f();
		normal.cross(v1,v2);
	}
	
	public void setVertices(Point3f a, Point3f b, Point3f c){
		vertex1 = a;
		vertex2 = b;
		vertex3 = c;
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
	
	
	public String toString(){
		return "Normal: "+normal+"\nVertices: "+vertex1+""+vertex2+""+vertex3;
	}
	
}
