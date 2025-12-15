#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;



template <typename T>
class Tree {
public:
    T value;                          
    Tree<T>* parent;                  
    vector<Tree<T>*> children;       

 
    Tree(T v) {
        value = v;
        parent = nullptr;
    }


    void insert(T v) {
        Tree<T>* node = new Tree<T>(v);
        node->parent = this;
        children.push_back(node);
    }


    Tree<T>* child(int n) {
        if (n < 0 || n >= children.size()) return nullptr;
        return children[n];
    }

    
    void BFS() {
        queue<Tree<T>*> q;
        q.push(this);

        while (!q.empty()) {
            Tree<T>* node = q.front();
            q.pop();

            cout << node->value << " ";

            for (auto c : node->children)
                q.push(c);
        }
    }

    void DFS() {
        cout << value << " ";
        for (auto c : children)
            c->DFS();
    }
};



int main() {

   
    Tree<char>* root = new Tree<char>('A');  

    root->insert('M');                     
    root->child(0)->insert('RA');            
    root->child(0)->child(0)->insert('H');  
    root->child(0)->child(0)->child(0)->insert('A');
    root->child(0)->child(0)->child(0)->child(0)->insert('M');

    cout << "BREADTH-FIRST (BFS): ";
    root->BFS();
    cout << "\n";

    cout << "DEPTH-FIRST (DFS): ";
    root->DFS();
    cout << "\n";

    return 0;
}
