public class CyclicQueue {
        private LinkedList list;

        // Queue constructor
        public CyclicQueue() {
            list = new LinkedList();
        }
    
        // Enqueue node at the rear of queue
        public void enqueue(String newData) {
            list.pushBack(newData);
        }

        // Dequeue node in front of queue
        public String dequeue() {
            String dequeueData = null;
            if (isEmpty()) {
                return dequeueData;
            } else {
                dequeueData = list.pop();
            }
            return dequeueData;
        }

        // check if queue is empty
        public boolean isEmpty() {
            return list.isEmpty();
        } 
}
