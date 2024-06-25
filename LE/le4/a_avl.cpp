#include <stdlib.h>
#include <iostream>
using namespace std;

class BSTNode {
public:
    BSTNode(int key): key(key) {
        left = right = NULL;
        height = 0;
        size = 1;
    }

    int key;
    int height;
    int size;
    BSTNode* left;
    BSTNode* right;
};

class AVL {
public:
    AVL() {
        root = NULL;
        nodecount = 0;
    }

    int find(int key) {
        return findhelp(root, key, 0);
    }

    void insert(int key) {
        root = inserthelp(root, key);
        nodecount++;
    }

    BSTNode* root;
    int nodecount;

    int findhelp(BSTNode* rt, int key, int current_index) {
        if (rt == NULL) return -1;
        if (rt->key > key) {
            return findhelp(rt->left, key, current_index);
        } else if (rt->key == key) {
            return current_index + size(rt->left) + 1;
        } else {
            current_index += size(rt->left) + 1;
            return findhelp(rt->right, key, current_index);
        }
    }
    

    BSTNode* inserthelp(BSTNode* rt, int key) {
        if (rt == NULL) return new BSTNode(key);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key);
        } else { // repeated elements into the right
            rt->right = inserthelp(rt->right, key);
        }
        // updating height and size
        rt->height = 1 + max(h(rt->left), h(rt->right));
        rt->size = 1 + size(rt->left) + size(rt->right);
        // rotation (balance)
        int balance = getBalance(rt);
        if (balance < -1 && key >= rt->right->key) return leftRotate(rt); // L-rotation
        if (balance > 1 && key < rt->left->key) return rightRotate(rt); // R-rotation
        if (balance > 1 && key >= rt->left->key) { // LR-rotation
            rt->left = leftRotate(rt->left);
            return rightRotate(rt);
        }
        if (balance < -1 && key < rt->right->key) { // RL-rotation
            rt->right = rightRotate(rt->right);
            return leftRotate(rt);
        }
        return rt;

    }

    int getBalance(BSTNode* rt) {
        if (rt == NULL) return 0;
        return h(rt->left) - h(rt->right);
    }

    int h(BSTNode* rt) {
        if (rt == NULL) return -1;
        return rt->height;
    }

    int size(BSTNode* rt) {
        return (rt == NULL) ? 0 : rt->size;
    }

    BSTNode* rightRotate(BSTNode* rt) {
        BSTNode* l = rt->left;
        BSTNode* lr = l->right;
        // making rotation
        l->right = rt;
        rt->left = lr;
        // calculating heights
        rt->height = 1 + max(h(rt->left), h(rt->right));
        l->height = 1 + max(h(l->left), h(l->right));
        // calculating sizes
        rt->size = size(rt->left) + size(rt->right) + 1;
        l->size = size(l->left) + size(l->right) + 1;

        return l;
    }

    BSTNode* leftRotate(BSTNode* rt) {
        BSTNode* r = rt->right;
        BSTNode* rl = r->left;
        // making rotation
        r->left = rt;
        rt->right = rl;
        // calculating heights
        rt->height = 1 + max(h(rt->left), h(rt->right));
        r->height = 1 + max(h(r->left), h(r->right));
        // calculating sizes
        rt->size = size(rt->left) + size(rt->right) + 1;
        r->size = size(r->left) + size(r->right) + 1;

        return r;
    }

};

int main() {
    int queries; cin >> queries;
    AVL avl = AVL();
    for (int i = 0; i < queries; i++) {
        int flag, element; cin >> flag; cin >> element;
        if (flag == 1) { 
            avl.insert(element); 
        } else {
            int result = avl.find(element);
            if (result == -1) {
                cout << "Data tidak ada" << endl;
            } else {
                cout << result << endl;
            }
        }
    }
    return 0;
}