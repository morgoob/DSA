// min heap class
import java.io.Serializable;

class intMinHeap implements Serializable {
    // member variables
    private int A[];
    private int capacity;
    private int size; // current size of data in array

    // constructor for min heap
    public intMinHeap(int cap) {
        A = new int[cap];
        capacity = cap;
        size = 0;
    }


    public int[] heapsort() {
        int copy[] = new int[size];
        int n = size;
        for(int i = 0; i < size; i++) {
            copy[i] = A[i];
        }
        for (int i = size - 1; i > 0; i--) {
            swap(0,i);
            size--;
            heapify(0);
        }
        size = n;
        int sorted[] = new int[size];
        for(int i = 0; i < size; i++) {
            sorted[i] = A[i];
            A[i] = copy[i];
        }
        return sorted;
    }

    // return a string with the heap values as a comma
    // separated list & include heap size
    public String toString() {
        String returnStr = "heap size " + size + ": " + A[0];
        for (int i = 1; i < size; i++) {
            returnStr += ", " + A[i];
        }
        return returnStr;
    }

    // add item to heap
    public boolean heapinsert(int n) {
        if (isFull()) {
            return false;
        }
        size++;
        A[size - 1] = n + 1;
        decreaseKey(size - 1, n);
        return true;
    }

    // returns minimum value in heap or 0 if empty
    public int minimum() {
        if (isEmpty()) {
            return 0;
        } else {
            return A[0];
        }
    }

    // extracts and returns minimum value (0 if empty)
    public int extractMin() {
        int min = 0;
        if (!isEmpty()) {
            min = minimum();
            A[0] = A[size - 1];
            size--;
            heapify(0);
        }
        return min;
    }

    // helper function, decreases key
    public void decreaseKey(int i, int k) {
        // i = index, k = key
        if((i >= 0) && (i < size)) {
            if(k >= A[i]) {
                return;
            }
            A[i] = k;
            while((i > 0) && (A[parent(i)] > A[i])) {
                swap(i, parent(i));
                i = parent(i);
            }
        }
    }

    public boolean isEmpty() {
        return size == 0;
    }

    // returns true if heap is full
    public boolean isFull() {
        return size == capacity;
    }

    // builds heap
    private void buildheap() {
        for(int i = (size/2); i > 0; i--) {
            heapify(i);
        }
    }

    // calculates min of three values; i is always valid
    private int minOf3(int i, int j, int k) {
        int min = i;
        if((j < size) && (A[j] < A[min])) {
            min = j;
        }
        if ((k < size) && (A[k] < A[min])) {
            min = k;
        }
        return min;
    }

    // calculates and returns index of left child
    private int left(int i) {
        return 2*i + 1;
    }

    // calculates and returns index of right child
    private int right(int i) {
        return 2*i + 2;
    }

    // calculates and returns index of parent
    private int parent(int i) {
        return (i-1)/2;
    }


    // heapify helper; swaps two values in heap
    private void swap(int index1, int index2) {
        int temp = A[index1];
        A[index1] = A[index2];
        A[index2] = temp;
    }

    // maintains heap property at position i
    private void heapify(int i) {
        int n = minOf3(i, left(i), right(i));
        if (i != n) {
            swap(i,n);
            heapify(n);
        }
    }
}






