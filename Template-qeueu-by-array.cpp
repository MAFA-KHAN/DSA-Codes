#include <iostream>
#include <stdexcept>
using namespace std;


class Underflow {
public:
    const char* what() const { return "Queue Underflow: Queue is empty."; }
};

class Overflow {
public:
    const char* what() const { return "Queue Overflow: Cannot push more elements."; }
};



template <typename T>
class Queue {
private:
    int queue_size;       
    int ifront;            
    int iback;            
    int array_capacity;    
    T* array;            

   
    void resize() {
        int new_capacity = array_capacity * 2;
        T* new_array = new T[new_capacity];

      
        for (int i = 0; i < queue_size; i++) {
            new_array[i] = array[(ifront + i) % array_capacity];
        }

        delete[] array;
        array = new_array;

        ifront = 0;
        iback = queue_size - 1;
        array_capacity = new_capacity;

        cout << "Capacity doubled to " << array_capacity << endl;
    }

public:
   
    Queue(int n = 10)
        : queue_size(0), ifront(0), iback(-1), array_capacity(n), array(new T[n]) {
    }

   
    ~Queue() {
        delete[] array;
    }

   
    bool empty() const {
        return queue_size == 0;
    }

    int size() const {
        return queue_size;
    }

 
    T front() const {
        if (empty()) throw Underflow();
        return array[ifront];
    }

   
    T back() const {
        if (empty()) throw Underflow();
        return array[iback];
    }

    void push(T value) {
        if (queue_size == array_capacity) {
            resize(); 
        }

        iback = (iback + 1) % array_capacity;
        array[iback] = value;
        queue_size++;
    }


    T pop() {
        if (empty()) throw Underflow();

        T value = array[ifront];
        ifront = (ifront + 1) % array_capacity;
        queue_size--;

        return value;
    }

  
    void erase() {
        queue_size = 0;
        ifront = 0;
        iback = -1;
    }

    void print() const {
        if (empty()) {
            cout << "Queue is empty.\n";
            return;
        }

        cout << "Queue: ";
        for (int i = 0; i < queue_size; i++) {
            cout << array[(ifront + i) % array_capacity] << " ";
        }
        cout << endl;
    }
};



int main() {
    try {
        Queue<int> q(3);

        q.push(10);
        q.push(20);
        q.push(30);

        q.print();

        q.push(40); 
        q.push(50);

        q.print();

        cout << "Front = " << q.front() << endl;
        cout << "Back = " << q.back() << endl;

        q.pop();
        q.print();

        q.erase();
        q.print();

    }
    catch (Underflow u) {
        cout << u.what() << endl;
    }
    catch (Overflow o) {
        cout << o.what() << endl;
    }

    return 0;
}
