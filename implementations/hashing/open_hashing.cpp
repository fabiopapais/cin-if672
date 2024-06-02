#include <stdlib.h>
#include <iostream>
#include <list>
#include "hash_functions.hpp"
using namespace std;

struct node {
    string key;
    string value;
};

// string to string cpp open-hashing dict
class OpenHashDictionary {
public:
    // constructor
    OpenHashDictionary(int size) {
        m = size; // set the size of the array
        H = new list<node>[m](); // create an array of empty lists of strings
    }

    bool find(string key) {
        int pos = h(key);
        for (node current_node : H[pos]) {
            if (current_node.key == key) {
                return true;
            }
        }
        return false;
    }

    void insert(string key, string value) {
        if (!find(key)) {
            int pos = h(key);
            node new_node = { .key = key, .value = value };
            H[pos].push_back(new_node);
            cnt++;
        }
    }

    void remove(string key) {
        int pos = h(key);
        for (auto it = H[pos].begin(); it != H[pos].end(); it++) {
            if (it->key == key) {
                H[pos].erase(it);
                cnt--;
                return;
            }
        }
    }

    void print() {
        for (int i = 0; i < m; i++) {
            cout << "Position " << i << ": ";
            for (node current_node : H[i]) {
                cout << current_node.key << ":" << current_node.value << " -> ";
            }
            cout << endl;
        }
    }

    int m; // size of array
    int cnt = 0; // quantity of elements in dictionary

private:
    list<node>* H; // hash table
    int h(string key) { // hash function for strings
        return sfold_h(key, m);
    }
};

int main() {
    OpenHashDictionary hash_table(5);

    hash_table.insert("tst", "1");
    hash_table.insert("uau", "2");
    hash_table.insert("cin", "3");
    hash_table.insert("luxai", "4");
    hash_table.insert("zedamanga", "5");
    hash_table.insert("teste", "6");
    hash_table.insert("tst", "7");
    hash_table.insert("12345678910", "8");
    hash_table.insert("ASLKDJASKJDAKSLJDALKSDJASJDAJSLAK", "9");
    
    cout << "Dictionary before removal:" << endl;
    hash_table.print();

    hash_table.remove("teste");
    hash_table.remove("12345678910");

    cout << "Dictionary after removal:" << endl;
    hash_table.print();

    cout << "Dictionary size: " << hash_table.m << " | Elements count: " << hash_table.cnt << endl;
}