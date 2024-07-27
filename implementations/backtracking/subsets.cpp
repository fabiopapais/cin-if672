#include <bits/stdc++.h>
using namespace std;

int subsets = 0;

bool calc_min(int sum, int d, int n, vector<int>& set, vector<bool>& used) {
    if (sum == d) {
        subsets++;
        return true;
    }

    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = true;
            if (calc_min(sum + set[i], d, n, set, used)) {
                return true;
            }
            used[i] = false;
        }
    }
    return false;
}

int main() {
    int cases, n, d;
    cin >> cases;
    for (int i = 0; i < cases; i++) {
        cin >> n;
        vector<int> set(n);
        for (int j = 0; j < n; j++) {
            cin >> set[j];
        }
        cin >> d;

        vector<bool> used(n, false); // if current number was used on current sum
        calc_min(0, d, n, set, used);

        cout << subsets << endl;
        subsets = 0;
    }

    return 0;
}