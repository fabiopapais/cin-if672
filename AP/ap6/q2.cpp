#include <stdlib.h>
#include <iostream>
using namespace std;

class ClosedHashTable {
public:
    ClosedHashTable(int size) {
        m = size;
        cnt = 0;
        H = new string[m];
        for (int i = 0; i < m; i++) {
            H[i] = ""; // tombstone
        }
    }

    int probe(int i) { return i; }

    // returns pos if found and -1 otherwise
    int find(string key) {
        int pos = h(key);
        int initial_pos = pos;
        for (int i = 0;
             (key != H[pos] && i <= m); 
             i++) {
            pos = abs(initial_pos + probe(i)) % m;
        }
        if (H[pos] == key) return pos;
        else return -1;
    }

    void insert(string key) {
        if (cnt == m) return;

        int pos = h(key);
        int initial_pos = pos;
        for (int i = 0;
             (H[pos] != "" && i <= m); 
             i++) {
            pos = abs(initial_pos + probe(i)) % m;
        }
        if (H[pos] == "") {
            H[pos] = key;
            cnt++;
        }
    }

    void remove(string key) {
        int find_pos = find(key);
        if (find_pos != -1) {
            H[find_pos] = "";
            cnt--;
        }
    }

    void free() { delete[] H; }

    int m;
    int cnt;
private:
    string* H;
    int h(string key) {
        int sum = 0;
        for (int i = 0; i < key.size(); i++) {
            sum += key[i];
        }
        return abs(sum) % m;
    }
};

int main() {
    int qty = 0; cin >> qty;
    ClosedHashTable table(qty);

    string command = ""; ;
    while (true) {
        cin >> command;
        if (command == "fim") break;
        
        string key; cin >> key;

        if (command == "add") table.insert(key);
        else if (command == "sch") {
            cout << key << " " << table.find(key) << endl;
        } else if (command == "rmv") table.remove(key);
    }
    
    table.free();
    return 0;
}