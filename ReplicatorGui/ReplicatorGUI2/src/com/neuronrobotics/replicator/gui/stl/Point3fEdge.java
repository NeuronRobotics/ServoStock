package com.neuronrobotics.replicator.gui.stl;

import javax.vecmath.Point3f;

public class Point3fEdge {

	private Point3f p0, p1;

	public Point3fEdge(Point3f a, Point3f b) {
		p0 = a;
		p1 = b;
	}

	public boolean equalsEpsilon(Point3fEdge edge, float epsilon) {
		return ((p0.epsilonEquals(edge.p0, epsilon) && p1.epsilonEquals(
				edge.p1, epsilon)) || (p1.epsilonEquals(edge.p0, epsilon) && p0
				.epsilonEquals(edge.p1, epsilon)));
	}

	public Point3f getPoint1() {
		return p0;
	}
	
	public Point3f getPoint2() {
		return p1;
	}

}