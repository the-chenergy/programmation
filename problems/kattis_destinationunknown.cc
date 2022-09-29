#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int nt;
  cin >> nt;
  while (nt--) {
    int n, m, t;
    cin >> n >> m >> t;
    int s, g, h;
    cin >> s >> g >> h;
    s--, g--, h--;
    if (g > h) swap(g, h);
    vector<vector<array<int, 2>>> adj(n);
    for (int i = 0; i < m; i++) {
      int a, b, d;
      cin >> a >> b >> d;
      a--, b--;
      adj[a].push_back({b, d});
      adj[b].push_back({a, d});
    }
    vector<bool> is_des(n);
    for (int i = 0; i < t; i++) {
      int x;
      cin >> x;
      is_des[x - 1] = 1;
    }
    vector<pair<int, bool>> dis(n, {1e9, 0});
    dis[s] = {0, 0};
    set<tuple<int, int, bool>> search = {{0, s, 0}};
    while (search.size()) {
      auto [d, cur, smell] = *search.begin();
      search.erase(search.begin());
      if (d > dis[cur].first) continue;
      dis[cur].second = smell;
      for (auto [nxt, w] : adj[cur]) {
        bool new_sm = smell || (min(cur, nxt) == g && max(cur, nxt) == h);
        if (!(d + w < dis[nxt].first || (d + w == dis[nxt].first && new_sm)))
          continue;
        dis[nxt].first = d + w;
        search.insert({d + w, nxt, new_sm});
      }
    }
    for (int i = 0; i < n; i++)
      if (is_des[i] && dis[i].second) cout << i + 1 << " ";
    cout << "\n";
  }
}
