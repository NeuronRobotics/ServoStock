package com.neuronrobotics.replicator.gui.stl;
import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;

import com.neuronrobotics.replicator.gui.stl.STLFacet;
import com.neuronrobotics.replicator.gui.stl.STLObject;

public class STLObjectIntersectionUtilities {
	
	public static boolean objectsIntersect(STLObject s1, STLObject s2) {
		
		if(!boundingBoxesIntersect(s1,s2)) return false;
				
		for(STLFacet f1:s1){
			for(STLFacet f2:s2){
				if(facetsIntersect(f1,f2)){
					//System.out.println("Facet Intersection found: ");
					//System.out.println("Facet 1: "+f1);
					//System.out.println("Facet 2: "+f2);
					return true;
				}
			}
		}		
		
		return false;
	}

	private static boolean boundingBoxesIntersect(STLObject s1, STLObject s2) {
		Point3f s1max = s1.getMax();
		Point3f s1min = s1.getMin();
		
		Point3f s2max = s2.getMax();
		Point3f s2min = s2.getMin();
		
		if(pointIsWithin(s2max,s1max,s1min)) return true;
		if(pointIsWithin(s2min,s1max,s1min)) return true;
		if(pointIsWithin(s1max,s2max,s2min)) return true;
		if(pointIsWithin(s1min,s2max,s2min)) return true;
					
		return false;
	}
	
	private static boolean boundingBoxesIntersect(STLFacet f1, STLFacet f2) {
		Point3f s1max = f1.getMax();
		Point3f s1min = f1.getMin();
		
		Point3f s2max = f2.getMax();
		Point3f s2min = f2.getMin();
		
		if(pointIsWithin(s2max,s1max,s1min)) return true;
		if(pointIsWithin(s2min,s1max,s1min)) return true;
		if(pointIsWithin(s1max,s2max,s2min)) return true;
		if(pointIsWithin(s1min,s2max,s2min)) return true;
					
		return false;
	}

	private static boolean pointIsWithin(Point3f point, Point3f max,
			Point3f min) {
		if (point.x>max.x||point.x<min.x) return false;
		if (point.y>max.y||point.y<min.y) return false;
		if (point.z>max.z||point.z<min.z) return false; 
				
		return true;
	}

	public static boolean facetsIntersect(STLFacet f1, STLFacet f2) {
		if(!boundingBoxesIntersect(f1, f2)) return false;
		
		return (segmentIntersectsFacet(f1.getVertex1(),f1.getVertex2(),f2)||segmentIntersectsFacet(f1.getVertex1(),f1.getVertex3(),f2)||segmentIntersectsFacet(f1.getVertex2(),f1.getVertex3(),f2));
	}

	public static boolean segmentIntersectsFacet(Point3f p1, Point3f p2, STLFacet f) {
		
		boolean b1 =  (intersect_RayTriangle(p2, p1, f) != 0);
		boolean b2 =  (intersect_RayTriangle(p1, p2, f) != 0);
		return b1&&b2;
	}
	
	
	//optimization, these objects either get instantiated and destroyed 
	//constantly or they can be reused for a slight boost in performance
	//as the below method is called a lot if at all
	private final static Vector3f u= new Vector3f(), v= new Vector3f(), n= new Vector3f(), dir= new Vector3f(), w0= new Vector3f(), w= new Vector3f();
	private final static Point3f I = new Point3f(), temp = new Point3f();
	
	//amended this code from a C++ algorithm
 	private static int intersect_RayTriangle(Point3f P0, Point3f P1, STLFacet T) {
		//Vector3f u, v, n; // triangle vectors
		//Vector3f dir, w0, w; // ray vectors
		float r, a, b; // params to calc ray-plane intersect

		// get triangle edge vectors and plane normal
		//u = new Vector3f(T.getVertex2());
		u.set(T.getVertex2());
		u.sub(T.getVertex1());// T.V1 - T.V0;
		//v = new Vector3f(T.getVertex3());// T.V2 - T.V0;
		v.set(T.getVertex3());
		v.sub(T.getVertex1());
		//n = new Vector3f();
		n.cross(u, v);

		// cross product
		if (n.equals(new Vector3f(0, 0, 0))) // triangle is degenerate
			return -1; // do not deal with this case

		//dir = new Vector3f(P1);
		dir.set(P1);
		dir.sub(P0); // ray direction vector

		//w0 = new Vector3f(P0);
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

		//Point3f I;
		//I= new Point3f(P0);
		I.set(P0);		
		//Point3f temp = new Point3f(dir);
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
 	
 	

}
