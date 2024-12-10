#include <bits/stdc++.h>

using namespace std;


template<class T, int order>
class BNode{
public:
 BNode* parentNode;

    vector<T> keys;
    bool isLeaf;
    vector<BNode<T,order>*> childrens;
    BNode(){
        isLeaf = false;
        parentNode = nullptr;
        keys.resize(0);
        childrens.resize(0);
    }

};

template<class T, int order>
class BTree{
private:
    BNode <T,order> * root ;

    // parentNode splitted its parentNode added to previous and back of neghibors
    void split(BNode<T,order> * originalNode, T midIndex, int indxnewParent = 0) {
        // get midIndex of child from the parentNode
        // Move Keys and Children to the New Node
        BNode<T,order> *  newnode = new BNode<T,order> ();

        for(int i =midIndex; i < originalNode->childrens[indxnewParent]->keys.size(); i++){
            newnode->keys.push_back(originalNode->childrens[indxnewParent]->keys[i]);

            if(!originalNode->childrens[indxnewParent]->isLeaf){
                newnode->childrens.push_back(originalNode->childrens[indxnewParent]->childrens[midIndex + 1]);}
            // Remove Key from the Original Node
            originalNode->childrens[indxnewParent]->keys.erase(originalNode->childrens[indxnewParent]->keys.begin() + midIndex);
            // Remove Child Pointer if Not a Leaf
            if(!originalNode->childrens[indxnewParent]->isLeaf){
                originalNode->childrens[indxnewParent]->childrens.erase(originalNode->childrens[indxnewParent]->childrens.begin() + midIndex + 1);}
            i--;
        }
        newnode->parentNode = originalNode;
        if(!originalNode->childrens[indxnewParent]->isLeaf)
            newnode->childrens.push_back(originalNode->childrens[indxnewParent]->childrens.back());
        if(originalNode->childrens.back()->isLeaf)
            newnode->isLeaf = 1;
        originalNode->childrens.insert(originalNode->childrens.begin() + indxnewParent + 1, newnode);
        if(!originalNode->childrens[indxnewParent]->isLeaf)
            originalNode->childrens[indxnewParent]->childrens.pop_back();

    }

    BNode <T,order>*  findKey(T key){
        BNode<T,order>* ptr = root;
        bool found =0;
        while(!found && ptr != nullptr && !ptr->isLeaf){
            for(int i =0; i < ptr-> keys.size()  ; i++){
                if(key < ptr->keys[i]){
                    if(!ptr->childrens.empty() && ptr->childrens[i] != nullptr) {
                        ptr = ptr->childrens[i];

                        found = 1;
                        break;
                    }
                    else {
                        found =1;
                        break;
                    }
                }
            }
            if(!found && !ptr->childrens.empty())
            {ptr = ptr->childrens.back();}
        }
        return ptr;
    }
    void traverse(BNode<T, order>* node, int level = 0) {
        if (node == nullptr) return;

        // Print current level
        for (int i = 0; i < level; ++i){
            cout << "  ";}

        // Print the keys of the current parentNode
        for (int i = 0; i < node->keys.size(); ++i) {
            cout << node->keys[i];
            if (i < node->keys.size() - 1) cout << ",";
        }
        cout << "\n";

        // Recursively print child nodes if not a isLeaf
        if (!node->isLeaf) {
            for (int i = 0; i < node->childrens.size(); ++i) {
                traverse(node->childrens[i], level + 1);
            }
        }
    }
public:
    BTree(){
        root = nullptr;
    }
    void Insert(T key){
        BNode<T,order>* targetNode = findKey(key);
        T tempKey = key;

        while(targetNode != nullptr && targetNode->keys.size() == order - 1 ) {
            vector<T> sorted = targetNode->keys;

            sorted.push_back(tempKey);
            sort(sorted.begin(),sorted.end());
            if(sorted.size()==order) {
                tempKey = sorted[order / 2];

                sorted.erase(find(sorted.begin(), sorted.end(), tempKey));

                targetNode->keys = sorted;
                if(targetNode->parentNode != nullptr){
                    int i =0;

                    for(auto child : targetNode->parentNode->childrens){
                        if(child == targetNode){
                            split(targetNode->parentNode, order / 2 , i);
                        }
                        i++;
                    }
                }
                else {
                    BNode<T, order> *newRoot = new BNode<T, order>;
                    newRoot->childrens.push_back(targetNode);
                    targetNode->parentNode = newRoot;
                    root = newRoot;
                    split(targetNode->parentNode, order / 2 );

                }
            }else{
                targetNode->keys = sorted;
                break;
            }

            targetNode = targetNode->parentNode;
        }
        if(targetNode == nullptr) {
            BNode<T, order> *newRoot = new BNode<T, order>;
            if (root == nullptr)
                newRoot->isLeaf = 1;
            newRoot->keys.push_back(tempKey);
            targetNode = newRoot;
            root = newRoot;
        }
        else{

            targetNode->keys.push_back(tempKey);
            sort(targetNode->keys.begin(), targetNode->keys.end());

        }
    }

    void Print() {
        traverse(root);
    }

};

int main(){
    BTree<int,3> t1;
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
    cout<<"\n";
    BTree <char,5> t; // Construct a BTree of order 5, which stores char data, Look at the example in our lecture:
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print();
}
