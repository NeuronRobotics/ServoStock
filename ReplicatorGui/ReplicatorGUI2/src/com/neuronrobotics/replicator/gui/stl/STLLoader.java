package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.FileInputStream;
//import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
//import java.util.Iterator;
//import java.util.Scanner;
//import java.util.StringTokenizer;

import javax.media.j3d.*;
import javax.vecmath.*;

//import org.j3d.loaders.InvalidFormatException;
//import com.sun.j3d.utils.behaviors.mouse.*;
import com.sun.j3d.utils.geometry.NormalGenerator;
import com.sun.j3d.utils.geometry.GeometryInfo;

public class STLLoader {
	
	//@SuppressWarnings("restriction")
	public static TransformGroup getSTLTransform(String filename,BranchGroup root) throws IOException{
		return getSTLTransform(new File(filename),root);
	}
	
	//@SuppressWarnings("restriction")
	public static TransformGroup getSTLTransform(File f,BranchGroup root) throws IOException{
		STLObject stl = loadFile(f);
		return getSTLTransform(stl,root);	
	}
	
	//@SuppressWarnings("restriction")
	public static TransformGroup getSTLTransform(STLObject stl,BranchGroup root) throws IOException{
		TransformGroup tg = new TransformGroup();
				
		tg.addChild(createModel(stl));
				
		//Outline with visibility option
		Shape3D outline = createModelOutline(stl);
		
		//RenderingAttributes ra = new RenderingAttributes();
		//ra.setVisible(true);		
		//ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ|RenderingAttributes.ALLOW_VISIBLE_WRITE);
		
		//Appearance outlineAppearance = new Appearance();
		//outlineAppearance.setRenderingAttributes(ra);
		
		//outline.setAppearance(outlineAppearance);
		
		
		tg.addChild(outline);
		
		//end outline creation
		
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
		
		
		
		/*
		MouseRotate myMouseRotate = new MouseRotate();
		myMouseRotate.setTransformGroup(tg);
		myMouseRotate.setSchedulingBounds(new BoundingSphere());
		
		root.addChild(myMouseRotate);
		*/
		
		return tg; 
	}
		
	public static STLObject loadFile(File theFile) throws IOException{
		InputStream is = new FileInputStream(theFile);
		return loadFile(is);
	}
	
	//@SuppressWarnings("restriction")
	public static STLObject loadFile(InputStream is) throws IOException{
		String name;
		//Point3f center = new Point3f();
		Point3f min = new Point3f(), max = new Point3f();
		ArrayList<STLFacet> facets = new ArrayList<STLFacet>();
		
		//InputStream is = new FileInputStream(theFile);
		
		STLParser theParser = STLParser.getParser(is);
		
		name = theParser.getName();
		
		facets=new ArrayList<STLFacet>();
		while(theParser.hasNextFacet()){
			STLFacet tempFacet;
			try {
				tempFacet = theParser.nextFacet();
			} catch (Exception e) {
				e.printStackTrace();
				System.out.print("This should never happen. Check for end of file may be failing.");
				break; //
			}
			
			//Update mins and maxes
			
			Point3f tempMin = new Point3f(), tempMax = new Point3f();
			tempMax.x = Math.max(Math.max(tempFacet.getVertex1().x,tempFacet.getVertex2().x),tempFacet.getVertex3().x);
			tempMin.x = Math.min(Math.min(tempFacet.getVertex1().x,tempFacet.getVertex2().x),tempFacet.getVertex3().x);
			tempMax.y = Math.max(Math.max(tempFacet.getVertex1().y,tempFacet.getVertex2().y),tempFacet.getVertex3().y);
			tempMin.y = Math.min(Math.min(tempFacet.getVertex1().y,tempFacet.getVertex2().y),tempFacet.getVertex3().y);
			tempMax.z = Math.max(Math.max(tempFacet.getVertex1().z,tempFacet.getVertex2().z),tempFacet.getVertex3().z);
			tempMin.z = Math.min(Math.min(tempFacet.getVertex1().z,tempFacet.getVertex2().z),tempFacet.getVertex3().z);
					
			if (facets.isEmpty()) {
				max = tempMax;
				min = tempMin;
			} else {
				if (tempMax.x > max.x) 
					max.x = tempMax.x;
				if (tempMin.x < min.x)
					min.x = tempMin.x;
				if (tempMax.y > max.y)
					max.y = tempMax.y;
				if (tempMin.y < min.y)
					min.y = tempMin.y;
				if (tempMax.z > max.z)
					max.z = tempMax.z;
				if (tempMin.z < min.z)
					min.z = tempMin.z;
			}
			
			facets.add(tempFacet);
		}
		
		return new STLObject(name,facets);//,null,min,max);
		
	}
		
	private static Shape3D createModelOutline(STLObject stlo){
		Shape3D outline = new Shape3D();
		int numVertices = stlo.getFacetAmount() * 3;
		LineArray olA = new LineArray(numVertices*2,GeometryArray.COORDINATES);
		
		int currV=0;
		
		//centeredScale(Point3f p,Point3f c, float scale)
		
		//float scale = 1f/Math.max(Math.max(stlo.getXDistance(),stlo.getYDistance()),stlo.getZDistance());
		
		//Point3f center =stlo.getCenter();
		
		for(STLFacet fac:stlo){
			/*
			olA.setCoordinate(currV++, centeredScale(fac.getVertex1(),center,scale));
			olA.setCoordinate(currV++, centeredScale(fac.getVertex2(),center,scale));
			
			olA.setCoordinate(currV++, centeredScale(fac.getVertex1(),center,scale));
			olA.setCoordinate(currV++,centeredScale( fac.getVertex3(),center,scale));
			
			olA.setCoordinate(currV++,centeredScale( fac.getVertex2(),center,scale));
			olA.setCoordinate(currV++,centeredScale( fac.getVertex3(),center,scale));
			*/
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
	
	private static Shape3D createModel(STLObject stlo) throws IOException {
		
		int numVertices = stlo.getFacetAmount() * 3;

		Appearance modelAppearance = new Appearance();
		modelAppearance.setColoringAttributes(new ColoringAttributes(new Color3f(.7f,0.7f,0.7f),ColoringAttributes.NICEST));
		modelAppearance.setMaterial(new Material());
		
		TriangleArray model = new TriangleArray(numVertices,
				TriangleArray.COORDINATES);
		
			
		int currVertex = 0;
		
		
		//float scale = 1f/Math.max(Math.max(stlo.getXDistance(),stlo.getYDistance()),stlo.getZDistance());
		
		//Vector3f[] normals = new Vector3f[stlo.getFacetAmount()];
				
		//Point3f center = stlo.getCenter();
		for(STLFacet sf:stlo){
			/*
			model.setCoordinate(currVertex++, centeredScale(sf.getVertex1(),center,scale));
			model.setCoordinate(currVertex++, centeredScale(sf.getVertex2(),center,scale));
			model.setCoordinate(currVertex++, centeredScale(sf.getVertex3(),center,scale));
			//normals[(currVertex/3)-1]=sf.getNormal();
			*/
			model.setCoordinate(currVertex++, sf.getVertex1());
			model.setCoordinate(currVertex++, sf.getVertex2());
			model.setCoordinate(currVertex++, sf.getVertex3());
			
			
		}
		
		GeometryInfo gi = new GeometryInfo(model);
		NormalGenerator ng = new NormalGenerator();
		ng.generateNormals(gi);
		
		model.setCapability(TriangleArray.NORMALS);
		//model.setNormals(0,normals);
		
		Shape3D theModel = new Shape3D(gi.getIndexedGeometryArray(), modelAppearance);
		
		Appearance appearance = new Appearance();
		Material material = new Material(); 
		material.setDiffuseColor(0.1f, 0.2f, 0.4f);
		material.setSpecularColor(0.2f, 0.2f, 0.2f);  // reduce default values
		appearance.setMaterial(material);
		
		theModel.setAppearance(appearance);
		
		return theModel;
	}

	/*
	private static Point3f centeredScale(Point3f p,Point3f c, float scale){
				
		float x = p.x;//(p.x-c.x)*scale;
		float y = p.y;//(p.y-c.y)*scale;
		float z = p.z;//(p.z-c.z)*scale;
		
		scale*=3;
		boolean noScale = true;
		if(noScale){
			scale = 1;
			c.x = 0;
			c.y = 0;
			c.z = 0;
		}
		float x = (p.x-c.x)*scale;
		float y = (p.y-c.y)*scale;
		float z = (p.z-c.z)*scale;
		
		return new Point3f(x,y,z);
	}
	*/
	//@SuppressWarnings("restriction")
	public static STLTransformGroup createSTLTransform(String filename,BranchGroup root) throws IOException{
		return createSTLTransform(new File(filename),root);
	}
	
	//@SuppressWarnings("restriction")
	public static STLTransformGroup createSTLTransform(File f,BranchGroup root) throws IOException{
		STLObject stl = loadFile(f);
		return createSTLTransform(stl,root);	
	}
	
	//@SuppressWarnings("restriction")
	public static STLTransformGroup createSTLTransform(STLObject stl,BranchGroup root) throws IOException{
		STLTransformGroup tg = new STLTransformGroup();
				
		tg.setModel(createModel(stl));
		
		//Outline with visibility option
		Shape3D outline = createModelOutline(stl);
		
		RenderingAttributes ra = new RenderingAttributes();
		ra.setVisible(true);		
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ|RenderingAttributes.ALLOW_VISIBLE_WRITE);
		
		Appearance outlineAppearance = new Appearance();
		outlineAppearance.setRenderingAttributes(ra);
		
		outline.setAppearance(outlineAppearance);
				
		tg.setOutline(outline);
		/////////// TODO only for debugging right now
		Point3f tc = stl.getCenter();
		LineArray olA = new LineArray(10,GeometryArray.COORDINATES);
		
		olA.setCoordinate(0, new Point3f(tc.x,tc.y,100));
		olA.setCoordinate(1, new Point3f(tc.x,tc.y,-100));
		
		olA.setCoordinate(2, new Point3f(100,tc.y,tc.z));
		olA.setCoordinate(3, new Point3f(-100,tc.y,tc.z));
		
		olA.setCoordinate(4, new Point3f(tc.x,100,tc.z));
		olA.setCoordinate(5, new Point3f(tc.x,-100,tc.z));
		
		olA.setCoordinate(6, new Point3f(tc.x,stl.getMin().y,100));
		olA.setCoordinate(7, new Point3f(tc.x,stl.getMin().y,-100));
		
		olA.setCoordinate(8, new Point3f(100,stl.getMin().y,tc.z));
		olA.setCoordinate(9, new Point3f(-100,stl.getMin().y,tc.z));
		
		System.out.println("Min "+stl.getMin().y);
				
		Shape3D centerLines = new Shape3D(olA);
		
		tg.addChild(centerLines);
				
			
		/////
		//end outline creation
		
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
		
		
		
		/*
		MouseRotate myMouseRotate = new MouseRotate();
		myMouseRotate.setTransformGroup(tg);
		myMouseRotate.setSchedulingBounds(new BoundingSphere());
		
		root.addChild(myMouseRotate);
		*/
		return tg; 
	}
	
}
