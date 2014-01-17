package com.neuronrobotics.sdk.commands.cartesian;

import com.neuronrobotics.sdk.common.BowlerAbstractCommand;
import com.neuronrobotics.sdk.common.BowlerMethod;

public class CancelPrintCommand extends BowlerAbstractCommand {
	public CancelPrintCommand() {
		setOpCode("prcl");
		setMethod(BowlerMethod.POST);
	}
}
