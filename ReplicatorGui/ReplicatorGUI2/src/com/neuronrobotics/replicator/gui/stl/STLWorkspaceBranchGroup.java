package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.IOException;

import javax.media.j3d.BranchGroup;
import javax.media.j3d.Shape3D;
import javax.vecmath.Vector3f;


public class STLWorkspaceBranchGroup extends BranchGroup{
	
	private STLWorkspaceObject workspaceSTL;
	private Shape3D theWorkspaceShape;
	private Shape3D theWorkspaceOutline;
	
	private STLFace theSurface;
	private double surfaceY;
		
	public static STLWorkspaceBranchGroup STLWorkspaceBranchGroupFactory(STLWorkspaceObject wsp){
		return new STLWorkspaceBranchGroup(wsp);
	}
	
	public static STLWorkspaceBranchGroup getSTLWorkspaceBranchGroup(File stlFile) throws IOException{
		STLObject theSTLObject = STLLoader.loadFile(stlFile);
		STLWorkspaceObject theWorkspaceObject = new STLWorkspaceObject(theSTLObject);
		return new STLWorkspaceBranchGroup(theWorkspaceObject);
	}
	
	private STLWorkspaceBranchGroup(STLWorkspaceObject wsp){
		this.workspaceSTL = wsp;
		this.setCapability(BranchGroup.ALLOW_DETACH);
		
		theWorkspaceShape = STLShape3DFactory.getWorkspaceShape3D(wsp);//createWorkspaceShape(wsp);
		theWorkspaceOutline = STLShape3DFactory.getFaceOutline(wsp);//createFaceOutline(workspaceSTL);
		
		
		this.addChild(theWorkspaceShape);
		this.addChild(theWorkspaceOutline);		
		
		theSurface = null;
		surfaceY = Double.MAX_VALUE;
	}
	
	public boolean stlIsInside(STLObject stlo){
		return workspaceSTL.stlIsInside(stlo);
		/*
		boolean intersect = STLObjectIntersectionUtilities.objectsIntersect(this.workspaceSTL, stlo);
		if(intersect) return false;
		
		return STLObjectIntersectionUtilities.isWithinBoundingBox(this.workspaceSTL, stlo);
		
		/*
		for(STLFacet facet:stlo){
			for (STLFacet workspaceFac:workspaceSTL){
				if(!isBehind(facet,workspaceFac)){
					//System.out.println("\n"+facet+"\n"+workspaceFac);
					return false;
				}
			}
		}
		return true;
		*/
	}
		
	/*
	private boolean isBehind(STLFacet facet, STLFacet workspaceFac) {
		
		//boolean r1a = !workspaceFac.segmentIntersectsWith(facet.getVertex1(),facet.getVertex2());
		///boolean r2a = !workspaceFac.segmentIntersectsWith(facet.getVertex3(),facet.getVertex3());
		
		boolean r1= workspaceFac.pointIsWithin(facet.getVertex1());
		boolean r2= workspaceFac.pointIsWithin(facet.getVertex2());
		boolean r3= workspaceFac.pointIsWithin(facet.getVertex3());
		
		//boolean resultA = r1&&r2;
		
		boolean result = r1&&r2&&r3;
		
		/*
		if(!resultA&&result){
			System.out.println();
			System.out.println("Dun Goof'd");
			System.out.println("result: "+result);
			System.out.println("\t"+r1+" "+r2);
			System.out.println("resultB: "+result);
			System.out.println("\t"+r1b+" "+r2b+" "+r3b);
			System.out.println("\t\tWorkspace Normal: "+workspaceFac.getNormal());
			System.out.println("\t\tWorkspace facet: "+workspaceFac.getVertex1()+" "+workspaceFac.getVertex2()+" "+workspaceFac.getVertex3()+" ");
			System.out.println("\t\tFacet: "+facet.getVertex1()+" "+facet.getVertex2()+" "+facet.getVertex3());
			System.out.println("\t\tWorkspace dist: "+workspaceFac.originToPlaneDistance());
			
			System.out.println();
		}*/
		
		/*
		System.out.println("Workspace fac dist: "+workspaceFac.originToPlaneDistance());
		System.out.println("facet dist: "+facet.originToPlaneDistance());
		System.out.println("r1: "+r1);
		System.out.println("r2: "+r2);
		System.out.println("Totale res: "+result);
		
		return result;
	}*/

	public STLWorkspaceObject getWorkspaceSTLObject(){
		return workspaceSTL; 
	}
	
	/*
	public STLFace getSurfaceFace(){
		
		if(theSurface!=null) return theSurface;
		
		double y = Double.MAX_VALUE;
		
		STLFace result = null;
		Vector3f down = new Vector3f(0,-1,0);
		
		for(STLFace face: workspaceSTL.getFaces()){
			Vector3f currNorm = face.getNormal();
			currNorm.normalize();
			double currY = face.iterator().next().getVertex1().y;
			if(down.epsilonEquals(currNorm, 0.0001f)&&(y==Double.MAX_VALUE||currY<=y)){
				result = face;
				y=currY;
			}
		}
				
		theSurface = result;
		surfaceY = y;
		return result;
	}
	
	public double getSurfaceY(){
		if(theSurface==null) this.getSurfaceFace();
		if(surfaceY==Double.MAX_VALUE) return 0; //TODO shitty practice
		return surfaceY;
	}*/
}
