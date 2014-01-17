package com.neuronrobotics.replicator.gui.preview.controller;

import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import com.neuronrobotics.replicator.gui.preview.view.STLWorkspaceView;


public class DefaultGeneralCameraController implements GeneralCameraController {
	
	private STLWorkspaceView theView;
	
	private double[] cameraPosition = new double[3], cameraFocus = new double[3];
	
	public DefaultGeneralCameraController(STLWorkspaceView view){
		theView = view;
	}
		
	@Override
	public void zoom(double dist) {
		this.validateCameraData();

		Point3d tempPos, tempDir;

		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		Vector3d dirVector = new Vector3d();
		dirVector.add(tempDir);
		dirVector.sub(tempPos);
		dirVector.normalize();
		dirVector.scale(dist);
		// System.out.println(dirVector);

		// Prevents zooming past focal point
		if (dist <= tempPos.distance(tempDir))
			tempPos.add(dirVector);
		
		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}

	@Override
	public void panX(double dist) {
		validateCameraData();

		Point3d tempPos, tempDir;

		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		tempPos.add(new Point3d(0, 0, dist));
		tempDir.add(new Point3d(0, 0, dist));
		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}

	@Override
	public void panY(double dist) {
		validateCameraData();
		
		Point3d tempPos, tempDir;

		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		tempPos.add(new Point3d(0, dist, 0));
		tempDir.add(new Point3d(0, dist, 0));
		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}

	@Override
	public void panZ(double dist) {
		validateCameraData();
		
		Point3d tempPos, tempDir;

		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		tempPos.add(new Point3d(dist , 0, 0));
		tempDir.add(new Point3d(dist , 0, 0));
		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}

	@Override
	public void panTo(double[] focus) {
		validateCameraData();
		
		Point3d tempPos, tempDir;
		
		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		Vector3d newPos = new Vector3d(0, 0, 0);
		newPos.add(tempPos);
		newPos.sub(tempDir);
		newPos.add(new Point3d(focus));

		tempDir = new Point3d(focus);
		tempPos = new Point3d(newPos);

		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}
	
	@Override
	public void revolveCameraXZ(double radians) {
		validateCameraData();
		
		Point3d tempPos, tempDir;

		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		Vector3d vec = new Vector3d();
		vec.add(tempPos);
		vec.sub(tempDir);

		double radius = Math.sqrt((vec.x * vec.x) + (vec.z * vec.z));

		double currentAngle = Math.acos(vec.x / radius);
		if (vec.z < 0)
			currentAngle = (2 * Math.PI) - currentAngle;

		double newAngle = currentAngle +radians;
		double newX = radius * Math.cos(newAngle) + tempDir.x;
		double newZ = radius * Math.sin(newAngle) + tempDir.z;

		/*
		 * System.out.println("Radius: "+radius);
		 * System.out.println("Initial Angle: "+currentAngle);
		 * System.out.println("Delta Angle: "+radians);
		 * System.out.println("Final Angle:" + newAngle);
		 * System.out.println("Initial position: "+tempPos);
		 */
		tempPos = new Point3d(newX, tempPos.y, newZ);
		/*
		 * System.out.println("Final position: "+tempPos);
		 * System.out.println("//////////////");
		 */

		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}

	@Override
	public void revolveCameraUp(double radians) {
		validateCameraData();
		
		Point3d tempPos, tempDir;

		tempDir = new Point3d(cameraFocus);
		tempPos = new Point3d(cameraPosition);

		Vector3d positionVector = new Vector3d();
		positionVector.add(tempPos);
		positionVector.sub(tempDir);

		double radius = positionVector.length();

		double currentAngle = Math.asin(positionVector.y / radius);

		double newAngle = radians + currentAngle;

		double newY = Math.sin(newAngle) * radius;

		double t = positionVector.x / positionVector.z;

		double newZ = Math.sqrt(((radius * radius) - (newY * newY))
				/ ((t * t) + 1));

		if (positionVector.z < 0)
			newZ *= -1;

		double newX = newZ * t;

		newY += tempDir.y;
		newZ += tempDir.z;
		newX += tempDir.x;

		tempPos = new Point3d(newX, newY, newZ);

		tempPos.get(cameraPosition);
		tempDir.get(cameraFocus);

		theView.setCamera(cameraPosition,cameraFocus);
	}

	@Override
	public void setCamera(double[] position, double[] focus) {
		theView.setCamera(position, focus);		
		validateCameraData();
	}
	
	private void validateCameraData(){
		theView.getCameraData(cameraPosition, cameraFocus);
	}

}
