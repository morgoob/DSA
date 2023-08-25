// Morgan Lloyd, mlloyd@Pengo.cabrillo.edu
// morganlloydd@gmail.com
// working/tested (compiles)
import java.util.ArrayList;
import java.lang.Math;
import java.util.Scanner;
public class p4 {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        ArrayList<Integer> alist = new ArrayList<Integer>();
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            int inputInt = Integer.parseInt(input);
            alist.add(inputInt);
            }

        bucketsort(alist);
         for (int element : alist) {
             String paddedInt = String.format("%09d", element);
             System.out.println(paddedInt);
         }
    }

    private static void bucketsort(ArrayList<Integer> A) {
        int numDigits = 2, numBuckets = 10;
        ArrayList <ArrayList<Integer>> buckets = setUpBuckets();
        for (int d = 1; d <= numDigits; d++) {
            for (int i = 0; i < A.size(); i++) {
                int dig = extractDig(A.get(i), d);
                buckets.get(dig).add(A.get(i));
            }
            clean(A);
            for(int i = 0; i < numBuckets; i++){
                for (int j = 0; j < buckets.get(i).size(); j++) {
                    A.add(buckets.get(i).get(j));
                }
                clean(buckets.get(i));
            }
        }
    }

    private static void clean(ArrayList<Integer> A) {
        A.clear();
    }

    private static int extractDig(int n, int pow) {
        double divider = Math.pow(10, pow);
        return (int) (n / divider) % 10;
    }
    private static ArrayList<ArrayList<Integer>> setUpBuckets() {
        int numBuckets = 256;
        ArrayList<ArrayList<Integer>> createBuckets = new ArrayList<ArrayList<Integer>>();
        for (int i =0; i <= numBuckets; i++) {
            ArrayList<Integer> A = new ArrayList<Integer>();
            createBuckets.add(A);
        }
        return createBuckets;
    }
}
