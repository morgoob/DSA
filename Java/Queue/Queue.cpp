#include <iostream>
#include <list>

using namespace std;

class queue {
private:
  list<string> linkedList;

public:
  queue();
  void enqueue(string);
  string dequeue();
  bool isEmpty();
  
};

queue::queue() {
  list<string> linkedList;
}

void queue::enqueue(string data) {
  linkedList.push_back(data);
}

string queue::dequeue(){
  string dequeueData = "";
  if (isEmpty()) {
    return dequeueData;
  } else {
    dequeueData = linkedList.front();
    linkedList.pop_front();
  }
  return dequeueData;
}

bool queue::isEmpty() {
  return linkedList.empty();
}

int main() {
  queue q;
  string line, dequeueData;

  while(getline(cin, line)) {
    q.enqueue(line);
  }

  while(!q.isEmpty()) {
    dequeueData = q.dequeue();
    cout << dequeueData << endl;
  }
}
