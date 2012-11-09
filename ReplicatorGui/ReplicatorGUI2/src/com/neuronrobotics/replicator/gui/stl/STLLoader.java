package com.neuronrobotics.replicator.gui.stl;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;

import javax.media.j3d.*;

import com.neuronrobotics.replicator.gui.preview.j3d.STLShape3DFactory;
import com.neuronrobotics.replicator.gui.preview.j3d.STLTransformGroup;

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
		return loadFile(is,true);
	}
	
	/**
	 * Takes in an InputStream for the stl file data and reads the data into 
	 * an STLObject which is returned 
	 * @param is
	 * @return and STLObject encapsulating the data read in from the file
	 * @throws IOException
	 */
	public static STLObject loadFile(InputStream is, boolean closeStream) throws IOException{
		String name;
		ArrayList<STLFacet> facets = new ArrayList<STLFacet>();
				
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
				break;
			}
					
			facets.add(tempFacet);
		}
		
		if(closeStream) is.close();
		
		return new STLObject(name,facets);
		
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
	public static STLTransformGroup createSTLTransform(String filename) throws IOException{
		return createSTLTransform(new File(filename));
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
	public static STLTransformGroup createSTLTransform(File file) throws IOException{
		STLObject stl = loadFile(file);
		return createSTLTransform(stl);	
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
	public static STLTransformGroup createSTLTransform(InputStream is,boolean closeStream) throws IOException{
		STLObject stl = loadFile(is,closeStream);
		return createSTLTransform(stl);	
	}
	
	/**
	 * Uses the STLObject and creates model and model outline which are added to an
	 * STLTransformGroup object along with a the capability for the outline to have its
	 * visibility read and written and the entire group to allow transform reads and writes
	 * @param stl
	 * @param root
	 * @return
	 */
	public static STLTransformGroup createSTLTransform(STLObject stl){
		//STLTransformGroup tg = new STLTransformGroup();
				
		//Actual 3d model
		Shape3D theModel = STLShape3DFactory.getModelShape3D(stl);
				
		//Outline with visibility option
		Shape3D outline = STLShape3DFactory.getFacetOutline(stl);
		
		RenderingAttributes ra = new RenderingAttributes();
		ra.setVisible(true);		
		ra.setCapability(RenderingAttributes.ALLOW_VISIBLE_READ|RenderingAttributes.ALLOW_VISIBLE_WRITE);
		
		Appearance outlineAppearance = new Appearance();
		outlineAppearance.setRenderingAttributes(ra);
		
		outline.setAppearance(outlineAppearance);
				
		//end outline creation
		
		STLTransformGroup tg = new STLTransformGroup(stl, theModel, outline);
				
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		tg.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
		
		return tg; 
	}
	
}
