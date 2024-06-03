#include <stdlib.h>
#include <iostream>
#include <string>
using namespace std;

#define EMPTYSTR "00000000000000000"

class ClosedHashTable {
public:
    // Constructor
    ClosedHashTable(int size) {
        m = size;
        cnt = 0;
        H = new string[m];
        for (int i = 0; i < m; i++) H[i] = EMPTYSTR; // initialize
    }

    // returns position if element is found and -1 otherwise
    int find(string key) {
        int initial_pos = h(key);
        int pos = initial_pos;
        bool continue_search = true;
        for (int i = 0;
             i < 20 && continue_search;
             i++
            ) {
                pos = abs(initial_pos + probe(i)) % m;
                if (key == H[pos]) {
                    continue_search = false;
                } else if (H[pos] == EMPTYSTR) {
                    continue_search = false;
                }
            }

        if (key == H[pos]) { // ensures position is found
            return pos;
        }
        return -1;
    }

    void insert(string key) {
        if (cnt < m && find(key) == -1) {
            int initial_pos = h(key);
            int pos = initial_pos;
            bool continue_search = true;
            for (int i = 0;
                 i < 20 && continue_search;
                 i++) {
                pos = abs(initial_pos + probe(i)) % m;
                if (H[pos] == EMPTYSTR || H[pos] == "empty") {
                    continue_search = false;
                }
            }
            if (H[pos] == EMPTYSTR || H[pos] == "empty") {
                H[pos] = key;
                cnt++;
            }
        }
    }
    
    void remove(string key) {
        int find_pos = find(key);
        if (find_pos != -1) {
            H[find_pos] = "empty";
            cnt--;
        }
    }

    void clear() {
        for (int i = 0; i < m; i++) H[i] = EMPTYSTR;
        cnt = 0;
    }

    int get_size() { return m; }
    int get_cnt() { return cnt; }
    void free() { delete[] H; }

    int m;
    int cnt;
    string* H;

private:
    int h(string key) {
        int sum = 0;
        for (int i = 0; i < key.size(); i++) {
            sum += (i + 1) * key[i];
        }
        sum *= 19;

        return abs(sum) % m;
    }

    int probe(int j) { return (j*j) + (23*j); };
};

int main() {
    int test_cases = 0; cin >> test_cases;
    ClosedHashTable table(101);
    for (int i = 0; i < test_cases; i++) {
        int operations = 0; cin >> operations;
        for (int j = 0; j < operations; j++) {
            string text; cin >> text;
            string command = text.substr(0, 3);
            string key;
            if (text.size() > 4) {
                key = text.substr(4);
            } else {
                key = "";
            }
            
            if (command == "ADD") {
                table.insert(key);
            } else {
                table.remove(key);
            }
        }
        cout << table.get_cnt() << endl;
        for (int i = 0; i < 101; i++) {
            if (table.H[i] != EMPTYSTR && table.H[i] != "empty") {
                cout << i << ":" << table.H[i] << endl;
            }
        }

        table.clear();
    }
    table.free();
    return 0;
}