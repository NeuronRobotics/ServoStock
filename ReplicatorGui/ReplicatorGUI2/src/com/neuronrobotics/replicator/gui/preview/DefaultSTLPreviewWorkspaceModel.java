package com.neuronrobotics.replicator.gui.preview;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.LinkedList;

import com.neuronrobotics.replicator.gui.stl.DefaultGeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.GeneralTransform3D;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.neuronrobotics.replicator.gui.stl.STLObjectCalculationUtilities;
import com.neuronrobotics.replicator.gui.stl.STLWorkspaceObject;

public class DefaultSTLPreviewWorkspaceModel implements STLWorkspaceModel {

	private LinkedList<STLWorkspaceModelListener> theListeners;
	private ArrayList<STLObject> theBaseSTLs;
	private ArrayList<STLObject> theTransformedSTLs;
	private ArrayList<double[]> theTransformMatrices;	
	private STLWorkspaceObject theWorkspaceObject;	

	private ArrayList<ArrayList<Boolean>> collisionTable;
	private ArrayList<PlacementStatus> placementStatuses;
	
	public DefaultSTLPreviewWorkspaceModel(){
		
		theListeners = new LinkedList<STLWorkspaceModelListener>();
		theBaseSTLs = new ArrayList<STLObject>();
		theTransformedSTLs = new ArrayList<STLObject>();
		collisionTable = new ArrayList<ArrayList<Boolean>>();
		placementStatuses = new ArrayList<PlacementStatus>();
		
		theTransformMatrices = new ArrayList<double[]>();
		theWorkspaceObject=null;
	}
	
	public DefaultSTLPreviewWorkspaceModel(STLWorkspaceObject thew){
		this();
		theWorkspaceObject = thew;
	}
	
	public boolean addSTLObject(STLObject newSTL){
		theBaseSTLs.add(newSTL);
		theTransformedSTLs.add(newSTL);
		theTransformMatrices.add(identityMatrix4X4());
		increaseCollisionTableSize();
		placementStatuses.add(PlacementStatus.UNKOWN);
		updatePlacementStatus(false);
		return true;
	}
	
	private void increaseCollisionTableSize() {
		ArrayList<Boolean> newCollisionList = new ArrayList<Boolean>();
		
		STLObject newTransform = theBaseSTLs.get(theBaseSTLs.size()-1);
		
		int ct = -1;
		boolean collisionFound = false;
		for (STLObject stg : theBaseSTLs) {
			ct++;
			
			DefaultGeneralTransform3D curr = new DefaultGeneralTransform3D(theTransformMatrices.get(ct));
						
			if (stg == newTransform) {
				newCollisionList.add(false);
				break;
			}
			stg=stg.getTransformedSTLObject(curr);
			if (STLObjectCalculationUtilities.objectsIntersect(stg, newTransform)) {
				collisionFound = true;
				if (placementStatuses.get(ct) != PlacementStatus.NOT_IN_WORKSPACE) {
					this.placementStatuses.set(ct,
							PlacementStatus.MODEL_COLLISION);
				}
				collisionTable.get(ct).add(true);
				newCollisionList.add(true);
			} else {
				collisionTable.get(ct).add(false);
				newCollisionList.add(false);
			}
		}
			
		boolean inWorkspace = true;
		if (theWorkspaceObject != null) theWorkspaceObject.stlIsInside(newTransform);
		if (theWorkspaceObject == null) placementStatuses.add(PlacementStatus.UNKOWN);
		else if (!inWorkspace) placementStatuses.add(PlacementStatus.NOT_IN_WORKSPACE);
		else if (collisionFound) placementStatuses.add(PlacementStatus.MODEL_COLLISION);
		else placementStatuses.add(PlacementStatus.VALID_PLACEMENT);

		this.collisionTable.add(newCollisionList);
		System.out.println(collisionTable);
		System.out.println(placementStatuses);
	}

	public boolean removeSTLObject(int index){
		if(index<0||index>=theBaseSTLs.size()) return false;
		theBaseSTLs.remove(index);
		theTransformedSTLs.remove(index);
		theTransformMatrices.remove(index);
		placementStatuses.remove(index);
		
		for(ArrayList<Boolean> b:collisionTable){
			b.remove(index);
		}
		collisionTable.remove(index);
		updatePlacementStatus(false);		
		return true;
	}
	
	public boolean removeSTLObject(STLObject toRemove){
		int index = theBaseSTLs.indexOf(toRemove);
		return removeSTLObject(index);
	}
	
	public void setWorkspaceObject(STLWorkspaceObject theW){
		theWorkspaceObject = theW;
	}
	
	public STLWorkspaceObject getWorkspaceObject(){
		return theWorkspaceObject;
	}
	
	public boolean getTransformMatrix(int index,double[] result){
		if(index<0||index>=theTransformMatrices.size()||result.length<16) return false;
		copyDoubleArray(theTransformMatrices.get(index),result);
		return true;
	}
	
	private void copyDoubleArray(double[] source, double[] result) {
		int len = source.length;
		for(int i=0;i<len;i++) result[i] = source[i];
	}

	public boolean getTransformMatrix(STLObject stl,double[] result){
		int index = theBaseSTLs.indexOf(stl);
		return getTransformMatrix(index,result);
	}
		
	public boolean setTransformMatrix(int index, double[] mat4){
		if(mat4.length<16||theBaseSTLs.size()<=index||index<0) return false;
		this.theTransformMatrices.set(index, Arrays.copyOf(mat4, 16));
		DefaultGeneralTransform3D curr = new DefaultGeneralTransform3D(mat4);
		this.theTransformedSTLs.set(index, theBaseSTLs.get(index).getTransformedSTLObject(curr));
		updateCollisionTable(index);		
		this.fireAlertSTLObjectMoved(this.theBaseSTLs.get(index),curr);
		return true;
	}
	
	public boolean setTransformMatrix(STLObject obj, double[] mat4) throws IndexOutOfBoundsException{
		int index = theBaseSTLs.indexOf(obj);
		return setTransformMatrix(index,mat4);
	}
		
	private double[] identityMatrix4X4(){
		return new double[]{
				1.0,0.0,0.0,0.0,
				0.0,1.0,0.0,0.0,
				0.0,0.0,1.0,0.0,
				0.0,0.0,0.0,1.0};
	}
		
	@Override
	public void addSTLWorkspaceModelListener(STLWorkspaceModelListener stlwml) {
		theListeners.add(stlwml);		
	}
	
	private void fireAlertSTLObjectMoved(STLObject stl, GeneralTransform3D transform){
		for(STLWorkspaceModelListener ml:theListeners){
			ml.alertSTLObjectMoved(stl, transform);
		}
	}
	
	private void fireAlertSTLObjectRemoved(STLObject stl){
		for(STLWorkspaceModelListener ml:theListeners){
			ml.alertSTLObjectRemoved(stl);
		}
	}
	
	private void fireAlertSTLObjectAdded(STLObject stl, GeneralTransform3D transform){
		for(STLWorkspaceModelListener ml:theListeners){
			ml.alertSTLObjectAdded(stl, transform);
		}
	}
	
	public boolean isWorkspacePlacementValid(){
		for(PlacementStatus ps:this.placementStatuses) if(ps!=PlacementStatus.VALID_PLACEMENT) return false;
		return true;
	}
	
	@Override
	public PlacementStatus getPlacementStatus(int index) {
		return this.placementStatuses.get(index);
	}

	@Override
	public PlacementStatus getPlacementStatus(STLObject obj) {
		return getPlacementStatus(this.theBaseSTLs.indexOf(obj));
	}

	@Override
	public void setWorkspace(STLWorkspaceObject theW) {
		theWorkspaceObject = theW;
		updatePlacementStatus(false);
	}
	
	//only to be called when something is moved not on removals
	private void updateCollisionTable(int index) {
		
		STLObject moved = theTransformedSTLs.get(index);
		
		for (int i = 0; i < theTransformedSTLs.size(); i++) {

			STLObject curr = theTransformedSTLs.get(i);
			if (curr == moved)
				continue;

			boolean collision = STLObjectCalculationUtilities.objectsIntersect(curr, moved);
			System.out.println(collision);
			collisionTable.get(index).set(i, collision);
			collisionTable.get(i).set(index, collision);
		}
		updatePlacementStatus(false);
	}
		
	private void updateCollisionTable() {
		int size = theBaseSTLs.size();
		for (int i = 0; i < size; i++) {
			STLObject stgA = theTransformedSTLs.get(i);
			for (int j = i + 1; j < size; j++) {
				STLObject stgB = theTransformedSTLs.get(j);
				boolean coll = STLObjectCalculationUtilities.objectsIntersect(
						stgA, stgB);
				collisionTable.get(j).set(i, coll);
				collisionTable.get(i).set(j, coll);
			}
		}

	}

	private void updatePlacementStatus(boolean updateCollisionTableFirst) {
		if (updateCollisionTableFirst) {
			updateCollisionTable();
		}

		for (int i = 0; i < theBaseSTLs.size(); i++) {
			if (theWorkspaceObject != null
					&& !theWorkspaceObject.stlIsInside(theTransformedSTLs.get(i))) {
				placementStatuses.set(i, PlacementStatus.NOT_IN_WORKSPACE);
				continue;
			}
			boolean collision = collisionTable.get(i).contains(true);
			if (collision) {
				placementStatuses.set(i, PlacementStatus.MODEL_COLLISION);
			} else if (theWorkspaceObject == null) {
				placementStatuses.set(i, PlacementStatus.UNKOWN);
			} else {
				placementStatuses.set(i, PlacementStatus.VALID_PLACEMENT);
			}

		}
		System.out.println("Placement Statuses: " + placementStatuses);
		System.out.println("Collision Table\n");
		for (ArrayList<Boolean> ab : collisionTable)
			System.out.println(ab);
		System.out.println("End collision table");
	}

	
	@Override
	public Iterator<STLObject> getBaseSTLObjectIterator() {
		return this.theBaseSTLs.iterator();
	}

	
	@Override
	public Iterator<double[]> getTransformMatrixIterator() {
		return this.theTransformMatrices.iterator();
	}
	
}
