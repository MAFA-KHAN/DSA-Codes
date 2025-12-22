#include <iostream>
#include <queue>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
};

// Create new node
Node* newNode(int value) {
    Node* temp = new Node();
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Insert node (simple left-first method)
Node* insert(Node* root, int value) {
    if (root == NULL)
        return newNode(value);

    if (root->left == NULL)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

/* -------- DFS TRAVERSALS -------- */

// Inorder DFS
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

/* -------- BFS TRAVERSAL -------- */

// Level Order (BFS)
void bfs(Node* root) {
    if (root == NULL) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left != NULL)
            q.push(curr->left);

        if (curr->right != NULL)
            q.push(curr->right);
    }
}

// Height of tree
int height(Node* root) {
    if (root == NULL) return -1;
    return max(height(root->left), height(root->right)) + 1;
}

// Size of tree
int size(Node* root) {
    if (root == NULL) return 0;
    return size(root->left) + size(root->right) + 1;
}

// Degree of node
int nodeDegree(Node* node) {
    if (node == NULL) return 0;
    int deg = 0;
    if (node->left) deg++;
    if (node->right) deg++;
    return deg;
}

// Max degree of tree
int treeDegree(Node* root) {
    if (root == NULL) return 0;
    return max(nodeDegree(root),
        max(treeDegree(root->left), treeDegree(root->right)));
}

// MAIN
int main() {
    Node* root = NULL;

    root = insert(root, 1);
    insert(root, 2);
    insert(root, 3);
    insert(root, 4);
    insert(root, 5);

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

    return 0;
}
