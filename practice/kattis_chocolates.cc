#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int h, w;
  cin >> h >> w;
  int ans = 0;
#define g(y, x) \
  (y >= 0 && x >= 0 && y < h && x < w && (con & (1 << (y * w + x))) > 0)
  vector<array<int, 2>> dir;
  for (int y = -1; y <= 1; y++)
    for (int x = -1; x <= 1; x++)
      if (y || x) dir.push_back({y, x});
  for (int con = 1; con < 1 << (h * w); con++) {
    vector<array<int, 2>> st(1);
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        if (g(y, x)) st[0] = {y, x};
      }
    }
    st.push_back({-1, -1});
    vector<vector<bool>> vis(h + 2, vector<bool>(w + 2));
    for (auto [sy, sx] : st) {
      vis[sy + 1][sx + 1] = 1;
      vector<array<int, 2>> search{{sy, sx}};
      while (search.size()) {
        auto [cy, cx] = search.back();
        search.pop_back();
        for (auto [dy, dx] : dir) {
          int y = cy + dy, x = cx + dx;
          if (g(cy, cx) && dy && dx) continue;
          if (y < -1 || y > h || x < -1 || x > w) continue;
          if (g(y, x) != g(cy, cx)) continue;
          if (vis[y + 1][x + 1]) continue;
          vis[y + 1][x + 1] = 1;
          search.push_back({y, x});
        }
      }
    }
    bool ok = 1;
    for (int y = 0; y < h; y++)
      for (int x = 0; x < w; x++)
        if (!vis[y + 1][x + 1]) ok = 0;
    ans += ok;
  }
  cout << ans;
}
