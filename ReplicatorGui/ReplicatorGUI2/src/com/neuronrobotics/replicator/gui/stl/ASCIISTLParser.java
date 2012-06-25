package com.neuronrobotics.replicator.gui.stl;

import java.io.InputStream;
import java.util.NoSuchElementException;
import java.util.Scanner;
import java.util.StringTokenizer;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;


public class ASCIISTLParser extends STLParser {

	private String nextLine;
	private Scanner s;
	
	protected ASCIISTLParser(InputStream is){
		name = null;
		nextLine = "";
		s = new Scanner(is);
	}
	
	@Override
	public STLFacet nextFacet() throws NoSuchElementException {
		//important to call this or we will try to read facets before header has been read
		if (name==null) getName();  
		STLFacet tempFacet;
				
		if (!hasNextFacet()) throw new NoSuchElementException();
					
		s.nextLine();//Skip line, should just say "outer loop" or "outerloop"
		
		//Extract vertex information
		Point3f v1, v2, v3;
		v1=extractVertex(s.nextLine());
		v2=extractVertex(s.nextLine());
		v3=extractVertex(s.nextLine());		
		
		
		String normalLine[] = nextLine.split("\\s+");
		
		//Process Normal information, may not be included
		if (normalLine.length==50){
			float nx, ny, nz;
			nx = parseFloatUtil(normalLine[2]);
			ny = parseFloatUtil(normalLine[3]);
			nz = parseFloatUtil(normalLine[4]);
			
			tempFacet = new STLFacet(v1, v2, v3,new Vector3f(nx,ny,nz));
			
		}
		else{
			//STLFacet will automatically calculate the normal if not given
			tempFacet = new STLFacet(v1,v2,v3);
			
		}
		
		s.nextLine();//skip over next line should say "endloop" or "end loop"
		s.nextLine();//skip over next line should say "end facet
		
		//This should contain first line of next facet or "endsolid" if no facets left
		nextLine = s.nextLine();
		
		return tempFacet;
	}

	@Override
	public String getName() {
		//by convention, name will be null iff header has not been parsed yet
		if (name==null){
			String line[] = s.nextLine().split("\\s+");
			if (line.length>1) name=line[1].trim();
			else name = "default";
			nextLine = s.nextLine(); 
		}
		//System.out.println(name);
		return name;
	}

	@Override
	public boolean hasNextFacet() {
		return !(nextLine.contains("endsolid")||nextLine.contains("end solid"));
	}
	
	/**
	 * Utility method that reads in a float represented as a string. 
	 * The variety in possible formatting
	 * gave unexpected output when simply using Float.parseFloat()
	 * @param s
	 * @return float 
	 */
	private static Float parseFloatUtil(String s){
		String line[] = s.split("e");
		float f = Float.parseFloat(line[0]);
		if (line.length==2) f*=(float)(Math.pow(10,Float.parseFloat(line[1])));
		return f;
	}
	
	/**
	 * Uses parseFloatUtil in order to read in the whole vertex
	 * @param nextLine
	 * @return Point3f comprised of the three read in floats
	 */
	private static Point3f extractVertex(String nextLine) {
		StringTokenizer strtok = new StringTokenizer(nextLine);
		strtok.nextToken(); //This should say vertex 
		Float x = parseFloatUtil(strtok.nextToken());
		Float y = parseFloatUtil(strtok.nextToken());
		Float z = parseFloatUtil(strtok.nextToken());
		return new Point3f(x, y, z);
	}

}
