#include <iostream>
using namespace std;

// --------------------------------------
// Node Structure
// --------------------------------------
class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// --------------------------------------
// Linked List Class
// --------------------------------------
class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    bool isEmpty() const {
        return head == nullptr;
    }

    // Insert at head
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    // Delete from head safely
    int deleteFromHead() {
        if (isEmpty()) {
            cout << " Cannot delete — list is empty.\n";
            return -1;
        }

        Node* temp = head;
        int val = temp->data;

        head = head->next;
        delete temp;

        return val;
    }

    // Get head value safely
    int getHeadValue() const {
        if (isEmpty()) {
            cout << " Cannot peek — list is empty.\n";
            return -1;
        }
        return head->data;
    }

    // Display entire list
    void display() const {
        if (isEmpty()) {
            cout << "List: [ empty ]\n";
            return;
        }

        cout << "List: ";
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Allow Stack to see private members
    friend class Stack;
};

// --------------------------------------
// Stack Class (Using LinkedList)
// --------------------------------------
class Stack {
private:
    LinkedList list;

public:
    bool isEmpty() const {
        return list.isEmpty();
    }

    void push(int val) {
        list.insertAtHead(val);
        cout << val << " pushed onto stack.\n";
    }

    void pop() {
        int val = list.deleteFromHead();
        if (val != -1)
            cout << val << " popped from stack.\n";
    }

    void peek() const {
        int val = list.getHeadValue();
        if (val != -1)
            cout << "Top element: " << val << endl;
    }

    void display() const {
        cout << "Stack  ";
        list.display();
    }
};

// --------------------------------------
// Main Function
// --------------------------------------
int main() {
    Stack s;

    s.push(10);
    s.push(20);
    s.push(30);

    s.display();

    s.pop();
    s.peek();

    s.display();

    s.pop();
    s.pop();

    s.peek(); 
    s.display();

    return 0;
}
