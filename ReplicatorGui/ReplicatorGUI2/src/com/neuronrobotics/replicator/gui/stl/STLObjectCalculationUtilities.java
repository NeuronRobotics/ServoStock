package com.neuronrobotics.replicator.gui.stl;

import java.util.LinkedList;
import java.util.Scanner;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.STLFacet;
import com.neuronrobotics.replicator.gui.stl.STLObject;

public class STLObjectCalculationUtilities {

	public static boolean objectsIntersect(STLObject s1, STLObject s2) {

		if (!boundingBoxesIntersect(s1, s2))
			return false;

		for (STLFacet f1 : s1) {
			for (STLFacet f2 : s2) {
				if (facetsIntersect(f1, f2)) {
					// System.out.println("Facet Intersection found: ");
					// System.out.println("Facet 1: "+f1);
					// System.out.println("Facet 2: "+f2);
					return true;
				}
			}
		}

		return false;
	}

	/*
	 * public static boolean objectsInteresect(STLObject s1, GeneralTransform3D
	 * gt1,STLObject s2, GeneralTransform3D gt2){
	 * if(!boundingBoxesIntersect(s1,gt1,s2,gt2)) return false;
	 * 
	 * for(STLFacet f1:s1){ for(STLFacet f2:s2){
	 * if(facetsIntersect(f1,gt1,f2,gt2)){
	 * //System.out.println("Facet Intersection found: ");
	 * //System.out.println("Facet 1: "+f1);
	 * //System.out.println("Facet 2: "+f2); return true; } } } return false;
	 * 
	 * }
	 * 
	 * private static boolean facetsIntersect(STLFacet f1, GeneralTransform3D
	 * gt1, STLFacet f2, GeneralTransform3D gt2) {
	 * if(!boundingBoxesIntersect(f1,gt1, f2,gt2)) return false;
	 * 
	 * return
	 * (segmentIntersectsFacet(f1.getVertex1(),f1.getVertex2(),gt1,f2,gt2)
	 * ||segmentIntersectsFacet
	 * (f1.getVertex1(),f1.getVertex3(),gt1,f2,gt2)||segmentIntersectsFacet
	 * (f1.getVertex2(),f1.getVertex3(),gt1,f2,gt2));
	 * 
	 * }
	 * 
	 * private static boolean segmentIntersectsFacet(Point3f vertex1, Point3f
	 * vertex3, GeneralTransform3D gt1, STLFacet f2, GeneralTransform3D gt2) {
	 * // TODO Auto-generated method stub return false; }
	 * 
	 * private static boolean boundingBoxesIntersect(STLFacet f1,
	 * GeneralTransform3D gt1, STLFacet f2, GeneralTransform3D gt2) {
	 * 
	 * Point3f f1max = f1.getVertex1(),cand = f1.getVertex2(); Point3f f1min =
	 * f1.getVertex1(); gt1.transform(f1max); gt1.transform(f1min);
	 * gt1.transform(cand); if(cand.x>f1max.x) f1max.setX(cand.x);
	 * if(cand.y>f1max.y) f1max.setY(cand.y); if(cand.z>f1max.z)
	 * f1max.setZ(cand.z); if(cand.x>f1min.x) f1min.setX(cand.x);
	 * if(cand.y>f1min.y) f1min.setY(cand.y); if(cand.z>f1min.z)
	 * f1min.setZ(cand.z); cand.set(f1.getVertex3()); gt1.transform(cand);
	 * if(cand.x>f1max.x) f1max.setX(cand.x); if(cand.y>f1max.y)
	 * f1max.setY(cand.y); if(cand.z>f1max.z) f1max.setZ(cand.z);
	 * if(cand.x>f1min.x) f1min.setX(cand.x); if(cand.y>f1min.y)
	 * f1min.setY(cand.y); if(cand.z>f1min.z) f1min.setZ(cand.z);
	 * 
	 * cand.set(f2.getVertex2()); Point3f f2max = f2.getVertex1(); Point3f f2min
	 * = f2.getVertex1(); gt2.transform(f2max); gt2.transform(f2min);
	 * gt2.transform(cand); if(cand.x>f2max.x) f2max.setX(cand.x);
	 * if(cand.y>f2max.y) f2max.setY(cand.y); if(cand.z>f2max.z)
	 * f2max.setZ(cand.z); if(cand.x>f2min.x) f2min.setX(cand.x);
	 * if(cand.y>f2min.y) f2min.setY(cand.y); if(cand.z>f2min.z)
	 * f2min.setZ(cand.z); cand.set(f2.getVertex3()); gt2.transform(cand);
	 * if(cand.x>f2max.x) f2max.setX(cand.x); if(cand.y>f2max.y)
	 * f2max.setY(cand.y); if(cand.z>f2max.z) f2max.setZ(cand.z);
	 * if(cand.x>f2min.x) f2min.setX(cand.x); if(cand.y>f2min.y)
	 * f2min.setY(cand.y); if(cand.z>f2min.z) f2min.setZ(cand.z);
	 * 
	 * return boundingBoxesIntersect(f1max, f1min, f2max, f2min); }
	 * 
	 * private static boolean boundingBoxesIntersect(STLObject s1,
	 * GeneralTransform3D gt1, STLObject s2, GeneralTransform3D gt2) { //TODO
	 * return false; }
	 */

	public static boolean boundingBoxesIntersect(STLObject s1, STLObject s2) {
		Point3f s1max = s1.getMax();
		Point3f s1min = s1.getMin();

		Point3f s2max = s2.getMax();
		Point3f s2min = s2.getMin();

		return boundingBoxesIntersect(s1max, s1min, s2max, s2min);
	}

	public static boolean boundingBoxesIntersect(STLFacet f1, STLFacet f2) {

		Point3f s1max = f1.getMax();
		Point3f s1min = f1.getMin();

		Point3f s2max = f2.getMax();
		Point3f s2min = f2.getMin();

		return boundingBoxesIntersect(s1max, s1min, s2max, s2min);
	}

	public static boolean boundingBoxesIntersect(Point3f max1, Point3f min1,
			Point3f max2, Point3f min2) {

		/*
		 * if(pointIsWithin(max2,max2,min2)) return true;
		 * if(pointIsWithin(min2,max1,min1)) return true;
		 * if(pointIsWithin(max1,max2,min2)) return true;
		 * if(pointIsWithin(min1,max2,min2)) return true;
		 * if(pointIsWithin(max2,max2,min2)) return true;
		 * if(pointIsWithin(min2,max1,min1)) return true;
		 * if(pointIsWithin(max1,max2,min2)) return true;
		 * if(pointIsWithin(min1,max2,min2)) return true;
		 */
		float[] x1 = { max1.x, min1.x };
		float[] y1 = { max1.y, min1.y };
		float[] z1 = { max1.z, min1.z };
		for (float x : x1) {
			for (float y : y1) {
				for (float z : z1) {
					if (pointIsWithin(x, y, z, max2, min2))
						return true;
				}
			}
		}

		float[] x2 = { max2.x, min2.x };
		float[] y2 = { max2.y, min2.y };
		float[] z2 = { max2.z, min2.z };
		for (float x : x2) {
			for (float y : y2) {
				for (float z : z2) {
					if (pointIsWithin(x, y, z, max1, min1))
						return true;
				}
			}
		}

		// note that this assumes no max/min points are within either
		// bounding box
		// TODO refactor the hell out of this, also it doesn't work

		if (max1.x < max2.x && max1.x > min2.x) {
			if (max1.y > max2.y && min1.y < min2.y)
				return true;
			if (max1.z > max2.z && min1.z < min2.z)
				return true;
		}
		if (max1.y < max2.y && max1.y > min2.y) {
			if (max1.x > max2.x && min1.x < min2.x)
				return true;
			if (max1.z > max2.z && min1.z < min2.z)
				return true;
		}
		if (max1.z < max2.z && max1.z > min2.z) {
			if (max1.y > max2.y && min1.y < min2.y)
				return true;
			if (max1.x > max2.x && min1.x < min2.x)
				return true;
		}

		if (max2.x < max1.x && max2.x > min1.x) {
			if (max2.y > max1.y && min2.y < min1.y)
				return true;
			if (max2.z > max1.z && min2.z < min1.z)
				return true;
		}
		if (max2.y < max1.y && max2.y > min1.y) {
			if (max2.x > max1.x && min2.x < min1.x)
				return true;
			if (max2.z > max1.z && min2.z < min1.z)
				return true;
		}
		if (max2.z < max1.z && max2.z > min1.z) {
			if (max2.y > max1.y && min2.y < min1.y)
				return true;
			if (max2.x > max1.x && min2.x < min1.x)
				return true;
		}
		// ////

		return false;
	}

	public static boolean isWithinBoundingBox(STLObject outer, STLObject inner) {
		Point3f outerMin = outer.getMin(), outerMax = outer.getMax();
		Point3f innerMin = inner.getMin(), innerMax = inner.getMax();

		return isWithinBoundingBox(outerMax, outerMin, innerMax, innerMin);
	}

	public static boolean isWithinBoundingBox(Point3f outerMax,
			Point3f outerMin, Point3f innerMax, Point3f innerMin) {

		if (innerMin.x < outerMin.x || innerMax.x > outerMax.x)
			return false;
		if (innerMin.y < outerMin.y || innerMax.y > outerMax.y)
			return false;
		if (innerMin.z < outerMin.z || innerMax.z > outerMax.z)
			return false;

		return true;
	}

	private static boolean pointIsWithin(Point3f point, Point3f max, Point3f min) {

		float epsilon = 0.0001f;

		if (point.x > max.x - epsilon || point.x < min.x + epsilon)
			return false;
		if (point.y > max.y - epsilon || point.y < min.y + epsilon)
			return false;
		if (point.z > max.z - epsilon || point.z < min.z + epsilon)
			return false;

		return true;
	}

	private static boolean pointIsWithin(float x, float y, float z,
			Point3f max, Point3f min) {
		float epsilon = 0.0001f;

		if (x > max.x - epsilon || x < min.x + epsilon)
			return false;
		if (y > max.y - epsilon || y < min.y + epsilon)
			return false;
		if (z > max.z - epsilon || z < min.z + epsilon)
			return false;

		return true;
	}

	public static boolean facetsIntersect(STLFacet f1, STLFacet f2) {
		if (!boundingBoxesIntersect(f1, f2))
			return false;

		return (segmentIntersectsFacet(f1.getVertex1(), f1.getVertex2(), f2)
				|| segmentIntersectsFacet(f1.getVertex1(), f1.getVertex3(), f2) || segmentIntersectsFacet(
					f1.getVertex2(), f1.getVertex3(), f2));
	}

	public static boolean segmentIntersectsFacet(Point3f p1, Point3f p2,
			STLFacet f) {

		boolean b1 = (intersect_RayTriangle(p2, p1, f) != 0);
		boolean b2 = (intersect_RayTriangle(p1, p2, f) != 0);
		return b1 && b2;
	}

	// optimization, these objects either get instantiated and destroyed
	// constantly or they can be reused for a slight boost in performance
	// as the below method is called a lot if at all
	private final static Vector3f u = new Vector3f(), v = new Vector3f(),
			n = new Vector3f(), dir = new Vector3f(), w0 = new Vector3f(),
			w = new Vector3f();
	private final static Point3f I = new Point3f(), temp = new Point3f();

	// amended this code from a C++ algorithm
	// found here
	// http://www.softsurfer.com/Archive/algorithm_0105/algorithm_0105.htm
	// // Copyright 2001, softSurfer (www.softsurfer.com)
	// This code may be freely used and modified for any purpose
	// providing that this copyright notice is included with it.
	// SoftSurfer makes no warranty for this code, and cannot be held
	// liable for any real or imagined damage resulting from its use.
	// Users of this code must verify correctness for their application.
	private static int intersect_RayTriangle(Point3f P0, Point3f P1, STLFacet T) {
		// Vector3f u, v, n; // triangle vectors
		// Vector3f dir, w0, w; // ray vectors
		float r, a, b; // params to calc ray-plane intersect

		// get triangle edge vectors and plane normal
		// u = new Vector3f(T.getVertex2());
		u.set(T.getVertex2());
		u.sub(T.getVertex1());// T.V1 - T.V0;
		// v = new Vector3f(T.getVertex3());// T.V2 - T.V0;
		v.set(T.getVertex3());
		v.sub(T.getVertex1());
		// n = new Vector3f();
		n.cross(u, v);

		// cross product
		if (n.equals(new Vector3f(0, 0, 0))) // triangle is degenerate
			return -1; // do not deal with this case

		// dir = new Vector3f(P1);
		dir.set(P1);
		dir.sub(P0); // ray direction vector

		// w0 = new Vector3f(P0);
		w0.set(P0);
		w0.sub(T.getVertex1());
		a = -n.dot(w0);
		b = n.dot(dir);

		float epsilon = 0.0001f;

		if (Math.abs(b) < epsilon) { // ray is parallel to triangle plane
			if (a == 0) // ray lies in triangle plane
				return 2;
			else
				return 0; // ray disjoint from plane
		}

		// get intersect point of ray with triangle plane
		r = a / b;
		if (r < 0.0) // ray goes away from triangle
			return 0; // => no intersect
		// for a segment, also test if (r > 1.0) => no intersect

		// Point3f I;
		// I= new Point3f(P0);
		I.set(P0);
		// Point3f temp = new Point3f(dir);
		temp.set(dir);
		temp.scale(r);
		I.add(temp); // intersect point of ray and plane

		// is I inside T?
		float uu, uv, vv, wu, wv, D;
		uu = u.dot(u);
		uv = u.dot(v);
		vv = v.dot(v);

		w.set(I);
		w.sub(T.getVertex1());
		wu = w.dot(u);
		wv = w.dot(v);
		D = uv * uv - uu * vv;

		// get and test parametric coords
		float s, t;
		s = (uv * wv - vv * wu) / D;
		if (s < 0.0 || s > 1.0) // I is outside T
			return 0;
		t = (uv * wu - uu * wv) / D;
		if (t < 0.0 || (s + t) > 1.0) // I is outside T
			return 0;

		return 1; // I is in T
	}

	// TODO under construction
	public static double approximateSupportVolume(STLObject obj,
			float iterations) {
		double volume = 0;

		System.out.println("Analyzing..." + System.currentTimeMillis());
		LinkedList<STLFacet> down = new LinkedList<STLFacet>(), up = new LinkedList<STLFacet>();
		for (STLFacet fac : obj) {
			Vector3f norm = fac.getNormal();
			norm.normalize();
			if (norm.y > 0.0001)
				up.add(fac);
			else if (norm.y <-0.0001)
				down.add(fac);
		} // O(n)
		System.out.println("Normals pre-processed..."
				+ System.currentTimeMillis());
		int ct = 1;
		int size = down.size();
		for (STLFacet d : down) {
			float volunder = 0;
			Point3f max = d.getMax(), min = d.getMin();
			float xDist = max.x - min.x;
			float zDist = max.z - min.z;

			float delta = Math.max(xDist, zDist) / iterations;
			float deltaSquared = delta * delta;
			for (double currX = min.x + delta / 2.0; currX < max.x; currX += delta) {
				for (double currZ = min.z + delta / 2.0; currZ < max.z; currZ += delta) {
					// volunder+=deltaSquared*testHeight(currX,currZ,d,up,yoffset);
					double currTestHeight = testHeight(currX, currZ, d, up);
					
					/*
					if(currTestHeight>0.0001){
						System.out.println("Curr x: "+currX);
						System.out.println("Curr z:"+ currZ);
						System.out.println("Start Facet: "+d);
						System.out.println("End Facet");
						System.out.println("Min "+obj.getMin());
						
						Scanner s = new Scanner(System.in);
						s.next();
					}*/
					
					volume += deltaSquared * currTestHeight;
					System.out.println("delta squared: " + deltaSquared);
					System.out.println("Test height " + currTestHeight);
					System.out.println("Curr volume " + volume);
				}
			}

			// volume+=volunder;
			System.out.println("Analyzed " + (ct++) + " of " + size);
		}

		return volume;
	}

	private static double testHeight(double x, double z, STLFacet d,
			LinkedList<STLFacet> up) {

		double yAtXZ = heightAtXZ(x, z, d);
		if (Double.isNaN(yAtXZ)) {
			return 0;
		}
		double sampleY = 0;
		for (STLFacet fac : up) {
			double currY = heightAtXZ(x, z, fac);
			if (Double.isNaN(currY))
				continue;
			if (currY > yAtXZ)
				continue;
			if (currY > sampleY)
				sampleY = currY;
		}

		double result = (yAtXZ - sampleY);
		return result;
	}

	private static double heightAtXZ(double x, double z, STLFacet d) {
		Vector3f norm = d.getNormal();
		Vector3f a = new Vector3f(d.getVertex1());
		Vector3f b = new Vector3f(d.getVertex2());
		b.y = 0;
		Vector3f c = new Vector3f(d.getVertex3());
		c.y = 0;
		// check if x,z is in the triangle
		// boolean isInTriangle = isInTriangle(x, z, d);

		boolean isInTriangle = PointInTriangle(new Vector3f((float) x, 0,
				(float) z), new Vector3f(a.x, 0, a.z), b, c);
		if (!isInTriangle)
			return Double.NaN;
		double y = (-norm.x * (x - a.x) - norm.z * (z - a.z) + norm.y * a.y)
				/ norm.y;
		return y;
	}

	// ///////////
	private static boolean SameSide(Vector3f p1, Vector3f p2, Vector3f a,
			Vector3f b) {
		Vector3f cp1 = new Vector3f();
		b.sub(a);
		p1.sub(a);
		cp1.cross(b, p1);
		Vector3f cp2 = new Vector3f();
		p2.sub(a);
		cp2.cross(b, p2);
		if (cp1.dot(cp2) >= 0)
			return true;
		else
			return false;
	}

	private static boolean PointInTriangle(Vector3f p, Vector3f a, Vector3f b,
			Vector3f c) {
		Vector3f aN = new Vector3f(a);
		Vector3f bN = new Vector3f(b);
		Vector3f cN = new Vector3f(c);
		Vector3f pN = new Vector3f(p);
		aN.y = 0;
		bN.y = 0;
		cN.y = 0;
		pN.y = 0;

		if (SameSide(pN, aN, bN, cN) && SameSide(pN, bN, aN, cN)
				&& SameSide(pN, cN, aN, bN))
			return true;
		else
			return false;
	}

	// ///////

}
