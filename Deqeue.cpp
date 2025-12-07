#include <iostream>
using namespace std;


class Underflow {
public:
    const char* what() const { return "Deque Underflow: deque is empty."; }
};

class Overflow {
public:
    const char* what() const { return "Deque Overflow: cannot push."; }
};



template <typename T>
class Deque {
private:
    int dq_size;         
    int ifront;         
    int iback;            
    int capacity;      
    T* array;             

    
    void resize() {
        int new_cap = capacity * 2;
        T* new_arr = new T[new_cap];

        for (int i = 0; i < dq_size; i++) {
            new_arr[i] = array[(ifront + i) % capacity];
        }

        delete[] array;
        array = new_arr;

        ifront = 0;
        iback = dq_size - 1;
        capacity = new_cap;

        cout << "Capacity doubled to " << capacity << endl;
    }

public:
    
    Deque(int n = 10)
        : dq_size(0), ifront(0), iback(-1), capacity(n), array(new T[n]) {
    }

    
    ~Deque() {
        delete[] array;
    }

    
    bool empty() const {
        return dq_size == 0;
    }

   
    int size() const {
        return dq_size;
    }

   
    T front() const {
        if (empty()) throw Underflow();
        return array[ifront];
    }

  
    T back() const {
        if (empty()) throw Underflow();
        return array[iback];
    }

    
    void push_front(T value) {
        if (dq_size == capacity) resize();

        ifront = (ifront - 1 + capacity) % capacity;
        array[ifront] = value;

        if (dq_size == 0) iback = ifront;

        dq_size++;
    }

 
    void push_back(T value) {
        if (dq_size == capacity) resize();

        iback = (iback + 1) % capacity;
        array[iback] = value;

        if (dq_size == 0) ifront = iback; 

        dq_size++;
    }

  
    T pop_front() {
        if (empty()) throw Underflow();

        T val = array[ifront];
        ifront = (ifront + 1) % capacity;
        dq_size--;

        return val;
    }

 
    T pop_back() {
        if (empty()) throw Underflow();

        T val = array[iback];
        iback = (iback - 1 + capacity) % capacity;
        dq_size--;

        return val;
    }

 
    void erase() {
        dq_size = 0;
        ifront = 0;
        iback = -1;
    }


    void print() const {
        if (empty()) {
            cout << "Deque is empty.\n";
            return;
        }

        cout << "Deque: ";
        for (int i = 0; i < dq_size; i++) {
            cout << array[(ifront + i) % capacity] << " ";
        }
        cout << endl;
    }
};


int main() {
    try {
        Deque<int> dq(4);

        dq.push_front(10);
        dq.push_back(20);
        dq.push_front(5);
        dq.push_back(30);
        dq.print();

        dq.push_back(40); 
        dq.print();

        cout << "Front: " << dq.front() << endl;
        cout << "Back: " << dq.back() << endl;

        dq.pop_front();
        dq.pop_back();
        dq.print();

        dq.erase();
        dq.print();

    }
    catch (Underflow e) {
        cout << e.what() << endl;
    }
    catch (Overflow e) {
        cout << e.what() << endl;
    }

    return 0;
}
