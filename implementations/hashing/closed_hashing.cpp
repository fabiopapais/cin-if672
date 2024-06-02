#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "hash_functions.hpp"
using namespace std;

struct cell {
    string key;
    string value;

    // constructor to initialize default values
    // value = 0 -> empty
    // value = 1 -> was filled (tombstone)
    cell() : key(""), value("0") {}
};

// string to string cpp closed-hashing dict
class ClosedHashDictionary {
public:
    // constructor
    ClosedHashDictionary(int size) {
        m = size;
        H = new cell[m];
        perm = create_perm(m);
    }

    // Probing function
    int probe(string key, int i) {
        // Linear probing
        // return i;

        // Quadratic probing
        // return ((i*i) + i) / 2;

        // Pseudo-random probing
        return perm[i - 1];

        // Double hashing
        // return i * h2(key);
    }

    // return position if true and -1 if false
    int find(string key) {
        return hash_search(key);
    }

    void insert(string key, string value) {
        if (cnt < m) {
            cout << "cheguei aqui";
            hash_insert(key, value);
        }
    }

    void remove(string key) {
        int pos = find(key);
        if (pos != -1) {
            cell new_cell; new_cell.key = ""; new_cell.value = "1";
            H[pos] = new_cell;
            cnt--;
        }
    }

    int get_size() { return m; }
    int get_count() { return cnt; }
    void clear() { delete[] H; }

    void print() {
        for (int i = 0; i < m; i++) {
            cout << "Position " << i << ": " << H[i].key << ":" << H[i].value << endl;
        }
    }

private:
    int m; // size of array
    int cnt = 0; // quantity of elements in dictionary
    cell *H; // hash table
    int h(string key) { // hash function for strings
        return sfold_h(key, m);
    }
    int h2(string key) { // optional double hash function
        return fold_h(key, m);
    }
    vector<int> perm; // permutation for pseudo-random probing

    // Creates arbitrary permutation array
    vector<int> create_perm(int size) {
        vector<int> temp_range(size);
        for (int i = 0; i < size; i++) temp_range[i] = i + 1;
        // stl functions to get randomness
        random_device rd;
        mt19937 g(rd());
        // shuffle the vector
        shuffle(temp_range.begin(), temp_range.end(), g);
        
        return temp_range;
    }

    // inserts key if not existent in hash table
    void hash_insert(string key, string value) {
        int initial_position;
        int pos = initial_position = h(key);
        for (int i = 1;
             (H[pos].key != "" && H[pos].value != "0") // cell is not empty
             && (i <= m);                              // prevents infty loop when array is full
             i++) {
            cout << pos << " ";
            pos = (initial_position + probe(key, i)) % m; // next on probe sequence
            if (H[pos].key == key) { // duplicates
                return;
            }
        }
        if (H[pos].key == "" && (H[pos].value == "0" || H[pos].value == "1")) { // ensuring cell is available
            cell new_cell;
            new_cell.key = key;
            new_cell.value = value;
            H[pos] = new_cell;
            cnt++;
        }
    }

    // searchs for key and returns position if exists or -1 otherwise
    int hash_search(string key) {
        int initial_position;
        int pos = initial_position = h(key);
        for (int i = 1;
             ((H[pos].key != key && H[pos].key != "")       // cell is not empty
              || (H[pos].key == "" && H[pos].value == "1")) // cell is empty, but was filled before
             && (i <= m);                                   // prevents infty loop when array is full
             i++) {
            pos = (initial_position + probe(key, i)) % m; // Next on probe sequence
        }
        if (key == H[pos].key) {
            return pos;
        } else {
            return -1; // k not in hash table
        }
    }
};

int main()
{
    ClosedHashDictionary hash_table(10);

    // Testing probing
    hash_table.insert("tstd", "1");
    hash_table.insert("ttsd", "2");
    hash_table.insert("sttd", "3");
    hash_table.insert("tsdt", "4");
    hash_table.print();

    // Testing overall inserts
    hash_table.insert("cin", "3");
    hash_table.insert("luxai", "4");
    hash_table.insert("zedamanga", "5");
    hash_table.insert("teste", "6");
    hash_table.insert("tst", "7");
    hash_table.insert("12345678910", "8"); // array full

    hash_table.insert("ASLKDJASKJDAKSLJDALKSDJASJDAJSLAK", "9");
    hash_table.insert("outroo", "6");
    hash_table.insert("rapaz", "asda");

    cout << "Dictionary before removal:" << endl;
    hash_table.print();

    hash_table.remove("teste");
    hash_table.remove("12345678910");
    hash_table.remove("12345"); // test removing element taht don't exist

    cout << "Dictionary after removal:" << endl;
    hash_table.print();

    cout << "Dictionary size: " << hash_table.get_size() << " | Elements count: " << hash_table.get_count() << endl;
    hash_table.clear();
}