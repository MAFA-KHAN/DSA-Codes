#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class Node {
private:
    T data;
    Node* next;

public:
    Node(T x, Node* n = nullptr) {
        data = x;
        next = n;
    }

    T retrieve() 
    { return data; }

    template <typename U>
    friend class List;
};

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List() { head = tail = nullptr; }

    void push_front(T x) {
        Node<T>* new_node = new Node<T>(x);
        if (!head) head = tail = new_node;
        else {
            new_node->next = head;
            head = new_node;
        }
    }

    void push_back(T x) {
        Node<T>* new_node = new Node<T>(x);
        if (!head) head = tail = new_node;
        else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void push_middle(T x, int pos) {
        if (pos <= 0) { push_front(x); return; }

        Node<T>* temp = head;
        int count = 0;

        while (temp && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (!temp || temp == tail) {
            push_back(x);
            return;
        }

        Node<T>* new_node = new Node<T>(x);
        new_node->next = temp->next;
        temp->next = new_node;
    }

    void pop_front() {
        if (!head) throw runtime_error("Error: Cannot pop from empty list.");

        Node<T>* temp = head;
        head = head->next;

        if (!head) tail = nullptr;

        delete temp;
    }

    void pop_back() {
        if (!head) throw runtime_error("Error: Cannot pop from empty list.");

        if (head == tail) {
            delete head;
            head = tail = nullptr;
            return;
        }

        Node<T>* temp = head;
        while (temp->next != tail)
            temp = temp->next;

        delete tail;
        tail = temp;
        tail->next = nullptr;
    }

    void erase(int pos) {
        if (!head) throw runtime_error("Error: Cannot erase from empty list.");

        if (pos <= 1) {
            pop_front();
            return;
        }

        Node<T>* temp = head;
        int count = 1;

        while (temp && count < pos - 1) {
            temp = temp->next;
            count++;
        }

        if (!temp || !temp->next)
            throw runtime_error("Error: Invalid position for erase.");

        Node<T>* delNode = temp->next;
        temp->next = delNode->next;

        if (delNode == tail) tail = temp;

        delete delNode;
    }

    void print() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node<T>* temp = head;
        cout << "List: ";
        while (temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    void print_rev(Node<T>* node) {
        if (!node) return;
        print_rev(node->next);
        cout << node->data << " -> ";
    }

    void print_reverse() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "Reverse List: ";
        print_rev(head);
        cout << "NULL" << endl;
    }

    int size() {
        int count = 0;
        Node<T>* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    int capacity() { return size(); }

    int count_value(T x) {
        int c = 0;
        Node<T>* temp = head;

        while (temp) {
            if (temp->data == x) c++;
            temp = temp->next;
        }

        return c;
    }

    T get_head() {
        if (!head) throw runtime_error("Error: List is empty, no head element.");
        return head->data;
    }

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

int main() {
    try {
        List<int> l;

        cout << "------------TEMPLATED Singly Linked List-----------" << endl;

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

        cout << "Size = " << l.size() << endl;
        cout << "Capacity = " << l.capacity() << endl;

        l.push_back(5);
        l.push_back(5);
        l.push_front(5);
        l.print();

        cout << "Count of 5 = " << l.count_value(5) << endl;

        cout << "Head = " << l.get_head() << endl;

        l.print_reverse();

        l.clear();
        l.print();
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
