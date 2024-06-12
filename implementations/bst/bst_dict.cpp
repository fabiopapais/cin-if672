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

// int to int dict implemented as BST 
class BST {
public:
    // default constructor
    BST() {
        root = NULL;
        nodecount = 0;
    }

    // returns element with desired key or -1 if not found
    int find(int key) {
        return findhelp(root, key);
    }

    // inserts key with element at correct position in bst 
    void insert(int key, int element) {
        root = inserthelp(root, key, element);
        nodecount++;
    }
    
    // returns removed element if it exists;
    int remove(int key) {
        int temp = findhelp(root, key);
        if (temp != NOT_FOUND) {
            root = removehelp(root, key);
            nodecount--;
        }
        return temp;
    }

    // clears all nodes and frees memory
    void clear() {
        clearhelp(root);
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

    // prints tabulating each tree
    void pretty_print() {
        pretty_printhelp(root, 0);
    }

private:
    int findhelp(BSTNode* rt, int key) {
        if (rt == NULL) return NOT_FOUND;
        if (rt->key > key) {
            return findhelp(rt->left, key);
        } else if (rt->key == key) {
            return rt->element;
        }  else {
            return findhelp(rt->right, key);
        }
    }

    BSTNode* inserthelp(BSTNode* rt, int key, int element) {
        if (rt == NULL) return new BSTNode(key, element);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key, element);
        } else { // repeated keys go to right subtree
            rt->right = inserthelp(rt->right, key, element);
        }
        return rt;
    }

    BSTNode* removehelp(BSTNode* rt, int key) {
        if (rt == NULL) return NULL;
        if (rt->key > key) {
            rt->left = removehelp(rt->left, key);
        } else if (rt->key < key) {
            rt->right = removehelp(rt->right, key);
        } else { // if key is found
            if (rt->left == NULL) return rt->right; // 1. rt.left is NULL
            else if (rt->right == NULL) return rt->left; // 2. rt.right is NULL
            else { // 3. otherwise
                BSTNode* temp = getmin(rt->right); // searchs for imediate bigger key after rt
                rt->element = temp->element;
                rt->key = temp->key;
                rt->right = deletemin(rt->right);
            }
        }
        return rt;
    }

    BSTNode* getmin(BSTNode* rt) {
        if (rt->left == NULL) return rt;
        return getmin(rt->left);
    }

    BSTNode* deletemin(BSTNode* rt) {
        if (rt->left == NULL) {
            BSTNode* temp = rt->right;
            delete rt;
            return temp;
        }
        rt->left = deletemin(rt->left);
        return rt;
    }

    void clearhelp(BSTNode* rt) {
        if (rt != NULL) {
            clearhelp(rt->left);
            clearhelp(rt->right);
            delete rt;
        }
    }

    void preorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            cout << rt->key << ":" << rt->element << endl;
            preorder_printhelp(rt->left);
            preorder_printhelp(rt->right);
        }
    }

    void inorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            inorder_printhelp(rt->left);
            cout << rt->key << ":" << rt->element << endl;
            inorder_printhelp(rt->right);
        }
    }

    void posorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            posorder_printhelp(rt->left);
            posorder_printhelp(rt->right);
            cout << rt->key << ":" << rt->element << endl;
        }
    }

    void pretty_printhelp(BSTNode* rt, int iteration) {
        if (rt != NULL) {
            for (int i = 0; i < iteration; i++) {
                cout << "  ";
            }
            cout << rt->key << ":" << rt->element << endl;
            pretty_printhelp(rt->left, iteration + 1);
            pretty_printhelp(rt->right, iteration + 1);
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

    bst.remove(7);
    bst.remove(20);
    
    cout << "Pre order:" << endl;
    bst.preorder_print();

    cout << "In order:" << endl;
    bst.inorder_print();

    cout << "Post order:" << endl;
    bst.posorder_print();

    bst.pretty_print();

    bst.clear();
    
    return 0;
}