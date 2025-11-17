#include <iostream>

#include <stdexcept>
using namespace std;

class Node {
private:
    int data;
    Node* next;
public:
    Node(int x, Node* n = nullptr) { data = x; next = n; }
    int retrieve() { return data; }
    friend class list;
};

class list {
private:
    Node* head;
    Node* tail;
public:
    list() { head = tail = nullptr; }

    void push_front(int x) {
        Node* new_node = new Node(x);
        if (!head) { head = tail = new_node; tail->next = head; }
        else { new_node->next = head; head = new_node; tail->next = head; }
    }

    void push_back(int x) {
        Node* new_node = new Node(x);
        if (!head) { head = tail = new_node; tail->next = head; }
        else { tail->next = new_node; tail = new_node; tail->next = head; }
    }

    void push_middle(int x, int pos) {
        if (!head || pos <= 0) { push_front(x); return; }
        Node* temp = head; int count = 0;
        while (temp->next != head && count < pos - 1) { temp = temp->next; count++; }
        if (temp == tail) { push_back(x); return; }
        Node* new_node = new Node(x); new_node->next = temp->next; temp->next = new_node;
    }

    void pop_front() {
        if (!head) throw runtime_error("Cannot pop from empty list.");
        if (head == tail) { delete head; head = tail = nullptr; return; }
        Node* temp = head; head = head->next; tail->next = head; delete temp;
    }

    void pop_back() {
        if (!head) throw runtime_error("Cannot pop from empty list.");
        if (head == tail) { delete head; head = tail = nullptr; return; }
        Node* temp = head;
        while (temp->next != tail) temp = temp->next;
        delete tail; tail = temp; tail->next = head;
    }

    void erase(int pos) {
        if (!head) throw runtime_error("Cannot erase from empty list.");
        if (pos <= 1) { pop_front(); return; }
        Node* temp = head; int count = 1;
        while (temp->next != head && count < pos - 1) { temp = temp->next; count++; }
        if (temp->next == head) throw runtime_error("Invalid position for erase.");
        Node* delNode = temp->next; temp->next = delNode->next;
        if (delNode == tail) tail = temp;
        delete delNode; tail->next = head;
    }

    void print() {
        if (!head) { cout << "List is empty." << endl; return; }
        Node* temp = head;
        cout << "List: ";
        do { cout << temp->data << " -> "; temp = temp->next; } while (temp != head);
        cout << "(back to head)" << endl;
    }


    void print_rev(Node* node, Node* start) {
        if (node->next != start) {
            print_rev(node->next, start);
        }
        cout << node->data << " -> ";
    }


    void print_reverse() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }
        cout << "Reverse List: ";
        print_rev(head, head);
        cout << "(back to head)" << endl;
    }

    int size() 
    { if (!head) return 0; int count = 0;
    Node* temp = head; do { count++; temp = temp->next; }
    while (temp != head); return count; }
    int capacity() { return size(); }
    int count(int x) 
    { if (!head) return 0; int c = 0; Node* temp = head;
    do { if (temp->data == x)c++; temp = temp->next; } while (temp != head); return c; }
    int get_head() 
    { if (!head) throw runtime_error("List empty"); 
    return head->data; }

    void clear() {
        if (!head) { cout << "List already empty." << endl; return; }
        Node* temp = head;
        do { Node* nextNode = temp->next; delete temp; temp = nextNode; } while (temp != head);
        head = tail = nullptr; cout << "List cleared successfully." << endl;
    }
};

int main() {
    try {
        list l;
        cout << "------------Circular Singly Linked List-----------" << endl;
        l.push_front(1); l.push_front(2); l.push_front(3); l.push_front(4); l.print();
        l.push_back(5); l.push_back(6); l.print();
        l.push_middle(7, 2); l.print();
        l.erase(3); l.print();
        l.pop_front(); l.print();
        l.pop_back(); l.print();
        l.print_reverse();
        cout << "Size = " << l.size() << endl;
        cout << "Capacity = " << l.capacity() << endl;
        cout << "Count of 5 = " << l.count(5) << endl;
        cout << "Head = " << l.get_head() << endl;
        l.clear(); l.print();
    }
    catch (const runtime_error& e) { cerr << e.what() << endl; }
    return 0;
}
