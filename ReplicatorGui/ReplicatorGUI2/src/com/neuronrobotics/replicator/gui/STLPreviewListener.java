package com.neuronrobotics.replicator.gui;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Point2D;

import javax.vecmath.Point2d;

public class STLPreviewListener implements MouseListener, MouseMotionListener{

	STLPreview thePreview;
	
	Point2D lastLocation;
	
	boolean mousePressed;
		
	public STLPreviewListener(STLPreview prev){
		thePreview = prev;
		thePreview.addMouseListener(this);
		thePreview.addMouseMotionListener(this);
		mousePressed = false;
		lastLocation = new Point2D.Double();
	}
	
	@Override
	public void mouseDragged(MouseEvent arg0) {
		// TODO Auto-generated method stub
		
		double radY = 0;
		double radZ = 0;
		
				
		Point2D temp = arg0.getLocationOnScreen();
		
		double scaleY;
		double scaleZ;
		scaleY=scaleZ=40.0;
		
		radY = (temp.getY() - lastLocation.getY())/scaleY;
		radZ = (temp.getX() - lastLocation.getX())/scaleZ;
		
		lastLocation = temp;
		
		thePreview.rotateCameraUp(radY);
		thePreview.rotateCameraXZ(radZ);
		
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
