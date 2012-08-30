package com.neuronrobotics.replicator.driver;

import java.io.InputStream;

import com.neuronrobotics.replicator.driver.delta.DeltaRobotConfig;
import com.neuronrobotics.replicator.driver.delta.DeltaRobotKinematics;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.LinkFactory;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.addons.kinematics.xml.XmlFactory;
import com.neuronrobotics.sdk.dyio.DyIO;

public class DeltaRobotPrinterPrototype extends AbstractKinematicsNR{
	DeltaRobotKinematics kinematics;
	
	//Configuration hard coded
	private  double e = 115.0;     // end effector
	private  double f = 457.3;     // base
	private  double re = 232.0;
	private  double rf = 112.0;
	private  double extrusionCachedValue = 0;
	//static InputStream s = XmlFactory.getDefaultConfigurationStream("DeltaPrototype.xml");
	
	public DeltaRobotPrinterPrototype(DeltaDoodle delt) {
		super(DeltaRobotKinematics.class.getResourceAsStream("DeltaPrototype.xml"),new LinkFactory( delt));
		//parse out the extruder configs
		//parse delta robot configs
		
		kinematics = new DeltaRobotKinematics(new DeltaRobotConfig(e, f, re, rf));
		//setNoFlush(true);
	}
	
	public MaterialData getMaterialData() {
		return new MaterialData();
	}
	
	public void setExtrusionTempreture(double [] extTemp) {
		
	}
	public void setBedTempreture(double bedTemp) {
		
	}
	public double[] setDesiredPrintLocetion(TransformNR taskSpaceTransform,double extrusionLegnth, double seconds) throws Exception{
		double[] back = super.setDesiredTaskSpaceTransform(taskSpaceTransform, seconds);
		//Set the extruder value
		
		//getFactory().flush(seconds);
		return back;
	}

	@Override
	public double[] inverseKinematics(TransformNR taskSpaceTransform)throws Exception {
		System.out.println("Setting printer to position: "+taskSpaceTransform);
		double [] links = kinematics.delta_calcInverse(taskSpaceTransform);
		double [] all = {links[0],links[1],links[2],getExtrusionCachedValue()};
		return all;
	}


	@Override
	public TransformNR forwardKinematics(double[] jointSpaceVector) {
		if(kinematics == null)
			return new TransformNR();
		return kinematics.delta_calcForward(jointSpaceVector);
	}

	public double getExtrusionCachedValue() {
		return extrusionCachedValue;
	}

	public void setExtrusionCachedValue(double extrusionCachedValue) {
		this.extrusionCachedValue = extrusionCachedValue;
	}
}
