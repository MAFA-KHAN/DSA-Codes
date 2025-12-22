#include <iostream>
#include <queue>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Create node
Node* newNode(int value) {
    Node* temp = new Node();
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Insert in BST
Node* insert(Node* root, int value) {
    if (root == NULL)
        return newNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

/* -------- DFS -------- */

// Inorder DFS (sorted)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Preorder DFS
void preorder(Node* root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Postorder DFS
void postorder(Node* root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

/* -------- BFS -------- */

// Level Order Traversal
void bfs(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left)
            q.push(curr->left);

        if (curr->right)
            q.push(curr->right);
    }
}

// Height
int height(Node* root) {
    if (root == NULL) return -1;
    return max(height(root->left), height(root->right)) + 1;
}

// Size
int size(Node* root) {
    if (root == NULL) return 0;
    return size(root->left) + size(root->right) + 1;
}

// Search
bool search(Node* root, int key) {
    if (root == NULL) return false;
    if (root->data == key) return true;

    if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Find minimum
Node* findMin(Node* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete node
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Degree
int nodeDegree(Node* node) {
    if (node == NULL) return 0;
    int deg = 0;
    if (node->left) deg++;
    if (node->right) deg++;
    return deg;
}

// Max degree
int treeDegree(Node* root) {
    if (root == NULL) return 0;
    return max(nodeDegree(root),
        max(treeDegree(root->left), treeDegree(root->right)));
}

// MAIN
int main() {
    Node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "DFS Inorder: ";
    inorder(root);

    cout << "\nDFS Preorder: ";
    preorder(root);

    cout << "\nDFS Postorder: ";
    postorder(root);

    cout << "\nBFS Level Order: ";
    bfs(root);

    cout << "\nHeight: " << height(root);
    cout << "\nSize: " << size(root);
    cout << "\nMax Degree: " << treeDegree(root);

    cout << "\nSearch 40: " << (search(root, 40) ? "Found" : "Not Found");

    root = deleteNode(root, 70);
    cout << "\nAfter Deleting 70 (Inorder): ";
    inorder(root);

    return 0;
}
