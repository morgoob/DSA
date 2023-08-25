// hashTable class for p5.java
// Morgan Lloyd
// morganlloydd@gmail.com
// Assignment 5, Hash Table
// working/tested

import java.lang.Math;
import java.util.ArrayList;

public class hashTable{
    ArrayList<ArrayList<hashNode>> hashTable = new ArrayList<ArrayList<hashNode>>();
    // m = capacity
    int m;
    int size;

    private class hashNode {
        int id;
        String data;

        private hashNode(int newID, String newData) {
            this.id = newID;
            this.data = newData;
        }
    }

    public hashTable(){
        this.size = 0;
        this.m = 100;
        genHash();
    }

    public hashTable(int n){
        this.size = 0;
        this.m = n;
        genHash();
    }

    public void insert(int n, String d){
        int index = hash(n);
        hashNode newNode = new hashNode(n, d);
        hashTable.get(index).add(newNode);
        size++;
    }


    public boolean delete(int key){
        int index = hash(key);
        int x = find(key);
        if(x != -1) {
            hashTable.get(index).remove(x);
            return true;
        } else {
            return false;
        }
    }

    public String search(int key){
        String returnStr = null;
        int index = hash(key);
        int x = find(key);
        if(x != -1) {
            returnStr = hashTable.get(index).get(x).data;
        }
        return returnStr;
    }


    // find return value: some type of index
    private int find(int key){
        int innerIndex = -1;
        int index = hash(key);
        for(int i = 0; i < hashTable.get(index).size(); i++) {
            if (hashTable.get(index).get(i).id == key) {
                innerIndex = i;
            }
        }
        return innerIndex;
    }

    private int hash(hashNode n){
        double c = (Math.sqrt(5) - 1)/2;
        return (int) (m*(n.id * c - (int) n.id*c));
    }

    private int hash(int key){
        double c = (Math.sqrt(5) - 1)/2;
        return (int) (m*(key * c - (int) key*c));
    }

    public void clear() {
        hashTable.clear();
    }


    public String[] hashArray() {
        String[] hashArr = new String[size];
        if(size == 0) {
            return hashArr;
        }
        for(int i = 0; i < size; i++) {
            for(int j = 0; j < hashTable.get(i).size(); j++) {
                hashArr[j] = String.format("%09d", hashTable.get(i).get(j).id) + " " + hashTable.get(i).get(j).data;
            }
        }
        return hashArr;
    }

    private void genHash() {
        for(int i = 0; i < m; i++) {
            ArrayList<hashNode> A = new ArrayList<hashNode>();
            hashTable.add(A);
        }
    }
}
