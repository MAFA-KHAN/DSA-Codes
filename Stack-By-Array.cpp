#include <iostream>
using namespace std;


class Underflow {};
class Overflow {};

class Stack {
private:
    int stack_size;      
    int array_capacity;  
    int* array;          

    // Double the capacity
    void double_capacity() {
        int* tmp_array = new int[2 * array_capacity];
        for (int i = 0; i < array_capacity; i++) {
            tmp_array[i] = array[i];
        }
        delete[] array;
        array = tmp_array;
        array_capacity *= 2;
        cout << "Capacity doubled to " << array_capacity << endl;
    }

public:
    // Constructor
    Stack(int n = 10) {
        if (n < 1) n = 1;
        stack_size = 0;
        array_capacity = n;
        array = new int[array_capacity];
    }

    // Destructor
    ~Stack() {
        delete[] array;
    }

    // Check if empty
    bool empty() const {
        return stack_size == 0;
    }

    // Push element
    void push(int val) {
        if (stack_size == array_capacity) {
            double_capacity();
        }
        array[stack_size++] = val;
        cout << val << " pushed\n";
    }

    // Pop element
    int pop() {
        if (empty()) throw Underflow();
        return array[--stack_size];
    }

    // Peek top element
    int top() const {
        if (empty()) throw Underflow();
        return array[stack_size - 1];
    }

    // Display stack
    void display() const {
        cout << "Stack: ";
        for (int i = stack_size - 1; i >= 0; i--) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Stack s(2); 
    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    cout << "Top: " << s.top() << endl;

    s.pop();
    s.display();

    return 0;
}
