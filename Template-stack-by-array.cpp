#include <iostream>
using namespace std;

class Underflow {};
class Overflow {};

template <typename T>
class Stack {
private:
    int stack_size;
    int array_capacity;
    T* array;

    void double_capacity() {
        T* tmp_array = new T[2 * array_capacity];

        for (int i = 0; i < array_capacity; i++)
        {
            tmp_array[i] = array[i];
        }

        delete[] array;
        array = tmp_array;
        array_capacity = array_capacity * 2;

        cout << "Capacity doubled to " << array_capacity << endl;
    }

public:
    Stack(int n = 10) {
        if (n < 1) n = 1;
        stack_size = 0;
        array_capacity = n;
        array = new T[array_capacity];
    }

    ~Stack() {
        delete[] array;
    }

    bool empty() const {
        return stack_size == 0;
    }

    void push(T val) {
        if (stack_size == array_capacity)
        {
            double_capacity();
        }

        array[stack_size] = val;
        stack_size++;

        cout << val << " pushed\n";
    }

    T pop() {
        if (empty())
        {
            throw Underflow();
        }
        stack_size--;
        return array[stack_size];
    }

    T top() const {
        if (empty())
        {
            throw Underflow();
        }
        return array[stack_size - 1];
    }

    void display() const {
        cout << "Stack: ";

        for (int i = stack_size - 1; i >= 0; i--)
        {
            cout << array[i] << " ";
        }

        cout << endl;
    }
};

int main()
{
    Stack<int> s(2);

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    cout << "Top: " << s.top() << endl;

    s.pop();

    s.display();

    return 0;
}
