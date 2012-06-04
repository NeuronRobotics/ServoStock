package com.neuronrobotics.replicator.gui.preview;

import java.awt.Container;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Point2D;

import javax.vecmath.Point2d;

public class STLPreviewMouseControls implements MouseListener, MouseMotionListener{

	STLPreview thePreview;

	Point2D lastLocation;
	
	long lastTime;
	int ct;
	
	boolean mousePressed;
		
	public STLPreviewMouseControls(STLPreview prev){
		thePreview = prev;
		thePreview.addMouseListener(this);
		thePreview.addMouseMotionListener(this);
		mousePressed = false;
		lastLocation = new Point2D.Double();
		lastTime = System.currentTimeMillis();
		ct = 0;
	}
	
	@Override
	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		long tempTime = System.currentTimeMillis();
		if((tempTime-lastTime)<20) return; 
		lastTime = tempTime;
		
		double radY = 0;
		double radZ = 0;
		
				
		Point2D temp = arg0.getLocationOnScreen();
		
		double scaleY;
		double scaleZ;
		scaleY=scaleZ=40.0;
		
		radY = (temp.getY() - lastLocation.getY())/scaleY;
		radZ = (temp.getX() - lastLocation.getX())/scaleZ;
		
		System.out.println("X change "+(temp.getX() - lastLocation.getX()));
		System.out.println("Current x: "+temp.getX());
		System.out.println("Last x: "+lastLocation.getX());
		System.out.println("RadZ: "+radZ);
		System.out.println("Call count: "+(++ct));
		
		
		lastLocation = temp;
		
		
		thePreview.rotateCameraXZ(radZ);
		thePreview.rotateCameraUp(radY);
				
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
		// TODO Auto-generated method stub
		Point2D temp = arg0.getLocationOnScreen();
		//lastLocation = temp;
		
	}

	@Override
	public void mouseClicked(MouseEvent arg0) {
		// TODO Auto-generated method stub
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;
		
		if(arg0.getClickCount()>=2){
			thePreview.zoom(3);
		}
		
	}

	@Override
	public void mouseEntered(MouseEvent arg0) {
		// TODO Auto-generated method stub
		Point2D temp = arg0.getLocationOnScreen();
		//lastLocation = temp;
	}

	@Override
	public void mouseExited(MouseEvent arg0) {
		// TODO Auto-generated method stub
		Point2D temp = arg0.getLocationOnScreen();
		//lastLocation = temp;
	}

	@Override
	public void mousePressed(MouseEvent arg0) {
		// TODO Auto-generated method stub
		mousePressed = true;
		Point2D temp = arg0.getLocationOnScreen();
		lastLocation = temp;
	}

	@Override
	public void mouseReleased(MouseEvent arg0) {
		// TODO Auto-generated method stub
		mousePressed = false;
		Point2D temp = arg0.getLocationOnScreen();
		//lastLocation = temp;
		
	}

}
