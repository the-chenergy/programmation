/** Solution to Toy Railway, a problem from the Spotify Code Quest 2012
    (https://open.kattis.com/problems/railway)

    BFS. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;
    vector<array<pair<int, int>, 3>> nei(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        char c, d;
        cin >> u >> c >> v >> d;
        c -= 'A', d -= 'A';
        nei[u][c] = {v, d}, nei[v][d] = {u, c};
    }

    vector<array<tuple<int, int, int>, 2>> par(n + 1);
    deque<pair<int, int>> bfs = {{1, 0}};
    while (bfs.size()) {
        int u, c;
        tie(u, c) = bfs.front();
        if (u == 1 && c == 0 && get<0>(par[u][!!c])) break;
        bfs.pop_front();
        auto add = [&](int c2) {
            auto [v, d] = nei[u][c2];
            if (!v || get<0>(par[v][!!d])) return;
            par[v][!!d] = {u, c2, c};
            bfs.push_back({v, d});
        };
        if (!c) add(1), add(2);
        else add(0);
    }

    auto [u, c2, c] = par[1][0];
    if (!u) {
        cout << "Impossible\n";
        exit(0);
    }

    string ans(n, 'B');
    int len = 1;
    set<pair<int, int>> seen;
    while (1) {
        if (c2) ans[u - 1] = (char)(c2 + 'A');
        if (u == 1 && c == 0) break;
        tie(u, c2, c) = par[u][!!c];
        len++;
    }
    cout << ans << "\n";
}
