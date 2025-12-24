#include <iostream>
using namespace std;

// BST Node structure
struct Node {
    int data;          // value stored in node
    Node* left;        // pointer to left child
    Node* right;       // pointer to right child
};

// Create a new node
Node* newNode(int value) {
    Node* temp = new Node();   // allocate memory
    temp->data = value;        // set data
    temp->left = NULL;         // left child empty
    temp->right = NULL;        // right child empty
    return temp;
}

// Insert node in BST (iterative)
Node* insert(Node* root, int value) {
    if (root == NULL)
        return newNode(value);

    Node* curr = root;

    while (true) {
        if (value < curr->data) {
            if (curr->left == NULL) {
                curr->left = newNode(value);
                break;
            }
            curr = curr->left;
        }
        else {
            if (curr->right == NULL) {
                curr->right = newNode(value);
                break;
            }
            curr = curr->right;
        }
    }
    return root;
}

// Inorder traversal (for checking result)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// ITERATIVE DELETE FUNCTION
Node* deleteNode(Node* root, int key) {

    Node* parent = NULL;   // to store parent of current node
    Node* curr = root;     // start from root

    // STEP 1: Search the node to delete
    while (curr != NULL && curr->data != key) {
        parent = curr;    // move parent
        if (key < curr->data)
            curr = curr->left;
        else
            curr = curr->right;
    }

    // If key not found
    if (curr == NULL)
        return root;

    // STEP 2: Case 1 & 2 ? Node has 0 or 1 child
    if (curr->left == NULL || curr->right == NULL) {

        Node* child;

        // choose the existing child
        if (curr->left != NULL)
            child = curr->left;
        else
            child = curr->right;

        // if deleting root node
        if (parent == NULL) {
            delete curr;
            return child;
        }

        // connect parent to child
        if (parent->left == curr)
            parent->left = child;
        else
            parent->right = child;

        delete curr;
    }

    // STEP 3: Case 3 ? Node has 2 children
    else {
        Node* succParent = curr;       // parent of successor
        Node* succ = curr->right;      // inorder successor

        // find leftmost node in right subtree
        while (succ->left != NULL) {
            succParent = succ;
            succ = succ->left;
        }

        // copy successor value to current node
        curr->data = succ->data;

        // delete successor node
        if (succParent->left == succ)
            succParent->left = succ->right;
        else
            succParent->right = succ->right;

        delete succ;
    }

    return root;
}

// MAIN FUNCTION
int main() {
    Node* root = NULL;

    root = insert(root, 50);
    insert(root, 30);
    insert(root, 70);
    insert(root, 20);
    insert(root, 40);
    insert(root, 60);
    insert(root, 80);

    cout << "BST Inorder before deletion: ";
    inorder(root);

    root = deleteNode(root, 50);

    cout << "\nBST Inorder after deleting 50: ";
    inorder(root);

    return 0;
}
