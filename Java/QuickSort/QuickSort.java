// Morgan Lloyd, mlloyd@Pengo.cabrillo.edu
// morganlloydd@gmail.com
// working/tested (compiles)

import java.util.Scanner;
import java.util.ArrayList;
import java.util.Collections;

public class p3 {
    public static void main(String args[]) {
        boolean hoare = false;
        if(args.length > 0) {
            hoare = true;
        }
        Scanner scanner = new Scanner(System.in);
        ArrayList<Integer> alist = new ArrayList<Integer>();
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            int inputInt = Integer.parseInt(input);
            alist.add(inputInt);
        }
        if (hoare == true) {
            hoareQuicksort(alist, 0, alist.size() -1);
        } else {
            lomutoQuicksort(alist, 0, alist.size() - 1);
        }
        for (int element : alist) {
            String paddedInt = String.format("%09d", element);
            System.out.println(paddedInt);
        }
    }

    // Lomuto quicksort function
    public static void lomutoQuicksort(ArrayList<Integer> A, int p, int r) {
        if (p < r) {
            int q = lomutoPartition(A, p, r);
            lomutoQuicksort(A, p, q-1);
            lomutoQuicksort(A, q+1, r);
        }
    }

    // Lomuto partitioning method
    private static int lomutoPartition(ArrayList<Integer> A, int p, int r) {
        if (A.size() > 35) {
            lomutoMedianOf3(A, p, r);
        }
        int x = A.get(r);
        int i = p - 1;
        for(int j = p; j < r; j++) {
            if(A.get(j) <= x) {
                i++;
                Collections.swap(A, i, j);
            }
        }
        Collections.swap(A, i + 1, r);
        return i + 1;
    }


    // calculates and returns the median of three values
    private static void lomutoMedianOf3(ArrayList<Integer> A, int p, int r) {
        int mid = (p + r)/2;
        if((A.get(p) <= mid && mid <= A.get(r)) || (A.get(r) <= mid && mid <= A.get(p))) {
            Collections.swap(A, mid, r);
        } else if ((mid <= A.get(p) && A.get(p) <= A.get(r)) || (A.get(r) <= A.get(p) && A.get(p) <= mid)) {
            Collections.swap(A, p, r);
        }
    }

    // hoare median of three helper function
    private static void hoareMedianOf3(ArrayList<Integer> A, int p, int r) {
        if (p >= 0 && r < A.size()) {
            int mid = (p + r)/2;
            if((A.get(p) <= mid && mid <= A.get(r)) || (A.get(r) <= mid && mid <= A.get(p))) {
                Collections.swap(A, mid, r);
            } else if ((mid <= A.get(r) && A.get(r) <= A.get(p)) || (A.get(p) <= A.get(r) && A.get(r) <= mid)) {
                Collections.swap(A, p, r);
            }
        }
    }


    // hoare quicksort method
    private static void hoareQuicksort(ArrayList<Integer> A, int p, int r) {
        if (p < r) {
            int q = hoarePartition(A, p, r);
            hoareQuicksort(A, p, q);
            hoareQuicksort(A, q + 1, r);
        }
    }

    // hoare partitioning method
    private static int hoarePartition(ArrayList<Integer> A, int p, int r) {
        if (A.size() > 25) {
            hoareMedianOf3(A, p, r);
        }
        int x = A.get(p);
        int i = p - 1;
        int j = r + 1;
        while (true) {
            do {
                i++;
            } while (A.get(i) < x);
            do {
                j--;
            } while (A.get(j) > x);
            if (i >= j) {
                return j;
            }
            Collections.swap(A, i, j);
        }
   }
}


