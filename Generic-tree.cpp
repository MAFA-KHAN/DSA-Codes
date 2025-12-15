// TREES	(GENERIC TREE , BINARY TREE , PERFECT BINARY TREE)
/*
Herarcical: as many children
-leaf nodes : specifically zero childrens
-branches: connection of a node with a node
-Siblings: same parent
-Levels: nodes count
-Height: total levels , depth , count of levels from root to leaf node having heighest level
-Subtree: small part of tree (left subtree , right subtree), define in the context of the node
*/
/*
A perfect binary tree means:
-Every internal node has exactly 2 children
-All leaf nodes are at the same level (same depth)
-Total nodes = 2^(h+1) - 1
-Levels must be filled completely.
-Always fill left to right.
PROPERTIES:
1. Number of levels(height h) :  h = log2(n + 1) - 1
2. Total nodes :  N = 2 ^ (h + 1) - 1
3. Number of leaf nodes :   Leaf nodes = 2 ^ h
4. Number of internal nodes :
Internal nodes = N - leafNodes = 2 ^ (h + 1) - 1 - 2 ^ h
*/
/*GENERIC TREE
Every node stores :
-value
-pointer to parent
-list of children(using Linked List)
-Each node has its own list of children
*/


#include<iostream>
using namespace std;

template <typename T>
class Node {
	T data;
	Node<T>* next;
public:
	Node(T val) :data(val), next(nullptr) {}
	friend class List;
	friend class Queue;
	friend class BinaryTree;
};


template <typename T>
class List {
	Node<T>* head;
	Node<T>* tail;
	int sz;
public:
	List() {
		head = tail = nullptr;
		sz = 0;
	}
	int size() {
		return sz;
	}
	bool isempty() {
		return sz == 0;
	}
	void pushback(T val) {
		Node<T>* newNode = new Node<T>(val);
		if (isempty()) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}
		sz++;
	}

	T erase(T val) {
		if (isempty()) {
			return;
		}
		//delete at head
		if (head->data == val) {
			Node<T>* temp = head;
			head = head->next;
			delete temp;
			sz--;
			if (sz == 0) {
				tail = nullptr;
			}
			return;
		}
		//delete in middle
		Node<T>* prev = head;
		Node<T>* cur = head->next;
		while (cur != nullptr && cur->data != val) {
			prev = cur;
			cur = cur->next;
		}
		if (cur == nullptr) {
			cout << "Not found." << endl;
			return;
		}
		prev->next = cur->next;
		if (cur == tail) {
			tail = prev;
		}
		delete cur;
		sz--;
	}
	Node<T>* begin() {
		return head;
	}
	friend class Queue;
	friend class BinaryTree;
};


template <typename T>
class Queue {
	Node<T>* ifront;
	Node<T>* iback;
	int size;
public:
	Queue() :ifront(nullptr), iback(nullptr), size(0) {}

	bool isempty() {
		return size == 0;
	}
	void enqueue(T val) {
		Node<T>* newNode = new Node<T>(val);
		if (isempty()) {
			ifront = iback = newNode;
		}
		else {
			iback->next = newNode;
			iback = newNode;
		}
		size++;
	}
	void dequeue() {
		if (isempty()) {
			return;
		}
		Node<T>* temp = ifront;
		ifront = ifront->next;
		if (ifront == nullptr) {
			iback = nullptr;
		}
		delete temp;
		size--;
	}
	T front() {
		if (isempty()) {
			return;
		}
		return ifront->data;
	}
	friend class BinaryTree;
};


template <typename T>			//Generic Tree
class Tree {
	T value;
	Node<T>* root;
	Node<T>* parentNode;
	List<Tree<T>*> children;
public:
	Tree(T val) {
		parentNode = nullptr;
		value = val;
	}
	bool isRoot() {
		return  parentNode == nullptr;
	}
	bool isleaf() {
		return children.size() == 0;			//calling size of list
	}
	int degree() {					//count of children
		return children.size();
	}

	Tree<T>* child(int n) {
		if (n < 0 || n >= degree) {
			return nullptr;
		}
		Node<Tree<T>*>* ptr = children.begin();			//calling begin of List
		for (int i = 0; i < n; i++) {
			ptr = ptr->next;
		}
		return ptr->data;
	}

	void insert(T val) {
		Tree<T>* newChild = new Tree<T>(val);		//creating nodes
		newChild->parentNode = this;
		children.pushback(newChild);			//calling pushback of List
	}

	void attach(Tree<T>* tree) {			//attaching subtrees
		if (!tree->isRoot()) {
			tree->detach();
		}
		tree->parentNode = this;
		children.pushback(tree);
	}

	void detach() {
		if (isRoot()) {
			return;
		}
		parentNode->children.erase(this);		//erase of List
		parentNode == nullptr;
	}
	int Size() {
		int total = 1;
		Node<Tree<T>*>* ptr = children.begin();
		while (ptr != nullptr) {
			total += ptr->data->size();
			ptr = ptr->next;
		}
		return total;
	}
	int height() {
		if (isleaf()) {
			return 0;
		}
		int h = 0;
		Node<Tree<T>*>* ptr = children.begin();
		while (ptr != nullptr) {
			h = max(h, 1 + ptr->data->height());		//recursive call
			ptr = ptr->next;
		}
		return h;
	}
	void BreadthFirstTraversal() {
		Queue<Tree<T>*> q;
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


template <typename T>
class BTNode {
	T data;
	Node<T>* left;
	Node<T>* right;
public:
	BTNode(T val) :data(val), left(nullptr), right(nullptr) {}
	friend class BinaryTree;
};


template <typename T>			// Almost complete binary tree
class BinaryTree {
	BTNode<T>* root;
public:
	BinaryTree() {
		root = left = right = nullptr;
	}
	BTNode<T>* getRoot() {
		return root;
	}
	void insert(T val) {
		BTNode<T>* newNode = new BTNode<T>(val);
		if (root == nullptr) {
			root = newNode;
			return;
		}
		Queue<BTNode*> q;
		q.enqueue(root);//root ko queue mein daal diya, taake hum tree ko level by level traverse karein (jaise BFS).

		while (!q.isempty()) {
			BTNode<T>* temp = q.front();
			q.dequeue();//ek ek node ko line se bahar laa kar check kar rahe hain.
			if (temp->left == nullptr) {
				temp->left = newNode;
				return;
			}
			else {
				q.enqueue(temp->left);//Agar left already filled hai, to us left child ko queue mein push kar do.
			}
			if (temp->right == nullptr) {
				temp->right = newNode;
				return;
			}
			else {
				q.enqueue(temp->right);
			}
		}
	}
	//  TREE TRAVERSALS (preorder, inorder, postorder, level order)

	//PRE-ORDER
	void preorder(BTNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		cout << node->data << " ";
		preorder(node->left);
		preorder(node->right);
	}
	//IN-ORDER
	void inorder(BTNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		inorder(node->left);
		cout << node->data << " ";
		inorder(node->right);
	}
	//POST-ORDER
	void postorder(BTNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		postorder(node->left);
		postorder(node->right);
		cout << node->data << " ";
	}
	//LEVEL-ORDER
	void levelorder(BTNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		Queue<BTNode*> q;
		q.enqueue(root);
		while (!q.isempty()) {
			BTNode<T>* temp = q.front();
			q.dequeue();
			cout << temp->data << " ";
			if (temp->left != nullptr) {
				q.enqueue(temp->left);
			}
			if (temp->right != nullptr) {
				q.enqueue(temp->right);
			}
		}
	}
	int height(BTNode<T>* node) {
		if (node == nullptr) {
			return 0;
		}
		int left_h = height(node->left);
		int right_h = height(node->right);
		return 1 + max(left_h, right_h);
	}
	int size(Node<T>* node) {
		if (node == nullptr) {
			return 0;
		}
		return 1 + size(node->left) + size(node->right);
	}
	int countleaves(BTNode<T>* node) {
		if (node == nullptr) {
			return 0;
		}
		if (node->left == nullptr && node->right == nullptr) {
			return 1;
		}
		return countleaves(node->left) + countleaves(node->right);
	}
	int countInternals(BTNode<T>* node) {		//(NON-LEAF) NODES
		if (node == nullptr) {
			return 0;
		}
		if (node->left == nullptr && node->right == nullptr) {
			return 0;
		}
		return 1 + countInternals(node->left) + countInternals(node->right);
	}
	bool search(BTNode<T>* node, T key) {
		if (node == nullptr) return false;
		if (node->data == key) return true;
		return search(node->left, key) || search(node->right, key);
	}

	//Mirror Tree
	void mirror(BTNode<T>* node) {
		if (node == nullptr) {
			return;
		}
		swap(node->left, node->right);
		mirror(node->left);
		mirror(node->right);
	}
	void deleteTree(BTNode<T>* node) {		//(Postorder style: Left, Right, Root)
		if (node == nullptr) {
			return;
		}
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
	~BinaryTree() {
		deleteTree(root);
	}
};


template <typename T>			//Perfect binary tree
class PerfectBinaryTree {

};


int main() {


	return 0;
}