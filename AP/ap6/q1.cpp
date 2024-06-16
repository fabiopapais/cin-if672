#include <stdio.h>
#include <iostream>
#include <list>
using namespace std;

class OpenHashTable {
public:
    OpenHashTable(int size) {
        m = size;
        cnt = 0;
        H = new list<long>[m];
    }
    
    // returns linked_list position if found and -1 otherwise
    long find(int key) {
        int pos = h(key);
        long i = 0;
        for (long item : H[pos]) {
            if (item == key) return i; 
            i++;
        }
        return -1;
    }

    // inserts element at table and end of linked list
    void insert(int key) {
        if (find(key) == -1) {
            int pos = h(key);
            H[pos].push_back(key);
        }
    }

    // removes element with specified key if it exists
    void remove(int key) {
        long find_pos = find(key);
        if (find_pos != -1) {
            int pos = h(key);
            auto it = H[pos].begin(); advance(it, find_pos);
            H[pos].erase(it);
        }
    }

    void free() {
        delete[] H;
    }

    list<long>* H;
private:
    int m;
    long cnt;
    long h(long key) { return abs(key) % m; }
};

int main() {
    OpenHashTable table(10);
    
    int qty; cin >> qty;
    for (int i = 0; i < qty; i++) {
        long current_item; cin >> current_item;
        table.insert(current_item);
    }

    for (int i = 0; i < 10; i++) {
        cout << i << " ";
        for (long item : table.H[i]) {
            cout << item << " ";
        }
        cout << endl;
    }

    table.free();
    return 0;
}