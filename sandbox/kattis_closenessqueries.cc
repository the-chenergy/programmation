#include <bits/stdc++.h>  // TLE
using namespace std;
using ll = int64_t;
using ull = uint64_t;
struct union_find {
  vector<int> _data;
  union_find(int size) : _data(size, -1){};
  int count(int x) { return -_data[find(x)]; }
  int find(int x) { return _data[x] < 0 ? x : _data[x] = find(_data[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (-_data[x] < -_data[y]) swap(x, y);
    _data[x] += _data[y], _data[y] = x;
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  union_find uf(n);
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    uf.unite(a, b);
    adj[a].push_back(b), adj[b].push_back(a);
  }
  int q;
  cin >> q;
  vector<map<int, int>> dis(n);
  for (int i = 0; i < n; i++) dis[i][i] = 0;
  while (q--) {
    int a, b;
    cin >> a >> b;
    if (!uf.same(a, b)) {
      cout << "-1\n";
      continue;
    }
    deque<int> search = {a};
    bool done = 0;
    while (search.size()) {
      auto cur = search.back();
      search.pop_back();
      int d = dis[a][cur];
      if (d >= 3) continue;
      for (auto nxt : adj[cur]) {
        if (dis[a].count(nxt) && d + 1 >= dis[a][nxt]) continue;
        if (nxt == b) {
          cout << d + 1 << "\n";
          done = 1;
          break;
        }
        dis[a][nxt] = dis[nxt][a] = d + 1;
        search.push_front(nxt);
      }
      if (done) break;
    }
    if (done) continue;
    search = {b};
    while (search.size()) {
      auto cur = search.back();
      search.pop_back();
      int d = dis[b][cur];
      for (auto nxt : adj[cur]) {
        if (dis[b].count(nxt) && d + 1 >= dis[b][nxt]) continue;
        if (nxt == a) {
          cout << d + 1 << "\n";
          done = 1;
          break;
        }
        if (dis[a].count(nxt)) {
          cout << d + 1 + dis[a][nxt] << "\n";
          done = 1;
          break;
        }
        dis[b][nxt] = dis[nxt][b] = d + 1;
        search.push_front(nxt);
      }
      if (done) break;
    }
  }
}
