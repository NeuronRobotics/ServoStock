package com.neuronrobotics.replicator.test;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import net.miginfocom.swing.MigLayout;

import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.ITaskSpaceUpdateListenerNR;
import com.neuronrobotics.sdk.addons.kinematics.DHParameterKinematics;
import com.neuronrobotics.sdk.addons.kinematics.gui.SampleGuiNR;
import com.neuronrobotics.sdk.addons.kinematics.gui.TrobotViewer;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.dyio.peripherals.DigitalInputChannel;
import com.neuronrobotics.sdk.dyio.peripherals.IDigitalInputListener;
import com.neuronrobotics.sdk.dyio.peripherals.ServoChannel;
import com.neuronrobotics.sdk.dyio.sequencer.ServoOutputScheduleChannel;
import com.neuronrobotics.sdk.serial.SerialConnection;
public class DirectControl implements ITaskSpaceUpdateListenerNR, IDigitalInputListener {
	DHParameterKinematics model;
	DeltaRobotPrinterPrototype deltaRobot;
	TransformNR current = new TransformNR();
	double scale=1.5;
	double [] startVect = new double [] { 0,0,0,0,0,0};
	private boolean button=false;
	private boolean lastButton=false;
	private int open = 20;
	private int closed = 100;
	
	public DirectControl() {
		DyIO.disableFWCheck();
		
		//Create the references for my known DyIOs
		DyIO master = null;
		DyIO slave = null;
		
		ArrayList<DyIO> temp= new ArrayList<DyIO>();
		List <String> ports = SerialConnection.getAvailableSerialPorts();
		//Start by searching through all available serial connections for DyIOs connected to the system
		for(String s: ports){
			if(s.toLowerCase().contains("dyio") ){//Change this to match the OS you are using and any known serial port filter
				try{
					DyIO d = new DyIO(new SerialConnection(s));
					d.connect();
					if(d.isAvailable()){
						temp.add(d);
					}
				}catch(Exception EX){
					EX.printStackTrace();
					System.err.println("Serial port "+s+" is not a DyIO");
				}
			}
		}
		
		//Now that all connected DyIOs are connected, search for the correct MAC addresses 
		for(DyIO d : temp){
			String addr = d.getAddress().toString();
			if(addr.equalsIgnoreCase("74:f7:26:00:00:6f")){
				master = d;
			}
			if(addr.equalsIgnoreCase("74:f7:26:80:00:99") || addr.equalsIgnoreCase("74:F7:26:80:00:A1")){//THis works with 2 different DyIOs as slaves
				slave = d;
			}
		}
		//If both are not found then the system can not run
		if(master == null || slave == null){
			for(DyIO d:temp){
				System.out.println(d);
				if(d!= null){
					if(d.isAvailable())
						d.disconnect();
				}
			}
			throw new RuntimeException("One or both devices were not found ");
		}
		
		
//		DyIO tmp0 = new DyIO(new SerialConnection("/dev/DyIO0"));	
//		if(!tmp0.connect()){
//			throw new RuntimeException("Not a bowler Device on connection: ");
//		}
//		DyIO tmp1 = new DyIO(new SerialConnection("/dev/DyIO1"));	
//		if(!tmp1.connect()){
//			throw new RuntimeException("Not a bowler Device on connection: ");
//		}
//		
//		String addr0 = tmp0.getAddress().toString().toLowerCase();
//		String addr1 = tmp1.getAddress().toString().toLowerCase();
//		
//		System.out.println("Addresses are "+addr0+" "+addr1);
//		
//		if(	addr0.contains("74:f7:26:00:00:6f")&&
//			addr1.contains("74:f7:26:80:00:99")	) {
//			master = tmp0;
//			delt = tmp1;
//		}else if(	addr1.contains("74:f7:26:00:00:6f")&&
//					addr0.contains("74:f7:26:80:00:99")	) {
//			master = tmp1;
//			delt = tmp0;
//		}else {
//			throw new RuntimeException("Not a bowler Device on connection: ");
//		}
		
		master.killAllPidGroups();
		model = new DHParameterKinematics(master,"TrobotMaster.xml");
		model.addPoseUpdateListener(this);
		slave.setServoPowerSafeMode(false);
		deltaRobot = new DeltaRobotPrinterPrototype(slave);
		deltaRobot.setCurrentPoseTarget(new TransformNR());
		
		DigitalInputChannel di = new DigitalInputChannel(master.getChannel(0));
		di.addDigitalInputListener(this);
		button=di.isHigh();
		lastButton = button;
		
		ServoChannel hand = new ServoChannel(slave.getChannel(15));
		hand.SetPosition(open);
		
		try{
			final SampleGuiNR gui = new SampleGuiNR();
			final JFrame frame = new JFrame();
			final JTabbedPane tabs = new JTabbedPane();
			JPanel starter = new JPanel(new MigLayout());
			gui.setKinematicsModel(model);
			try{
				tabs.add("Display",new TrobotViewer(model));
			}catch(Error ex){
				JPanel error = new JPanel(new MigLayout());
				error.add(new JLabel("Error while loading Java3d library:"),"wrap");
				error.add(new JLabel(ex.getMessage()),"wrap");
				error.add(new JLabel(System.getProperty("java.library.path")),"wrap");
				tabs.add("Display [ERROR]",error);
				ex.printStackTrace();
				System.out.println("Lib path searched");
			}
			
			frame.setLocationRelativeTo(null);
			zero();
			
			gui.add(starter);
			tabs.add("Control",gui);
			//Add scroller here
			frame.getContentPane().add(tabs);
			//frame.setSize(640, 480);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.pack();
			frame.setLocationRelativeTo(null);
			frame.setVisible(true);
			
		}catch(Exception ex){
			ex.printStackTrace();
			System.exit(1);
		}
		
		while (slave.isAvailable() && master.isAvailable()) {
			long time = System.currentTimeMillis();
			try {				
				if(button!=lastButton) {
					lastButton = button;
					hand.SetPosition(button?open:closed);
					hand.flush();
				}
				deltaRobot.setDesiredTaskSpaceTransform(current,.1);

			} catch (Exception e) {
				e.printStackTrace();
			}
			//System.out.println("Took "+(System.currentTimeMillis()-time)+"ms");
		}
	}
	
	private void zero(){
		try {
			model.setDesiredJointSpaceVector(startVect, 2);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public static void main(String[] args) {
		new DirectControl();
	}
	public void onTaskSpaceUpdate(AbstractKinematicsNR source, TransformNR pose) {
		System.err.println("Got:"+pose);
		double ws=50;
		current = new TransformNR(	((pose.getX()+ 87)*scale)+ws ,
									((pose.getY()- 64)*scale)-ws,
									((pose.getZ()+ 91)*-1*scale),
				new RotationNR());
		System.out.println("Current = "+current);
		
	}
	public void onTargetTaskSpaceUpdate(AbstractKinematicsNR source,TransformNR pose) {}

	@Override
	public void onDigitalValueChange(DigitalInputChannel source, boolean isHigh) {
		button=isHigh;
		System.out.println("Hand is "+isHigh);
	}
}
