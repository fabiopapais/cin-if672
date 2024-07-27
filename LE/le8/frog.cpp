#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    vector<int> h(N+1);

    for (int i = 1; i <= N; ++i) {
        cin >> h[i];
    }

    vector<int> dp(N+1, INT_MAX);
    dp[1] = 0;

    for (int i = 1; i < N; ++i) {
        for (int j = i+1; j <= min(i+K, N); ++j) {
            dp[j] = min(dp[j], dp[i] + abs(h[i] - h[j]));
        }
    }

    cout << dp[N] << endl;

    return 0;
}
