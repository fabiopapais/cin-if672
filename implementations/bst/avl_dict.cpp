#include <stdlib.h>
#include <iostream>
using namespace std;

#define NOT_FOUND -1

// int to int dict element
class BSTNode {
public:
    BSTNode(int key, int element): key(key), element(element) {
        left = right = NULL;
        height = 0;
    }

    int key;
    int element;
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

    // returns NOT_FOUND if not found or element otherwise
    int find(int key) { 
        BSTNode* temp = findhelp(root, key);
        if (temp == NULL) return NOT_FOUND;
        return temp->element; 
    }

    // inserts key with element at correct position in bst 
    void insert(int key, int element) {
        root = inserthelp(root, key, element);
        nodecount++;
    }

    int remove(int key) {
        BSTNode* temp = findhelp(root, key);
        if (temp != NULL) {
            root = removehelp(root, key);
            nodecount--;
            return temp->element;
        }
        return NOT_FOUND;
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
    BSTNode* findhelp(BSTNode* rt, int key) {
        if (rt == NULL) return NULL;
        if (rt->key > key) {
            return findhelp(rt->left, key);
        } else if (rt->key == key) {
            return rt;
        } else {
            return findhelp(rt->right, key);
        }
    }

    BSTNode* inserthelp(BSTNode* rt, int key, int element) {
        if (rt == NULL) return new BSTNode(key, element);
        if (rt->key > key) {
            rt->left = inserthelp(rt->left, key, element);
        } else { // repeated elements into the right
            rt->right = inserthelp(rt->right, key, element);
        }
        // rotation (balance)
        rt->height = 1 + max(h(rt->left), h(rt->right));
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
        // rotation (balance)
        rt->height = 1 + max(h(rt->left), h(rt->right));
        int balance = getBalance(rt);
        if (balance > 1) { // left heavy
            if (getBalance(rt->left) >= 0) return rightRotate(rt);
            else { // LR-rotation
                rt->left = leftRotate(rt->left);
                return rightRotate(rt);
            }
        } else if (balance < -1) { // right heavy
            if (getBalance(rt->right) <= 0) {
                return leftRotate(rt);
            }
            else { // RL-rotation
                rt->right = rightRotate(rt->right);
                return leftRotate(rt);
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
        // making rotation
        l->right = rt;
        rt->left = lr;
        // calculating heights
        rt->height = 1 + max(h(rt->left), h(rt->right));
        l->height = 1 + max(h(l->left), h(l->right));

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

        return r;
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
        } else {
            for (int i = 0; i < iteration; i++) {
                cout << "  ";
            }
            cout << "empty" << endl;
        }
    }

    BSTNode* root;
    int nodecount;
};

int main() {
    int n; cin >> n;
    AVL avl = AVL();
    for (int i = 0; i < n; i++) {
        int current_key; cin >> current_key;
        avl.insert(current_key, 0);
    }

    avl.pretty_print();

    avl.remove(2);

    avl.pretty_print();

    avl.remove(3);

    avl.pretty_print();
}