package com.neuronrobotics.replicator.common;

import java.io.FileWriter;
import java.io.IOException;
import java.text.DecimalFormat;
import java.text.Format;

import javax.vecmath.Point3f;
import javax.vecmath.Vector3f;


public class ASCIISTLWriter extends STLWriter{

	public ASCIISTLWriter(STLObject stl) {
		super(stl);
	}

	@Override
	public void writeHeader(FileWriter fw) throws IOException {
		fw.write("solid "+theSTL.getName()+"\n");
	}

	@Override
	public void writeFacet(STLFacet fac, FileWriter fw) throws IOException {
		fw.write("facet ");
		Vector3f norm = fac.getNormal();
		if(norm!=null){
			writeNormal(norm,fw);
		}
		fw.write("outer loop\n");
		
		writeVertex(fac.getVertex1(),fw);
		writeVertex(fac.getVertex2(),fw);
		writeVertex(fac.getVertex3(),fw);
		
		fw.write("endloop\n");
		fw.write("endfacet\n");		
	}

	private void writeVertex(Point3f vertex, FileWriter fw) throws IOException {
		fw.write("vertex "+toMantissaString(vertex.x)+" "+toMantissaString(vertex.y)+" "+toMantissaString(vertex.z)+"\n");
		
	}

	private void writeNormal(Vector3f norm, FileWriter fw) throws IOException {
		fw.write("normal "+toMantissaString(norm.x)+" "+toMantissaString(norm.y)+" "+toMantissaString(norm.z)+"\n");
	}

	private String toMantissaString(float x) {
		// TODO Auto-generated method stub
		int exp = (int)Math.log10(x);
		char plusMinus = '+';
		if (exp<0){
			exp--;
			plusMinus = '-';
		}
		else exp++;
		
		float tempX = (float) (x/Math.pow(10, exp));
		
		String num = String.format("%.6f", tempX);
		
		return num+"e"+plusMinus+exp;
	}

	@Override
	public void writeFooter(FileWriter fw) throws IOException {
		// TODO Auto-generated method stub
		fw.write("endsolid "+theSTL.getName());
	}


}
