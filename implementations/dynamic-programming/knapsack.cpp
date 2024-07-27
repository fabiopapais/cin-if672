#include <bits/stdc++.h>
using namespace std;


// bottom-up implementation
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


int main() {
    // First line: capacity of knapsack and quantity of items
    int capacity; int n_items; cin >> capacity >> n_items;
    vector<int> weights(n_items + 1);
    vector<int> sizes(n_items + 1);
    for (int i = 1; i <= n_items; i++) {
        int weight, size; cin >> weight >> size;
        weights[i] = weight; sizes[i] = size;
    }

    // initializing may depend on implementation
    vector<vector<int>> F(n_items + 1, vector<int>(capacity + 1));

    int solve = knapsack(n_items, capacity, weights, sizes, F);

    cout << solve << endl;

    return 0;
}