package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

import javax.media.j3d.*;
import javax.vecmath.*;

import com.sun.j3d.utils.geometry.NormalGenerator;
import com.sun.j3d.utils.geometry.GeometryInfo;

public class STLLoader {
	
	/**
	 * Takes in file, converts to an InputStream and returns resulting
	 * STLObject from loadFile(InputStream is)
	 * @param theFile
	 * @return an STLObject encapsulating the data read in from the file
	 * @throws IOException
	 */
	public static STLObject loadFile(File theFile) throws IOException{
		InputStream is = new FileInputStream(theFile);
		return loadFile(is);
	}
	
	/**
	 * Takes in an InputStream for the stl file data and reads the data into 
	 * an STLObject which is returned 
	 * @param is
	 * @return and STLObject encapsulating the data read in from the file
	 * @throws IOException
	 */
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

	/**
	 * Uses the STLObject gained by reading the file location specified by filename
	 * and creates model and model outline which are added to an
	 * STLTransformGroup object along with a the capability for the outline to have its
	 * visibility read and written and the entire group to allow transform reads and writes
	 * @param stl
	 * @param root
	 * @return
	 */
	public static STLTransformGroup createSTLTransform(String filename,BranchGroup root) throws IOException{
		return createSTLTransform(new File(filename),root);
	}
	
	/**
	 * Uses the STLObject gained by reading the file location specified by file
	 * and creates model and model outline which are added to an
	 * STLTransformGroup object along with a the capability for the outline to have its
	 * visibility read and written and the entire group to allow transform reads and writes
	 * @param stl
	 * @param root
	 * @return
	 */
	public static STLTransformGroup createSTLTransform(File file,BranchGroup root) throws IOException{
		STLObject stl = loadFile(file);
		return createSTLTransform(stl,root);	
	}
	
	/**
	 * Uses the STLObject gained by reading the data from the InputStream
	 * and creates model and model outline which are added to an
	 * STLTransformGroup object along with a the capability for the outline to have its
	 * visibility read and written and the entire group to allow transform reads and writes
	 * @param stl
	 * @param root
	 * @return
	 */
	public static STLTransformGroup createSTLTransform(InputStream is,BranchGroup root) throws IOException{
		STLObject stl = loadFile(is);
		return createSTLTransform(stl,root);	
	}
	
	/**
	 * Uses the STLObject and creates model and model outline which are added to an
	 * STLTransformGroup object along with a the capability for the outline to have its
	 * visibility read and written and the entire group to allow transform reads and writes
	 * @param stl
	 * @param root
	 * @return
	 */
	public static STLTransformGroup createSTLTransform(STLObject stl,BranchGroup root){
		//STLTransformGroup tg = new STLTransformGroup();
				
		//Actual 3d model
		Shape3D theModel = createModel(stl);
				
		//Outline with visibility option
		Shape3D outline = createModelOutline(stl);
		
		RenderingAttributes ra = new RenderingAttributes();
		ra.setVisible(true);		
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ|RenderingAttributes.ALLOW_VISIBLE_WRITE);
		
		Appearance outlineAppearance = new Appearance();
		outlineAppearance.setRenderingAttributes(ra);
		
		outline.setAppearance(outlineAppearance);
				
		//tg.setOutline(outline);
		
		/*
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
				
			
		*/////
		//end outline creation
		
		STLTransformGroup tg = new STLTransformGroup(stl, theModel, outline);
				
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
		
		return tg; 
	}
	
	/**
	 * Using the STLObject given this creates an outline of the model specified by 
	 * drawing lines along the edges of each facet
	 * @param stlo
	 * @return a Shape3D object created with a LineArray Geometry
	 */
	private static Shape3D createModelOutline(STLObject stlo){
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
	
	/**
	 * Using the STLObject given this creates the Shape3D model representing
	 * the model
	 * @param stlo
	 * @return Shape3D object created through TriangleArray Geometry
	 */
	private static Shape3D createModel(STLObject stlo){
		
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
	
}
