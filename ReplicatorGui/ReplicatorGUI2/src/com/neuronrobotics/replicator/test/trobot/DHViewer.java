package com.neuronrobotics.replicator.test.trobot;

import java.awt.GraphicsConfiguration;
import java.util.ArrayList;

import javax.media.j3d.BoundingSphere;
import javax.media.j3d.BranchGroup;
import javax.media.j3d.Canvas3D;
import javax.media.j3d.Transform3D;
import javax.media.j3d.TransformGroup;
import javax.swing.JPanel;
import javax.vecmath.Point3d;
import javax.vecmath.Vector3d;

import com.neuronrobotics.sdk.addons.kinematics.DHChain;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.sun.j3d.utils.behaviors.mouse.MouseBehavior;
import com.sun.j3d.utils.behaviors.mouse.MouseRotate;
import com.sun.j3d.utils.behaviors.mouse.MouseTranslate;
import com.sun.j3d.utils.behaviors.mouse.MouseWheelZoom;
import com.sun.j3d.utils.universe.SimpleUniverse;


public class DHViewer extends Canvas3D {
	SimpleUniverse simpleU ;
	TransformGroup base;
	private Transform3D baseLocation = null;
	private ArrayList<TransformGroup> links = new ArrayList<TransformGroup>();
    /**
	 * 
	 */
	private static final long serialVersionUID = -7066991305201979906L;
	
	public DHViewer (DHChain tk,double[] jointSpaceVector){
		super( SimpleUniverse.getPreferredConfiguration());
		
		simpleU = new SimpleUniverse(this);
        BranchGroup scene = createSceneGraph(simpleU, tk,jointSpaceVector);

        // SimpleUniverse is a Convenience Utility class
       

	// This will move the ViewPlatform back a bit so the
	// objects in the scene can be viewed.

        simpleU.addBranchGraph(scene);
        resetView();
	}

	public BranchGroup createSceneGraph(SimpleUniverse su,DHChain tk,double[] jointSpaceVector ) {
		//System.out.println("Current pose = "+tk.forwardKinematics(new  double [] {0,0,0,0,0,0}));
		//System.out.println("Current pose = "+tk.forwardKinematics(new  double [] {0,90,0,0,0,0}));
		
    	// Create the root of the branch graph
    	BranchGroup rootBranchGroup = new BranchGroup();
    	
    	base = TransformFactory.getLabledAxis(new TransformNR(), "Base");
    	//links.add(base);
    	base.setTransform(getBaseLocation());
    	rootBranchGroup.addChild(base); 
    	
    	int i=0;
    	ArrayList<TransformNR> chain = tk.getChain(jointSpaceVector);
    	for(TransformNR t:chain){
    		TransformGroup tmp = TransformFactory.getLabledAxis(t, "Link #"+i++);
    		links.add(tmp);
    		base.addChild(tmp);
    	}
    	
        BoundingSphere mouseBounds = null;

        TransformGroup  vpTrans = su.getViewingPlatform().getViewPlatformTransform();
        //vpTrans = base; 

        rootBranchGroup.addChild(new Axis());

        mouseBounds = new BoundingSphere(new Point3d(), 100.0);

        MouseRotate myMouseRotate = new MouseRotate();
        myMouseRotate.setTransformGroup(base);
        myMouseRotate.setSchedulingBounds(mouseBounds);
        //rootBranchGroup.addChild(myMouseRotate);
        //base.addChild(myMouseRotate);

        MouseTranslate myMouseTranslate = new MouseTranslate(MouseBehavior.INVERT_INPUT);
        myMouseTranslate.setTransformGroup(vpTrans);
        myMouseTranslate.setSchedulingBounds(mouseBounds);
        rootBranchGroup.addChild(myMouseTranslate);
        //base.addChild(myMouseTranslate);

        MouseWheelZoom myMouseZoom = new MouseWheelZoom(MouseBehavior.INVERT_INPUT);
        myMouseZoom.setTransformGroup(vpTrans);
        myMouseZoom.setSchedulingBounds(mouseBounds);
        rootBranchGroup.addChild(myMouseZoom);
        //base.addChild(myMouseZoom);
    	// Let Java 3D perform optimizations on this scene graph.
    	rootBranchGroup.compile();

    	return rootBranchGroup;
	} // end of CreateSceneGraph method of HelloJava3Db
	
	public void resetView(){
		//System.out.println("Resetting view");
        TransformGroup viewTransform = simpleU.getViewingPlatform().getViewPlatformTransform();
        
        Transform3D t3d = new Transform3D();        
        t3d.lookAt(new Point3d(20,20,20), new Point3d(0,5,-3), new Vector3d(0,1,0));
        t3d.invert();
        
        viewTransform.setTransform(t3d);
        base.setTransform(getBaseLocation());
	}
	
	public void updatePoseDisplay(ArrayList<TransformNR> current) {
		//System.out.println("Updating Display");
		//ArrayList<Transform> current = robot.getDhChain().getChain(robot.getCurrentJointSpaceVector());
		for(int i=0;i<links.size();i++){
    		links.get(i).setTransform(TransformFactory.getTransform(current.get(i)));
    	}
	}
	public Transform3D getBaseLocation() {
		if(baseLocation == null) {
			baseLocation = new Transform3D();
			Transform3D x = new Transform3D();
			x.rotX(Math.toRadians(-90));
			Transform3D z = new Transform3D();
			z.rotZ(Math.toRadians(180));
			baseLocation.mul(x);
			baseLocation.mul(z);
		}
		return baseLocation;
	}

}
