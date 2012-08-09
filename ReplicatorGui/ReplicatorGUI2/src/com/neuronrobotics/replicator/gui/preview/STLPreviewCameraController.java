package com.neuronrobotics.replicator.gui.preview;

import javax.vecmath.Point3d;
import javax.vecmath.Tuple3d;
import javax.vecmath.Vector3d;

import com.neuronrobotics.replicator.gui.stl.STLObject;

public class STLPreviewCameraController {

	/**
	 * enum for encapsulating camera focus methods currently provides simple
	 * methods for getting current point to focus on as well as the base camera
	 * position, both of which may be dependent on selected mode
	 * 
	 */
	public enum CameraMode {

		WORKSPACE_BASE {

			@Override
			public Point3d getFocus(STLPreviewCanvas3D sp) {
				return new Point3d(0, 0, 0); // TODO
			}

			@Override
			public Point3d getBaseCameraPosition(STLPreviewCanvas3D sp) {
				double m = Math.max(60, Math.max(60, 60)); // TODO get from
															// STLWorkspaceBranchGroup
				return new Point3d(2 * m, 2 * m, 2 * m);
			}

			public String toString() {
				return "Focus Camera on Workspace";
			}

			@Override
			public boolean cameraIsFixed() {
				return preferCameraFixed;
			}

			@Override
			public Vector3d getCameraOrientation() {
				return new Vector3d(0, 1, 0);
			}
		},
		STL_CENTER {

			@Override
			public Point3d getFocus(STLPreviewCanvas3D sp) {

				if (sp.getCurrentSTLTransform() == null)
					return ORIGIN.getFocus(sp);

				Point3d newFocus = new Point3d(sp.getCurrentSTLTransform()
						.getCurrentCenter());

				/*
				 * System.out.println("Current center "+newFocus);
				 * 
				 * System.out.println("Base Min (STLTransform)"+
				 * sp.stlTransform.getBaseCenter());
				 * System.out.println("Base min (STLObject)"+
				 * sp.theSTLObject.getCenter()); System.out.println();
				 */

				return new Point3d(newFocus);
			}

			@Override
			public Point3d getBaseCameraPosition(STLPreviewCanvas3D sp) {

				if (sp.getCurrentSTLTransform() == null)
					return ORIGIN.getBaseCameraPosition(sp);
				STLObject currObj = sp.getcurrentSTLTransform().getSTLObject();
				double m = Math.max(currObj.getXLength(), Math.max(currObj.getYLength(), currObj
						.getZLength()));
				Point3d basePos = new Point3d(2 * m, 2 * m, 2 * m);
				basePos.add(this.getFocus(sp));
				System.out.println("Base camera position " + basePos);
				return basePos;
			}

			public String toString() {
				return "Focus Camera on STL";
			}

			@Override
			public boolean cameraIsFixed() {
				return preferCameraFixed;
			}

			@Override
			public Vector3d getCameraOrientation() {
				return new Vector3d(0, 1, 0);
			}
		},
		ORIGIN {
			@Override
			public Point3d getFocus(STLPreviewCanvas3D sp) {
				return new Point3d(0, 0, 0);
			}

			@Override
			public Point3d getBaseCameraPosition(STLPreviewCanvas3D sp) {
				return new Point3d(20, 20, 20);
			}

			@Override
			public boolean cameraIsFixed() {
				return preferCameraFixed;
			}

			@Override
			public Vector3d getCameraOrientation() {
				return new Vector3d(0, 1, 0);
			}
		},
		AERIAL {

			@Override
			public Point3d getFocus(STLPreviewCanvas3D sp) {
				if (sp.getTheWorkspaceTransform() != null)
					return WORKSPACE_BASE.getFocus(sp);
				if (sp.getCurrentSTLTransform() != null)
					return STL_CENTER.getFocus(sp);
				return ORIGIN.getFocus(sp);
			}

			@Override
			public Point3d getBaseCameraPosition(STLPreviewCanvas3D sp) {
				Point3d camPos;
				if (sp.getTheWorkspaceTransform() != null) {
					camPos = WORKSPACE_BASE.getFocus(sp);
					double h;
					if (sp.getCurrentSTLTransform() != null)
						h = sp.getCurrentSTLTransform().getCurrentMax().y * 2;
					else
						h = sp.getTheWorkspaceTransform()
								.getWorkspaceSTLObject().getMax().y * 2;
					return new Point3d(camPos.x, h, camPos.z);
				} else if (sp.getCurrentSTLTransform() != null) {
					camPos = STL_CENTER.getFocus(sp);
					double h = sp.getCurrentSTLTransform().getCurrentMax().y * 2;
					return new Point3d(camPos.x, h, camPos.z);
				} else {
					return new Point3d(0, 20, 0);
				}

			}

			@Override
			public boolean cameraIsFixed() {
				return true;
			}

			@Override
			public Vector3d getCameraOrientation() {
				return new Vector3d(0, 0, -1);
			}
		};

		// may be overridden if mode requires fixed camera
		public boolean preferCameraFixed = false;

		public abstract Point3d getFocus(STLPreviewCanvas3D sp);

		public abstract Point3d getBaseCameraPosition(STLPreviewCanvas3D sp);

		public abstract boolean cameraIsFixed();

		public abstract Vector3d getCameraOrientation();

		public static CameraMode[] getModes() {
			return new CameraMode[] { WORKSPACE_BASE, STL_CENTER, ORIGIN,
					AERIAL };
		}

	};

	private STLPreviewCanvas3D thePreview;

	private CameraMode currentCameraFocusMode;

	public STLPreviewCameraController(STLPreviewCanvas3D thePrev) {
		thePreview = thePrev;
		currentCameraFocusMode = CameraMode.ORIGIN;
	}

	public void zoom(double d) {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		Vector3d dirVector = new Vector3d();
		dirVector.add(tempDir);
		dirVector.sub(tempPos);
		dirVector.normalize();
		dirVector.scale(d);
		// System.out.println(dirVector);

		// Prevents zooming past focal point
		if (d <= tempPos.distance(tempDir))
			tempPos.add(dirVector);

		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	public void panX(double d) {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		tempPos.add(new Point3d(0, 0, d));
		tempDir.add(new Point3d(0, 0, d));
		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	public void panY(double d) {
		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		tempPos.add(new Point3d(0, d, 0));
		tempDir.add(new Point3d(0, d, 0));
		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	public void panZ(double d) {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		tempPos.add(new Point3d(d, 0, 0));
		tempDir.add(new Point3d(d, 0, 0));
		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	public void panTo(Tuple3d focus) {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		if (tempPos == null || tempDir == null) {
			resetCamera();
		}

		Vector3d newPos = new Vector3d(0, 0, 0);
		newPos.add(tempPos);
		newPos.sub(tempDir);
		newPos.add(focus);

		tempDir = new Point3d(focus);
		tempPos = new Point3d(newPos);

		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	public void resetCamera() {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempPos = currentCameraFocusMode.getBaseCameraPosition(thePreview);
		tempDir = currentCameraFocusMode.getFocus(thePreview);
		tempOri = currentCameraFocusMode.getCameraOrientation();

		thePreview.setCamera(tempPos, tempDir, tempOri);

		STLObject currObj = thePreview.getCurrentSTLTransform().getSTLObject();
		
		double clipDist = 900;
		if (thePreview.getCurrentSTLTransform() != null) {
			clipDist = tempPos.distance(new Point3d(thePreview
					.getCurrentSTLTransform().getCurrentCenter()));
			clipDist += Math.max(Math.max(currObj
					.getXLength(), currObj.getYLength()),
					currObj.getZLength());
		}
		thePreview.getView().setBackClipDistance(clipDist);

	}

	public void resetCamera(CameraMode newMode) {
		currentCameraFocusMode = newMode;
		resetCamera();
	}

	public void setCameraFocusMode(CameraMode newMode) {
		currentCameraFocusMode = newMode;
		// tempDir = currentCameraFocusMode.getFocus(thePreview);
		autoPan();
	}

	public void rotateCameraXZ(double rot) {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		Vector3d vec = new Vector3d();
		vec.add(tempPos);
		vec.sub(tempDir);

		double radius = Math.sqrt((vec.x * vec.x) + (vec.z * vec.z));

		double currentAngle = Math.acos(vec.x / radius);
		if (vec.z < 0)
			currentAngle = (2 * Math.PI) - currentAngle;

		double newAngle = currentAngle + rot;
		double newX = radius * Math.cos(newAngle) + tempDir.x;
		double newZ = radius * Math.sin(newAngle) + tempDir.z;

		/*
		 * System.out.println("Radius: "+radius);
		 * System.out.println("Initial Angle: "+currentAngle);
		 * System.out.println("Delta Angle: "+rot);
		 * System.out.println("Final Angle:" + newAngle);
		 * System.out.println("Initial position: "+tempPos);
		 */
		tempPos = new Point3d(newX, tempPos.y, newZ);
		/*
		 * System.out.println("Final position: "+tempPos);
		 * System.out.println("//////////////");
		 */

		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	public void rotateCameraUp(double rot) {

		Point3d tempPos, tempDir;
		Vector3d tempOri;

		tempDir = new Point3d(thePreview.getCameraDirection());
		tempPos = new Point3d(thePreview.getCameraPosition());
		tempOri = new Vector3d(thePreview.getCameraOrientation());

		Vector3d positionVector = new Vector3d();
		positionVector.add(tempPos);
		positionVector.sub(tempDir);

		double radius = positionVector.length();

		double currentAngle = Math.asin(positionVector.y / radius);

		double newAngle = rot + currentAngle;

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

		thePreview.setCamera(tempPos, tempDir, tempOri);
	}

	protected void autoPan() {

		panTo(this.currentCameraFocusMode.getFocus(thePreview));

	}

}
