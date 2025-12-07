#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class List;   

// ---------------- NODE CLASS ----------------
template <typename T>
class Node {
private:
    T data;
    Node<T>* next;
    Node<T>* prev;

public:
    Node(T x, Node<T>* n = nullptr, Node<T>* p = nullptr) {
        data = x;
        next = n;
        prev = p;
    }

    T retrieve() { return data; }

    friend class List<T>;  
};

// ---------------- LIST CLASS ----------------
template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List() { head = tail = nullptr; }

    // Push Front
    void push_front(T x) {
        Node<T>* new_node = new Node<T>(x);
        if (!head)
            head = tail = new_node;
        else {
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
    }

    // Push Back
    void push_back(T x) {
        Node<T>* new_node = new Node<T>(x);
        if (!head)
            head = tail = new_node;
        else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }

    // Push Middle
    void push_middle(T x, int pos) {
        if (pos <= 0) { push_front(x); return; }

        Node<T>* temp = head;
        int count = 0;
        while (temp && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (!temp || temp == tail) { push_back(x); return; }

        Node<T>* new_node = new Node<T>(x);
        Node<T>* nextNode = temp->next;

        temp->next = new_node;
        new_node->prev = temp;

        new_node->next = nextNode;
        nextNode->prev = new_node;
    }

    // Pop Front
    void pop_front() {
        if (!head) throw runtime_error("Cannot pop from empty list.");

        Node<T>* temp = head;
        head = head->next;

        if (head) head->prev = nullptr;
        else tail = nullptr;

        delete temp;
    }

    // Pop Back
    void pop_back() {
        if (!head) throw runtime_error("Cannot pop from empty list.");

        Node<T>* temp = tail;
        tail = tail->prev;

        if (tail) tail->next = nullptr;
        else head = nullptr;

        delete temp;
    }

    // Erase
    void erase(int pos) {
        if (!head) throw runtime_error("Cannot erase from empty list.");
        if (pos <= 1) { pop_front(); return; }

        Node<T>* temp = head;
        int count = 1;
        while (temp && count < pos) {
            temp = temp->next;
            count++;
        }

        if (!temp) throw runtime_error("Invalid position for erase.");
        if (temp == tail) { pop_back(); return; }

        Node<T>* prevNode = temp->prev;
        Node<T>* nextNode = temp->next;

        prevNode->next = nextNode;
        nextNode->prev = prevNode;

        delete temp;
    }

    // Print Forward
    void print() {
        if (!head) { cout << "List is empty." << endl; return; }

        Node<T>* temp = head;
        cout << "List: ";
        while (temp) {
            cout << temp->data << " <=> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Print Reverse
    void print_reverse() {
        if (!tail) { cout << "List is empty." << endl; return; }

        Node<T>* temp = tail;
        cout << "Reverse List: ";
        while (temp) {
            cout << temp->data << " <=> ";
            temp = temp->prev;
        }
        cout << "NULL" << endl;
    }

    // Size / Capacity
    int size() {
        int count = 0;
        Node<T>* temp = head;
        while (temp) { count++; temp = temp->next; }
        return count;
    }

    int capacity() { return size(); }

    // Count occurrences
    int count(T x) {
        int c = 0;
        Node<T>* temp = head;
        while (temp) {
            if (temp->data == x) c++;
            temp = temp->next;
        }
        return c;
    }

    // Get head value
    T get_head() {
        if (!head) throw runtime_error("List empty");
        return head->data;
    }

    // Clear
    void clear() {
        Node<T>* temp = head;
        while (temp) {
            Node<T>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        head = tail = nullptr;
        cout << "List cleared successfully." << endl;
    }
};

// ---------------- MAIN ----------------
int main() {
    try {
        List<int> l;

        cout << "------------Doubly Linked List-----------" << endl;
        l.push_front(1); 
        l.push_front(2); 
        l.push_front(3);
        l.push_front(4); 
        l.push_front(5); 
        l.print();
        l.push_back(6);
        l.print();
        l.push_middle(7, 2); 
        l.print();
        l.erase(3); 
        l.print();
        l.pop_front();
        l.print();
        l.pop_back(); 
        l.print();
        l.print_reverse();

        cout << "Size = " << l.size() << endl;
        cout << "Capacity = " << l.capacity() << endl;

        l.push_back(5); l.push_back(5); l.push_front(5); l.print();

        cout << "Count of 5 = " << l.count(5) << endl;
        cout << "Head = " << l.get_head() << endl;

        l.clear();
        l.print();
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
