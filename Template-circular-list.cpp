#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class List;  

// --------------------- NODE CLASS ---------------------
template <typename T>
class Node {
private:
    T data;
    Node<T>* next;

public:
    Node(T x, Node<T>* n = nullptr) {
        data = x;
        next = n;
    }

    T retrieve() {
        return data;
    }

    friend class List<T>;
};


// ---------------------- LIST CLASS ----------------------
template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List() {
        head = tail = nullptr;
    }

    // push front
    void push_front(T x) {
        Node<T>* new_node = new Node<T>(x);

        if (!head) {
            head = tail = new_node;
            tail->next = head;
        }
        else {
            new_node->next = head;
            head = new_node;
            tail->next = head;
        }
    }

    // push back
    void push_back(T x) {
        Node<T>* new_node = new Node<T>(x);

        if (!head) {
            head = tail = new_node;
            tail->next = head;
        }
        else {
            tail->next = new_node;
            tail = new_node;
            tail->next = head;
        }
    }

    // push at position
    void push_middle(T x, int pos) {
        if (!head || pos <= 0) {
            push_front(x);
            return;
        }

        Node<T>* temp = head;
        int count = 0;

        while (temp->next != head && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp == tail) {
            push_back(x);
            return;
        }

        Node<T>* new_node = new Node<T>(x);
        new_node->next = temp->next;
        temp->next = new_node;
    }

    // pop front
    void pop_front() {
        if (!head) {
            throw runtime_error("Cannot pop from empty list.");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node<T>* temp = head;
        head = head->next;
        tail->next = head;
        delete temp;
    }

    // pop back
    void pop_back() {
        if (!head) {
            throw runtime_error("Cannot pop from empty list.");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node<T>* temp = head;

        while (temp->next != tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = head;
    }

    // erase at position
    void erase(int pos) {
        if (!head) {
            throw runtime_error("Cannot erase from empty list.");
        }

        if (pos <= 1) {
            pop_front();
            return;
        }

        Node<T>* temp = head;
        int count = 1;

        while (temp->next != head && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (temp->next == head) {
            throw runtime_error("Invalid position for erase.");
        }

        Node<T>* delNode = temp->next;
        temp->next = delNode->next;

        if (delNode == tail) {
            tail = temp;
        }

        delete delNode;
        tail->next = head;
    }

    // print list
    void print() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* temp = head;
        cout << "List: ";

        do {
            cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);

        cout << "(back to head)" << endl;
    }

    // reverse print (recursive helper)
    void print_rev(Node<T>* node, Node<T>* start) {
        if (node->next != start) {
            print_rev(node->next, start);
        }
        cout << node->data << " -> ";
    }

    // reverse print main
    void print_reverse() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        cout << "Reverse List: ";
        print_rev(head, head);
        cout << "(back to head)" << endl;
    }

    // size
    int size() {
        if (!head) {
            return 0;
        }

        int count = 0;
        Node<T>* temp = head;

        do {
            count++;
            temp = temp->next;
        } while (temp != head);

        return count;
    }

    // capacity = size
    int capacity() {
        return size();
    }

    // count value
    int count(T x) {
        if (!head) {
            return 0;
        }

        int c = 0;
        Node<T>* temp = head;

        do {
            if (temp->data == x) {
                c++;
            }
            temp = temp->next;
        } while (temp != head);

        return c;
    }

    // get head value
    T get_head() {
        if (!head) {
            throw runtime_error("List empty");
        }
        return head->data;
    }

    // clear list
    void clear() {
        if (!head) {
            cout << "List already empty." << endl;
            return;
        }

        Node<T>* temp = head;

        do {
            Node<T>* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        } while (temp != head);

        head = tail = nullptr;

        cout << "List cleared successfully." << endl;
    }
};


// ----------------------- MAIN -----------------------
int main() {
    try {
        List<int> l;

        cout << "------------Circular Singly Linked List-----------" << endl;

        l.push_front(1);
        l.push_front(2);
        l.push_front(3);
        l.push_front(4);
        l.print();

        l.push_back(5);
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
