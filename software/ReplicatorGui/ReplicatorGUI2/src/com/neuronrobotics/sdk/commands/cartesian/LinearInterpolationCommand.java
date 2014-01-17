package com.neuronrobotics.sdk.commands.cartesian;

import com.neuronrobotics.sdk.addons.kinematics.math.TransformNR;
import com.neuronrobotics.sdk.common.BowlerAbstractCommand;
import com.neuronrobotics.sdk.common.BowlerMethod;

public class LinearInterpolationCommand extends BowlerAbstractCommand {

	public LinearInterpolationCommand(TransformNR taskSpaceTransform, double mmOfFiliment, int ms) {
		setOpCode("_sli");
		setMethod(BowlerMethod.POST);
		getCallingDataStorage().addAs32(ms);
		
		getCallingDataStorage().addAs32((int) (taskSpaceTransform.getX()*1000));
		getCallingDataStorage().addAs32((int) (taskSpaceTransform.getY()*1000));
		getCallingDataStorage().addAs32((int) (taskSpaceTransform.getZ()*1000));
		
		getCallingDataStorage().addAs32((int) (mmOfFiliment*1000));


	}
}
