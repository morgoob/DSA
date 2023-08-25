// Morgan Lloyd, mlloyd@Pengo.cabrillo.edu
// morganlloydd@gmail.com
// working, tested

import java.util.Scanner;

public class p2 {
    public static void main(String args[]) {
        Scanner scanner = new Scanner(System.in);
        int heapCapacity = 2400000;
        intMinHeap minHeap = new intMinHeap(heapCapacity);
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            try {
                int inputInt = Integer.parseInt(input);
            if (inputInt > 0) {
                // insert int into heap
                if(minHeap.heapinsert(inputInt)) {
                    System.out.println("insert: " + inputInt);
                }
            } else if (inputInt == 0) {
                // print heap size and heap contents on single line
                String outputHeap = minHeap.toString();
                System.out.println(outputHeap);
            } else if (inputInt == -1) {
                // extract min and print
                int extractedMin = minHeap.extractMin();
                System.out.println("extract min: " + extractedMin);
            } else if (inputInt == -2) {
                // comma separated list sorted array
                int[] sortedArray = minHeap.heapsort();
                System.out.print("sorted array: [");
                for(int i = 0; i < sortedArray.length; i++) {
                    System.out.print(sortedArray[i]);
                    if(i < sortedArray.length - 1) {
                        System.out.print(", ");
                    }
                }
                System.out.print("]");
            }
            } catch (NumberFormatException e) {
                System.out.println("Error: invalid input, please try again");
            }
        }
    }
}
