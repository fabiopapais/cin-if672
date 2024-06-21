#include <iostream>
using namespace std;

class BSTNode {
public:
    BSTNode(int key): key(key) {
        height = 0;
        left = right = NULL;
    }

    int key;
    int height;
    BSTNode* left;
    BSTNode* right;
};

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

    void preorder() {
        preorderhelp(root);
    }

private:

    BSTNode* inserthelp(BSTNode* rt, int key) {
        if (rt == NULL) return new BSTNode(key);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key);
        } else {
            rt->right = inserthelp(rt->right, key);
        }
        // balancing
        rt->height = 1 + max(h(rt->left), h(rt->right));
        int balance = getBalance(rt);
        // rotations
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

    int getBalance(BSTNode* rt) {
        if (rt == NULL) return 0;
        return h(rt->left) - h(rt->right);
    }

    int h(BSTNode* rt) {
        if (rt == NULL) return -1;
        return rt->height;
    }

    BSTNode* rightRotate(BSTNode* rt) {
        BSTNode* l = rt->left;
        BSTNode* lr = l->right;
        l->right = rt;
        rt->left = lr;
        rt->height = max(h(rt->left), h(rt->right)) + 1;
        l->height = max(h(l->left), h(l->right)) + 1;
        return l;
    }

    BSTNode* leftRotate(BSTNode* rt) {
        BSTNode* r = rt->right;
        BSTNode* rl = r->left;
        r->left = rt;
        rt->right = rl;
        rt->height = max(h(rt->left), h(rt->right)) + 1;
        r->height = max(h(r->left), h(r->right)) + 1;
        return r;
    }

    void preorderhelp(BSTNode* rt) {
        if (rt != NULL) {
            cout << rt->key << endl;
            preorderhelp(rt->left);
            preorderhelp(rt->right);
        }
    }

    BSTNode* root;
    int nodecount;
};


int main() {
    int cases; cin >> cases;
    for (int i = 0; i < cases; i++) {
        int n_keys; cin >> n_keys;
        AVL avl = AVL();
        for (int j = 0; j < n_keys; j++) {
            int element; cin >> element;
            avl.insert(element);
        }
        avl.preorder();
        cout << "END" << endl;
    }
    return 0;
}