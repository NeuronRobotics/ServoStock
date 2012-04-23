package com.neuronrobotics.replicator.test.trobot;

import com.neuronrobotics.sdk.addons.kinematics.DHChain;
import com.neuronrobotics.sdk.addons.kinematics.DhInverseSolver;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;

public class ComputedGeometricModel  implements DhInverseSolver{
	private final DHChain dhChain;
	private final boolean debug;
	public ComputedGeometricModel(DHChain dhChain, boolean debug) {
		this.dhChain = dhChain;
		this.debug = debug;
	}
	
	public double[] inverseKinematics(TransformNR target,double[] jointSpaceVector ) {
		int linkNum = jointSpaceVector.length;
		double [] inv = new double[linkNum];
		if(!checkSphericalWrist() || dhChain.getLinks().size() != 6) {
			throw new RuntimeException("This is not a 6DOF arm with a spherical wrist, this solver will not work");
		}
		double [] assumption = new double [linkNum];
		for(int i=0;i<linkNum;i++) {
			assumption[i]=1;
		}
		
		return inv;
	}

	private boolean checkSphericalWrist() {
		int end = dhChain.getLinks().size()-1;
		return 	dhChain.getLinks().get(end).getR()	==0 && 
				dhChain.getLinks().get(end-1).getR()==0 && 
				dhChain.getLinks().get(end-2).getR()==0  ;
	}
}
