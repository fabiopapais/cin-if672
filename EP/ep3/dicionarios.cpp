#include <stdlib.h>
#include <iostream>
#include <cmath>
using namespace std;

struct cell {
    int key;
    int value;
    int empty; // -1: was empty, 1: empty, 0: not empty 
};

class ClosedHashTable {
public:

    ClosedHashTable(int size) {
        m = size;
        cnt = 0;
        H = new cell[m];
        for (int i = 0; i < m; i++) {
            H[i].key = 0;
            H[i].value = 0;
            H[i].empty = 1;
        }
        perm = new int[m - 1];
    }

    // returns position if found and -1 otherwise
    int find(int key) {
        int initial_pos = h(key);
        if (H[initial_pos].key == key) {
            return initial_pos;
        }
        int pos = initial_pos;
        bool continue_search = true;
        for (int i = 1;
            i <= m && continue_search;
            i++) {
                pos = abs(initial_pos + probe(i)) % m;
                if (H[pos].key == key && H[pos].empty == 0) {
                    continue_search = false;
                }
        }
        if (H[pos].key == key) { // ensure key is found
            return pos;
        }
        return -1;
    }

    void insert(int key, int value) {
        if (cnt >= m) {
            return;
        } 
        int initial_pos = h(key);
        if (H[initial_pos].empty == 1) {
            H[initial_pos].key = key;
            H[initial_pos].value = value;
            H[initial_pos].empty = 0;
            cnt++;
            return;
        }
        int pos = initial_pos;
        bool continue_search = true;
        for (int i = 1;
            i <= m && continue_search;
            i++) {
                pos = abs(initial_pos + probe(i)) % m;
                if (H[pos].empty == 1) {
                    continue_search = false;
                }
        }
        if (H[pos].empty == 1) {
            H[pos].key = key;
            H[pos].value = value;
            H[pos].empty = 0;
            cnt++;
        }
    }

    int* perm; // due to implementation
    cell* H;

    void print() {
        for (int i = 0; i < m; i++) {
            cout << i << " " << H[i].key << ":" << H[i].value << "  " << H[i].empty << endl;
        }
    }

    void print_perm() {
        for (int i = 0; i < m - 1; i++) {
            cout << perm[i] << endl;
        }
    }
     
private:
    int m;
    int cnt;

    int h(int key) {
        //  h(k) = k − (m * floor(k/m))
        int temp = (int) floor(((double) key) / ((double) m));
        return abs(key - (m * temp));
    }

    int probe(int i) { return perm[i - 1]; }
};


int main() {
    int m;
    while (true) {
        cin >> m;
        if (m == 0) { break; }

        ClosedHashTable table(m);
        // read perm array
        for (int i = 0; i < m - 1; i++) {
            cin >> table.perm[i];
        }

        
        int n_operations; cin >> n_operations;
        for (int i = 0; i < n_operations; i++) {
            string command; cin >> command;
            if (command == "add") {
                int key, value;
                cin >> key; cin >> value;
                table.insert(key, value);
            } else if (command == "find") {
                int key; cin >> key;
                int pos = table.find(key);
                if (pos != -1) {
                    cout << pos << " " << table.H[pos].value << endl;
                } else {
                    cout << -1 << endl;
                }
            }
        }
        
    }
    return 0;
}