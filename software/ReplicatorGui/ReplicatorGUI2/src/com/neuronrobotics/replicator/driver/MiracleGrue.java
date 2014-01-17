package com.neuronrobotics.replicator.driver;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Arrays;

public class MiracleGrue extends ExternalSlicer {

	MiracleGrue(MaterialData data) {
		if(!(data instanceof MiracleGrueMaterialData))
			throw new RuntimeException("Inappropriate material data format");
		this.cmdline=Arrays.asList("./lib/miracle_grue", "-j");
	}
	
	public static void main(String args[]) throws Exception {
		ExternalSlicer slicer=new MiracleGrue(new MiracleGrueMaterialData());
		FileInputStream stlFile=new FileInputStream(args[0]);
		FileOutputStream dumpFile=new FileOutputStream(args[0]+"-dump.gcode");
		slicer.slice(stlFile, dumpFile);
	}

}
