// Generates data files for testing 

import java.lang.*;
import java.util.*;
import java.io.*;

public class dataGenerator {
    public static void main(String args[]) {
	int numData = 0;
	Random rand = new Random();
	Scanner scanner = new Scanner(System.in);
	System.out.println("How many pieces of data do you want in your file? :)");
	if(scanner.hasNextInt()) {
	    numData = scanner.nextInt();
	}
	String fileName = "d_" + numData + ".txt";
	try {
	PrintWriter out = new PrintWriter(new File(fileName));
	for(int i = 0; i <= numData; i++) {
		i = rand.nextInt(i);
	    out.println(i);
	}
	out.close();
	}catch(FileNotFoundException e) {
	    System.exit(-1);
	}
    }
}
