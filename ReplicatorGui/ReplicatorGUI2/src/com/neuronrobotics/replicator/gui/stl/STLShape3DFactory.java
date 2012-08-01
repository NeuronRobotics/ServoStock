package com.neuronrobotics.replicator.gui.stl;

import java.util.ArrayList;
import java.util.Collection;

import javax.media.j3d.Appearance;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.GeometryArray;
import javax.media.j3d.LineArray;
import javax.media.j3d.Material;
import javax.media.j3d.Shape3D;
import javax.media.j3d.TransparencyAttributes;
import javax.media.j3d.TriangleArray;
import javax.vecmath.Color3f;

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
		ArrayList<Point3fEdge> theEdges = new ArrayList<Point3fEdge>();

		for (STLFace face : stlo.getFaces()) {
			theEdges.addAll(getFacePerimeter(face));
		}

		int vertCount = theEdges.size() * 2;

		LineArray perim = new LineArray(vertCount, LineArray.COORDINATES);

		int ct = 0;
		for (Point3fEdge edge : theEdges) {
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

	//Private Utility Methods
	
	private static ArrayList<Point3fEdge> getFacePerimeter(STLFace theFace) {

		ArrayList<Point3fEdge> theList = new ArrayList<Point3fEdge>();

		for (STLFacet facet : theFace) {
			Point3fEdge e0, e1, e2;
			e0 = new Point3fEdge(facet.getVertex1(), facet.getVertex2());
			e1 = new Point3fEdge(facet.getVertex1(), facet.getVertex3());
			e2 = new Point3fEdge(facet.getVertex2(), facet.getVertex3());

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

	private static int indexOfEdge(Point3fEdge theEdge,
			Collection<Point3fEdge> coll) {
		int ct = 0;
		for (Point3fEdge curr : coll) {
			if (theEdge.equalsEpsilon(curr, 0.0001f))
				return ct;
			ct++;
		}
		return -1;
	}

}
