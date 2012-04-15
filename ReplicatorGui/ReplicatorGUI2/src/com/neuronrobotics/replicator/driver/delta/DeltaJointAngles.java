package com.neuronrobotics.replicator.driver.delta;

public class DeltaJointAngles {
	private double theta1, theta2,  theta3;
	/**
	 * All angles in radians
	 * @param theta1
	 * @param theta2
	 * @param theta3
	 */
	public DeltaJointAngles(double theta1, double theta2, double theta3){
		setTheta1(theta1);
		setTheta2(theta2);
		setTheta3(theta3);
	}
	private void setTheta1(double theta1) {
		this.theta1 = theta1;
	}
	public double getTheta1() {
		return theta1;
	}
	private void setTheta2(double theta2) {
		this.theta2 = theta2;
	}
	public double getTheta2() {
		return theta2;
	}
	private void setTheta3(double theta3) {
		this.theta3 = theta3;
	}
	public double getTheta3() {
		return theta3;
	}
}
