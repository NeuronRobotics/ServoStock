package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;

import javax.media.j3d.Appearance;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.GeometryArray;
import javax.media.j3d.IndexedLineArray;
import javax.media.j3d.LineArray;
import javax.media.j3d.Material;
import javax.media.j3d.Shape3D;
import javax.media.j3d.TransparencyAttributes;
import javax.media.j3d.TriangleArray;
import javax.vecmath.Color3f;
import javax.vecmath.Point3f;

import com.sun.j3d.utils.geometry.GeometryInfo;
import com.sun.j3d.utils.geometry.NormalGenerator;

public class STLShape3DFactory {

	public static Shape3D getFacetOutline(STLObject stlo) {
		Shape3D outline = new Shape3D();
		int numVertices = stlo.getFacetAmount() * 3;
		LineArray olA = new LineArray(numVertices*2,GeometryArray.COORDINATES);
		
		int currV=0;
		
		for(STLFacet fac:stlo){
			olA.setCoordinate(currV++, fac.getVertex1());
			olA.setCoordinate(currV++, fac.getVertex2());
			
			olA.setCoordinate(currV++, fac.getVertex1());
			olA.setCoordinate(currV++, fac.getVertex3());
			
			olA.setCoordinate(currV++, fac.getVertex2());
			olA.setCoordinate(currV++, fac.getVertex3());			
		}
		
		outline.setGeometry(olA);
		
		return outline;
	}

	public static Shape3D getFaceOutline(STLObject stlo) {
		ArrayList<Edge3f> theEdges = new ArrayList<Edge3f>();

		Iterator<STLFace> theFaces = stlo.getFaceIterator();
		
		while (theFaces.hasNext()) {
			STLFace face = theFaces.next();
			theEdges.addAll(getFacePerimeter(face));
		}

		int vertCount = theEdges.size() * 2;

		LineArray perim = new LineArray(vertCount, LineArray.COORDINATES);

		int ct = 0;
		for (Edge3f edge : theEdges) {
			perim.setCoordinate(ct++, edge.getPoint1());
			perim.setCoordinate(ct++, edge.getPoint2());
		}

		Shape3D outline = new Shape3D(perim);

		return outline;
	}

	public static Shape3D getModelShape3D(STLObject stlo) {
		int numVertices = stlo.getFacetAmount() * 3;

		Appearance modelAppearance = new Appearance();
		modelAppearance.setColoringAttributes(new ColoringAttributes(new Color3f(.7f,0.7f,0.7f),ColoringAttributes.NICEST));
		modelAppearance.setMaterial(new Material());
		
		TriangleArray model = new TriangleArray(numVertices,
				TriangleArray.COORDINATES);		
			
		int currVertex = 0;
		
		for(STLFacet sf:stlo){
			
			model.setCoordinate(currVertex++, sf.getVertex1());
			model.setCoordinate(currVertex++, sf.getVertex2());
			model.setCoordinate(currVertex++, sf.getVertex3());
					
		}
		
		GeometryInfo gi = new GeometryInfo(model);
		NormalGenerator ng = new NormalGenerator();
		ng.generateNormals(gi);
		
		model.setCapability(TriangleArray.NORMALS);
		
		Shape3D theModel = new Shape3D(gi.getIndexedGeometryArray(), modelAppearance);
		
		Appearance appearance = new Appearance();
		Material material = new Material(); 
		material.setDiffuseColor(0.1f, 0.2f, 0.4f);
		material.setSpecularColor(0.2f, 0.2f, 0.2f);  // reduce default values
		appearance.setMaterial(material);
		
		theModel.setAppearance(appearance);
		
		return theModel;
	}
	
	public static Shape3D getWorkspaceShape3D(STLObject stlo) {
		TriangleArray theTA = new TriangleArray(stlo.getFacetAmount()*3*2,TriangleArray.COORDINATES);
		int ct = 0;
		for(STLFacet sf:stlo){
			theTA.setCoordinate(ct++, sf.getVertex1());
			theTA.setCoordinate(ct++, sf.getVertex2());
			theTA.setCoordinate(ct++, sf.getVertex3());
			
			theTA.setCoordinate(ct++, sf.getVertex3());
			theTA.setCoordinate(ct++, sf.getVertex2());
			theTA.setCoordinate(ct++, sf.getVertex1());	
		}
		
		Appearance ap = new Appearance();
		Material mat = new Material();
		TransparencyAttributes tra = new TransparencyAttributes();
		tra.setTransparency(0.9f);
		tra.setTransparencyMode(TransparencyAttributes.NICEST);
		ap.setTransparencyAttributes(tra);
		ap.setMaterial(mat);
		
		GeometryInfo gi = new GeometryInfo(theTA);
		
		Shape3D theShape = new Shape3D(gi.getGeometryArray(),ap);
		
		return theShape;
	}

	public static Shape3D getRectangularOutline(Point3f min, Point3f max){
		IndexedLineArray ils = new IndexedLineArray(8, IndexedLineArray.COORDINATES, 24);
		
		float xMin = min.x,yMin = min.y, zMin = min.z;
		float xMax = max.x,yMax = max.y, zMax = max.z;
		
		ils.setCoordinate(0, new Point3f(xMin,yMin,zMin));
		ils.setCoordinate(1, new Point3f(xMin,yMin,zMax));
		ils.setCoordinate(2, new Point3f(xMin,yMax,zMin));
		ils.setCoordinate(3, new Point3f(xMin,yMax,zMax));
		ils.setCoordinate(4, new Point3f(xMax,yMin,zMin));
		ils.setCoordinate(5, new Point3f(xMax,yMin,zMax));
		ils.setCoordinate(6, new Point3f(xMax,yMax,zMin));
		ils.setCoordinate(7, new Point3f(xMax,yMax,zMax));
		
		ils.setCoordinateIndex(0, 0);
		ils.setCoordinateIndex(1, 1);
		ils.setCoordinateIndex(2, 0);
		ils.setCoordinateIndex(3, 2);
		ils.setCoordinateIndex(4, 0);
		ils.setCoordinateIndex(5, 4);
		
		ils.setCoordinateIndex(6, 1);
		ils.setCoordinateIndex(7, 3);
		ils.setCoordinateIndex(8, 1);
		ils.setCoordinateIndex(9, 5);
		
		ils.setCoordinateIndex(10, 2);
		ils.setCoordinateIndex(11, 3);
		ils.setCoordinateIndex(12, 2);
		ils.setCoordinateIndex(13, 6);
		
		ils.setCoordinateIndex(14, 3);
		ils.setCoordinateIndex(15, 7);
		
		ils.setCoordinateIndex(16, 4);
		ils.setCoordinateIndex(17, 5);
		ils.setCoordinateIndex(18, 4);
		ils.setCoordinateIndex(19, 6);
		
		ils.setCoordinateIndex(20, 5);
		ils.setCoordinateIndex(21, 7);
		
		ils.setCoordinateIndex(22, 6);
		ils.setCoordinateIndex(23, 7);
		
		
		return new Shape3D(ils);
	}
	
	//Private Utility Methods
	
	private static ArrayList<Edge3f> getFacePerimeter(STLFace theFace) {

		ArrayList<Edge3f> theList = new ArrayList<Edge3f>();

		for (STLFacet facet : theFace) {
			Edge3f e0, e1, e2;
			e0 = new Edge3f(facet.getVertex1(), facet.getVertex2());
			e1 = new Edge3f(facet.getVertex1(), facet.getVertex3());
			e2 = new Edge3f(facet.getVertex2(), facet.getVertex3());

			int currI;
			currI = indexOfEdge(e0, theList);
			if (currI == -1) {
				theList.add(e0);
			} else {
				theList.remove(currI);
			}
			currI = indexOfEdge(e1, theList);
			if (currI == -1) {
				theList.add(e1);
			} else {
				theList.remove(currI);
			}
			currI = indexOfEdge(e2, theList);
			if (currI == -1) {
				theList.add(e2);
			} else {
				theList.remove(currI);
			}

		}

		return theList;
	}

	private static int indexOfEdge(Edge3f theEdge,
			Collection<Edge3f> coll) {
		int ct = 0;
		for (Edge3f curr : coll) {
			if (theEdge.equalsEpsilon(curr, 0.0001f))
				return ct;
			ct++;
		}
		return -1;
	}

	
	
}
