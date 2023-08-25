
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class tailTest {
    private LinkNode head;
    private LinkNode tail;

    private class LinkNode {
        String data;
        LinkNode next;
        LinkNode prev;

        public LinkNode(String newData) {
            this.data = newData;
        }

    }

    public tailTest() {
        head = null;
        tail = null;
    }
    //returns size of linked list
    public int getSize() {
        int count = 0;
        if (head == null) {
            return count;
        }
        LinkNode temp = head;
        while (temp != null) {
            temp = temp.next;
            count++;
        }
        return count;
    }

    // inserts link node at front of list 
    public void push(String newData) {
        LinkNode temp = new LinkNode(newData);
        if (isEmpty()) {
            tail = temp;
        } else {
            head.prev = temp;
        }
        temp.next = head;
        head = temp;
    }

    // inserts link node at end of list 
    public void pushBack(String newData){
        LinkNode temp = new LinkNode(newData);
        if (isEmpty()) {
            head = temp;
        } else {
            tail.next = temp;
            temp.prev = tail;
        }
        tail = temp;
    }

    //deletes (& returns data) first node
    public String pop() {
        if (this.getSize() == 0) { 
            return null; 
        } 
        LinkNode temp = head;
        if (head == tail) {
            tail = null;
        } else {
            head.next.prev = null;
        }
        head = head.next;
        temp.next = null;
        return temp.data;
    }

    //deletes (& returns data) last node 
    public String popBack() {
        if (this.getSize() == 0) { 
            return null; 
        }
        LinkNode temp = tail;
        if (head == tail) {
            head = null;
        } else {
            tail.prev.next = null;
        }
        tail = tail.prev;
        tail.prev = null;
        return temp.data;
    }

    // prints linked list beginning to end 
    public void printList() {
        LinkNode temp = head;
        while (temp != null) {
            System.out.println(temp.data);
            temp = temp.next;
        }
    }

    // check if list is empty
    public boolean isEmpty() {
        return (head == null);
    }

    // main
    public static void main(String args[]) {
        tailTest list = new tailTest();
        String fileName, frontInput, endInput;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please enter the name of the file to read: ");
        fileName = scanner.nextLine();
        System.out.println("Please enter a String to add to front of list: ");
        frontInput = scanner.nextLine();
        System.out.println("Please enter a String to add to end of list: ");
        endInput = scanner.nextLine();
        BufferedReader reader;
        try {
            reader = new BufferedReader(new FileReader(fileName));
            String line = reader.readLine();
            while (line != null) {
                list.push(line);
                line = reader.readLine();
            }
            reader.close();
        }
        catch (FileNotFoundException e) {
            System.err.println(fileName + ": Not found, please try again!");
            System.exit(-1);
        }

        catch(IOException e) {
            System.err.println(fileName + ": Error reading input from file!");
            System.exit(-1);
        }

        System.out.println("***Testing Doubly Linked List***");
        if ((frontInput != null) && (endInput != null)) {
        list.push(frontInput);
        list.pushBack(endInput);
        }
        list.popBack();
        list.printList();
    }
}
