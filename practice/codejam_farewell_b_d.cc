/* Solution to "Railroad Maintenance", problem D from the Google Code Jam
   Farewell Round B.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c9607c/0000000000cad77d)
 */

#include <bits/stdc++.h>
using namespace std;

set<int> cps;
void IS_CUTPOINT(int i) { cps.insert(i); }

/* Source: https://cp-algorithms.com/graph/cutpoints.html#implementation */

int n;  // number of nodes
vector<vector<int>> adj;  // adjacency list of graph

vector<bool> visited;
vector<int> tin, low;
int timer;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    int children = 0;
    for (int to : adj[v]) {
        if (to == p) continue;
        if (visited[to]) {
            low[v] = min(low[v], tin[to]);
        } else {
            dfs(to, v);
            low[v] = min(low[v], low[to]);
            if (low[to] >= tin[v] && p != -1) IS_CUTPOINT(v);
            ++children;
        }
    }
    if (p == -1 && children > 1) IS_CUTPOINT(v);
}

void find_cutpoints() {
    timer = 0;
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) dfs(i);
    }
}

int num_cases, case_id;

void solve() {
    int m, l;
    cin >> m >> l;
    adj.assign(m + l, {});

    n = m + l;
    for (int i = 0; i < l; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int s;
            cin >> s, s--;
            adj[l + s].push_back(i);
            adj[i].push_back(l + s);
        }
    }

    cps = {};
    find_cutpoints();

    int ans = 0;
    for (int i = 0; i < l; i++) {
        ans += (int)cps.count(i);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> num_cases;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve();
    }
}
