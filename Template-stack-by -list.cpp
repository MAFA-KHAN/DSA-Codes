#include <iostream>
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node* next;

    Node(T val) : data(val), next(nullptr) {}
};


template <typename T>
class LinkedList {
private:
    Node<T>* head;

public:
    LinkedList() : head(nullptr) {}

    bool isEmpty() const {
        return head == nullptr;
    }

    // Insert at head
    void insertAtHead(T val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = head;
        head = newNode;
    }

    // Delete from head 
    T deleteFromHead() {
        if (isEmpty()) {
            cout << " Cannot delete — list is empty.\n";
            return T();   
        }

        Node<T>* temp = head;
        T val = temp->data;

        head = head->next;
        delete temp;

        return val;
    }

    // Get head value 
    T getHeadValue() const {
        if (isEmpty()) {
            cout << " Cannot peek — list is empty.\n";
            return T();
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
        Node<T>* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

  
    template <typename> friend class Stack;
};


template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    bool isEmpty() const {
        return list.isEmpty();
    }

    void push(T val) {
        list.insertAtHead(val);
        cout << val << " pushed onto stack.\n";
    }

    void pop() {
        T val = list.deleteFromHead();
        if (!(val == T()))  
            cout << val << " popped from stack.\n";
    }

    void peek() const {
        T val = list.getHeadValue();
        if (!(val == T()))
            cout << "Top element: " << val << endl;
    }

    void display() const {
        cout << "Stack  ";
        list.display();
    }
};


int main()
{
    Stack<int> s;     
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
