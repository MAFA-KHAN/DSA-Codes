#include<iostream>
using namespace std;



//node class
template <typename T>
class Node {
    Node<T>* next;
    T data;
public:
    Node(T val):data(val),next(nullptr){}
    friend class TreeLL;
    friend class TreeQueue;
    friend class Tree;
};

//tree list
template <typename T>
class TreeLL {
    Node<T>* head;
    Node<T>* tail;
    int sz;
public:
    TreeLL():head(nullptr),tail(nullptr),sz(0){}

    bool isEmpty() const { return sz == 0; }

    int size() const { return sz; }

    void pushBack(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty())
            head = tail = newNode;
        else {
            tail->next = newNode;
            tail = newNode;
        }
        sz++;
    }

    void erase(T val) {
        if (isEmpty()) return;

        // delete at head
        if (head->data == val) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            sz--;
            if (sz == 0) tail = nullptr;
            return;
        }

        // delete in middle
        Node<T>* prev = head;
        Node<T>* curr = head->next;

        while (curr != nullptr && curr->data != val) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == nullptr) return; 

        prev->next = curr->next;
        if (curr == tail) tail = prev;

        delete curr;
        sz--;
    }

    Node<T>* begin() const {
        return head;
    }
};

//treequeue
template<typename T>
class TreeQueue {
    Node<T>* frontPtr;
    Node<T>* backPtr;
    int sz;
public:
    TreeQueue() : frontPtr(nullptr), backPtr(nullptr), sz(0) {}

    bool isEmpty() const { return sz == 0; }

    void enqueue(T val) {
        Node<T>* newNode = new Node<T>(val);
        if (isEmpty())
            frontPtr = backPtr = newNode;
        else {
            backPtr->next = newNode;
            backPtr = newNode;
        }
        sz++;
    }

    void dequeue() {
        if (isEmpty()) return;
        Node<T>* temp = frontPtr;
        frontPtr = frontPtr->next;
        if (frontPtr == nullptr) backPtr = nullptr;
        delete temp;
        sz--;
    }

    T front() const {
        if (isEmpty()) return T();
        return frontPtr->data;
    }
};

//class tree

template <typename T>
class Tree {
    T value;
    Tree<T>* parentNode;
    TreeLL<Tree<T>*> children;
public:
    Tree(T val, Tree<T>* p = nullptr) {
        value = val;
        parentNode = p;
    }
    bool isRoot() const { return parentNode == nullptr; }

    bool isLeaf() const { return children.size() == 0; }

    int degree() const { return children.size(); }

    Tree<T>* child(int n) {
        if (n < 0 || n >= degree()) return nullptr;

        Node<Tree<T>*>* ptr = children.begin();
        for (int i = 0; i < n; i++)
            ptr = ptr->next;

        return ptr->data;
    }

    void insert(T val) {
        Tree<T>* newChild = new Tree<T>(val, this);
        children.pushBack(newChild);
    }

    void attach(Tree<T>* tree) {
        if (!tree->isRoot()) tree->detach();
        tree->parentNode = this;
        children.pushBack(tree);
    }

    void detach() {
        if (isRoot()) return;
        parentNode->children.erase(this);
        parentNode = nullptr;
    }

    int size() {
        int total = 1;

        Node<Tree<T>*>* ptr = children.begin();
        while (ptr != nullptr) {
            total += ptr->data->size();
            ptr = ptr->next;
        }

        return total;
    }
    int height() {
        if (isLeaf()) return 0;

        int h = 0;
        Node<Tree<T>*>* ptr = children.begin();

        while (ptr != nullptr) {
            h = max(h, 1 + ptr->data->height());
            ptr = ptr->next;
        }

        return h;
    }

    void BreadthFirstTraversal() {
        TreeQueue<Tree<T>*> q;
        q.enqueue(this);

        while (!q.isEmpty()) {
            Tree<T>* node = q.front();
            q.dequeue();

            cout << node->value << " ";

            Node<Tree<T>*>* c = node->children.begin();
            while (c != nullptr) {
                q.enqueue(c->data);
                c = c->next;
            }
        }
    }

    void DepthFirstTraversal() {
        cout << value << " ";

        Node<Tree<T>*>* c = children.begin();
        while (c != nullptr) {
            c->data->DepthFirstTraversal();
            c = c->next;
        }
    }
};

//main
int main() {

    

    Tree<int>* root = new Tree<int>(1);

    root->insert(2);
    root->insert(3);
    root->insert(4);

    Tree<int>* node3 = root->child(1);

    node3->insert(5);
    node3->insert(6);

    cout << "DFS: ";
    root->DepthFirstTraversal();
    cout << endl;

    cout << "BFS: ";
    root->BreadthFirstTraversal();
    cout << endl;

    cout << "Tree size = " << root->size() << endl;
    cout << "Tree height = " << root->height() << endl;

    return 0;
}


//      Perfect Binary Tree



template <typename T>
class BTNode {

    T data;
    BTNode<T>* left;
    BTNode<T>* right;
    public:
    BTNode(T val) : data(val), left(nullptr), right(nullptr) {}
    friend class BinaryTree;
};
template <typename T>
 class QNode {
        T data;
        QNode* next;
        QNode(T d) : data(d), next(nullptr) {}
        public:
        friend class Queue;
    };

template <typename T>
class Queue {

    QNode* frontPtr;
    QNode* backPtr;

public:
    Queue() : frontPtr(nullptr), backPtr(nullptr) {}

    bool empty() { return frontPtr == nullptr; }

    void push(T val) {
        QNode* n = new QNode(val);
        if (empty()) frontPtr = backPtr = n;
        else {
            backPtr->next = n;
            backPtr = n;
        }
    }

    void pop() {
        if (empty()) return;
        QNode* t = frontPtr;
        frontPtr = frontPtr->next;
        delete t;
        if (frontPtr == nullptr) backPtr = nullptr;
    }

    T front() { return frontPtr->data; }
};

template <typename T>
class BinaryTree {
private:
    BTNode<T>* root;

public:
    BinaryTree() : root(nullptr) {}

    BTNode<T>* getRoot() { return root; }

    void setRoot(T val) {
        root = new BTNode<T>(val);
    }

    BTNode<T>* insertLeft(BTNode<T>* parent, T val) {
        parent->left = new BTNode<T>(val);
        return parent->left;
    }

    BTNode<T>* insertRight(BTNode<T>* parent, T val) {
        parent->right = new BTNode<T>(val);
        return parent->right;
    }

    int height(BTNode<T>* node) {
        if (node == nullptr) return -1;
        return 1 + max(height(node->left), height(node->right));
    }

    int countNodes(BTNode<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    int countLeaves(BTNode<T>* node) {
        if (node == nullptr) return 0;
        if (!node->left && !node->right) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    int countInternal(BTNode<T>* node) {
        if (node == nullptr || (!node->left && !node->right))
            return 0;
        return 1 + countInternal(node->left) + countInternal(node->right);
    }

    bool search(BTNode<T>* node, T key) {
        if (node == nullptr) return false;
        if (node->data == key) return true;
        return search(node->left, key) || search(node->right, key);
    }


    void preorder(BTNode<T>* node) {   // N L R
        if (!node) return;
        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void inorder(BTNode<T>* node) {    // L N R
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void postorder(BTNode<T>* node) {  // L R N
        if (!node) return;
        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    void levelOrder() {
        if (!root) return;
        Queue<BTNode<T>*> q;
        q.push(root);

        while (!q.empty()) {
            BTNode<T>* n = q.front();
            q.pop();
            cout << n->data << " ";

            if (n->left) q.push(n->left);
            if (n->right) q.push(n->right);
        }
    }


    void reverseLevelOrder() {
        if (!root) return;

        Queue<BTNode<T>*> q;
        BTNode<T>* stack[1000];
        int top = -1;

        q.push(root);

        while (!q.empty()) {
            BTNode<T>* n = q.front();
            q.pop();
            stack[++top] = n;

            if (n->right) q.push(n->right);
            if (n->left) q.push(n->left);
        }

        while (top >= 0) {
            cout << stack[top--]->data << " ";
        }
    }


    void zigZag() {
        if (!root) return;

        BTNode<T>* stack1[1000]; // left to right
        BTNode<T>* stack2[1000]; // right to left
        int top1 = -1, top2 = -1;

        stack1[++top1] = root;

        while (top1 >= 0 || top2 >= 0) {

            while (top1 >= 0) {
                BTNode<T>* n = stack1[top1--];
                cout << n->data << " ";

                if (n->left) stack2[++top2] = n->left;
                if (n->right) stack2[++top2] = n->right;
            }

            while (top2 >= 0) {
                BTNode<T>* n = stack2[top2--];
                cout << n->data << " ";

                if (n->right) stack1[++top1] = n->right;
                if (n->left)  stack1[++top1] = n->left;
            }
        }
    }

    BTNode<T>* mirror(BTNode<T>* node) {
        if (!node) return nullptr;
        mirror(node->left);
        mirror(node->right);
        swap(node->left, node->right);
        return node;
    }


    void destroy(BTNode<T>* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    ~BinaryTree() { destroy(root); }
};
int main() {
    

    BinaryTree<int> bt;
    bt.setRoot(1);

    BTNode<int>* r = bt.getRoot();
    BTNode<int>* n2 = bt.insertLeft(r, 2);
    BTNode<int>* n3 = bt.insertRight(r, 3);

    bt.insertLeft(n2, 4);
    bt.insertRight(n2, 5);

    bt.insertRight(n3, 6);

    cout << "Preorder: ";
    bt.preorder(bt.getRoot());
    cout << "\n";

    cout << "Inorder: ";
    bt.inorder(bt.getRoot());
    cout << "\n";

    cout << "Postorder: ";
    bt.postorder(bt.getRoot());
    cout << "\n";

    cout << "Level Order: ";
    bt.levelOrder();
    cout << "\n";

    cout << "Reverse Level: ";
    bt.reverseLevelOrder();
    cout << "\n";

    cout << "ZigZag: ";
    bt.zigZag();
    cout << "\n";

    cout << "Height: " << bt.height(bt.getRoot()) << "\n";
    cout << "Total nodes: " << bt.countNodes(bt.getRoot()) << "\n";
    cout << "Leaves: " << bt.countLeaves(bt.getRoot()) << "\n";
    cout << "Internal nodes: " << bt.countInternal(bt.getRoot()) << "\n";

    cout << "Search 5: " << (bt.search(bt.getRoot(), 5) ? "Found" : "Not Found") << "\n";

    return 0;
}