package com.neuronrobotics.replicator.gui.preview;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Point2D;

public class STLPreviewMouseControls implements MouseListener, MouseMotionListener{

	STLPreviewCanvas3D thePreview;

	Point2D lastLocation;
	
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
								
				preview.rotateCameraXZ(radZ);
				preview.rotateCameraUp(radY);
			}
			
			public String toString(){
				return "Camera Rotate";
			}
			
		},
		MODEL_ROTATE_X {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
			
				
				preview.rotateX(yDist/rotateScale);
			}
			
			public String toString(){
				return "Model Rotate (X)";
			}

		
		},
		MODEL_ROTATE_Y {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
				preview.rotateY(xDist/rotateScale);
			}
			
			public String toString(){
				return "Model Rotate (Y)";
			}
		
		},	
		MODEL_ROTATE_Z {

			@Override
			protected void mouseDragged(STLPreviewCanvas3D preview, double xDist, double yDist) {
								
				preview.rotateZ(xDist/rotateScale);
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
				
				preview.translateLeftRight(xDist/translateScale);
				preview.translateUpDown(yDist/translateScale);
				
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
				
				preview.translateBackForth(xDist/translateScale);
				preview.translateUpDown(yDist/translateScale);
			}
			
			public String toString(){
				return "Model Translate (ZY)";
			}

			
		};
		
		double translateScale = 15.0;
		double rotateScale = 40.0;
		
		protected abstract void mouseDragged(STLPreviewCanvas3D preview,double xDist, double yDist);

		public static MouseControlMode[] getModes() {
			return new MouseControlMode[]{CAMERA_ROTATE,MODEL_ROTATE_X,MODEL_ROTATE_Y,MODEL_ROTATE_Z,MODEL_TRANSLATE_XY,MODEL_TRANSLATE_ZY};
		}
		
	}
	
	public void setMouseControlMode(MouseControlMode mcm){
		this.theMode = mcm;
	}
		
	public STLPreviewMouseControls(STLPreviewCanvas3D prev){
		thePreview = prev;
		thePreview.getCanvas3D().addMouseListener(this);
		thePreview.getCanvas3D().addMouseMotionListener(this);
		mousePressed = false;
		lastLocation = new Point2D.Double();
		lastTime = System.currentTimeMillis();
		ct = 0;
		//theMode = MouseControlMode.CAMERA_ROTATE;
		theMode = MouseControlMode.MODEL_ROTATE_X;
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
		
		theMode.mouseDragged(thePreview, xDist, yDist);
		
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
		
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;
		
		//Point3f dim = thePreview.getWorkspaceDimensions();
		//TODO
		double zoomDist = 6;//Math.max(Math.max(dim.x,dim.y),dim.z)/10.0;
		
		if(arg0.getClickCount()>=2){
			thePreview.zoom(zoomDist);
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
		mousePressed = true;
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		mousePressed = false;
		
	}

}
