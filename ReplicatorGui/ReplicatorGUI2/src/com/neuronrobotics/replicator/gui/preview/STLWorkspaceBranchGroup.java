package com.neuronrobotics.replicator.gui.preview;

import java.util.ArrayList;
import java.util.Collection;

import javax.media.j3d.Appearance;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.LineArray;
import javax.media.j3d.Material;
import javax.media.j3d.Shape3D;
import javax.media.j3d.TransparencyAttributes;
import javax.media.j3d.TriangleArray;
import javax.vecmath.Point3f;

import com.neuronrobotics.replicator.gui.stl.Point3fEdge;
import com.neuronrobotics.replicator.gui.stl.STLFacet;
import com.neuronrobotics.replicator.gui.stl.STLFace;
import com.neuronrobotics.replicator.gui.stl.STLObject;
import com.sun.j3d.utils.geometry.GeometryInfo;
import com.sun.j3d.utils.geometry.NormalGenerator;

public class STLWorkspaceBranchGroup extends BranchGroup{
	
	private STLObject workspaceSTL;
	private Shape3D theWorkspaceShape;
	
	public STLWorkspaceBranchGroup(STLObject wsp){
		this.workspaceSTL = wsp;
		this.setCapability(BranchGroup.ALLOW_DETACH);
		
		theWorkspaceShape = createWorkspaceShape(wsp);
		this.addChild(theWorkspaceShape);
		this.addChild(createFaceOutline(workspaceSTL));
		
		//TODO a bunch more stuff (which face is the surface, etc
			
	}
	
	private static Shape3D createFaceOutline(STLObject workspaceSTL){
		
		ArrayList<Point3fEdge> theEdges = new ArrayList<Point3fEdge>();
		
		for(STLFace face:workspaceSTL.getFaces()){
			theEdges.addAll(getFacePerimeter(face));
		}
		
		int vertCount = theEdges.size()*2;
		
		LineArray perim = new LineArray(vertCount,LineArray.COORDINATES);
		
		int ct=0;
		for(Point3fEdge edge:theEdges){
			perim.setCoordinate(ct++, edge.getPoint1());
			perim.setCoordinate(ct++, edge.getPoint2());
		}
		
		Shape3D outline = new Shape3D(perim);
		return outline;
	}

	private static int numCalls = 0;//TODO for testing. 
	//TODO Also should remove things to Factory class
	private static ArrayList<Point3fEdge> getFacePerimeter(STLFace theFace){
		
		System.out.println(++numCalls);
		
		
		ArrayList<Point3fEdge> theList = new ArrayList<Point3fEdge>();
		
		for(STLFacet facet:theFace){
			Point3fEdge e0,e1,e2;
			e0 = new Point3fEdge(facet.getVertex1(),facet.getVertex2());
			e1 = new Point3fEdge(facet.getVertex1(),facet.getVertex3());
			e2 = new Point3fEdge(facet.getVertex2(),facet.getVertex3());
			
			int currI;
			currI = indexOfEdge(e0,theList);
			if(currI==-1){
				theList.add(e0);
			} else {
				theList.remove(currI);
			}
			currI = indexOfEdge(e1,theList);
			if(currI==-1){
				theList.add(e1);
			} else {
				theList.remove(currI);
			}
			currI = indexOfEdge(e2,theList);
			if(currI==-1){
				theList.add(e2);
			} else {
				theList.remove(currI);
			}
			
		}		
				
		return theList;
	}
		
	private static int indexOfEdge(Point3fEdge theEdge,Collection<Point3fEdge> coll){
		int ct=0;
		for(Point3fEdge curr:coll){
			if(theEdge.equalsEpsilon(curr,0.0001f)) return ct;
			ct++;
		}			
		return -1;
	}

	private static Shape3D createWorkspaceShape(STLObject workspaceSTL) {
		TriangleArray theTA = new TriangleArray(workspaceSTL.getFacetAmount()*3*2,TriangleArray.COORDINATES);
		int ct = 0;
		for(STLFacet sf:workspaceSTL){
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
		NormalGenerator ng = new NormalGenerator();
		//ng.generateNormals(gi);
		
		Shape3D theShape = new Shape3D(gi.getGeometryArray(),ap);
		
		return theShape;
	}

}
