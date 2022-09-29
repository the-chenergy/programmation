#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  ll sx, sy, ex, ey;
  cin >> sx >> sy >> ex >> ey;
  if (sx == ex && sy == ey) {
    cout << 0;
    return 0;
  }
  map<ll, vector<ll>> xy, yx;
  for (int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    xy[x].push_back(y);
    yx[y].push_back(x);
  }
  for (auto& [x, ys] : xy) sort(ys.begin(), ys.end());
  for (auto& [y, xs] : yx) sort(xs.begin(), xs.end());
  deque<tuple<int, ll, ll>> search{{0, sx, sy}};
  set<array<ll, 2>> vis;
  vector<array<int, 4>> dir;
  for (int i = -2; i <= 2; i += 4)
    for (int j = -1; j <= 1; j += 2) {
      dir.push_back({i, 0, 0, j});
      dir.push_back({0, i, j, 0});
    }
  vis.insert({sx, sy});
  while (search.size()) {
    auto [d, cx, cy] = search.back();
    search.pop_back();
    for (auto [dx0, dy0, dx1, dy1] : dir) {
      ll x = cx, y = cy;
      if (dx0) {
        auto& rank = yx[y];
        int xi = lower_bound(rank.begin(), rank.end(), x) - rank.begin() + dx0;
        if (xi < 0 || xi >= (int)rank.size()) continue;
        x = rank[xi];
      } else {
        auto& file = xy[x];
        int yi = lower_bound(file.begin(), file.end(), y) - file.begin() + dy0;
        if (yi < 0 || yi >= (int)file.size()) continue;
        y = file[yi];
      }
      if (dx1) {
        auto& rank = yx[y];
        int xi = lower_bound(rank.begin(), rank.end(), x) - rank.begin() + dx1;
        if (xi < 0 || xi >= (int)rank.size()) continue;
        x = rank[xi];
      } else {
        auto& file = xy[x];
        int yi = lower_bound(file.begin(), file.end(), y) - file.begin() + dy1;
        if (yi < 0 || yi >= (int)file.size()) continue;
        y = file[yi];
      }
      if (x == ex && y == ey) {
        cout << d + 1;
        return 0;
      }
      if (vis.count({x, y})) continue;
      vis.insert({x, y});
      search.push_front({d + 1, x, y});
    }
  }
  cout << -1;
}
