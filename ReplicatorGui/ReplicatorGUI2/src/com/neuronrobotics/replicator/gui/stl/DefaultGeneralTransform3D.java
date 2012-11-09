package com.neuronrobotics.replicator.gui.stl;

import javax.vecmath.Matrix3d;
import javax.vecmath.Matrix4d;
import javax.vecmath.Point3d;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3d;
import javax.vecmath.Vector3f;

public class DefaultGeneralTransform3D implements GeneralTransform3D{

	private Matrix4d theMatrix;	
	
	public DefaultGeneralTransform3D(double[] tran){
		theMatrix = new Matrix4d(tran);
	}
	
	public DefaultGeneralTransform3D(Matrix4d tran){
		theMatrix = new Matrix4d(tran);
	}
		
	@Override
	public void transform(Point3f p) {
		theMatrix.transform(p);
	}

	@Override
	public void transform(Point3d p) {
		theMatrix.transform(p);
	}

	@Override
	public void transform(Vector3f v) {
		theMatrix.transform(v);
	}

	@Override
	public void transform(Vector3d v) {
		theMatrix.transform(v);
	}
	
	public void transform(double[] point){
		Point3d temp = new Point3d(point);
		theMatrix.transform(temp);
		temp.get(point);
	}

	@Override
	public double get(Matrix3d rotation, Vector3d translation) {
		return theMatrix.get(rotation, translation);
	}

	@Override
	public void get(double[] transform) {
		for(int i=0;i<4;i++){
			for (int j=0;j<4;j++){
				transform[i*4+j]=theMatrix.getElement(i,j);//TODO test this
			}
		}
	}

	@Override
	public void set(double[] newTransform) {
		theMatrix.set(newTransform);		
	}

}
