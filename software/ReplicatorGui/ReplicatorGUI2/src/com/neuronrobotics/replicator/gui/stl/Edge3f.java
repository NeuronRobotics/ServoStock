package com.neuronrobotics.replicator.gui.stl;

import javax.vecmath.Point3f;

public class Edge3f {

	private Point3f p0, p1;

	public Edge3f(Point3f a, Point3f b) {
		p0 = a;
		p1 = b;
	}

	public boolean equalsEpsilon(Edge3f edge, float epsilon) {
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