import com.neuronrobotics.sdk.addons.kinematics.AbstractKinematics;
import com.neuronrobotics.sdk.addons.kinematics.GenericKinematicsModel;
import com.neuronrobotics.sdk.addons.kinematics.math.Transform;
import com.neuronrobotics.sdk.addons.kinematics.math.Rotation;

public class GenericKinematicsGCodeInterpreter extends GCodeInterpreter {
	AbstractKinematics machine;


	GenericKinematicsGCodeInterpreter(AbstractKinematics m) {
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

	void addDefaultHandlers() {
		super.addDefaultHandlers();
		// Override G00 and G01 here.
		//G0 - no handler.
		addGHandler(0, new SimpleCodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next) throws Exception {
				Transform t = new Transform(next.getWord('X'), next.getWord('Y'), next.getWord('Z'), new Rotation());
				double destination[] = machine.setDesiredTaskSpaceTransform(t,0.0);
				// Loop to wait, I guess.
				waitForMachine(destination, 0.1);
			}
		});
		//G1 - no handler.
		addGHandler(1, new SimpleCodeHandler() {
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
