package com.neuronrobotics.replicator.common;

import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Scanner;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;


public class BinarySTLParser extends STLParser {
	
	
	private long facetAmount, currentFacet;
	private byte[] header;
	private DataInputStream dataStream;
	private int bytesPreRead;
	private byte[] preBuff;

	protected BinarySTLParser(InputStream is, int ct, byte[] preBuff) throws IOException{
		name = null;
		header = null;
		this.stream=is;
		facetAmount = -1;
		currentFacet = -1;
		dataStream = new DataInputStream(is);
		this.preBuff = preBuff;
		bytesPreRead=ct;
		readHeader();//TODO change readHeader to protected, call from AbstractFactory?

	}
	
	@Override
	public STLFacet nextFacet() throws Exception {
		if (header==null) readHeader();
		STLFacet tempFacet = new STLFacet();
		Vector3f normal = extractNormal();
		Point3f v1 = extractVertex();
		Point3f v2 = extractVertex();
		Point3f v3 = extractVertex();
		int colorInfo = dataStream.readUnsignedShort();
		tempFacet.setNormal(normal);
		tempFacet.setVertices(v1, v2, v3);
		currentFacet++;
		return tempFacet;
	}
	/**
	 * This method assumes the next bytes in the stream are a vertex
	 * It reads 3 floats and puts them into a Point3f object
	 * @return a vertex as a Point3f object
	 * @throws IOException 
	 */
	private Point3f extractVertex() throws IOException {
		// TODO Auto-generated method stub
		float x, y, z;
		x=dataStream.readFloat();
		y=dataStream.readFloat();
		z=dataStream.readFloat();
		return new Point3f(x,y,z);
	}

	/**
	 * This method assumes the next bytes in the stream are a normal
	 * It reads 3 floats and puts them into a Vector3f object 
	 * @return Vector3f object representing the normal
	 * @throws IOException 
	 */
	private Vector3f extractNormal() throws IOException {
		float x, y, z;
		x=dataStream.readFloat();
		y=dataStream.readFloat();
		z=dataStream.readFloat();
		return new Vector3f(x,y,z);
	}

	private void readHeader() throws IOException {
		header = new byte[80];
		int i;
		for (i = 0; i<bytesPreRead;i++){
			header[i]=preBuff[i];
		}
		if(bytesPreRead>0) dataStream.read(header, bytesPreRead, 80-bytesPreRead);
		
		byte[] buf = new byte[4];
		
		dataStream.read(buf, 0, 4);
		facetAmount=buf[3];
		facetAmount<<=8;
		facetAmount=buf[2];
		facetAmount<<=8;
		facetAmount=buf[1];
		facetAmount<<=8;
		facetAmount=buf[0];
		currentFacet=1;
	}

	@Override
	public String getName() throws IOException {
		if (header==null) readHeader();
		name = "default";//TODO look at the header for the name?
		return name;
	}

	@Override
	public boolean hasNextFacet() {
		return currentFacet<=facetAmount;
	}
	
	

}
