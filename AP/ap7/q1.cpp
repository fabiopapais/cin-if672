#include <stdlib.h>
#include <iostream>
using namespace std;

#define NOT_FOUND -1;

class BSTNode {
public:
    BSTNode(int key): key(key) {
        left = right = NULL;
    }

    int key;
    BSTNode* left;
    BSTNode* right;
};

class BST {
public:
    BST() {
        root = NULL;
        nodecount = 0;
    }

    int find(int key) {
        return findhelp(root, key);
    }

    void insert(int key) {
        root = inserthelp(root, key);
        nodecount++;
    }

    void preorder() { 
        preorderhelp(root); 
        cout << endl;
    }
    void inorder() { 
        inorderhelp(root); 
        cout << endl;
    }
    void posorder() { 
        posorderhelp(root); 
        cout << endl;
    }

private:
    int findhelp(BSTNode* rt, int key) {
        if (rt == NULL) return NOT_FOUND;
        if (rt->key > key) {
            return findhelp(rt->left, key);
        } else if (rt->key == key) {
            return rt->key;
        } else {
            return findhelp(rt->right, key);
        }
    }

    BSTNode* inserthelp(BSTNode* rt, int key) {
        if (rt == NULL) return new BSTNode(key);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key);
        } else {
            rt->right = inserthelp(rt->right, key);
        }
        return rt;
    }

    void preorderhelp(BSTNode* rt) {
        if (rt != NULL) {
            cout << rt->key << " ";
            preorderhelp(rt->left);
            preorderhelp(rt->right);
        }
    }
    void inorderhelp(BSTNode* rt) {
        if (rt != NULL) {
            inorderhelp(rt->left);
            cout << rt->key << " ";
            inorderhelp(rt->right);
        }
    }
    void posorderhelp(BSTNode* rt) {
        if (rt != NULL) {
            posorderhelp(rt->left);
            posorderhelp(rt->right);
            cout << rt->key << " ";
        }
    }

    BSTNode* root;
    int nodecount;
};

int main() {
    int operations; cin >> operations;
    BST bst = BST();
    for (int i = 0; i < operations; i++) {
        string command; cin >> command;
        if (command == "insert") {
            int element_to_add; cin >> element_to_add;
            bst.insert(element_to_add); 
        } else if (command == "pre") {
            bst.preorder();
        } else if (command == "in") {
            bst.inorder();
        } else if (command == "post") {
            bst.posorder();
        }
    }
    return 0;
}