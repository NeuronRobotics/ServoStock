package com.neuronrobotics.replicator.test.trobot;


import java.awt.BorderLayout;
import java.awt.GraphicsConfiguration;

import javax.media.j3d.BoundingSphere;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.vecmath.Point3d;

import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematicsNR;
import com.neuronrobotics.sdk.addons.kinematics.IJointSpaceUpdateListenerNR;
import com.neuronrobotics.sdk.addons.kinematics.JointLimit;
import com.neuronrobotics.sdk.addons.kinematics.TrobotKinematics;
import com.neuronrobotics.sdk.common.BowlerAbstractConnection;
import com.neuronrobotics.sdk.dyio.DyIO;
import com.neuronrobotics.sdk.ui.ConnectionDialog;
import com.sun.j3d.utils.behaviors.mouse.MouseBehavior;
import com.sun.j3d.utils.behaviors.mouse.MouseRotate;
import com.sun.j3d.utils.behaviors.mouse.MouseTranslate;
import com.sun.j3d.utils.behaviors.mouse.MouseZoom;
import com.sun.j3d.utils.geometry.ColorCube;
import com.sun.j3d.utils.pickfast.behaviors.PickRotateBehavior;
import com.sun.j3d.utils.universe.SimpleUniverse;

import com.sun.j3d.utils.applet.MainFrame; 
import com.sun.j3d.utils.universe.*;
import com.sun.j3d.utils.behaviors.mouse.*;
import com.sun.j3d.utils.behaviors.vp.OrbitBehavior;
import com.sun.j3d.utils.behaviors.vp.ViewPlatformBehavior;

import javax.media.j3d.*;
import javax.vecmath.*;

import net.miginfocom.swing.MigLayout;

import java.awt.event.*;
import java.util.ArrayList;
import java.util.Enumeration;


public class TrobotViewer  extends JPanel implements IJointSpaceUpdateListenerNR{

	/**
	 * 
	 */
	private static final long serialVersionUID = 4624867202513493512L;
	TrobotKinematics robot;
	DHViewer dh;
	
	public TrobotViewer(TrobotKinematics bot){
		robot = bot;
		
		JPanel controls = new JPanel(new MigLayout());
		
        setLayout(new BorderLayout());
        JButton resetViewButton = new JButton("Reset View");
        resetViewButton.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent arg0) {
				dh.resetView();
			}
		});
        
        controls.add(resetViewButton);
 
        dh = new DHViewer(robot.getDhChain(), robot.getCurrentJointSpaceVector());
        add("North", controls);
        add("Center", dh);
        robot.addJointSpaceListener(this);
        
	}


	@Override
	public void onJointSpaceUpdate(AbstractKinematicsNR source, double[] joints) {
		dh.updatePoseDisplay(robot.getDhChain().getChain(joints));
	}

	@Override
	public void onJointSpaceTargetUpdate(AbstractKinematicsNR source,double[] joints) {
		dh.updatePoseDisplay(robot.getDhChain().getChain(joints));
	}

	@Override
	public void onJointSpaceLimit(AbstractKinematicsNR source, int axis,JointLimit event) {
		
	}

}
