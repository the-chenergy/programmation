/* Solution to Hipster Jazz, a problem from the Nordic Olympiad in Informatics
   2022. (https://open.kattis.com/problems/hipsterjazz)

   Just simulate until convergence. Turned out this works. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;
    const int N = 201;
    static vector<int> nei[N];
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        nei[u].push_back(v), nei[v].push_back(u);
    }

    static int ans[N];
    for (int ok = 0; !ok;) {
        ok = 1;
        for (int u = 1; u <= n; u++) {
            int ct = 0;
            for (auto v : nei[u]) ct += ans[u] ^ ans[v];
            if (ct < ((int)nei[u].size() + 1) / 2) ans[u] ^= 1, ok = 0;
        }
    }
    for (int u = 1; u <= n; u++) cout << (ans[u] ? 'P' : 'S');
    cout << "\n";
}
