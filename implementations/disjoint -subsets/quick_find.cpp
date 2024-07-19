#include <bits/stdc++.h>
using namespace std;

// simple disjoint subset quick find implementation
class DS {
public:
    DS(int size) {
        for (int i = 0; i < size; i++) {
            R[i] = i;
            sets[i] = new vector<int>;
            sets[i]->push_back(i);
        }
    }

    int find(int curr) {
        return R[curr];
    }

    void union_set(int a, int b) {
        int root1 = find(a), root2 = find(b);
        if (root1 != root2) {
            vector<int>* l1 = sets[root1]; vector<int>* l2 = sets[root2];
            if (l1->size() < l2->size()) swap(l1, l2); // ensures l1 is bigger
            // updates representatives
            for (int i = 0; i < l2->size(); i++) {
                R[l2->at(i)] = l1->at(0);
            }
            // concats two lists
            l1->insert(l1->end(), l2->begin(), l2->end());
            l2->clear();
        }
    }
    unordered_map<int, int> R; // representatives
    unordered_map<int, vector<int>*> sets; // set of lists
};

int main() {
    DS ds = DS(6);

    ds.union_set(0, 3);
    ds.union_set(3, 4);
    ds.union_set(0, 1);

    ds.union_set(2, 5);

    if (ds.find(0) == ds.find(4)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    for (int i = 0; i < 6; i++) {
        cout << ds.R[i] << " ";
    }
    cout << endl;

    return 0;
}