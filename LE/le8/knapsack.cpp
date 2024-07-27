#include <bits/stdc++.h>
using namespace std;

/* bottom_up 
int knapsack(int n, int W, vector<int> w, vector<int> v, vector<vector<int>>& F) {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= W; j++) {
            if (i == 0 || j == 0) F[i][j] = 0;
            else if (w[i] <= j) {
                F[i][j] = max(F[i - 1][j], v[i] + F[i - 1][j - w[i]]);
            } else {
                F[i][j] = F[i - 1][j];
            }
        }
    }
    return F[n][W];
}
*/

// top-down
int knapsack(int i, int j, vector<int> w, vector<int> v, vector<vector<int>>& F) {
    if (F[i][j] < 0) {
        int value;
        if (j < w[i]) {
            value = knapsack(i - 1, j , w, v, F); 
        } else {
            value = max(knapsack(i - 1, j, w, v, F), v[i] + knapsack(i - 1, j - w[i], w, v, F));
        }
        F[i][j] = value;
    }
    return F[i][j];
}

int main() {
    int capacity; int n_items; cin >> capacity >> n_items;
    vector<int> weights(n_items + 1);
    vector<int> sizes(n_items + 1);
    for (int i = 1; i <= n_items; i++) {
        int weight, size; cin >> weight >> size;
        weights[i] = weight; sizes[i] = size;
    }

    // initializing may depend on implementation
    vector<vector<int>> F(n_items + 1, vector<int>(capacity + 1, -1));
    for (int i = 0; i <= n_items; i++) F[0][i] = 0;
    for (int i = 0; i <= capacity; i++) F[i][0] = 0;

    int solve = knapsack(n_items, capacity, weights, sizes, F);

    cout << solve << endl;

    return 0;
}