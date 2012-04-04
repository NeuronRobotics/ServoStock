
public interface CodeHandler {
	void execute(GCodeLineData prev, GCodeLineData line) throws Exception;
}

