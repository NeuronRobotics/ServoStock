package com.neuronrobotics.replicator.gui.preview.controller;

import java.util.Arrays;
import java.util.Iterator;

import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModel;
import com.neuronrobotics.replicator.gui.preview.view.STLWorkspaceView;
import com.neuronrobotics.replicator.gui.stl.DefaultGeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;

public class DefaultSTLPreviewController {
	
	private GeneralSTLTransformHelper theTransformHelper;
	private GeneralCameraController theCameraController;
	private STLPreviewMouseController theMouseController;
	private STLWorkspaceView theWorkspaceView;
	private STLWorkspaceModel theWorkspaceModel;

	public DefaultSTLPreviewController(STLWorkspaceView theView, STLWorkspaceModel theModel){
		
		theWorkspaceView = theView;
		theWorkspaceModel = theModel;
		
		theTransformHelper = new DefaultGeneralSTLTransformHelper();
		theCameraController = new DefaultGeneralCameraController(theView);
		theMouseController = new STLPreviewMouseController(theWorkspaceView, theWorkspaceModel, theTransformHelper, theCameraController);
	}
	
	public STLPreviewMouseController getSTLPreviewMouseController(){
		return this.theMouseController;
	}
	
	public GeneralCameraController getGeneralCameraController(){
		return this.theCameraController;
	}
	
	public GeneralSTLTransformHelper getGeneralSTLTransformHelper(){
		return this.theTransformHelper;
	}
	
	public boolean placeAllObjectsOnWorkspace(){
		
		STLWorkspaceObject theWorkspaceObject = theWorkspaceModel.getWorkspaceObject(); 
		if(theWorkspaceObject==null) return false;
		
		double workspaceY = theWorkspaceObject.getSurfaceY();
		System.out.println("workspce y:  "+workspaceY);
		
		Iterator<STLObject> theBaseObjects = theWorkspaceModel.getBaseSTLObjectIterator();
		Iterator<double[]> theTransforms = theWorkspaceModel.getTransformMatrixIterator();
				
		while(theBaseObjects.hasNext()){
			double[] currTrans = theTransforms.next();
			STLObject baseObj = theBaseObjects.next();
			STLObject currObject = baseObj.getTransformedSTLObject(new DefaultGeneralTransform3D(currTrans));
			theTransformHelper.setCurrentTransform(currTrans);
			double currMin = currObject.getMin().y;
			//theTransformHelper.translateUpDown(workspaceY-currMin);
			theTransformHelper.placeOnWorkspace(workspaceY, currMin);
			System.out.println("OldTransform: "+Arrays.toString(currTrans));
			System.out.println("Translating "+baseObj.getName()+" up down: "+(workspaceY-currMin));
			double[] newT = new double[16];
			theTransformHelper.getCurrentTransform(newT);
			System.out.println("NewTransform: "+Arrays.toString(newT));
			System.out.println("Old min: "+currMin);
			System.out.println("New Min: "+baseObj.getTransformedSTLObject(new DefaultGeneralTransform3D(newT)).getMin().y);
			double[] result = new double[16];
			
			theWorkspaceModel.setTransformMatrix(baseObj, newT);
			
			theWorkspaceModel.getCurrMins(baseObj, result);
			
			
			System.out.println("Curr min: "+Arrays.toString(result));
			
		}
		
		return true;
		
	}	
	
	public void duplicateSTLObject(STLObject currPick){
		//TODO
	}
	
	public void setScale(STLObject currPick){
		//TODO
	}
	
	public void scaleToHeight(STLObject currPick){
		//TODO
	}
	
	public void removeSTLObject(STLObject currPick){
		this.theWorkspaceModel.removeSTLObject(currPick);
	}
	
	public void orientNextFace(STLObject currPick) {
		double[] result = new double[16];
		this.theWorkspaceModel.getTransformMatrix(currPick, result);	
		this.theTransformHelper.setCurrentTransform(result);
		double[] normal = new double[3];
		currPick.getNextUniqueNormal(normal);
		this.theTransformHelper.pointNormalDown(normal);
		
		double workspaceY, currMin;
		double[] mins = new double[3];
		theWorkspaceModel.getCurrMins(currPick, mins);
		STLWorkspaceObject currWS = theWorkspaceModel.getWorkspaceObject();
		if (currWS != null) {
			currMin = mins[1];
			workspaceY = currWS.getSurfaceY();
			this.theTransformHelper.placeOnWorkspace(workspaceY, currMin);
		}
		double[] newT = new double[16];
		this.theTransformHelper.getCurrentTransform(newT);
		this.theWorkspaceModel.setTransformMatrix(currPick, newT );		
	}

	public void resetCurrentModel(STLObject currPick) {
		double[] ident = new double[]{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};	
		this.theWorkspaceModel.setTransformMatrix(currPick, ident);
	}
	

}
