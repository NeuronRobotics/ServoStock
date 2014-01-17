package com.neuronrobotics.replicator.driver;

import java.io.InputStream;

import com.neuronrobotics.replicator.driver.delta.DeltaRobotConfig;
import com.neuronrobotics.replicator.driver.delta.DeltaRobotKinematics;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.AbstractLink;
import com.neuronrobotics.sdk.addons.kinematics.ILinkListener;
import com.neuronrobotics.sdk.addons.kinematics.LinkFactory;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.addons.kinematics.xml.XmlFactory;
import com.neuronrobotics.sdk.common.DeviceConnectionException;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.pid.PIDLimitEvent;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class DeltaRobotPrinterPrototype extends AbstractKinematicsNR{
	DeltaRobotKinematics kinematics;
	
	//Configuration hard coded
	private  double extrusionCachedValue = 0;
	private double currentTemp =0;
	//static InputStream s = XmlFactory.getDefaultConfigurationStream("DeltaPrototype.xml");
	private AbstractLink extruder;
	private AbstractLink hotEnd;
	private double temp = 0;

	private final DeltaForgeDevice deltaDevice;
	
	public DeltaRobotPrinterPrototype(DeltaForgeDevice delt) {
		super(DeltaRobotKinematics.class.getResourceAsStream("DeltaPrototype.xml"),new LinkFactory( delt));
		this.deltaDevice = delt;
		
		extruder = getFactory().getLink("extruder");
		hotEnd = getFactory().getLink("hotEnd");
		setTempreture(getTempreture());
		getFactory().addLinkListener(new ILinkListener() {
			@Override
			public void onLinkPositionUpdate(AbstractLink source,double engineeringUnitsValue) {
				if(source == hotEnd) {
					setTempreture(engineeringUnitsValue);
				}
			}
			
			@Override
			public void onLinkLimit(AbstractLink source, PIDLimitEvent event) {
				// TODO Auto-generated method stub
				
			}
		});
		
		//parse out the extruder configs
		//parse delta robot configs
		
		setExtrusionTempreture(new double [] {getTempreture()});
	}
	
	private double getTempreture() {
		return temp;
	}
	public void setTempreture(double temp) {
		this.temp = temp;
	}
	
	public MaterialData getMaterialData() {
		return new MiracleGrueMaterialData();
	}
	
	public void setExtrusionTempreture(double [] extTemp) {
		if(extTemp[0] == currentTemp) {
			System.out.println("Printer at tempreture "+currentTemp+" C");
			return;
		}else
			currentTemp=extTemp[0];
		setTempreture(hotEnd.getCurrentEngineeringUnits());
		hotEnd.setTargetEngineeringUnits(extTemp[0]);
		hotEnd.flush(0);
		getTempreture();
		System.out.print("\r\nWaiting for Printer to come up to tempreture "+currentTemp+" C \n");
		Log.enableSystemPrint(false);
		int iter=0;
		while(temp>(extTemp[0]+10) || temp< (extTemp[0]-10)) {
			getTempreture();
			System.out.print(".");
			ThreadUtil.wait(100);
			iter++;
			if(iter==50) {
				System.out.print("\r\n "+temp+" C");
				iter=0;
			}
		}
		Log.enableSystemPrint(true);
	}
	public void setBedTempreture(double bedTemp) {
		
	}
	public int setDesiredPrintLocetion(TransformNR taskSpaceTransform,double extrusionLegnth, double seconds) throws Exception{
		System.out.println("Telling printer to go to extrusion len "+extrusionLegnth);
		return deltaDevice.sendLinearSection(taskSpaceTransform, extrusionLegnth, (int) (seconds*1000));
	}

	@Override
	public double[] inverseKinematics(TransformNR taskSpaceTransform)throws Exception {
		//System.out.println("Setting printer to position: "+taskSpaceTransform);
		double [] links = kinematics.delta_calcInverse(taskSpaceTransform);
		double [] all = {links[0],links[1],links[2],getExtrusionCachedValue(),130};
		
		String s = "[ ";
		for(int i=0;i<all.length;i++) {
			s+=all[i];
			if(i<all.length-1) {
				s+=",";
			}
			//all[i] = Math.toDegrees(all[i]);
		}
		s+="]";
		
		//System.out.println("Joint level = "+s);
		
		//return all;
		throw new RuntimeException();
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
	
	public void setExtrusionPoint(int materialNumber, double setPoint) {
		//TODO another method to set material
		extruder.setTargetEngineeringUnits(setPoint);
		setExtrusionCachedValue(setPoint);
	}
	
	public int getNumberOfSpacesInBuffer() {
		return deltaDevice.getNumberOfSpacesInBuffer();
	}
	
	public void cancelRunningPrint() {
		
		deltaDevice.cancelRunningPrint();
		
	}
	

}
