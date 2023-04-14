/**
    Solution to "Paths", a problem from the Baltic Olympiad in Informatics 2018.

    Let f(R, u) represent the number of paths beginning at vertex u with the set
    of unseen colors R. Simple bit-mask DP from there.
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 300'001, K = 5;

int col[N];
vector<int> nei[N];
long long dp[1 << K][N];

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    for (int u = 1; u <= n; u++) cin >> col[u], col[u]--;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        nei[u].push_back(v);
        nei[v].push_back(u);
    }

    for (int rem = 1; rem < (1 << k) - 1; rem++) {
        for (int u = 1; u <= n; u++) {
            if (rem >> col[u] & 1) continue;
            for (int v : nei[u]) {
                if (~rem >> col[v] & 1) continue;
                dp[rem][u] += dp[rem ^ 1 << col[v]][v] + 1;
            }
        }
    }

    long long ans = 0;
    for (int u = 1; u <= n; u++) ans += dp[(1 << k) - 1 ^ 1 << col[u]][u];
    cout << ans << "\n";
}
