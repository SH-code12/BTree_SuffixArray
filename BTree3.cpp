#include <bits/stdc++.h>

using namespace std;

template <class T, int order>
class BNode {
public:
    vector<T> keys;
    vector<BNode<T, order>*> childrens;
    bool isLeaf;
    BNode<T, order>* parentNode;

    BNode() {
        isLeaf = true;
        parentNode = nullptr;
        keys.resize(0);
        childrens.resize(0);
    }
};

template <class T, int order>
class BTree {
private:
    BNode<T, order>* root;

    void split(BNode<T, order>* parent, int index) {
        BNode<T, order>* child = parent->childrens[index];
        BNode<T, order>* newChild = new BNode<T, order>();
        int midIndex = (order - 1) / 2;

        // Promote the middle key to the parent
        T midKey = child->keys[midIndex];
        parent->keys.insert(parent->keys.begin() + index, midKey);

        // Assign keys and children to the new child
        newChild->keys.assign(child->keys.begin() + midIndex + 1, child->keys.end());
        child->keys.resize(midIndex);

        if (!child->isLeaf) {
            newChild->childrens.assign(child->childrens.begin() + midIndex + 1, child->childrens.end());
            child->childrens.resize(midIndex + 1);

            for (auto& grandChild : newChild->childrens) {
                grandChild->parentNode = newChild;
            }
        }

        // Update parent's children
        parent->childrens.insert(parent->childrens.begin() + index + 1, newChild);
        newChild->isLeaf = child->isLeaf;
        newChild->parentNode = parent;
    }

    void insertNonFull(BNode<T, order>* node, T key) {
        if (node->isLeaf) {
            // Insert key into the leaf node
            node->keys.insert(upper_bound(node->keys.begin(), node->keys.end(), key), key);
        } else {
            // Find the child to descend
            int i = upper_bound(node->keys.begin(), node->keys.end(), key) - node->keys.begin();
            if (node->childrens[i]->keys.size() == order - 1) {
                split(node, i);
                if (key > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->childrens[i], key);
        }
    }

    void traverse(BNode<T, order>* node, int level = 0) {
        if (!node) return;

        for (int i = 0; i < level; ++i) cout << "  ";

        for (size_t i = 0; i < node->keys.size(); ++i) {
            cout << node->keys[i];
            if (i < node->keys.size() - 1) cout << ",";
        }
        cout << "\n";

        if (!node->isLeaf) {
            for (size_t i = 0; i < node->childrens.size(); ++i) {
                traverse(node->childrens[i], level + 1);
            }
        }
    }

public:
    BTree() {
        root = new BNode<T, order>();
    }

    void Insert(T key) {
        if (root->keys.size() == order) {
            BNode<T, order>* newRoot = new BNode<T, order>();
            newRoot->isLeaf = false;
            newRoot->childrens.push_back(root);
            root->parentNode = newRoot;
            split(newRoot, 0);
            root = newRoot;
        }
        insertNonFull(root, key);
    }

    void Print() {
        traverse(root);
    }
};

int main() {
    BTree<int, 4> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print(); // Should output the following on the screen:
    /*
    1,4
      0
      2,3
      5
    */
    cout << "\n";

    BTree<char, 5> t2;
    t2.Insert('G');
    t2.Insert('I');
    t2.Insert('B');
    t2.Insert('J');
    t2.Insert('C');
    t2.Insert('A');
    t2.Insert('K');
    t2.Insert('E');
    t2.Insert('D');
    t2.Insert('S');
    t2.Insert('T');
    t2.Insert('R');
    t2.Insert('L');
    t2.Insert('F');
    t2.Insert('H');
    t2.Insert('M');
    t2.Insert('N');
    t2.Insert('P');
    t2.Insert('Q');
    t2.Print();
    return 0;
}
