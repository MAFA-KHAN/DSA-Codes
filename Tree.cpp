#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
class Tree {
private:
    T value;                           ab 
    Tree<T>* parent;                  
    vector<Tree<T>*> children;        

public:

   
    Tree(T val = T(), Tree<T>* p = nullptr) {
        value = val;
        parent = p;
    }

    
    T getValue() const { return value; }
    Tree<T>* getParent() const { return parent; }
    int degree() const { return children.size(); }
    bool isRoot() const { return parent == nullptr; }
    bool isLeaf() const { return children.empty(); }

    
    Tree<T>* child(int n) const {
        if (n < 0 || n >= degree()) return nullptr;
        return children[n];
    }

  
    void insert(T const& obj) {
        Tree<T>* node = new Tree<T>(obj, this);
        children.push_back(node);
    }

   
    void attach(Tree<T>* subtree) {
        if (subtree == nullptr) return;

      
        if (!subtree->isRoot()) {
            subtree->detach();
        }

        subtree->parent = this;
        children.push_back(subtree);
    }


    void detach() {
        if (isRoot()) return;

       
        vector<Tree<T>*>& siblings = parent->children;

        for (unsigned i = 0; i < siblings.size(); i++) {
            if (siblings[i] == this) {
                siblings.erase(siblings.begin() + i);
                break;
            }
        }
        parent = nullptr;
    }

   
    int size() const {
        int s = 1; 
        for (unsigned i = 0; i < children.size(); i++)
            s += children[i]->size();
        return s;
    }


    int height() const {
        if (children.empty())
            return 0;

        int h = 0;
        for (unsigned i = 0; i < children.size(); i++) {
            int child_h = children[i]->height();
            if (child_h + 1 > h)
                h = child_h + 1;
        }
        return h;
    }

  
    void BFS() const {
        queue<const Tree<T>*> q;
        q.push(this);

        while (!q.empty()) {
            const Tree<T>* node = q.front();
            q.pop();

            cout << node->value << " ";

            for (unsigned i = 0; i < node->children.size(); i++)
                q.push(node->children[i]);
        }
    }

    void DFS_recursive() const {
        cout << value << " ";
        for (unsigned i = 0; i < children.size(); i++)
            children[i]->DFS_recursive();
    }

    
    void DFS_stack() const {
        stack<const Tree<T>*> st;
        st.push(this);

        while (!st.empty()) {
            const Tree<T>* node = st.top();
            st.pop();

            cout << node->value << " ";

           
            for (int i = node->children.size() - 1; i >= 0; i--)
                st.push(node->children[i]);
        }
    }
};

int main() {

    Tree<string>* root = new Tree<string>("A");

    root->insert("B");
    root->insert("C");
    root->insert("D");

    root->child(0)->insert("E");
    root->child(0)->insert("F");
    root->child(2)->insert("G");

    cout << "BFS: ";
    root->BFS();
    cout << "\n";

    cout << "DFS Recursive: ";
    root->DFS_recursive();
    cout << "\n";

    cout << "DFS Stack: ";
    root->DFS_stack();
    cout << "\n";

    cout << "Size = " << root->size() << "\n";
    cout << "Height = " << root->height() << "\n";

    return 0;
}
