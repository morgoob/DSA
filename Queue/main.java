
import java.util.Scanner;

public class p1 {
    public static void main(String args[]) {
        Queue queue = new Queue();
        Scanner scanner = new Scanner(System.in);
        while (scanner.hasNextLine()) {
            String input = scanner.nextLine();
            queue.enqueue(input);
        }

        while (!(queue.isEmpty())) {
            System.out.println(queue.isEmpty());
            String dequeueData = queue.dequeue();
            System.out.println(dequeueData);
        }
    }
}