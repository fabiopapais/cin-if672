#include <bits/stdc++.h>
using namespace std;

#define EMPTY -1

class DS {
public:
    DS(int size) {
        for (int i = 0; i < size; i++) {
            A[i] = EMPTY;
        }
    }

    int find(int curr) {
        if (A[curr] == EMPTY) return curr;
        A[curr] = find(A[curr]);
        return A[curr];
    }

    void union_set(int a, int b) {
        int root1 = find(a); int root2 = find(b);
        if (root1 != root2) {
            A[root2] = root1;
        }
    }

    unordered_map<int, int> A;
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
        cout << ds.A[i] << " ";
    }
    cout << endl;

    return 0;
}