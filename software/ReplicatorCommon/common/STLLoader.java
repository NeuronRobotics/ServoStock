package com.neuronrobotics.replicator.common;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.Scanner;
import java.util.StringTokenizer;

import javax.media.j3d.*;
import javax.vecmath.*;

import org.j3d.loaders.InvalidFormatException;
import com.sun.j3d.utils.behaviors.mouse.*;
import com.sun.j3d.utils.geometry.NormalGenerator;
import com.sun.j3d.utils.geometry.GeometryInfo;

public class STLLoader {
	
	@SuppressWarnings("restriction")
	public static TransformGroup getSTLTransform(String filename,BranchGroup root) throws IOException{
		return getSTLTransform(new File(filename),root);
	}
	
	@SuppressWarnings("restriction")
	public static TransformGroup getSTLTransform(File f,BranchGroup root) throws IOException{
		STLObject stl = loadFile2(f);
		return getSTLTransform(stl,root);	
	}
	
	@SuppressWarnings("restriction")
	public static TransformGroup getSTLTransform(STLObject stl,BranchGroup root) throws IOException{
		TransformGroup tg = new TransformGroup();
		tg.addChild(createModel(stl));
		
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
		
		MouseRotate myMouseRotate = new MouseRotate();
		myMouseRotate.setTransformGroup(tg);
		myMouseRotate.setSchedulingBounds(new BoundingSphere());
		
		root.addChild(myMouseRotate);//TODO find out why this needs to be a child here and eb connected to the transformgroup
		
		return tg; //TODO implement
	}
	
	@SuppressWarnings("restriction")
	public static STLObject loadFile(File theFile) throws IOException{
		String name;
		//TODO re add in functionality
		Point3f center = new Point3f(), min = new Point3f(), max = new Point3f();
		ArrayList<STLFacet> facets = new ArrayList<STLFacet>();
		
		Scanner s; //TODO Change this to some sort of STLParser
		s = new Scanner(theFile);
		String line[] = s.nextLine().split(" ");
		if (line.length>1) name=line[1].trim();
		else name ="";
		facets=new ArrayList<STLFacet>();
		while(s.hasNext()){
			STLFacet tempFacet = new STLFacet();
			String normalLine[] = s.nextLine().split(" ");
			if(normalLine[0].contains("endsolid")) break;
			if (normalLine.length==5){
				float nx, ny, nz;
				nx = parseFloatUtil(normalLine[2]);
				ny = parseFloatUtil(normalLine[3]);
				nz = parseFloatUtil(normalLine[4]);
								
				tempFacet.setNormal(new Vector3f(nx,ny,nz));
			}
			s.nextLine();
			Point3f v1, v2, v3;
			v1=extractVertex(s.nextLine());
			v2=extractVertex(s.nextLine());
			v3=extractVertex(s.nextLine());
			//Update mins and maxes
			if (facets.isEmpty()) {
				max.x = Math.max(Math.max(v1.x,v2.x),v3.x);
				min.x = Math.min(Math.min(v1.x,v2.x),v3.x);
				max.y = Math.max(Math.max(v1.y,v2.y),v3.y);
				min.y = Math.min(Math.min(v1.y,v2.y),v3.y);
				max.z = Math.max(Math.max(v1.z,v2.z),v3.z);
				min.z = Math.min(Math.min(v1.z,v2.z),v3.z);
			} else {
				//TODO, should get these mins, maxes once and deuglyfy this
				if (Math.max(Math.max(v1.x,v2.x),v3.x) > max.x)
					max.x = Math.max(Math.max(v1.x,v2.x),v3.x);
				if (Math.min(Math.min(v1.x,v2.x),v3.x) < min.x)
					min.x = Math.min(Math.min(v1.x,v2.x),v3.x);
				if (Math.max(Math.max(v1.y,v2.y),v3.y) > max.y)
					max.y = Math.max(Math.max(v1.y,v2.y),v3.y);;
				if (Math.min(Math.min(v1.y,v2.y),v3.y) < min.y)
					min.y = Math.min(Math.min(v1.y,v2.y),v3.y);
				if (Math.max(Math.max(v1.z,v2.z),v3.z) > max.z)
					max.z = Math.max(Math.max(v1.z,v2.z),v3.z);
				if (Math.min(Math.min(v1.z,v2.z),v3.z) < min.z)
					min.z = Math.min(Math.min(v1.z,v2.z),v3.z);
			}
			////
			tempFacet.setVertices(v1, v2, v3);
			
			s.nextLine();
			s.nextLine();//TODO, use these lines to check correct file format
			
			facets.add(tempFacet);
		}
		return new STLObject(theFile,name,facets,null,min,max);
		
	}
	
	@SuppressWarnings("restriction")
	public static STLObject loadFile2(File theFile) throws IOException{
		String name;
		Point3f center = new Point3f(), min = new Point3f(), max = new Point3f();
		ArrayList<STLFacet> facets = new ArrayList<STLFacet>();
		
		InputStream is = new FileInputStream(theFile);//TODO change to accept input stream
		
		STLParser theParser = STLParser.getParser(is);
		
		name = theParser.getName();
		
		facets=new ArrayList<STLFacet>();
		while(theParser.hasNextFacet()){
			STLFacet tempFacet;
			try {
				tempFacet = theParser.nextFacet();
			} catch (Exception e) { //TODO this will use a more appropriate exception
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
		
		return new STLObject(theFile,name,facets,null,min,max);
		
	}
	
	//TODO remove
	private static Float parseFloatUtil(String s){
		String line[] = s.split("e");
		float f = Float.parseFloat(line[0]);
		if (line.length==2) f*=(float)(Math.pow(10,Float.parseFloat(line[1])));
		return f;
	}
	
	//TODO remove
	private static Point3f extractVertex(String nextLine) {
		// TODO
		StringTokenizer strtok = new StringTokenizer(nextLine);
		strtok.nextToken(); //TODO check if this says vertex?
		Float x = parseFloatUtil(strtok.nextToken());
		Float y = parseFloatUtil(strtok.nextToken());
		Float z = parseFloatUtil(strtok.nextToken());
		return new Point3f(x, y, z);
	}
	
	private static Shape3D createModel(STLObject stlo) throws IOException {
		// TODO Auto-generated method stub

		//STLObject stlo;
		
		//stlo = STLLoader.loadFile(f);//)new STLObject(f);
		//stlo.loadFile();

		Iterator<STLFacet> facets = stlo.getFacetIterator();

		int numVertices = stlo.getFacetAmount() * 3;

		Appearance modelAppearance = new Appearance();
		
		modelAppearance.setColoringAttributes(new ColoringAttributes(new Color3f(.7f,0.7f,0.7f),ColoringAttributes.NICEST));

		modelAppearance.setMaterial(new Material());//TODO what?
		
		TriangleArray model = new TriangleArray(numVertices,
				TriangleArray.COORDINATES);
		
			
		int currVertex = 0;
		
		
		float scale = 1f/Math.max(Math.max(stlo.getXDistance(),stlo.getYDistance()),stlo.getZDistance());
		
		Vector3f[] normals = new Vector3f[stlo.getFacetAmount()];
		
		Point3f center = stlo.getCenter();
		for(STLFacet sf:stlo.getFacetIterable()){
			model.setCoordinate(currVertex++, centeredScale(sf.getVertex1(),center,scale));
			model.setCoordinate(currVertex++, centeredScale(sf.getVertex2(),center,scale));
			model.setCoordinate(currVertex++, centeredScale(sf.getVertex3(),center,scale));
			normals[(currVertex/3)-1]=sf.getNormal();
		}
		
		GeometryInfo gi = new GeometryInfo(model);
		NormalGenerator ng = new NormalGenerator();
		ng.generateNormals(gi);
		
		model.setCapability(TriangleArray.NORMALS);
		//model.setNormals(0,normals);
		
		
		return new Shape3D(model, modelAppearance);
	}
	
	private static Point3f centeredScale(Point3f p,Point3f c, float scale){
		//TODO remove this completely eventually
		/*
		float x = p.x;//(p.x-c.x)*scale;
		float y = p.y;//(p.y-c.y)*scale;
		float z = p.z;//(p.z-c.z)*scale;
		*/
		float x = (p.x-c.x)*scale;
		float y = (p.y-c.y)*scale;
		float z = (p.z-c.z)*scale;
		
		return new Point3f(x,y,z);
	}

}
