package com.neuronrobotics.replicator.driver;

import java.io.File;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.ProcessBuilder.Redirect;

public class ExternalSlicer extends StlSlicer {
	List<String> cmdline;

	public ExternalSlicer() {
		super(new MaterialData());
	}

	public ExternalSlicer(MaterialData data) {
		super(data);
		// Ignore the data for now.
	}

	public boolean slice(InputStream stl, OutputStream gcode) {
	try {
		ProcessBuilder builder=new ProcessBuilder();
		File input=File.createTempFile("replicator_toprint",".stl");
		File output=File.createTempFile("replicator_slicer_output",".stl");
//		File output=new File(input.getAbsolutePath().replaceAll("\\.stl\\z",".gcode")); // For the moment.
		List<String> thisCommand=new ArrayList<String>(cmdline);
		thisCommand.add("-o");
		thisCommand.add(output.getAbsolutePath());
		thisCommand.add(input.getAbsolutePath());
		OutputStream toTemp=new FileOutputStream(input);
		new StreamDump(stl, toTemp).run();
		System.err.println(thisCommand);
		builder.redirectErrorStream(true);
		builder.redirectOutput(Redirect.INHERIT);
		builder.command(thisCommand);
		Process p=builder.start();
		new Thread(new StreamDump(p.getInputStream(), System.out)).start();
		p.waitFor();
		FileInputStream inFromTemp=new FileInputStream(output);
		new StreamDump(inFromTemp, gcode).run();
		return true;
	} catch(IOException e) {
		System.err.println(e);
		return false;
	} catch(InterruptedException e) {
		System.err.println(e);
		return false;
	}
	}
	public static void main(String args[]) throws Exception {
		ExternalSlicer slicer=new MiracleGrue(null);
//		slicer.cmdline=Arrays.asList("skeinforge");
		FileInputStream stlFile=new FileInputStream(args[0]);
		FileOutputStream dumpFile=new FileOutputStream(args[0]+"-dump.gcode");
		slicer.slice(stlFile, dumpFile);
	}
}

class StreamDump implements Runnable {
	InputStream in;
	OutputStream out;
	StreamDump(InputStream in, OutputStream out) {
		this.in=in;
		this.out=out;
	}
	public void run() {
		try {
		int len;
		byte buffer[]=new byte[256];
		while((len=in.read(buffer))!=-1)
			out.write(buffer,0,len);
		} catch(IOException e) {
			return;
		}
	}
}

