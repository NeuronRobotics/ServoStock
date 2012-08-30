package com.neuronrobotics.replicator.test;

import java.util.ArrayList;
import java.util.List;

import net.java.games.input.Component;
import net.java.games.input.Controller;
import net.java.games.input.ControllerEnvironment;

import com.neuronrobotics.replicator.driver.DeltaDoodle;
import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.dyio.peripherals.ServoChannel;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.util.ThreadUtil;

public class JoystickRecord {
	DeltaRobotPrinterPrototype deltaRobot;
	DeltaDoodle slave = null;
	private int open = 20;
	private int closed = 100;
	private boolean button=false;
	private boolean lastButton=false;
	
	TransformNR current = new TransformNR();
	TransformNR currentNew = new TransformNR();
	
	private Controller pad=null;
	private Component padX=null;
	private Component padY=null;
	private Component padZ=null;
	private Component saveLocation=null;
	private Component trigger=null;
	
	
	public JoystickRecord(){
		connectDelta();
		
		startJoystick();
		
//		ServoChannel hand = new ServoChannel(slave.getChannel(15));
//		hand.SetPosition(open);
		
		try {
			System.out.println("Setting to 0,0,0");
			deltaRobot.setDesiredTaskSpaceTransform(new TransformNR(),.5);
			ThreadUtil.wait(1000);
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		
		while(slave.isAvailable() && pad.poll()){
			ThreadUtil.wait(30);
			button = trigger.getPollData()<=0;
			boolean save = saveLocation.getPollData()<=0;
			if(button!=lastButton) {
				lastButton = button;
//				hand.SetPosition(button?open:closed);
//				hand.flush();
			}
			Log.enableDebugPrint(false);
			try {
				double XYscale = 70;
				double x=padX.getPollData()*-XYscale;
				double y=padY.getPollData()*XYscale;
				double z=padZ.getPollData()*100 + 200;
				if(z<150)
					z=150;

				currentNew = new TransformNR(x, y, z, new RotationNR());
				System.out.println("Attempting :"+currentNew);
				deltaRobot.setDesiredTaskSpaceTransform(currentNew,.1);
				current =currentNew.copy(); 
			} catch (Exception e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}
	private void startJoystick() {
		Controller[] controllers = ControllerEnvironment.getDefaultEnvironment().getControllers(); // get input devices
	      for(int i=0;i<controllers.length && pad==null;i++) {
	    	  // Look for the first gamepad or joystick
	    	  if(controllers[i].getType()==Controller.Type.GAMEPAD || controllers[i].getType()==Controller.Type.STICK) {
	              // Found a mouse
	              pad = controllers[i];
	           }
	        }
	    if (pad==null) System.exit(0);
	    System.out.println("First gamepad is: " + pad.getName()); 
	    Component[] components = pad.getComponents();
	    for(int i=0;i<components.length;i++) {
	    	if(components[i].isAnalog()) {
	    		System.out.println("Checking \""+components[i].getName()+"\""); 
	    		if(components[i].getName().equals("X Axis") || components[i].getName().equals("x")){
	    			padX=components[i];
	    			System.out.println("Found X Axis, "+i); 
	    		}
	    		if(components[i].getName().equals("Y Axis") || components[i].getName().equals("y")){
	    			padY=components[i];
	    			System.out.println("Found Y Axis, "+i); 
	    		}
	    		if(components[i].getName().equals("Z Axis") || components[i].getName().equals("z")){
	    			padZ=components[i];
	    			System.out.println("Found Thrust Axis, "+i); 
	    		}
	    	}
	    }
	    trigger = pad.getComponents()[0];
		saveLocation = pad.getComponents()[1];
	}
	public static void main(String[] args) {
		try{
			new JoystickRecord();
		}catch (Exception ex){
			ex.printStackTrace();
			System.exit(0);
		}
	}
	private void connectDelta(){
		ArrayList<DeltaDoodle> temp= new ArrayList<DeltaDoodle>();
		List <String> ports = SerialConnection.getAvailableSerialPorts();
		//Start by searching through all available serial connections for DyIOs connected to the system
		for(String s: ports){
			if(s.toLowerCase().contains("delta") ){//Change this to match the OS you are using and any known serial port filter
				try{
					DeltaDoodle d = new DeltaDoodle();
					d.setConnection(new SerialConnection(s));
					d.connect();
					if(d.isAvailable()){
						temp.add(d);
					}
				}catch(Exception EX){
					EX.printStackTrace();
					System.err.println("Serial port "+s+" is not a Delta");
				}
			}
		}
		
		//Now that all connected DyIOs are connected, search for the correct MAC addresses 
		for(DeltaDoodle d : temp){
			String addr = d.getAddress().toString();
			if(addr.equalsIgnoreCase("74:f7:26:01:01:01") ){
				slave = d;
			}
		}
		//If both are not found then the system can not run
		if(slave == null){
			for(DeltaDoodle d:temp){
				System.out.println(d);
				if(d!= null){
					if(d.isAvailable())
						d.disconnect();
				}
			}
			throw new RuntimeException("One or both devices were not found ");
		}
		//slave.setServoPowerSafeMode(false);
		deltaRobot = new DeltaRobotPrinterPrototype(slave);
		deltaRobot.setCurrentPoseTarget(new TransformNR());
	}
}
