#include <iostream>
using namespace std;

template <typename T, int order>
class Node {
public:
    T keys[order - 1];       // Keys in the node (order - 1 keys)
    Node* children[order];   // Pointers to child nodes (order children)
    int keyCount;            // Current number of keys
    bool isLeafNode;         // True if leaf node

    // Constructor
    Node(bool isLeafNode = true) {
        this->isLeafNode = isLeafNode;
        keyCount = 0;
        for (int i = 0; i < order; ++i) {  // Initialize children array to nullptr
            children[i] = nullptr;
        }
    }
};

template <typename T, int order>
class BTree {
private:
    Node<T, order>* root;

    // Split the child of a node
    void split(Node<T, order>* parentNode, int childIndex) {
        Node<T, order>* fullChildNode = parentNode->children[childIndex];
        Node<T, order>* newChildNode = new Node<T, order>(fullChildNode->isLeafNode);

        int midIndex = (order - 1) / 2;

        // Copy second half of keys from fullChildNode to newChildNode
        newChildNode->keyCount = fullChildNode->keyCount - midIndex - 1;
        for (int i = 0; i < newChildNode->keyCount; ++i) {
            newChildNode->keys[i] = fullChildNode->keys[midIndex + 1 + i];
        }

        // If not a leaf, copy second half of children
        if (!fullChildNode->isLeafNode) {
            for (int i = 0; i <= newChildNode->keyCount; ++i) {
                newChildNode->children[i] = fullChildNode->children[midIndex + 1 + i];
            }
        }

        // Reduce the key count of fullChildNode
        fullChildNode->keyCount = midIndex;

        // Shift parent's children and insert newChildNode
        for (int i = parentNode->keyCount; i > childIndex; --i) {
            parentNode->children[i + 1] = parentNode->children[i];
        }
        parentNode->children[childIndex + 1] = newChildNode;

        // Shift parent's keys and insert middle key
        for (int i = parentNode->keyCount - 1; i >= childIndex; --i) {
            parentNode->keys[i + 1] = parentNode->keys[i];
        }
        parentNode->keys[childIndex] = fullChildNode->keys[midIndex];

        parentNode->keyCount++;
    }

    // Insert into a node that is not full
    void insertIntoNonFullNode(Node<T, order>* currentNode, T key) {
        int insertIndex = currentNode->keyCount - 1;

        if (currentNode->isLeafNode) {
            // Insert key into the correct position in the leaf node in sorted order
            while (insertIndex >= 0 && key < currentNode->keys[insertIndex]) {
                currentNode->keys[insertIndex + 1] = currentNode->keys[insertIndex];
                insertIndex--;
            }
            currentNode->keys[insertIndex + 1] = key;  // Insert the key at the correct position
            currentNode->keyCount++;
        } else {
            // Find the child to descend into
            while (insertIndex >= 0 && key < currentNode->keys[insertIndex]) {
                insertIndex--;
            }
            insertIndex++;

            // Split the child if full
            if (currentNode->children[insertIndex]->keyCount == order) { // Check if the child is full
                split(currentNode, insertIndex);
                // After splitting, check which child the new key should go into
                if (key > currentNode->keys[insertIndex]) {
                    insertIndex++;
                }
            }
            // Recursively insert the key into the appropriate child
            insertIntoNonFullNode(currentNode->children[insertIndex], key);
        }
    }

    // Traverse and print the tree
    void traverseTree(Node<T, order>* currentNode, int level = 0) {
        if (currentNode == nullptr) return;

        // Print current level
        for (int i = 0; i < level; ++i) cout << "  ";
        for (int i = 0; i < currentNode->keyCount; ++i) {
            cout << currentNode->keys[i];
            if (i < currentNode->keyCount - 1) cout << ",";
        }
        cout << endl;

        // Recursively print child nodes
        if (!currentNode->isLeafNode) {
            for (int i = 0; i <= currentNode->keyCount; ++i) {
                traverseTree(currentNode->children[i], level + 1);
            }
        }
    }

public:
    BTree() {
        root = nullptr;
    }

    // Insert a key into the BTree
    void insert(T key) {
        if (root == nullptr) {
            root = new Node<T, order>(true);
            root->keys[0] = key;
            root->keyCount = 1;
        } else {
            if (root->keyCount == order) {
                Node<T, order>* newRoot = new Node<T, order>(false);
                newRoot->children[0] = root;
                split(newRoot, 0);
                root = newRoot;
            }
            insertIntoNonFullNode(root, key);
        }
    }

    // Print the BTree
    void print() {
        traverseTree(root);
    }
};

int main() {
    BTree<int, 3> intTree;
    intTree.insert(1);
    intTree.insert(5);
    intTree.insert(0);
    intTree.insert(4);
    intTree.insert(3);
    intTree.insert(2);
    intTree.print();

    BTree<char, 5> charTree; // Construct a BTree of order 5, which stores char data
    charTree.insert('G');
    charTree.insert('I');
    charTree.insert('B');
    charTree.insert('J');
    charTree.insert('C');
    charTree.insert('A');
    charTree.insert('K');
    charTree.insert('E');
    charTree.insert('D');
    charTree.insert('S');
    charTree.insert('T');
    charTree.insert('R');
    charTree.insert('L');
    charTree.insert('F');
    charTree.insert('H');
    charTree.insert('M');
    charTree.insert('N');
    charTree.insert('P');
    charTree.insert('Q');
    charTree.print(); // Should output the tree in the correct structure

    return 0;
}
