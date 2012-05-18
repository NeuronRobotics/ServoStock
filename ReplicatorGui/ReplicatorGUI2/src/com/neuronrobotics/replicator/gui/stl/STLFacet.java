package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.*;

public class STLFacet {

	private Point3f vertex1, vertex2, vertex3;
	private Vector3f normal;
	
	public void setNormal(Vector3f n){
		normal = n;
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
