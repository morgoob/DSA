
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

// LinkedList only contains main and calls queue 
public class LinkedList {
    private LinkNode head;
    private LinkNode tail;

    private class LinkNode {
        String data;
        LinkNode next;
        LinkNode prev;

        // Node constructor
        public LinkNode(String newData) {
            this.data = newData;
        }
    }

    // Linked list constructor 
    public LinkedList() {
        head = null;
        tail = null;
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
            temp = temp.next;
        }
    }

    // check if list is empty
    public boolean isEmpty() {
        return (head == null);
    }
}
