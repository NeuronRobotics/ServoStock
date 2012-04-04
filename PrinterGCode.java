

class PrinterGCodeInterpreter {
	GCodeInterpreter interp;
	DeltaRobotPrinterPrototype controller;

	char motionAxes[] = {'X','Y','Z'};

	PrinterGCodeInterpreter(PrinterDevice d) {
		controller=d;
		interp.addGHandler(00,new CodeHandler() {
			void execute(GCodeLineData prev, GCodeLineData line) {
				// Handle G00 commands - just set the destination.
				Transform destination = new Transform(getWords(motionAxes), 
			}
		});
		interp.addGHandler(01,new CodeHandler() {
			void execute(GCodeLineData prev, GCodeLineData line) {
				// Handle G01 commands - interpolation stuff.
				double feed = getWord('F');
			}
		});
		interp.addGHandler(92,new CodeHandler() {
			void execute(GCodeLineData prev, GCodeLineData line) {
				// Set the zero point.
			}
		});
		CodeHandler setTemp=new CodeHandler() {
			void execute(GCodeLineData prev, GCodeLineData line) {
				d.setTemperature();
			}
		};
		interp.addMHandler(104,setTemp); // Hack. This shouldn't wait.
		interp.addMHandler(109,setTemp); // Hack. This should wait.
		
	}
}
