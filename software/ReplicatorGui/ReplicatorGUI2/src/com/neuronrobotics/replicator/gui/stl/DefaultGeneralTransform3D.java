package com.neuronrobotics.replicator.gui.stl;

import javax.vecmath.Matrix4d;

public class DefaultGeneralTransform3D implements GeneralTransform3D{

	private Matrix4d theMatrix;	
	
	public DefaultGeneralTransform3D(){
		theMatrix = new Matrix4d(new double[]{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1});
	}
	
	public DefaultGeneralTransform3D(double[] tran){
		theMatrix = new Matrix4d(tran);
	}
	
	public DefaultGeneralTransform3D(Matrix4d tran){
		theMatrix = new Matrix4d(tran);
	}
	
	@Override
	public void get(double[] transform) {
		for(int i=0;i<4;i++){
			for (int j=0;j<4;j++){
				transform[i*4+j]=theMatrix.getElement(i,j);
			}
		}
	}

	@Override
	public void set(double[] newTransform) {
		theMatrix.set(newTransform);		
	}

}
