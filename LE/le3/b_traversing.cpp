#include <stdlib.h>
#include <iostream>
using namespace std;

#define NOT_FOUND -1

// int to int bst node 
class BSTNode {
public:
    BSTNode(int key, int element) {
        this->key = key;
        this->element = element;
        left = right = NULL;
    }

    int key;
    int element;
    BSTNode* left;
    BSTNode* right;
};

// BSTNode* create_BSTNode(int key, int element) {
//     BSTNode* n = new BSTNode(key, element);
//     return n;
// }

// int to int dict implemented as BST 
class BST {
public:
    // default constructor
    BST() {
        root = NULL;
        nodecount = 0;
    }

    // inserts key with element at correct position in bst 
    void insert(int key, int element) {
        root = inserthelp(root, key, element);
        nodecount++;
    }

    void preorder_print() {
        preorder_printhelp(root);
    }

    void inorder_print() {
        inorder_printhelp(root);
    }

    void posorder_print() {
        posorder_printhelp(root);
    }


private:

    BSTNode* inserthelp(BSTNode* rt, int key, int element) {
        if (rt == NULL) return new BSTNode(key, element);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key, element);
        } else { // repeated keys go to right subtree
            rt->right = inserthelp(rt->right, key, element);
        }
        return rt;
    }

    void preorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            cout << " " << rt->key;
            preorder_printhelp(rt->left);
            preorder_printhelp(rt->right);
        }
    }

    void inorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            inorder_printhelp(rt->left);
            cout << " " << rt->key;
            inorder_printhelp(rt->right);
        }
    }

    void posorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            posorder_printhelp(rt->left);
            posorder_printhelp(rt->right);
            cout << " " << rt->key;
        }
    }

    BSTNode* root;
    int nodecount;
};

int main() {
    int n; cin >> n;
    BST bst = BST();
    for (int i = 0; i < n; i++) {
        int current_key; cin >> current_key;
        bst.insert(current_key, 0);
    }
    
    cout << "Pre order :";
    bst.preorder_print();
    cout << endl;

    cout << "In order  :";
    bst.inorder_print();
    cout << endl;

    cout << "Post order:";
    bst.posorder_print();
    cout << endl;

    return 0;
}