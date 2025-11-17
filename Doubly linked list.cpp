
#include <iostream>
#include <stdexcept>
using namespace std;

class Node {
private:
    int data;
    Node* next;
    Node* pre;
public:
    Node(int x, Node* n = nullptr, Node* p = nullptr)
    {
        data = x; next = n; pre = p;
    }
    int retrieve() { return data; }
    friend class list;
};

class list {
private:
    Node* head; Node* tail;
public:
    list() { head = tail = nullptr; }

    void push_front(int x) {
        Node* new_node = new Node(x);
        if (!head) head = tail = new_node;
        else { new_node->next = head; head->pre = new_node; head = new_node; }
    }

    void push_back(int x) {
        Node* new_node = new Node(x);
        if (!head) head = tail = new_node;
        else { tail->next = new_node; new_node->pre = tail; tail = new_node; }
    }

    void push_middle(int x, int pos) {
        if (pos <= 0) { push_front(x); return; }
        Node* temp = head; int count = 0;
        while (temp && count < pos - 1) { temp = temp->next; count++; }
        if (!temp || temp == tail) { push_back(x); return; }
        Node* new_node = new Node(x); Node* nextNode = temp->next;
        temp->next = new_node; new_node->pre = temp;
        new_node->next = nextNode; nextNode->pre = new_node;
    }

    void pop_front() {
        if (!head) throw runtime_error("Cannot pop from empty list.");
        Node* temp = head; head = head->next;
        if (head) head->pre = nullptr; else tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!head) throw runtime_error("Cannot pop from empty list.");
        Node* temp = tail; tail = tail->pre;
        if (tail) tail->next = nullptr; else head = nullptr;
        delete temp;
    }

    void erase(int pos) {
        if (!head) throw runtime_error("Cannot erase from empty list.");
        if (pos <= 1) { pop_front(); return; }
        Node* temp = head; int count = 1;
        while (temp && count < pos) { temp = temp->next; count++; }
        if (!temp) throw runtime_error("Invalid position for erase.");
        if (temp == tail) { pop_back(); return; }
        Node* prevNode = temp->pre; Node* nextNode = temp->next;
        prevNode->next = nextNode; nextNode->pre = prevNode;
        delete temp;
    }

    void print() {
        if (!head) { cout << "List is empty." << endl; return; }
        Node* temp = head;
        cout << "List: ";
        while (temp) { cout << temp->data << " <=> "; temp = temp->next; }
        cout << "NULL" << endl;
    }

    void print_reverse() {
        if (!tail) { cout << "List is empty." << endl; return; }
        Node* temp = tail;
        cout << "Reverse List: ";
        while (temp) { cout << temp->data << " <=> "; temp = temp->pre; }
        cout << "NULL" << endl;
    }

    int size()
    {
        int count = 0; Node* temp = head;
        while (temp) { count++; temp = temp->next; }
        return count;
    }
    int capacity()
    {
        return size();
    }
    int count(int x)
    {
        int c = 0; Node* temp = head;
        while (temp) { if (temp->data == x)c++; temp = temp->next; }
        return c;
    }
    int get_head()
    {
        if (!head)
            throw runtime_error("List empty");
        return head->data;
    }

    void clear() {
        Node* temp = head;
        while (temp) { Node* nextNode = temp->next; delete temp; temp = nextNode; }
        head = tail = nullptr; cout << "List cleared successfully." << endl;
    }
};

int main() {
    try {
        list l;
        cout << "------------Doubly Linked List-----------" << endl;
        l.push_front(1); l.push_front(2); l.push_front(3); l.push_front(4); l.push_front(5); l.print();
        l.push_back(6); l.print();
        l.push_middle(7, 2); l.print();
        l.erase(3); l.print();
        l.pop_front(); l.print();
        l.pop_back(); l.print();
        l.print_reverse();
        cout << "Size = " << l.size() << endl;
        cout << "Capacity = " << l.capacity() << endl;
        l.push_back(5); l.push_back(5); l.push_front(5); l.print();
        cout << "Count of 5 = " << l.count(5) << endl;
        cout << "Head = " << l.get_head() << endl;
        l.clear(); l.print();
    }
    catch (const runtime_error& e) { cerr << e.what() << endl; }
    return 0;
}
