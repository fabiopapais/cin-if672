#include <bits/stdc++.h>
using namespace std;

int coin_row(int n, vector<int>& C, vector<int>& F) {
    F[0] = 0; F[1] = C[1];
    for (int i = 2; i <= n; i++) {
        F[i] = max(C[i] + F[i - 2], F[i - 1]);
    }
    return F[n];
}

int main() {
    int cases; cin >> cases;
    for (int i = 1; i <= cases; i++) {
        int n; cin >> n;

        if (n == 0) {
            cout << "Caso " << i << ": 0=0" << endl;
            continue;
        }

        vector<int> coins(n + 1);
        for (int j = 1; j <= n; j++) {
            cin >> coins[j];
        }
        vector<int> F(n + 1, 0);

        int sum = coin_row(n, coins, F);

        vector<int> used_coins;
        for (int j = n; j > 0; j) {
            if (F[j] == F[j - 1]) {
                j--;
            } else {
                used_coins.push_back(coins[j]);
                j -= 2;
            }
        }

        cout << "Caso " << i << ": ";

        for (int j = used_coins.size() - 1; j > 0; j--) {
            cout << used_coins[j] << "+";
        }
        cout << used_coins[0] << "=";

        cout << sum << endl;

    }
    return 0;
}