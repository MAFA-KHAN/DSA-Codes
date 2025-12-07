#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T x) {
        data = x;
        next = nullptr;
    }
};

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    Queue() {
        head = nullptr;
        tail = nullptr;
    }

    bool empty() const {
        return head == nullptr;
    }

    // Insert at front
    void push_front(T x) {
        Node<T>* newNode = new Node<T>(x);

        if (empty()) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        cout << x << " pushed at front\n";
    }

    // Insert at end
    void push_end(T x) {
        Node<T>* newNode = new Node<T>(x);

        if (empty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        cout << x << " pushed at end\n";
    }

    // Remove from front
    T pop_front() {
        if (empty()) {
            cout << "Queue empty\n";
            return T();
        }

        Node<T>* temp = head;
        T val = temp->data;

        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;

        return val;
    }

    // Remove from end
    T pop_end() {
        if (empty()) {
            cout << "Queue empty\n";
            return T();
        }

        if (head == tail) {
            T val = head->data;
            delete head;
            head = tail = nullptr;
            return val;
        }

        Node<T>* temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }

        T val = tail->data;
        delete tail;

        tail = temp;
        tail->next = nullptr;

        return val;
    }

    // Erase by position (1-based)
    void erase(int pos) {
        if (empty()) {
            cout << "Queue empty\n";
            return;
        }

        if (pos <= 1) {
            pop_front();
            return;
        }

        Node<T>* temp = head;
        int count = 1;

        while (temp->next != nullptr && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp->next == nullptr) {
            cout << "Invalid position\n";
            return;
        }

        Node<T>* del = temp->next;
        temp->next = del->next;

        if (del == tail) {
            tail = temp;
        }

        delete del;
    }

    // Return front element
    T front() const {
        if (empty()) {
            cout << "Queue empty\n";
            return T();
        }
        return head->data;
    }

    // Return last element
    T end() const {
        if (empty()) {
            cout << "Queue empty\n";
            return T();
        }
        return tail->data;
    }

    // Count occurrences of x
    int count(T x) const {
        int c = 0;
        Node<T>* temp = head;

        while (temp != nullptr) {
            if (temp->data == x) {
                c++;
            }
            temp = temp->next;
        }
        return c;
    }

    // Size of queue
    int size() const {
        int c = 0;
        Node<T>* temp = head;

        while (temp != nullptr) {
            c++;
            temp = temp->next;
        }
        return c;
    }

    // Print queue
    void print() const {
        if (empty()) {
            cout << "Queue empty\n";
            return;
        }

        cout << "Queue: ";
        Node<T>* temp = head;

        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }

        cout << endl;
    }
};

int main() {
    Queue<int> q;

    q.push_end(10);
    q.push_end(20);
    q.push_front(5);
    q.push_end(30);

    q.print();

    cout << "Front : " << q.front() << endl;
    cout << "End   : " << q.end() << endl;

    cout << "Pop front: " << q.pop_front() << endl;
    cout << "Pop end: " << q.pop_end() << endl;

    q.print();

    cout << "Size : " << q.size() << endl;
    cout << "Count of 20 : " << q.count(20) << endl;

    q.erase(2);
    q.print();

    return 0;
}
