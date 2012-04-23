package com.neuronrobotics.replicator.test.trobot;

import java.awt.Font;

import javax.media.j3d.AmbientLight;
import javax.media.j3d.Appearance;
import javax.media.j3d.BoundingBox;
import javax.media.j3d.BoundingSphere;
import javax.media.j3d.Bounds;
import javax.media.j3d.ColoringAttributes;
import javax.media.j3d.DirectionalLight;
import javax.media.j3d.Font3D;
import javax.media.j3d.FontExtrusion;
import javax.media.j3d.Material;
import javax.media.j3d.Shape3D;
import javax.media.j3d.Text3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.vecmath.Color3f;
import javax.vecmath.Vector3f;

import Jama.Matrix;

import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.sun.j3d.utils.geometry.ColorCube;


public class TransformFactory {
	
	public static Transform3D getTransform(double x, double y, double z){
		return getTransform(new TransformNR(x, y, z, new RotationNR()));
	}
	
	public static Transform3D getTransform(TransformNR input){
		double [][] data = input.getMatrixTransform().getArray();
		int div = 20;
		data[0][3]/=div;
		data[1][3]/=div;
		data[2][3]/=div;
		double [] output = new double [16];
		int x=0;
		int y=0;
		for(int i=0;i<16;i++){
			output[i]=data[y][x++];
			if(x>3){
				x=0;
				y++;
			}
		}
		Transform3D t = new Transform3D(output);
		return t;
	}
	public static TransformGroup getLabledAxis(TransformNR input, String text){
		//System.out.println("Creating transform "+text+" with\n"+input);
		Transform3D trans = getTransform(input);
		TransformGroup back = new TransformGroup(trans);
		
		
		Appearance textAppear = new Appearance();
        ColoringAttributes textColor = new ColoringAttributes();
        textColor.setColor(1.0f, 0.0f, 0.0f);
        textAppear.setColoringAttributes(textColor);
        textAppear.setMaterial(new Material());
        
        Font3D font3D = new Font3D(new Font("Helvetica", Font.PLAIN, 1), new FontExtrusion());
		Text3D textGeom = new Text3D(font3D, new String(text));
		textGeom.setAlignment(Text3D.ALIGN_FIRST);
		Shape3D textShape = new Shape3D();
		textShape.setGeometry(textGeom);
		textShape.setAppearance(textAppear);
		
		//back.addChild(new ColorCube(.5));
		back.addChild(new Axis());
		Transform3D txtTrans = new Transform3D();
		txtTrans.mul(trans);
		txtTrans.rotX(Math.PI/2);
		txtTrans.rotY(-Math.PI/2);
		TransformGroup textGroup = new TransformGroup(txtTrans);
		//Add text
		textGroup.addChild(textShape);
		
		back.addChild(textGroup);
        // a bounding sphere specifies a region a behavior is active
        // create a sphere centered at the origin with radius of 100
        BoundingSphere bounds = new BoundingSphere();;

        DirectionalLight lightD = new DirectionalLight();
        lightD.setInfluencingBounds(bounds);
        lightD.setDirection(new Vector3f(0.0f, 0.0f, -1.0f));
        lightD.setColor(new Color3f(1.0f, 0.0f, 1.0f));
        back.addChild(lightD);

        AmbientLight lightA = new AmbientLight();
        lightA.setInfluencingBounds(bounds);
        back.addChild(lightA);
        BoundingBox pickBox = new BoundingBox();

		back.setCapability(TransformGroup.ALLOW_TRANSFORM_READ);
		back.setCapability(TransformGroup.ALLOW_TRANSFORM_WRITE);
		back.setCapability(TransformGroup.ALLOW_BOUNDS_READ);
		back.setCapability(TransformGroup.ALLOW_BOUNDS_WRITE);
		back.setCapability(TransformGroup.ENABLE_PICK_REPORTING);
		back.setBounds(pickBox);
		back.setPickable(true);
		return back;
	}
}
