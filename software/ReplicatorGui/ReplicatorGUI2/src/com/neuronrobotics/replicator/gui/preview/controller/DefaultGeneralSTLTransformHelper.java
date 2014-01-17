package com.neuronrobotics.replicator.gui.preview.controller;

import java.util.Arrays;

import javax.vecmath.AxisAngle4d;
import javax.vecmath.Matrix4d;
import javax.vecmath.Vector3d;

public class DefaultGeneralSTLTransformHelper implements GeneralSTLTransformHelper{
	
	final private double[] identityArray = new double[]{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
	
	private double[] currentTransform;
	private Matrix4d currentMatrix;	
	
	public DefaultGeneralSTLTransformHelper(){
		currentTransform = Arrays.copyOf(identityArray, 16);
		currentMatrix = new Matrix4d(currentTransform);
	}
	
	public DefaultGeneralSTLTransformHelper(double[] initialTransform){
		currentTransform = Arrays.copyOf(initialTransform,16);
		currentMatrix.set(currentTransform);
	}
	
	@Override
	public void rotateX(double angle) {
		Matrix4d temp = identityMatrix();
		temp.rotX(angle);
		currentMatrix.mul(temp);
		this.getDoubleArrayFromMatrix(currentMatrix, currentTransform);		
	}

	@Override
	public void rotateY(double angle) {
		Matrix4d temp = identityMatrix();
		temp.rotY(angle);
		currentMatrix.mul(temp);
		this.getDoubleArrayFromMatrix(currentMatrix, currentTransform);
	}

	@Override
	public void rotateZ(double angle) {
		Matrix4d temp = identityMatrix();
		temp.rotZ(angle);
		currentMatrix.mul(temp);
		this.getDoubleArrayFromMatrix(currentMatrix, currentTransform);
	}
	
	public void translate(double x, double y, double z) {
		Matrix4d tempMat = identityMatrix();
		tempMat.setTranslation(new Vector3d(x,y,z));
		currentMatrix.mul(tempMat);
		this.getDoubleArrayFromMatrix(currentMatrix, currentTransform);
	}

	private Matrix4d identityMatrix() {
		return new Matrix4d(identityArray);
	}

	@Override
	public void translateLeftRight(double dist) {
		Vector3d tran = new Vector3d(1, 0, 0);
		Matrix4d curMat = new Matrix4d(currentTransform);
		
		try{
		curMat.invert();
		} catch(Exception e){
			System.out.println(curMat);
			throw new javax.vecmath.SingularMatrixException();
			//this blew up once?
		}
		
		curMat.transform(tran);
		tran.normalize();
		tran.scale(dist);
		translate(tran.x,tran.y,tran.z); 
	}

	@Override
	public void translateBackForth(double dist) {
		Vector3d tran = new Vector3d(0, 0, 1);
		Matrix4d curMat = new Matrix4d(currentTransform);
		curMat.invert();
			
		curMat.transform(tran);
		tran.normalize();
		tran.scale(dist);
		
		translate(tran.x,tran.y,tran.z);		
	}

	@Override
	public void translateUpDown(double dist) {
		Vector3d tran = new Vector3d(0, 1, 0);
		Matrix4d curMat = new Matrix4d(currentTransform);
		curMat.invert();

		curMat.transform(tran);
		tran.normalize();
		tran.scale(dist);
		
		translate(tran.x,tran.y,tran.z);		
	}
	
	public void rotateAroundUpVector(double rad){
			
		//System.out.println("Initial transform(stlController): "+Arrays.toString(this.currentTransform));
		
		Vector3d up = new Vector3d(0,1,0);
		Matrix4d invMat = new Matrix4d(currentMatrix);
		invMat.invert();
		invMat.transform(up);		
		
		
		AxisAngle4d axAngRot = new AxisAngle4d(up, rad);
		this.rotateX(axAngRot.x*rad);
		this.rotateY(axAngRot.y*rad);
		this.rotateZ(axAngRot.z*rad);
		
		System.out.println("Rot x"+axAngRot.x*rad);
		System.out.println("Rot y"+axAngRot.y*rad);
		System.out.println("Rot z"+axAngRot.z*rad);
				
		System.out.println("Final transform(stlController): "+Arrays.toString(this.currentTransform));
		
	}
		
	public void placeOnWorkspace(double workspaceY, double currMin){
		double epsilon = 0.000001;
		this.translateUpDown(workspaceY-currMin+epsilon);
	}
		
	private AxisAngle4d getRotationDown(double[] someNormal){
		
		float epsilon = 0.0001f;
		
		Vector3d curr = new Vector3d(someNormal);
		Vector3d down = new Vector3d(0,-1,0);
		curr.normalize();
		down.normalize();
		
		Vector3d up = new Vector3d(0,1,0);
		
		
		if(curr.epsilonEquals(down, epsilon)){
			return new AxisAngle4d();
		} else if(curr.epsilonEquals(up, epsilon)){
			return new AxisAngle4d(1,0,0,Math.PI);
		}
		
		Vector3d rotVec = new Vector3d();
		rotVec.cross(curr, down);
		rotVec.normalize();
		
		double angle = curr.angle(down);
		
		AxisAngle4d rotAxAng = new AxisAngle4d(rotVec.x,rotVec.y,rotVec.z,angle);
		
		if(Double.isNaN(rotVec.x)){
			System.out.println("Curr "+curr);
			System.out.println("down: "+down);
		}
		
		return rotAxAng;
	}
	
	@Override
	public void setCurrentTransform(double[] newTrans){
		this.currentTransform = Arrays.copyOf(newTrans, 16);
		this.currentMatrix.set(currentTransform);
	}
	
	@Override
	public void getCurrentTransform(double[] result){
		for(int i =0;i<16;i++) result[i]=this.currentTransform[i];
	}
	
	private void getDoubleArrayFromMatrix(Matrix4d source, double[] result){
		for(int i=0;i<4;i++){
			for (int j=0;j<4;j++){
				result[i*4+j]=currentMatrix.getElement(i,j);
			}
		}		
	}

	@Override
	public void pointNormalDown(double[] normal) {
		AxisAngle4d rotAxAng = getRotationDown(normal);
		this.currentMatrix.setRotation(rotAxAng);
		this.getDoubleArrayFromMatrix(currentMatrix, currentTransform);
	}

	
}