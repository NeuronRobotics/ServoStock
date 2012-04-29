package com.neuronrobotics.replicator.test;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

import net.miginfocom.swing.MigLayout;

import com.neuronrobotics.replicator.driver.DeltaRobotPrinterPrototype;
import com.neuronrobotics.replicator.test.trobot.TrobotViewer;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.ITaskSpaceUpdateListenerNR;
import com.neuronrobotics.sdk.addons.kinematics.TrobotKinematics;
import com.neuronrobotics.sdk.addons.kinematics.gui.SampleGuiNR;
import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.Log;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.serial.SerialConnection;
public class DirectControl implements ITaskSpaceUpdateListenerNR {
	TrobotKinematics model;
	DeltaRobotPrinterPrototype deltaRobot;
	TransformNR current = new TransformNR();
	double scale=.75;
	double [] startVect = new double [] { 0,0,0,0,0,0};
	public DirectControl() {
		DyIO.disableFWCheck();
		DyIO master = new DyIO(new SerialConnection("/dev/DyIO1"));
		if(!master.connect()){
			throw new RuntimeException("Not a bowler Device on connection: ");
		}
		master.killAllPidGroups();
		model = new TrobotKinematics(master,"TrobotMaster.xml");
		model.addPoseUpdateListener(this);
		DyIO delt = new DyIO(new SerialConnection("/dev/DyIO0"));
		delt.connect();
		delt.enableBrownOutDetect(false);
		deltaRobot = new DeltaRobotPrinterPrototype(delt);
		Log.enableDebugPrint(false);
		deltaRobot.setCurrentPoseTarget(new TransformNR());
		
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
				tabs.add("Display [ERROR]",error);
				ex.printStackTrace();
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
		
		while (delt.isAvailable() && master.isAvailable()) {
			long time = System.currentTimeMillis();
			try {
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
		current = new TransformNR(pose.getX()*scale,pose.getY()*scale,-pose.getZ()*scale,new RotationNR());
		//System.out.println("Current = "+pose);
	}
	public void onTargetTaskSpaceUpdate(AbstractKinematicsNR source,TransformNR pose) {}
}
