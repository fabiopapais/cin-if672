#include <bits/stdc++.h>
using namespace std;

bool calc(int sum, int n, int d, vector<int>& elements, vector<bool>& used) {
    if (sum == d) {
        return true;
    } else if (sum > d) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;
            if (calc(sum + elements[i], n, d, elements, used)) {
                return true;
            } else {
                used[i] = false;
            }
        }
    }
    return false;
}


int main() {
    int cases; cin >> cases;
    for (int i = 1; i <= cases; i++) {
        int n, d; cin >> n;
        vector<int> elements(n);
        for (int j = 0; j < n; j++) {
            int element; cin >> element;
            elements[j] = element;
        }

        cin >> d;

        if (d == 0) {
            cout << "Caso " << i << ": {}" << endl;
            continue;
        }

        vector<bool> used(n, false);
        calc(0, n, d, elements, used);

        bool first = true;

        for (int j = 0; j < n; j++) {
            if (used[j]) {
                if (first) {
                    cout << "Caso " << i << ": {" << elements[j];
                    first = false;
                } else {
                    cout << "," << elements[j];
                }
            }
        }
        if (!first) cout << "}" << endl;
        else {
            cout << "Caso " << i << ": -1" << endl;
        }


    }

    return 0;
}