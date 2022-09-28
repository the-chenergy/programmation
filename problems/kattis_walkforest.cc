#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while (1) {
    int n, m;
    cin >> n >> m;
    if (cin.fail()) break;
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0; i < m; i++) {
      int u, v, w;
      cin >> u >> v >> w;
      u--, v--;
      adj[u].push_back({v, w});
      adj[v].push_back({u, w});
    }
    vector<int64_t> dis(n, 1e18);
    dis[1] = 0;
    multiset<pair<int64_t, int>> search;
    search.insert({0, 1});
    while (search.size()) {
      auto [d, cur] = *search.begin();
      search.erase(search.begin());
      if (d > dis[cur]) continue;
      for (auto [nxt, w] : adj[cur]) {
        if (d + w >= dis[nxt]) continue;
        dis[nxt] = d + w;
        search.insert({d + w, nxt});
      }
    }
    vector<int64_t> cache(n, -1);
    cache[1] = 1;
    function<int64_t(int)> ct = [&](int cur) -> int64_t {
      if (cache[cur] >= 0) return cache[cur];
      int64_t tot = 0;
      for (auto [nxt, _] : adj[cur]) {
        if (dis[nxt] >= dis[cur]) continue;
        tot += ct(nxt);
      }
      return cache[cur] = tot;
    };
    cout << ct(0) << "\n";
  }
}
