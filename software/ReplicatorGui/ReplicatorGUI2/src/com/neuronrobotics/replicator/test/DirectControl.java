package com.neuronrobotics.replicator.test;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import net.miginfocom.swing.MigLayout;

import com.neuronrobotics.replicator.driver.BowlerBoardDevice;
import com.neuronrobotics.replicator.driver.NRPrinter;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.ITaskSpaceUpdateListenerNR;
import com.neuronrobotics.sdk.addons.kinematics.DHParameterKinematics;
import com.neuronrobotics.sdk.addons.kinematics.gui.DHKinematicsViewer;
import com.neuronrobotics.sdk.addons.kinematics.gui.SampleGuiNR;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.BowlerAbstractConnection;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.dyio.DyIOChannel;
import com.neuronrobotics.sdk.dyio.peripherals.DigitalInputChannel;
import com.neuronrobotics.sdk.dyio.peripherals.IDigitalInputListener;
import com.neuronrobotics.sdk.dyio.peripherals.ServoChannel;
import com.neuronrobotics.sdk.dyio.sequencer.ServoOutputScheduleChannel;
import com.neuronrobotics.sdk.serial.SerialConnection;
import com.neuronrobotics.sdk.ui.ConnectionDialog;
import com.neuronrobotics.sdk.util.ThreadUtil;
public class DirectControl implements ITaskSpaceUpdateListenerNR, IDigitalInputListener {
	DHParameterKinematics model;
	//DeltaForgeDevice deltaRobot;
	TransformNR current = new TransformNR();
	double scale=.5;
	double [] startVect = new double [] { 0,0,0,0,0,0};
	private boolean button=false;
	private boolean lastButton=false;
	private int open = 20;
	private int closed = 100;
	
	public DirectControl() {
		DyIO.disableFWCheck();
		
		//Create the references for my known DyIOs
		DyIO master = null;
		
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
		BowlerAbstractConnection deltaConnection = null;
		//Now that all connected DyIOs are connected, search for the correct MAC addresses 
		for(DyIO d : temp){
			String addr = d.getAddress().toString();
			if(addr.equalsIgnoreCase("74:f7:26:00:00:6f")){
				d.getConnection().setSynchronusPacketTimeoutTime(2000);
				master = d;
				System.out.println("Master found! "+master);
			}else{
				d.getConnection().setSynchronusPacketTimeoutTime(2000);
				deltaConnection = d.getConnection();
				d.disconnect();
			}
		}
		//If both are not found then the system can not run
		if(master == null ){
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
		
		//master.killAllPidGroups();
		model = new DHParameterKinematics(master,"TrobotMaster.xml");
		
		
		BowlerBoardDevice delt = new BowlerBoardDevice();
		if(!ConnectionDialog.getBowlerDevice(delt)){
			System.exit(0);
		}
//		delt.setConnection(deltaConnection);		
		//delt.setConnection(new SerialConnection("/dev/ttyACM0"));
		//delt.connect();
		
		//deltaRobot = new DeltaForgeDevice(delt);
		//deltaRobot.setCurrentPoseTarget(new TransformNR());
		
		DigitalInputChannel di = new DigitalInputChannel(master.getChannel(0));
		di.addDigitalInputListener(this);
		button=di.isHigh();
		lastButton = button;
		
//		ServoChannel hand = new ServoChannel(slave.getChannel(15));
//		hand.SetPosition(open);

		try{
			final SampleGuiNR gui = new SampleGuiNR();
			final JFrame frame = new JFrame();
			final JTabbedPane tabs = new JTabbedPane();
			JPanel starter = new JPanel(new MigLayout());
			gui.setKinematicsModel(model);
			try{
				//tabs.add("Display",new DHKinematicsViewer(model));
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
		model.addPoseUpdateListener(this);
		Log.enableWarningPrint();
		int loopTime=50;
		master.getConnection().setSynchronusPacketTimeoutTime(2000);
		delt.getConnection().setSynchronusPacketTimeoutTime(2000);
		int x=0,y=0,z=0;
		Log.enableDebugPrint();
		for (DyIOChannel c: master.getChannels()){
			c.setAsync(false);
		}
		while ( true) {
			long time = System.currentTimeMillis();
			try {				
				master.getAllChannelValues();
				//printer.setDesiredTaskSpaceTransform(current,.1);
//				if((int)current.getX() != x && (int)current.getY() != y && (int)current.getZ() != z ){
//					x=(int)current.getX();
//					y=(int)current.getY();
//					z=(int)current.getZ();
					if(current.getZ()<400&&current.getZ()>-10){
						delt.sendLinearSection(current, 0, 0,true);
						//System.out.println("Setting x="+current.getX()+" y="+current.getY()+" z="+current.getZ());
					}
				//}
				ThreadUtil.wait(0,1);
				
			} catch (Exception e) {
				e.printStackTrace();
			}
			//System.out.println("Took "+(System.currentTimeMillis()-time)+"ms");
		}
		//throw new RuntimeException("Main exited!");
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
		//System.err.println("Got:"+pose);
		double ws=50;
		current = new TransformNR(	((pose.getX())*scale/2),
									((pose.getY())*scale/2),
									((pose.getZ() +165)*scale),
				new RotationNR());
		//System.out.println("Current = "+current);
	}
	public void onTargetTaskSpaceUpdate(AbstractKinematicsNR source,TransformNR pose) {}

	@Override
	public void onDigitalValueChange(DigitalInputChannel source, boolean isHigh) {
		button=isHigh;
		System.out.println("Hand is "+isHigh);
	}
}
