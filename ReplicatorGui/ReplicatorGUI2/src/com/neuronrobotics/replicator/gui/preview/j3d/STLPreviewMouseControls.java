package com.neuronrobotics.replicator.gui.preview.j3d;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.geom.Point2D;

import javax.swing.SwingUtilities;

import com.sun.j3d.utils.picking.PickCanvas;
import com.sun.j3d.utils.picking.PickResult;

public class STLPreviewMouseControls extends MouseAdapter  {

	private STLPreviewCanvas3D thePreview;

	private Point2D lastLocation;
	
	private PickCanvas thePickCanvas;
	
	long lastTime;
	int ct;
		
	boolean mousePressed;
	
	private MouseControlMode theMode;
	
	public enum MouseControlMode{
		
		CAMERA_ROTATE {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
				double scaleY, scaleZ;
				scaleY = scaleZ = 40.0;
				
				double radY = yDist/scaleY;
				double radZ = xDist/scaleZ;
								
				preview.getTheCameraController().rotateCameraXZ(radZ);
				preview.getTheCameraController().rotateCameraUp(radY);
			}
			
			public String toString(){
				return "Camera Rotate";
			}
			
		},
		MODEL_ROTATE_X {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
			
				if(preview.getCurrentSTLTransform()==null) return;
				preview.getCurrentSTLTransform().rotateX(yDist/rotateScale);
			}
			
			public String toString(){
				return "Model Rotate (X)";
			}

		
		},
		MODEL_ROTATE_Y {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
				STLTransformGroup current = preview.getCurrentSTLTransform();
				if(current!=null) current.rotateAroundUpVector(xDist/rotateScale);
			}
			
			public String toString(){
				return "Model Rotate (Y)";
			}
		
		},	
		MODEL_ROTATE_Z {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
				if(preview.getCurrentSTLTransform()==null) return;		
				preview.getCurrentSTLTransform().rotateZ(xDist/rotateScale);
			}
			
			public String toString(){
				return "Model Rotate (Z)";
			}

		
		},		
		MODEL_TRANSLATE_XY {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
				//preview.translateX(xDist);
				//preview.translateY(yDist);
				
				//double scale = 40.0;
				if(preview.getCurrentSTLTransform()==null) return;
				STLTransformGroup currObj = preview.getCurrentSTLTransform();
								
				currObj.translateLeftRight(xDist/translateScale);
				currObj.translateUpDown(yDist/translateScale);
				
			}
			
			public String toString(){
				return "Model Translate (XY)";
			}

			
		},
		MODEL_TRANSLATE_ZY {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
				//preview.translateZ(xDist);
				//preview.translateY(yDist);
				if(preview.getCurrentSTLTransform()==null) return;			
				preview.getCurrentSTLTransform().translateBackForth(xDist/translateScale);
				preview.getCurrentSTLTransform().translateUpDown(yDist/translateScale);
			}
			
			public String toString(){
				return "Model Translate (ZY)";
			}

			
		},
		MODEL_TRANSLATE_XZ{

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview,
					double xDist, double yDist) {
				if(preview.getCurrentSTLTransform()==null) return;
				System.out.println("Starting translate");
				preview.getCurrentSTLTransform().translateLeftRight(xDist/translateScale);
				preview.getCurrentSTLTransform().translateBackForth(yDist/translateScale);
				System.out.println("Finished translate");
				
			}
			
			public String toString(){
				return "Model Translate (XZ)";
			}
			
		};
		
		double translateScale = 15.0;
		double rotateScale = 40.0;
		
		protected abstract void mouseDragged(STLPreviewCanvas3D preview,double xDist, double yDist);

		public static MouseControlMode[] getModes() {
			return new MouseControlMode[]{CAMERA_ROTATE,MODEL_ROTATE_Y,/*MODEL_ROTATE_Z,MODEL_ROTATE_X,MODEL_TRANSLATE_XY,MODEL_TRANSLATE_ZY,*/MODEL_TRANSLATE_XZ};
		}
		
	}
	
	public void setMouseControlMode(MouseControlMode mcm){
		this.theMode = mcm;
		thePreview.alertMouseControlModeChanged(this);
	}
		
	public STLPreviewMouseControls(STLPreviewCanvas3D prev){
		thePreview = prev;
		thePreview.addMouseListener(this);
		thePreview.addMouseMotionListener(this);
		mousePressed = false;
		lastLocation = new Point2D.Double();
		lastTime = System.currentTimeMillis();
		ct = 0;
		//theMode = MouseControlMode.CAMERA_ROTATE;
		theMode = MouseControlMode.MODEL_ROTATE_X;
		
		thePickCanvas = new PickCanvas(prev,prev.getMainBranch());
		thePickCanvas.setMode(PickCanvas.BOUNDS);
	}
		
	@Override
	public void mouseDragged(MouseEvent arg0) {
		long tempTime = System.currentTimeMillis();
		if((tempTime-lastTime)<20) return; 
		lastTime = tempTime;
						
		Point2D temp = arg0.getLocationOnScreen();
		
		
		double yDist = (temp.getY() - lastLocation.getY());
		double xDist = (temp.getX() - lastLocation.getX());
		
		lastLocation = temp;
		
		//if(thePreview.getCurrentSTLTransform()!=null)
		theMode.mouseDragged(thePreview, xDist, yDist);
		
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
		thePickCanvas.setShapeLocation(arg0);
		if (this.thePreview.getMainBranch().isLive()) {
			PickResult result = thePickCanvas.pickClosest();
			this.thePreview.setCurrentPick(result);
		}
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		
		thePickCanvas.setShapeLocation(arg0);
		
		if (this.thePreview.getMainBranch().isLive()) {
			PickResult result = thePickCanvas.pickClosest();
			this.thePreview.setCurrentPick(result);
		}
		
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;		
		
		if(SwingUtilities.isRightMouseButton(arg0)){
			thePreview.alertRightClick(arg0.getX(),arg0.getY());
			return;
		}
		
		
		//Point3f dim = thePreview.getWorkspaceDimensions();
		double zoomDist = 6;//Math.max(Math.max(dim.x,dim.y),dim.z)/10.0;
		
		if(arg0.isShiftDown()) zoomDist*=-1;
		
		if(arg0.getClickCount()>=2){
			thePreview.getTheCameraController().zoom(zoomDist);
		}
		//thePickCanvas.pickClosest();
		
		
		
		//System.out.println("Picked: "+result);

	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		
		thePickCanvas.setShapeLocation(arg0);
		
		if (this.thePreview.getMainBranch().isLive()) {
			PickResult result = thePickCanvas.pickClosest();
			this.thePreview.setCurrentPick(result);
			System.out.println("Picked: " + result);
		}
		
		
						
		mousePressed = true;
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		mousePressed = false;
		
	}
	
	public MouseControlMode getCurrentMode() {
		return theMode;
	}

}
