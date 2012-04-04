import java.util.ArrayList;
import java.util.Scanner;
import java.util.List;
import java.util.Arrays;
import java.util.Comparator;
import java.io.InputStream;

public class GCodeInterpreter {

	double line_values[]=new double[26];
	ArrayList<Integer> mcodes=new ArrayList<Integer>();
	ArrayList<Integer> gcodes=new ArrayList<Integer>(); // Keep this is an order that works properly. Code implementations are allowed to modify the line.

	List<CodeHandler> gHandlers[];
	List<Integer> gClearOnSet[];
	List<Integer> gOneShot;
	List<CodeHandler> mHandlers[];

	Comparator<Integer> gCodeOrdering;

	char motion_axes[]={'X','Y','Z'};
	
	long nextFlushTime = 0;
	
	GCodeLineData lastLine;
	GCodeLineData nextLine;
	
	GCodeInterpreter() {
		gHandlers=(List<CodeHandler>[]) new ArrayList<?>[310];
		mHandlers=(List<CodeHandler>[]) new ArrayList<?>[310];
		gClearOnSet=(List<Integer>[]) new List<?>[310]; // Maybe not the best storage mechanism. Good in C...
		List<Integer>[] exclGroups=(List<Integer>[]) new List<?>[] {
			Arrays.asList(0,1,4,28), // All of these might need to change to be mutable later.
			Arrays.asList(20,21), 
			Arrays.asList(90,91)};
		for(List<Integer> group : exclGroups) {
			for(int code : group) {
				gClearOnSet[code]=group;
			}
		}
		gClearOnSet[91]=Arrays.asList(90,91,92); // Incremental and setting positions makes no sense.
		gOneShot = Arrays.asList(28, 92);
		nextLine=new GCodeLineData();
		lastLine=new GCodeLineData();

		addDefaultHandlers();
	}
	
	void parseWord(Scanner s) throws Exception {
		s.useDelimiter("[ \t]+(\\(.*\\))?[ \t]*|(?=\n)|(?<=\n)|\\(.*\\)");
		String word=s.next();
//		System.out.println("Token: "+word);
		char c=word.charAt(0);
		switch(Character.toUpperCase(c)) {
			case 'M':
				mcodes.add(Integer.parseInt(word.substring(1)));
				break;
			case 'G':
				int code=Integer.parseInt(word.substring(1));
				if(gClearOnSet[code]!=null)gcodes.removeAll(gClearOnSet[code]);
				gcodes.add(code);
				break;
			case '\n':
				executeLine();
				break;
			default:
				nextLine.storeWord(c,Double.parseDouble(word.substring(1)));
		}
	}

	void executeLine() throws Exception {
		for(int m : mcodes)
			if(mHandlers[m]!=null) {
				for(CodeHandler handler: mHandlers[m]) {
					handler.execute(lastLine, nextLine);
				}
			} else {
				System.out.println("No implementation found for M"+m);
			}
		for(int g : gcodes)
			if(gHandlers[g]!=null) {
				for(CodeHandler handler: gHandlers[g]) {
					handler.execute(lastLine, nextLine);
				}
			} else {
				System.out.println("No implementation found for G"+g);
			}
		lastLine=nextLine;
		nextLine=new GCodeLineData(lastLine);
		gcodes.removeAll(gOneShot);
		mcodes.clear();
	}

	void interpretStream(InputStream in) throws Exception {
		Scanner s=new Scanner(in);
		while(s.hasNext()) {
			parseWord(s);
		}
	}

	void addGHandler(int code, CodeHandler handler) { // Should really do boundschecking. New code happens before old.
		if(gHandlers[code]==null) gHandlers[code]=new ArrayList<CodeHandler>();
		gHandlers[code].add(handler);
	}
	void setGHandler(int code, CodeHandler handler) { // For overriding all default behavior of a code.
		gHandlers[code]=new ArrayList<CodeHandler>();
		gHandlers[code].add(handler);
	}

	void addGSorting(final Comparator c) {
		// ...perhaps I've had too much haskell to write java-style code easily. I do believe this is a combinator.
		final Comparator oldComparator=gCodeOrdering; // Make a constant reference to the old one, for the inner class.
		gCodeOrdering = new Comparator() {
			public int compare(Object o1, Object o2) {
				int r1=c.compare(o1,o2);
				if(r1==0) return oldComparator.compare(o1, o2);
				return r1;
			}
			public boolean equals(Object o1, Object o2) {
				return this.compare(o1,o2)==0;
			}
		};
	}

	void setGSorting(Comparator c) {
		gCodeOrdering=c;
	}

	void addDefaultHandlers() {
		final double curOffset[] = new double[26]; // Yes, we'll let them offset on any axis they feel like.
		//G0 - no handler.
		addGHandler(0, new SimpleCodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next) {
				System.out.println("Rapid move to "+next.getWord('X')+", "+next.getWord('Y')+", "+next.getWord('Z'));
			}
		});
		//G1 - no handler.
		addGHandler(1, new SimpleCodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next) {
				if(next.getWord('F')==0.0) System.out.println("Zero feedrate; action will never complete.");
				System.out.println("Feed move to "+next.getWord('X')+", "+next.getWord('Y')+", "+next.getWord('Z')+" at feed "+next.getWord('F'));
			}
		});
		//G21 - program in mm - present but nullary.
		addGHandler(21,new SimpleCodeHandler());
		//G22 - program in in - convert to mm. Only on xyz for now.
		addGHandler(22,new SimpleCodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next ) {
				char axes[]={'X','Y','Z'};
				for(char c : axes) {
					next.storeWord(c,next.getWord(c)*25.4);
				}
			}
		});
		//G90 - absolute positioning - default, so empty.
		addGHandler(90,new SimpleCodeHandler());
		//G91 - relative positioning - convert to absolute. Only do this for xyz by default.
		addGHandler(91,new SimpleCodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next ) {
				char axes[]={'X','Y','Z'};
				for(char c : axes) {
					next.storeWord(c,next.getWord(c)+prev.getWord(c));
				}
			}
		});
		//G92 - set position ( reprap usage ) - messy. This probably goes in the printer class.
		addGHandler(92,new SimpleCodeHandler() {
			public void execute(GCodeLineData prev, GCodeLineData next ) {
				System.out.println("G92 is not complete");
				char axes[]={'X','Y','Z'};
				for(char c : axes) {
					next.storeWord(c,next.getWord(c)+curOffset[c-'A']);
				}
			// And copy the last line to the current line, because we don't want to change actual positions.
			}
		});
		// GROUPS:
		// 21,22 , 90,91, 0-5
		setGSorting(new Comparator<Integer>() {
			public int compare(Integer o1, Integer o2) {
				int a=o1.intValue();
				int b=o2.intValue();
				if(a>=21&&a<=22) {
					return -1; // Unit conversions default to first.
				} else if(a>=90 && a<=91) {
					if(b>=21 && b<=22) return 1;
					if(b>=0 && b<6) return -1;
				} else if(a>=0 && a<6) {
					return 1; // Movements are last.
				}
				return 0;
			}
		});
	}

	public static void main(String args[]) throws Exception {
		GCodeInterpreter interp = new GCodeInterpreter();
		interp.interpretStream(System.in);
	}
}

