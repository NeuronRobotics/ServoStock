package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.STLFacet;
import com.neuronrobotics.replicator.gui.stl.STLObject;

public class STLObjectUtilities {

	public static boolean objectsIntersect(STLObject s1, STLObject s2) {
		
		for(STLFacet f1:s1){
			for(STLFacet f2:s2){
				if(facetsIntersect(f1,f2)) return true;
			}
		}
		
		
		return false;
	}

	public static boolean facetsIntersect(STLFacet f1, STLFacet f2) {
		return (rayIntersectsFacet(f1.getVertex1(),f1.getVertex2(),f2)||rayIntersectsFacet(f1.getVertex1(),f1.getVertex3(),f2)||rayIntersectsFacet(f1.getVertex2(),f1.getVertex3(),f2));
	}

	public static boolean rayIntersectsFacet(Point3f p1, Point3f p2, STLFacet f) {
		return (intersect_RayTriangle(p2, p1, f) != 0);
	}

	public static int intersect_RayTriangle(Point3f P0, Point3f P1, STLFacet T) {
		Vector3f u, v, n; // triangle vectors
		Vector3f dir, w0, w; // ray vectors
		float r, a, b; // params to calc ray-plane intersect

		// get triangle edge vectors and plane normal
		u = new Vector3f(T.getVertex2());
		u.sub(T.getVertex1());// T.V1 - T.V0;
		v = new Vector3f(T.getVertex3());// T.V2 - T.V0;
		v.sub(T.getVertex1());
		n = new Vector3f();
		n.cross(u, v);

		// cross product
		if (n.equals(new Vector3f(0, 0, 0))) // triangle is degenerate
			return -1; // do not deal with this case

		dir = new Vector3f(P1);
		dir.sub(P0); // ray direction vector

		w0 = new Vector3f(P0);
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

		Point3f I;
		I = new Point3f(P0);
		Point3f temp = new Point3f(dir);
		temp.scale(r);
		I.add(temp); // intersect point of ray and plane

		// is I inside T?
		float uu, uv, vv, wu, wv, D;
		uu = u.dot(u);
		uv = u.dot(v);
		vv = v.dot(v);

		w = new Vector3f(I);
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

}
