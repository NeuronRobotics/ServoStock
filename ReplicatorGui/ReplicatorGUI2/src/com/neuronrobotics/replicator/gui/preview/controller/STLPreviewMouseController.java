package com.neuronrobotics.replicator.gui.preview.controller;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;
import java.util.ArrayList;
import java.util.Arrays;

import javax.media.j3d.Transform3D;
import javax.swing.SwingUtilities;
import javax.vecmath.Matrix4d;

import com.neuronrobotics.replicator.gui.preview.model.STLWorkspaceModel;
import com.neuronrobotics.replicator.gui.preview.view.STLWorkspaceView;

public class STLPreviewMouseController extends MouseAdapter {

	public enum MouseControlMode {

		CAMERA_ROTATE {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				double scaleY, scaleZ;
				scaleY = scaleZ = 40.0;

				double radY = yDist / scaleY;
				double radZ = xDist / scaleZ;

				theCameraController.revolveCameraXZ(radZ);
				theCameraController.revolveCameraUp(radY);
			}

			public String toString() {
				return "Camera Rotate";
			}

		},
		MODEL_ROTATE_X {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				stlController.rotateX(yDist / rotateScale);
			}

			public String toString() {
				return "Model Rotate (X)";
			}

		},
		MODEL_ROTATE_Y {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				double rotAng = xDist/rotateScale;
				double[] currT = new double[16];
				double[] baseT = new double[16];
				System.out.println("Rotation angle: "+rotAng);
				stlController.getCurrentTransform(currT);
				stlController.getCurrentTransform(baseT);
				System.out.println("Initial Transform: "+Arrays.toString(currT));
								
				stlController.rotateAroundUpVector(xDist / rotateScale);
				Transform3D testTrans = new Transform3D(currT);
				testTrans.rotZ(rotAng);				
				stlController.getCurrentTransform(currT);
				System.out.println("My calculated transform: "+Arrays.toString(currT));
				
				
				//Matrix4d baseMat = new Matrix4d(baseT);
				Matrix4d currMat = new Matrix4d(currT);
				currMat.invert();
				System.out.println("Curr mat inverted? "+currMat);
				
				testTrans.get(currT);
				System.out.println("T3D calculated transform: "+Arrays.toString(currT));
				
				
				
			}

			public String toString() {
				return "Model Rotate (Y)";
			}

		},
		MODEL_ROTATE_Z {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				stlController.rotateZ(xDist / rotateScale);
			}

			public String toString() {
				return "Model Rotate (Z)";
			}

		},
		MODEL_TRANSLATE_XY {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				stlController.translateLeftRight(xDist / translateScale);
				stlController.translateUpDown(yDist / translateScale);
			}

			public String toString() {
				return "Model Translate (XY)";
			}

		},
		MODEL_TRANSLATE_ZY {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				stlController.translateBackForth(xDist / translateScale);
				stlController.translateUpDown(yDist / translateScale);
			}

			public String toString() {
				return "Model Translate (ZY)";
			}

		},
		MODEL_TRANSLATE_XZ {

			@Override
			protected void mouseDragged(
					GeneralSTLTransformHelper stlController,
					GeneralCameraController theCameraController, double xDist,
					double yDist) {
				stlController.translateLeftRight(xDist / translateScale);
				stlController.translateBackForth(yDist / translateScale);
			}

			public String toString() {
				return "Model Translate (XZ)";
			}

		};

		double translateScale = 15.0;
		double rotateScale = 40.0;

		protected abstract void mouseDragged(
				GeneralSTLTransformHelper stlController,
				GeneralCameraController theCameraController, double xDist,
				double yDist);

		public static MouseControlMode[] getModes() {
			return new MouseControlMode[] { CAMERA_ROTATE, MODEL_ROTATE_Y,/*
																		 * MODEL_ROTATE_Z
																		 * ,
																		 * MODEL_ROTATE_X
																		 * ,
																		 * MODEL_TRANSLATE_XY
																		 * ,
																		 * MODEL_TRANSLATE_ZY
																		 * ,
																		 */
					MODEL_TRANSLATE_XZ };
		}

	}

	private GeneralSTLTransformHelper stlTransformHelper;
	private GeneralCameraController theCameraController;
	private STLWorkspaceView theView;
	private STLWorkspaceModel theModel;
	
	private double[] currentPickTransform = new double[16];
	
	

	private MouseControlMode currentMode = MouseControlMode.MODEL_ROTATE_Y;
	private Point2D lastLocation;
	
	private ArrayList<STLPreviewMouseControlListener> theListeners;

	public STLPreviewMouseController(STLWorkspaceView view, STLWorkspaceModel model,GeneralSTLTransformHelper stlc,
			GeneralCameraController tgc) {
		stlTransformHelper = stlc;
		theModel = model;
		theCameraController = tgc;
		theView = view;
		theView.getComponent().addMouseListener(this);
		theView.getComponent().addMouseMotionListener(this);
		
		theListeners  = new ArrayList<STLPreviewMouseControlListener>();
		
	}
	
	public void addSTLPreviewMouseControlListener(STLPreviewMouseControlListener newL){
		theListeners.add(newL);
	}

	public void setCurrentMouseControlMode(MouseControlMode newMode) {
		currentMode = newMode;
	}

	public MouseControlMode getCurrentMouseControlMode() {
		return currentMode;
	}

	@Override
	public void mouseDragged(MouseEvent arg0) {
		
		//long tempTime = System.currentTimeMillis();
		//System.out.println("Enter mouse drag: "+tempTime);
		//if ((tempTime - lastTime) < 20)
		//	return;
		//lastTime = tempTime;

		Point2D temp = arg0.getLocationOnScreen();

		double yDist = (temp.getY() - lastLocation.getY());
		double xDist = (temp.getX() - lastLocation.getX());

		lastLocation = temp;

		// if(thePreview.getCurrentSTLTransform()!=null)
		
		currentMode.mouseDragged(stlTransformHelper, theCameraController, xDist,	yDist);		
		
		//System.out.println("About to update model: "+ System.currentTimeMillis());
		
		this.updateModel();

		//System.out.println("Exit mouse drag: "+System.currentTimeMillis());
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
		updatePick(arg0);
	}

	private void updatePick(MouseEvent arg0) {
		//System.out.println("Update pick called");
		theView.setPickLocation(arg0.getX(), arg0.getY());		
		theModel.getTransformMatrix(theView.getPick(), currentPickTransform);
		stlTransformHelper.setCurrentTransform(currentPickTransform);
	}
	
	private void updateModel(){
	//	System.out.println("Enter update model: "+System.currentTimeMillis());
		stlTransformHelper.getCurrentTransform(currentPickTransform);
	//	System.out.println("About to set actual transform: "+System.currentTimeMillis());
		theModel.setTransformMatrix(theView.getPick(), currentPickTransform);
		//System.out.println("Exit update model: "+System.currentTimeMillis());
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		updatePick(arg0);
		
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;

		if (SwingUtilities.isRightMouseButton(arg0)) {
			fireRightClick(arg0.getLocationOnScreen().x,arg0.getLocationOnScreen().y);
			return;
		}

		// Point3f dim = thePreview.getWorkspaceDimensions();
		double zoomDist = 6;// Math.max(Math.max(dim.x,dim.y),dim.z)/10.0;

		if (arg0.isShiftDown())
			zoomDist *= -1;

		if (arg0.getClickCount() >= 2) {
			this.theCameraController.zoom(zoomDist);
		}

	}

	private void fireRightClick(int x, int y) {
		for(STLPreviewMouseControlListener l:theListeners){
			l.alertRightClick(x, y);
		}
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {

	}

	@Override
	public void mouseExited(MouseEvent arg0) {

	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		updatePick(arg0);

		//mousePressed = true;
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		//mousePressed = false;
	}

}
