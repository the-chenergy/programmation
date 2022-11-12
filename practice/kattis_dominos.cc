#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
const double PI = 3.141592653589793;
void dfs1(int u, vector<vector<int>>& nx, vector<bool>& vis, vector<int>& rev) {
  for (int v : nx[u]) {
    if (!vis[v]) {
      vis[v] = true;
      dfs1(v, nx, vis, rev);
    }
  }
  rev.push_back(u);
}
void dfs2(int v, vector<vector<int>>& pv, vector<int>& comp,
          vector<bool>& comp_has_in) {
  comp[v] = comp_has_in.size() - 1;
  for (int u : pv[v]) {
    if (comp[u] >= 0) {
      if (comp[u] != comp[v]) comp_has_in[comp[v]] = true;
      continue;
    }
    dfs2(u, pv, comp, comp_has_in);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int nt;
  cin >> nt;
  for (int t = 0; t < nt; ++t) {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> nx(n);
    vector<vector<int>> pv(n);
    for (int i = 0; i < m; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      nx[u].push_back(v);
      pv[v].push_back(u);
    }
    vector<bool> vis(n);
    vector<int> rev;
    for (int s = 0; s < n; ++s) {
      if (vis[s]) continue;
      vis[s] = true;
      dfs1(s, nx, vis, rev);
    }
    vector<int> comp(n, -1);
    vector<bool> comp_has_in;
    reverse(rev.begin(), rev.end());
    for (int s : rev) {
      if (comp[s] >= 0) continue;
      comp_has_in.push_back(false);
      dfs2(s, pv, comp, comp_has_in);
    }
    int ans = 0;
    for (bool has_in : comp_has_in) {
      if (!has_in) ++ans;
    }
    cout << ans << "\n";
  }
}
