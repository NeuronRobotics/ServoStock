import java.util.Arrays;

public class GCodeLineData {
	double lineValues[];

	GCodeLineData(){
		lineValues=new double[26];
	}
	GCodeLineData(GCodeLineData toCopy) {
		lineValues=Arrays.copyOf(toCopy.lineValues,26);
	}

	void storeWord(char c, double val) {
		int i=Character.toUpperCase(c)-'A';
		lineValues[i]=val;
	}
	
	double getWord(char c) {
		return lineValues[c-'A'];
	}
	
	double[] getWords(char words[]) {
		double[] d=new double[words.length];
		for(int i=0; i<words.length; i++) {
			d[i]=lineValues[words[i]-'A'];
		}
		return d;
	}
}
