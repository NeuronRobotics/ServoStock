package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.IOException;

import javax.media.j3d.BranchGroup;
import javax.media.j3d.Shape3D;


public class STLWorkspaceBranchGroup extends BranchGroup{
	
	private STLObject workspaceSTL;
	private Shape3D theWorkspaceShape;
	private Shape3D theWorkspaceOutline;
	
	public static STLWorkspaceBranchGroup STLWorkspaceBranchGroupFactory(STLObject wsp){
		return new STLWorkspaceBranchGroup(wsp);
	}
	
	public static STLWorkspaceBranchGroup STLWorkspaceBranchGroupFactory(File stlFile) throws IOException{
		STLObject theObject = STLLoader.loadFile(stlFile);
		return new STLWorkspaceBranchGroup(theObject);
	}
	
	private STLWorkspaceBranchGroup(STLObject wsp){
		this.workspaceSTL = wsp;
		this.setCapability(BranchGroup.ALLOW_DETACH);
		
		theWorkspaceShape = STLShape3DFactory.getWorkspaceShape3D(wsp);//createWorkspaceShape(wsp);
		theWorkspaceOutline = STLShape3DFactory.getFaceOutline(wsp);//createFaceOutline(workspaceSTL);
		
		
		this.addChild(theWorkspaceShape);
		this.addChild(theWorkspaceOutline);		
		
	}
	
	//TODO this currently returns true if object is completely in or completely out
	public boolean stlIsContained(STLObject stlo){
		for(STLFacet facet:stlo){
			for (STLFacet workspaceFac:workspaceSTL){
				if(!isBehind(facet,workspaceFac)){
					//System.out.println("\n"+facet+"\n"+workspaceFac);
					return false;
				}
			}
		}
		return true;
	}
		
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
		*/
		return result;
	}

}
