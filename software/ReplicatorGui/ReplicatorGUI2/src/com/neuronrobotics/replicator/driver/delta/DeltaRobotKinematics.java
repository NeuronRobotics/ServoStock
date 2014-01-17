package com.neuronrobotics.replicator.driver.delta;

import com.neuronrobotics.sdk.addons.kinematics.math.RotationNR;
import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;

public class DeltaRobotKinematics {
	//Sample code from http://forums.trossenrobotics.com/tutorials/introduction-129/delta-robot-kinematics-3276/
	 // robot geometry
	 // (look at pics above for explanation)
	DeltaRobotConfig configuration;
	 /**
	  * All units in milimeters
	  * @param e
	  * @param f
	  * @param re
	  * @param rf
	  */
	 public DeltaRobotKinematics(DeltaRobotConfig config){
		 configuration=new DeltaRobotConfig(config);
	 }
	 
	 
	 // trigonometric private ants
	 private  double sqrt3 = Math.sqrt(3.0);
	 private  double pi = Math.PI;    // PI
	 private  double sin120 = sqrt3/2.0;   
	 private  double cos120 = -0.5;        
	 private  double tan60 = sqrt3;
	 private  double sin30 = 0.5;
	 private  double tan30 = 1/sqrt3;
	 
	 // forward kinematics: (theta1, theta2, theta3) -> (x0, y0, z0)
	 // returned status:  CartesianCoordinante=OK, null=non-existing position
	 public TransformNR delta_calcForward(double [] input) {
		 double x0, y0, z0;
		 for(int i=0;i<3;i++){
			 if(input[i]>=85)
				 throw new RuntimeException("Angle hit toggle point: "+input[i] );
		 }
		 double theta1 = Math.toRadians(input[0]);
		 double theta2 = Math.toRadians(input[1]);
		 double theta3 = Math.toRadians(input[2]);
	     double t = (getF()-getE())*tan30/2;
	 
	     double y1 = -(t + getRf()*Math.cos(theta1));
	     double z1 = -getRf()*Math.sin(theta1);
	 
	     double y2 = (t + getRf()*Math.cos(theta2))*sin30;
	     double x2 = y2*tan60;
	     double z2 = -getRf()*Math.sin(theta2);
	 
	     double y3 = (t + getRf()*Math.cos(theta3))*sin30;
	     double x3 = -y3*tan60;
	     double z3 = -getRf()*Math.sin(theta3);
	 
	     double dnm = (y2-y1)*x3-(y3-y1)*x2;
	 
	     double w1 = y1*y1 + z1*z1;
	     double w2 = x2*x2 + y2*y2 + z2*z2;
	     double w3 = x3*x3 + y3*y3 + z3*z3;
	     
	     // x = (a1*z + b1)/dnm
	     double a1 = (z2-z1)*(y3-y1)-(z3-z1)*(y2-y1);
	     double b1 = -((w2-w1)*(y3-y1)-(w3-w1)*(y2-y1))/2.0;
	 
	     // y = (a2*z + b2)/dnm;
	     double a2 = -(z2-z1)*x3+(z3-z1)*x2;
	     double b2 = ((w2-w1)*x3 - (w3-w1)*x2)/2.0;
	 
	     // a*z^2 + b*z + c = 0
	     double a = a1*a1 + a2*a2 + dnm*dnm;
	     double b = 2*(a1*b1 + a2*(b2-y1*dnm) - z1*dnm*dnm);
	     double c = (b2-y1*dnm)*(b2-y1*dnm) + b1*b1 + dnm*dnm*(z1*z1 - getRe()*getRe());
	  
	     // discriminant
	     double d = b*b - (double)4.0*a*c;
	     if (d < 0) return null; // non-existing point
	 
	     z0 = -(double)0.5*(b+Math.sqrt(d))/a;
	     x0 = (a1*z0 + b1)/dnm;
	     y0 = (a2*z0 + b2)/dnm;
	     return new TransformNR(x0, y0, z0, new RotationNR());
	 }
	 
	 // inverse kinematics
	 // helper functions, calculates angle theta1 (for YZ-pane)
	 private double delta_calcAngleYZ(double x0, double y0, double z0 ) {
		 double theta;
//		 if(z0<=0)
//			 throw new RuntimeException("Z values must be greater then zero");
	     double y1 = -0.5 * 0.57735 * getF(); // f/2 * tg 30
	     y0 -= 0.5 * 0.57735    * getE();    // shift center to edge
	     // z = a + b*y
	     double a = (x0*x0 + y0*y0 + z0*z0 +getRf()*getRf() - getRe()*getRe() - y1*y1)/(2*z0);
	     double b = (y1-y0)/z0;
	     // discriminant
	     double d = -(a+b*y1)*(a+b*y1)+getRf()*(b*b*getRf()+getRf()); 
	     if (d < 0)
	    	 throw new RuntimeException("Out Of Workspace! Inverse kinematics failed, D < 0"); // non-existing point
	     double yj = (y1 - a*b - Math.sqrt(d))/(b*b + 1); // chooMath.sing outer point
	     double zj = a + b*yj;
	     theta = Math.atan(-zj/(y1 - yj)) + ((yj>y1)?180.0:0.0);
	     return theta;
	 }
	 
	 // inverse kinematics: (x0, y0, z0) -> (theta1, theta2, theta3)
	 // returned status: 0=OK, -1=non-existing position
	 public double [] delta_calcInverse(TransformNR input ) {
		 double theta1, theta2,  theta3;
		 double x0 = input.getX();
		 double y0 = input.getY();
		 double z0 = input.getZ();
		 if(z0==0) {
			 z0=.0001;
		 }
	     theta1 = theta2 = theta3 = 0;
	     theta1 = delta_calcAngleYZ(x0, y0, z0);
	     theta2 = delta_calcAngleYZ(x0*cos120 + y0*sin120, y0*cos120-x0*sin120, z0);  // rotate coords to +120 deg
	     theta3 = delta_calcAngleYZ(x0*cos120 - y0*sin120, y0*cos120+x0*sin120, z0);  // rotate coords to -120 deg
	     return new double[] {Math.toDegrees(theta1),Math.toDegrees(theta2),Math.toDegrees(theta3)};
	 }

	public double getE() {
		return configuration.getE();
	}

	public double getF() {
		return configuration.getF();
	}

	public double getRe() {
		return configuration.getRe();
	}

	public double getRf() {
		return configuration.getRf();
	}
}
