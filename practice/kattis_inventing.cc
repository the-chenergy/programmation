#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
const double PI = 3.141592653589793;
struct union_find {
  vector<int> _data;
  union_find(int size) : _data(size, -1){};
  int size(int x) { return -_data[find(x)]; }
  int find(int x) { return _data[x] < 0 ? x : _data[x] = find(_data[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (-_data[x] < -_data[y]) swap(x, y);
    _data[x] += _data[y];
    _data[y] = x;
    return true;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n_tests;
  cin >> n_tests;
  for (int i_test = 0; i_test < n_tests; ++i_test) {
    int n;
    cin >> n;
    ll ans = 0;
    vector<array<int, 3>> links(n - 1);
    for (int i = 1; i < n; ++i) {
      int a, b, w;
      cin >> a >> b >> w;
      --a, --b;
      ans += w;
      links.push_back({w, a, b});
    }
    sort(links.begin(), links.end());
    union_find uf(n);
    for (auto [w, a, b] : links) {
      ans += ((ll)uf.size(a) * uf.size(b) - 1) * (w + 1);
      uf.unite(a, b);
    }
    cout << ans << "\n";
  }
}
