#include <stdlib.h>
#include <iostream>
using namespace std;

class BSTNode {
public:
    BSTNode(int key): key(key) {
        left = right = NULL;
        height = 0;
    }

    int key;
    int height;
    BSTNode* left;
    BSTNode* right;
};    

// AVL int tree
class AVL {
public:
    AVL() {
        root = NULL;
        nodecount = 0;
    }

    void insert(int key) {
        root = inserthelp(root, key);
        nodecount++;
    }

    void preorder_print() {
        preorder_printhelp(root);
        cout << endl;
    }

    void inorder_print() {
        inorder_printhelp(root);
        cout << endl;
    }

    void posorder_print() {
        posorder_printhelp(root);
        cout << endl;
    }


private:

    BSTNode* inserthelp(BSTNode* rt, int key) {
        if (rt == NULL) return new BSTNode(key);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key);
        } else {
            rt->right = inserthelp(rt->right, key);
        }
        // rotation (balance)
        rt->height = 1 + max(h(rt->left), h(rt->right));
        int balance = getBalance(rt);
        if (balance < -1 && key >= rt->right->key) return leftRotate(rt);
        if (balance > 1 && key < rt->left->key) return rightRotate(rt);
        if (balance > 1 && key >= rt->left->key) {
            rt->left = leftRotate(rt->left);
            return rightRotate(rt);
        }
        if (balance < -1 && key < rt->right->key) {
            rt->right = rightRotate(rt->right);
            return leftRotate(rt);
        }
        return rt;
    }

    BSTNode* rightRotate(BSTNode* rt) {
        BSTNode* l = rt->left;
        BSTNode* lr = l->right;
        l->right = rt;
        rt->left = lr;
        rt->height = 1 + max(h(rt->left), h(rt->right));
        l->height = 1 + max(h(l->left), h(l->right));
        return l;
    }

    BSTNode* leftRotate(BSTNode* rt) {
        BSTNode* r = rt->right;
        BSTNode* rl = r->left;
        r->left = rt;
        rt->right = rl;
        rt->height = 1 + max(h(rt->left), h(rt->right));
        r->height = 1 + max(h(r->left), h(r->right));
        return r;
    }

    int getBalance(BSTNode* rt) {
        if (rt == NULL) return 0;
        return h(rt->left) - h(rt->right);
    }

    int h(BSTNode* rt) {
        if (rt == NULL) return -1;
        return rt->height;
    }

    void preorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            cout << rt->key << " ";
            preorder_printhelp(rt->left);
            preorder_printhelp(rt->right);
        }
    }

    void inorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            inorder_printhelp(rt->left);
            cout << rt->key << " ";
            inorder_printhelp(rt->right);
        }
    }

    void posorder_printhelp(BSTNode* rt) {
        if (rt != NULL) {
            posorder_printhelp(rt->left);
            posorder_printhelp(rt->right);
            cout << rt->key << " ";
        }
    }

    BSTNode* root;
    int nodecount;
};

int main() {
    int operations; cin >> operations;
    AVL avl = AVL();
    for (int i = 0; i < operations; i++) {
        string command; cin >> command;
        if (command == "insert") {
            int value; cin >> value;
            avl.insert(value);
        } else if (command == "pre") {
            avl.preorder_print();
        } else if (command == "post") {
            avl.posorder_print();
        } else if (command == "in") {
            avl.inorder_print();
        }
    }
    return 0;
}