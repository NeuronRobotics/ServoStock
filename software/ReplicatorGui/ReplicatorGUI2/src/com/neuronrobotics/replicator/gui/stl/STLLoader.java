package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

public class STLLoader {

	/**
	 * Takes in file, converts to an InputStream and returns resulting STLObject
	 * from loadFile(InputStream is)
	 * 
	 * @param theFile
	 * @return an STLObject encapsulating the data read in from the file
	 * @throws IOException
	 */
	public static STLObject loadFile(File theFile) throws IOException {
		InputStream is = new FileInputStream(theFile);
		return loadFile(is, true);
	}

	/**
	 * Takes in an InputStream for the stl file data and reads the data into an
	 * STLObject which is returned
	 * 
	 * @param is
	 * @return and STLObject encapsulating the data read in from the file
	 * @throws IOException
	 */
	public static STLObject loadFile(InputStream is, boolean closeStream)
			throws IOException {
		String name;
		ArrayList<STLFacet> facets = new ArrayList<STLFacet>();

		STLParser theParser = STLParser.getParser(is);

		name = theParser.getName();

		facets = new ArrayList<STLFacet>();
		while (theParser.hasNextFacet()) {
			STLFacet tempFacet;
			try {
				tempFacet = theParser.nextFacet();
			} catch (Exception e) {
				e.printStackTrace();
				System.out
						.print("This should never happen. Check for end of file may be failing.");
				break;
			}

			facets.add(tempFacet);
		}

		if (closeStream)
			is.close();

		return new STLObject(name, facets);

	}
	
}
