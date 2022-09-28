#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int p;
  cin >> p;
  vector<array<int, 2>> dir = {{0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  while (p--) {
    int goal = 0;
    for (int i = 0; i < 9; i++) {
      char x;
      cin >> x;
      goal |= (1 << i) * (x == '*');
    }
    if (goal == 0) {
      cout << "0\n";
      continue;
    }
    set<int> vis;
    vis.insert(0);
    deque<pair<int, int>> search{{0, 0}};
    while (true) {
      auto [steps, cur] = search.back();
      search.pop_back();
      for (int sy = 0; sy < 3; sy++) {
        for (int sx = 0; sx < 3; sx++) {
          auto nxt = cur;
          for (auto [dy, dx] : dir) {
            int y = sy + dy, x = sx + dx;
            if (y < 0 || y >= 3 || x < 0 || x >= 3) continue;
            nxt ^= 1 << (y * 3 + x);
          }
          if (nxt == goal) {
            cout << steps + 1 << "\n";
            goto nxt_p;
          }
          if (vis.count(nxt)) continue;
          vis.insert(nxt);
          search.push_front({steps + 1, nxt});
        }
      }
    }
  nxt_p:;
  }
}
