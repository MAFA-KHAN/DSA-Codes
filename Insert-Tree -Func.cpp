//INSERT FUNCTIONS OF ALL THE TYPES OF TREE 

#include<iostream>
#include<vector>
using namespace std;

// ==================== QUEUE AND NODE ====================

// NODE CLASS
template<typename T>
class Node {
    Node<T>* next;
    T data;
public:
    Node(T val) : data(val), next(nullptr) {}

    // Getters - maintain encapsulation
    T getData() const { return data; }
    Node<T>* getNext() const { return next; }

    // Setters - maintain encapsulation
    void setNext(Node<T>* n) { next = n; }
};

// TREE-QUEUE
template<typename T>
class TreeQueue {
    Node<T>* frontPtr;
    Node<T>* backPtr;
    int sz;
public:
    TreeQueue() : frontPtr(nullptr), backPtr(nullptr), sz(0) {}
    ~TreeQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return sz == 0;
    }

    int size() const { return sz; }

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty()) {
            frontPtr = backPtr = newNode;
        }
        else {
            backPtr->setNext(newNode);
            backPtr = newNode;
        }
        sz++;
    }

    void dequeue() {
        if (isEmpty()) {
            return;
        }
        Node<T>* temp = frontPtr;
        frontPtr = frontPtr->getNext();
        delete temp;
        sz--;
        if (!frontPtr) {
            backPtr = nullptr;
        }
    }

    T front() const {
        if (isEmpty()) {
            return T();
        }
        return frontPtr->getData();
    }
};

// ==================== TREE NODES ====================

// GENERIC TREE NODE CLASS
template<typename T>
class GTNode {
    T data;
    GTNode<T>* parent;
    GTNode<T>* child1;
    GTNode<T>* nextchild;
public:
    GTNode(T val) : data(val), parent(nullptr), child1(nullptr), nextchild(nullptr) {}

    // Getters
    T getData() const { return data; }
    GTNode<T>* getParent() const { return parent; }
    GTNode<T>* getFirstChild() const { return child1; }
    GTNode<T>* getNextChild() const { return nextchild; }

    // Setters
    void setParent(GTNode<T>* p) { parent = p; }
    void setFirstChild(GTNode<T>* c) { child1 = c; }
    void setNextChild(GTNode<T>* nc) { nextchild = nc; }
};

// BINARY TREE NODE CLASS 
template<typename T>
class BTNode {
    T data;
    BTNode<T>* left;
    BTNode<T>* right;
public:
    BTNode(T val) : data(val), left(nullptr), right(nullptr) {}

    // Getters
    T getData() const { return data; }
    BTNode<T>* getLeft() const { return left; }
    BTNode<T>* getRight() const { return right; }

    // Setters
    void setData(T d) { data = d; }
    void setLeft(BTNode<T>* l) { left = l; }
    void setRight(BTNode<T>* r) { right = r; }
};

// Expression tree node class
template <typename T>
class ETNode {
    char data;
    ETNode<T>* left;
    ETNode<T>* right;
public:
    ETNode(T val) : data(val), left(nullptr), right(nullptr) {}

    // Getters
    char getData() const { return data; }
    ETNode<T>* getLeft() const { return left; }
    ETNode<T>* getRight() const { return right; }

    // Setters
    void setLeft(ETNode<T>* l) { left = l; }
    void setRight(ETNode<T>* r) { right = r; }
};

// Operand check for ET insert - non-member function
bool isOperand(char c) {
    return (c >= '0' && c <= '9') ||
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z');
}

// ==================== STACK ====================

// Stack node class for Expression tree
template <typename T>
class StackNode {
    ETNode<T>* data;
    StackNode<T>* next;
public:
    StackNode(ETNode<T>* ptr) : data(ptr), next(nullptr) {}

    // Getters
    ETNode<T>* getData() const { return data; }
    StackNode<T>* getNext() const { return next; }

    // Setters
    void setNext(StackNode<T>* n) { next = n; }
};

template <typename T>
class Stack {
    StackNode<T>* topNode;

public:
    Stack() : topNode(nullptr) {}
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    void push(ETNode<T>* val) {
        StackNode<T>* newNode = new StackNode<T>(val);
        newNode->setNext(topNode);
        topNode = newNode;
    }

    ETNode<T>* pop() {
        if (isEmpty()) {
            cout << "Stack Underflow!" << endl;
            return nullptr;
        }
        StackNode<T>* temp = topNode;
        ETNode<T>* val = temp->getData();
        topNode = temp->getNext();
        delete temp;
        return val;
    }

    ETNode<T>* top() const {
        if (isEmpty()) return nullptr;
        return topNode->getData();
    }
};

// NODE CLASS FOR PERFECT BT
template<typename T>
class PNode {
    T data;
    PNode<T>* left;
    PNode<T>* right;
public:
    PNode(T val) : data(val), left(nullptr), right(nullptr) {}

    // Getters
    T getData() const { return data; }
    PNode<T>* getLeft() const { return left; }
    PNode<T>* getRight() const { return right; }

    // Setters
    void setLeft(PNode<T>* l) { left = l; }
    void setRight(PNode<T>* r) { right = r; }
};

// ==================== INSERTION CLASS ====================

template<typename T>
class INSERT {
public:
    // GENERIC-TREE-INSERTION (as many children as you want)
    void insertGeneric(GTNode<T>* parent, T val) {
        if (!parent) {
            return;
        }
        GTNode<T>* newChild = new GTNode<T>(val);
        newChild->setParent(parent);
        if (!parent->getFirstChild()) {
            parent->setFirstChild(newChild);
            return;
        }
        GTNode<T>* temp = parent->getFirstChild();
        while (temp->getNextChild()) {
            temp = temp->getNextChild();
        }
        temp->setNextChild(newChild);
    }

    // EXPRESSION-TREE-INSERTION
    ETNode<T>* insertExpression(const vector<char>& postfix) {
        Stack<T> st;

        for (char c : postfix) {
            if (isOperand(c)) {
                st.push(new ETNode<T>(c));
            }
            else {
                ETNode<T>* right = st.pop();
                ETNode<T>* left = st.pop();
                ETNode<T>* op = new ETNode<T>(c);

                op->setLeft(left);
                op->setRight(right);

                st.push(op);
            }
        }
        return st.pop(); // root of expression tree
    }

    // BINARY-TREE-INSERTION (0 or 1 or 2 children)
    void BTInsert(BTNode<T>*& root, T val) {
        BTNode<T>* node = new BTNode<T>(val);
        if (!root) {
            root = node;
            return;
        }
        TreeQueue<BTNode<T>*> q;
        q.enqueue(root);
        while (!q.isEmpty()) {
            BTNode<T>* curr = q.front();
            q.dequeue();
            if (!curr->getLeft()) {
                curr->setLeft(node);
                return;
            }
            else {
                q.enqueue(curr->getLeft());
            }
            if (!curr->getRight()) {
                curr->setRight(node);
                return;
            }
            else {
                q.enqueue(curr->getRight());
            }
        }
    }

    // INSERTION OF FULL BINARY TREE (0 or 2 children)
    void fullInsert(BTNode<T>*& root, T val) {
        BTNode<T>* node = new BTNode<T>(val);
        if (!root) {
            root = node;
            return;
        }
        TreeQueue<BTNode<T>*> q;
        q.enqueue(root);
        while (!q.isEmpty()) {
            BTNode<T>* curr = q.front();
            q.dequeue();
            if (!curr->getLeft() && !curr->getRight()) {
                curr->setLeft(node);
                return;
            }
            else if (curr->getLeft() && !curr->getRight()) {
                curr->setRight(node);
                return;
            }
            q.enqueue(curr->getLeft());
            q.enqueue(curr->getRight());
        }
    }

    // INSERTION OF PERFECT BINARY TREE
    PNode<T>* buildPerfect(int h) {
        if (h < 0) {
            return nullptr;
        }
        int totalNodes = (1 << (h + 1)) - 1; // 2^(h+1)-1

        // Create array of nodes
        vector<PNode<T>*> arr(totalNodes + 1);

        for (int i = 1; i <= totalNodes; i++)
            arr[i] = new PNode<T>(i);

        // Link like heap
        for (int i = 1; i <= totalNodes; i++) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;

            if (leftIndex <= totalNodes)
                arr[i]->setLeft(arr[leftIndex]);

            if (rightIndex <= totalNodes)
                arr[i]->setRight(arr[rightIndex]);
        }

        return arr[1]; // root
    }

    // INSERTION OF BINARY SEARCH TREE
    BTNode<T>* BSTinsert(BTNode<T>* root, T val) {
        if (!root) {
            return new BTNode<T>(val);
        }
        if (val < root->getData()) {
            root->setLeft(BSTinsert(root->getLeft(), val));
        }
        else if (val > root->getData()) {
            root->setRight(BSTinsert(root->getRight(), val));
        }
        return root;
    }
};

// ==================== HELPER FUNCTIONS ====================

// Helper function to print binary tree in inorder
template<typename T>
void printInorder(BTNode<T>* root) {
    if (!root) return;
    printInorder(root->getLeft());
    cout << root->getData() << " ";
    printInorder(root->getRight());
}

// Helper function to print expression tree
template<typename T>
void printExpression(ETNode<T>* root) {
    if (!root) return;
    if (root->getLeft()) {
        cout << "(";
        printExpression(root->getLeft());
    }
    cout << root->getData();
    if (root->getRight()) {
        printExpression(root->getRight());
        cout << ")";
    }
}

// Helper function to print generic tree
template<typename T>
void printGenericTree(GTNode<T>* root, int depth = 0) {
    if (!root) return;

    for (int i = 0; i < depth; i++) cout << "  ";
    cout << root->getData() << endl;

    GTNode<T>* child = root->getFirstChild();
    while (child) {
        printGenericTree(child, depth + 1);
        child = child->getNextChild();
    }
}

// Helper function to print perfect binary tree
template<typename T>
void printPerfectTree(PNode<T>* root) {
    if (!root) return;

    cout << root->getData() << " ";
    printPerfectTree(root->getLeft());
    printPerfectTree(root->getRight());
}

// ==================== MAIN FUNCTION ====================

int main() {
    INSERT<int> i;

    cout << "=== TESTING ALL TREE INSERTIONS ===\n\n";

    // 1. TEST GENERIC TREE
    cout << "1. Generic Tree Insertion:\n";
    GTNode<int>* gtRoot = new GTNode<int>(1);
    i.insertGeneric(gtRoot, 2);
    i.insertGeneric(gtRoot, 3);
    i.insertGeneric(gtRoot, 4);

    // Add children to node 2
    GTNode<int>* node2 = gtRoot->getFirstChild();
    i.insertGeneric(node2, 5);
    i.insertGeneric(node2, 6);

    cout << "Generic Tree structure:\n";
    printGenericTree(gtRoot);
    cout << endl;

    // 2. TEST BINARY TREE
    cout << "2. Binary Tree Insertion (Level Order):\n";
    BTNode<int>* btRoot = nullptr;
    i.BTInsert(btRoot, 1);
    i.BTInsert(btRoot, 2);
    i.BTInsert(btRoot, 3);
    i.BTInsert(btRoot, 4);
    i.BTInsert(btRoot, 5);

    cout << "Inorder traversal: ";
    printInorder(btRoot);
    cout << "\n\n";

    // 3. TEST EXPRESSION TREE
    cout << "3. Expression Tree Insertion:\n";
    vector<char> postfix = { '2', '3', '+', '4', '*' }; // Represents (2+3)*4
    ETNode<int>* exprRoot = i.insertExpression(postfix);

    cout << "Expression tree for postfix '23+4*': ";
    printExpression(exprRoot);
    cout << "\n\n";

    // 4. TEST FULL BINARY TREE
    cout << "4. Full Binary Tree Insertion (0 or 2 children):\n";
    BTNode<int>* fullRoot = nullptr;
    i.fullInsert(fullRoot, 1);
    i.fullInsert(fullRoot, 2);
    i.fullInsert(fullRoot, 3);

    cout << "Full binary tree inorder: ";
    printInorder(fullRoot);
    cout << "\n\n";

    // 5. TEST PERFECT BINARY TREE
    cout << "5. Perfect Binary Tree Construction (height=2):\n";
    PNode<int>* perfectRoot = i.buildPerfect(2);

    cout << "Perfect tree nodes (preorder): ";
    printPerfectTree(perfectRoot);
    cout << "\n\n";

    // 6. TEST BINARY SEARCH TREE
    cout << "6. Binary Search Tree Insertion:\n";
    BTNode<int>* bstRoot = nullptr;
    bstRoot = i.BSTinsert(bstRoot, 50);
    bstRoot = i.BSTinsert(bstRoot, 30);
    bstRoot = i.BSTinsert(bstRoot, 70);
    bstRoot = i.BSTinsert(bstRoot, 20);
    bstRoot = i.BSTinsert(bstRoot, 40);
    bstRoot = i.BSTinsert(bstRoot, 60);
    bstRoot = i.BSTinsert(bstRoot, 80);

    cout << "BST inorder (should be sorted): ";
    printInorder(bstRoot);
    cout << "\n\n";

    // 7. TEST COMPLETE TREE (same as binary tree insertion)
    cout << "7. Complete Binary Tree Insertion:\n";
    BTNode<int>* completeRoot = nullptr;
    i.BTInsert(completeRoot, 10);
    i.BTInsert(completeRoot, 11);
    i.BTInsert(completeRoot, 12);
    i.BTInsert(completeRoot, 13);
    i.BTInsert(completeRoot, 14);

    cout << "Complete tree inorder: ";
    printInorder(completeRoot);
    cout << "\n\n";

    cout << "=== ALL TESTS COMPLETED ===\n";

    return 0;
}