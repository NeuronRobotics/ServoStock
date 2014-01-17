package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.*;

public class STLFacet {

	private Point3f baseVertex1, baseVertex2, baseVertex3;
	private Vector3f baseNormal;
	
	private boolean allowTransforms = true;
	private Point3f transVertex1 = new Point3f(), transVertex2= new Point3f(),transVertex3= new Point3f();
	private Vector3f transNormal = new Vector3f();
	private float surfaceArea, volumeUnder,projectedArea,originToPlaneDistance;
			
	public STLFacet(Point3f a, Point3f b, Point3f c){
		baseVertex1 = a;
		baseVertex2 = b;
		baseVertex3 = c;
		transVertex1.set(baseVertex1);
		transVertex2.set(baseVertex2);
		transVertex3.set(baseVertex3);
		calculateNormal(a,b,c);
		this.calculateMetaInformation();
	}
	
	public STLFacet(Point3f a, Point3f b, Point3f c, Vector3f norm){
		baseVertex1 = a;
		baseVertex2 = b;
		baseVertex3 = c;
		baseNormal = norm;
		transVertex1.set(baseVertex1);
		transVertex2.set(baseVertex2);
		transVertex3.set(baseVertex3);
		transNormal.set(baseNormal);
		this.calculateMetaInformation();
	}
		
	public boolean pointIsWithin(Point3f a){
		
		float epsilon = 0.0001f; //TODO might need to leave at 0 to prevent slicer exceptions
		
		Vector3f temp = new Vector3f(getNormal());
		Vector3f temp2 = new Vector3f(a);
		Vector3f temp3 = new Vector3f(baseVertex1);
		
		float dist = temp.dot(temp3);
		float d2 = temp.dot(temp2);
		if(dist>=0){
			return d2<=(dist+epsilon);
		} else {
			return d2>=(dist-epsilon);
		}
		//return temp.dot(temp2)<=(this.originToPlaneDistance()+epsilon);
		
	}
	
	private void calculateNormal(Point3f a, Point3f b, Point3f c){
		
		Vector3f v1 = new Vector3f();
		v1.add(a);
		v1.sub(b);
		
		Vector3f v2 = new Vector3f();
		v2.add(a);
		v2.sub(c);
		 		
		if(baseNormal==null) baseNormal = new Vector3f();
		baseNormal.cross(v1,v2);
		transNormal.set(baseNormal);
	}
	
	public Vector3f getNormal(){
		return new Vector3f(transNormal);
	}

	public Point3f getVertex1() {
		return new Point3f(transVertex1);
	}
	
	public Point3f getVertex2() {
		return new Point3f(transVertex2);
	}
	
	public Point3f getVertex3() {
		return new Point3f(transVertex3);
	}
	
	public Point3f getCenter(){
		
		float x = (transVertex1.x+transVertex2.x+transVertex3.x)/3;
		float y = (transVertex1.y+transVertex2.y+transVertex3.y)/3;
		float z = (transVertex1.z+transVertex2.z+transVertex3.z)/3;
		
		return new Point3f(x,y,z);
	}
	
	public Point3f getMax(){
		float x,y,z;
		x = Math.max(Math.max(transVertex1.x,transVertex2.x), transVertex3.x);
		y = Math.max(Math.max(transVertex1.y,transVertex2.y), transVertex3.y);
		z = Math.max(Math.max(transVertex1.z,transVertex2.z), transVertex3.z);
		return new Point3f(x,y,z);
	}
	
	public Point3f getMin(){
		float x,y,z;
		x = Math.min(Math.min(transVertex1.x,transVertex2.x), transVertex3.x);
		y = Math.min(Math.min(transVertex1.y,transVertex2.y), transVertex3.y);
		z = Math.min(Math.min(transVertex1.z,transVertex2.z), transVertex3.z);
		return new Point3f(x,y,z);
	}
	
	public float getTriangleArea() {
		return surfaceArea;
	}
	
	private float volumeUnderTriangle(){
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
		originToPlaneDistance = temp.dot(new Vector3f(baseVertex1));
		
		//calculating surface area
		Vector3f v = new Vector3f(this.baseVertex2), w = new Vector3f(this.baseVertex3);
		Vector3f v0 = new Vector3f(baseVertex1);
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
		volumeUnder = (float)((baseVertex1.y+baseVertex2.y+baseVertex3.y)/3.0)*projectedArea;
		
	}	
			
	public String toString(){
		return "Normal: "+transNormal+"\n"+
				"Vertices: "+transVertex1+""+transVertex2+""+transVertex3;
	}
	
	public String metaInformation(){
		return "Surface Area: "+this.surfaceArea+"\n"+
				"Projeced Area: "+projectedArea+"\n"+
				"Volume Under: "+volumeUnder+"\n"+
				"Origin to plane distance: "+originToPlaneDistance;
	}
	
	protected boolean acceptTransform(GeneralTransform3D gt){
		
		double[] tempD = new double[16];
		gt.get(tempD);		
		Matrix4d mat = new Matrix4d(tempD);
		
		if(!allowTransforms) return false;
		resetTransforms();
		mat.transform(this.transVertex1);
		mat.transform(this.transVertex2);
		mat.transform(this.transVertex3);
		mat.transform(this.transNormal);		
		Vector3f temp = this.getNormal();
		temp.normalize();
		originToPlaneDistance = temp.dot(new Vector3f(transVertex1));
		volumeUnder = (float)((transVertex1.y+transVertex2.y+transVertex3.y)/3.0)*projectedArea;
		return true;
	}
	
	private void resetTransforms() {
		transVertex1.set(baseVertex1);
		transVertex2.set(baseVertex2);
		transVertex3.set(baseVertex3);
		transNormal.set(baseNormal);		
		Vector3f temp = this.getNormal();
		temp.normalize();
		originToPlaneDistance = temp.dot(new Vector3f(transVertex1));
		volumeUnder = (float)((transVertex1.y+transVertex2.y+transVertex3.y)/3.0)*projectedArea;
	}

	protected void setAllowTransforms(boolean allow){
		this.allowTransforms = allow;
	}
	
}
