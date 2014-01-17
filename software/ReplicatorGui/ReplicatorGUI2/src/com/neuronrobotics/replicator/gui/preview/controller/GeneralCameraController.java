package com.neuronrobotics.replicator.gui.preview.controller;

public interface GeneralCameraController {
	
	/**
	 * Zooms along current sight vector by given distance (dist)
	 * @param dist
	 */
	public void zoom(double dist);

	/**
	 * Pans camera along x axis by given distance
	 * @param dist
	 */
	public void panX(double dist);

	/**
	 * Pans camera along y axis by given distance
	 * @param dist
	 */
	public void panY(double dist);

	/**
	 * Pans camaera along y axis by given distance
	 * @param dist
	 */
	public void panZ(double dist);

	/**
	 * Maintains camera position and orientation but focuses on given point
	 * @param focus
	 */
	public void panTo(double[] focus);
	
	/**
	 * Positions camera at given position point, focusing on given focus point
	 * @param position
	 * @param focus
	 */
	public void setCamera(double[] position, double[] focus);

	/**
	 * Maintains Y value, revolves camera around focal point by radians given
	 * @param radians
	 */
	public void revolveCameraXZ(double radians);

	/**
	 * Revolves camera upwards, maintaining focal distance
	 * @param radians
	 */
	public void revolveCameraUp(double radians);
	
}
