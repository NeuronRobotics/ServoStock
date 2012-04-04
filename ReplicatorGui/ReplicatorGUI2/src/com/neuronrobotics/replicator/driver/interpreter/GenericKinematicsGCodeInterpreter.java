package com.neuronrobotics.replicator.driver.interpreter;
import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematics;
import com.neuronrobotics.sdk.addons.kinematics.GenericKinematicsModel;
import com.neuronrobotics.sdk.addons.kinematics.math.Transform;
import com.neuronrobotics.sdk.addons.kinematics.math.Rotation;

/** 
 * A G-code interpreter for a generic AbstractKinematics object.
 * Has default implementations for G00 and G01 linear motion. Does not support rotational positions of end effector.
 */
public class GenericKinematicsGCodeInterpreter extends GCodeInterpreter {
	AbstractKinematics machine;


	/** 
	 * Build a new interpreter to drive the kinematics object <tt>m</tt> with G code.
	 * 
	 * @param m the kinematics object to drive.
	 */
	public GenericKinematicsGCodeInterpreter(AbstractKinematics m) {
		super();
		machine=m; // Okay, checked, member fields of the enclosing class do get updates visible to the inner class.
	}

	void waitForMachine(double destination[],double threshold) throws InterruptedException {
		double current[];
		int distance=100;
		while(distance > threshold) {
			distance=0;
			current=machine.getCurrentJointSpaceVector();
			for(int i=0;i<current.length;i++) {
				distance+=current[i]-destination[i]; // Taxicab metric is good enough.
			}
			Thread.currentThread().sleep(30);
		}
	}

	/** 
	 * Add the handlers to drive motion for this kinematics object.  
	 *
	 * This provides an implementation for G00 that simply sets the task
	 * space transform for the kinematics object directly and waits for the
	 * machine to be within a tolerance, and an implementation for G01 that
	 * calculates a duration for the transition based on the feedrate in F.
	 *
	 * The G01 implementation <em>does not</em> presently properly implement
	 * linear motion in systems where the kinematics are not linear, but
	 * should approximate reasonably for small motions.
	 * 
	 * Also calls the superclass implementation to include the default
	 * handlers from GCodeInterpreter.
	 *
	 */
	public void addDefaultHandlers() {
		super.addDefaultHandlers();
		// Override G00 and G01 here.
		//G0 - no handler.
		addGHandler(0, new CodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next) throws Exception {
				Transform t = new Transform(next.getWord('X'), next.getWord('Y'), next.getWord('Z'), new Rotation());
				double destination[] = machine.setDesiredTaskSpaceTransform(t,0.0);
				// Loop to wait, I guess.
				waitForMachine(destination, 0.1);
			}
		});
		//G1 - no handler.
		addGHandler(1, new CodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next) throws Exception {
				// This is basically garbage and assumes that linear motion in cartesian space maps to linear motion in joint space. Interpolation would be vastly preferred.

				Transform t = new Transform(next.getWord('X'), next.getWord('Y'), next.getWord('Z'), new Rotation());
				Transform prevt = new Transform(prev.getWord('X'), prev.getWord('Y'), prev.getWord('Z'), new Rotation());
				double secondsAtFeed = t.getOffsetVectorMagnitude(prevt) / next.getWord('F');

				double destination[] = machine.setDesiredTaskSpaceTransform(t,secondsAtFeed);
				Thread.currentThread().sleep(((long)(secondsAtFeed*1000.0))-200); //Should truncate.
				// Loop to wait, I guess.
				waitForMachine(destination, 0.1);
			}
		});
	}

	public static void main(String args[]) throws Exception {
		AbstractKinematics kin = new GenericKinematicsModel();
		GenericKinematicsGCodeInterpreter interp = new GenericKinematicsGCodeInterpreter(kin);
		interp.interpretStream(System.in);
	}
}
