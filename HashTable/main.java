// Morgan Lloyd, mlloyd@pengo.cabrillo.edu
// morganlloydd@gmail.com
// Assignment 5, Hash Table
// working/tested (compiles)
import java.util.Scanner;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;

public class p5 {
    public static void main(String args[]) {
        String strChoice;
        hashTable hash = new hashTable(178000);
        Scanner scanner = new Scanner(System.in);
        System.out.println("(1) load (2)insert (3)delete (4)search (5)clear (6)save (7)quit -- Your choice? ");
        while (scanner.hasNextLine()) {
            strChoice = scanner.nextLine();
            int choice = Integer.parseInt(strChoice);
            int key;
            String inputKey, inputData, filename, paddedInt;
            if (choice == 1) {
                System.out.print("\nread hash table - filename? ");
                if(scanner.hasNext()) {
                    filename = scanner.nextLine();
                    readFile(filename, hash);
                }
            } else if (choice == 2) {
                System.out.print("input new record: ");
                if(scanner.hasNextLine()) {
                    inputData = scanner.nextLine();
                    insert(hash, inputData);
                }
            } else if (choice == 3) {
                System.out.print("delete record - key? ");
                if(scanner.hasNextLine()) {
                    inputKey = scanner.nextLine();
                    key = Integer.parseInt(inputKey);
                    if(hash.delete(key)) {
                        System.out.println("Delete: " + inputKey);
                    } else {
                        System.out.println("Delete not found: " + inputKey);
                    }
                }
            } else if (choice == 4) {
                System.out.print("search for record - key? ");
                if(scanner.hasNextLine()) {
                    inputKey = scanner.nextLine();
                    key = Integer.parseInt(inputKey);
                    String data = hash.search(key);
                    paddedInt = String.format("%09d", key);
                    if(data != null) {
                        System.out.println("Found: " + paddedInt + " " + data);
                    } else {
                        System.out.println("Search not found: " + paddedInt);
                    }
                }
            } else if (choice == 5) {
                System.out.println("clearing hash table.");
                hash.clear();
            } else if (choice == 6) {
                System.out.print("write hash table - filename? ");
                if(scanner.hasNextLine()) {
                    filename = scanner.nextLine();
                    writeFile(hash, filename);
                }
            } else if (choice == 7) {
                System.exit(0);
            } else {
                System.out.println("Invalid choice, please try again.");
            }
            System.out.println("(1) load (2)insert (3)delete (4)search (5)clear (6)save (7)quit -- Your choice? ");
        }
    }

    public static void insert(hashTable hashT, String data) {
        int i = data.indexOf(' ');
        String key = data.substring(0, i);
        String str = data.substring(i);
        hashT.insert(Integer.parseInt(key), str);
    }

    public static void readFile(String file, hashTable hashT) {
        try {
            BufferedReader br = new BufferedReader(new FileReader(file));
            String line;
            while((line = br.readLine()) != null) {
                insert(hashT, line);
            }
        } catch (IOException e) {
            System.err.println("Error: IO exception with ." + file);
        }
    }
    public static void writeFile(hashTable hashT, String file) {
        try {
            PrintWriter writer = new PrintWriter(file);
            String[] hashArr = hashT.hashArray();
            for(int i = 0; i < hashArr.length; i++) {
                writer.println(hashArr[i]);
            }
            writer.close();
        } catch (IOException e) {
            System.err.println("Error, IO exception with " + file);
        }
    }
}



