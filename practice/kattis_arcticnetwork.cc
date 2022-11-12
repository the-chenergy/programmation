#include <bits/stdc++.h>
using namespace std;
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
  cout << setprecision(2) << fixed;
  int n;
  cin >> n;
  while (n--) {
    int s, p;
    cin >> s >> p;
    vector<complex<double>> pts(p);
    multiset<tuple<double, int, int>> edges;
    for (int i = 0; i < p; i++) {
      double x, y;
      cin >> x >> y;
      pts[i] = {x, y};
      for (int j = 0; j < i; j++) edges.insert({abs(pts[i] - pts[j]), i, j});
    }
    union_find uf(p);
    vector<double> ds;
    int m = 0;
    while (m < p - 1) {
      auto [d, i, j] = *edges.begin();
      edges.erase(edges.begin());
      if (uf.same(i, j)) continue;
      uf.unite(i, j);
      ds.push_back(d);
      m++;
    }
    cout << ds[p - 1 - s] << "\n";
  }
}
