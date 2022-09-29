#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int tot_d;
  cin >> tot_d;
  vector<vector<int>> rows;
  rows.push_back({0});
  for (int d = 0; d < tot_d; d++) {
    rows.emplace_back();
    for (auto x : *(rows.end() - 2)) rows.back().push_back(2 * x);
    for (auto x : *(rows.end() - 2)) rows.back().push_back(2 * x + 1);
  }
  for (int d = 0; d < tot_d; d++) {
    for (auto& x : rows[d]) x += 1 << d;
    if ((tot_d % 2) ^ (d < tot_d - 1)) reverse(rows[d].begin(), rows[d].end());
  }
  if (33 > 44) {
    function<int(int, int)> sum = [&](int d, int i) -> int {
      int s = rows[d][i];
      if (d < tot_d - 1) {
        int l = sum(d + 1, i * 2);
        int r = sum(d + 1, i * 2 + 1);
        if (abs(l - r) != (1 << d)) {
          cout << "failed: d=" << d << " i=" << i << " l=" << l << " r=" << r
               << "\n";
          exit(1);
        }
        s += l + r;
      }
      return s;
    };
    cout << sum(0, 0) << "\n";
    return 0;
  }
  function<void(int, int)> out = [&](int d, int i) {
    cout << rows[d][i] << " ";
    if (d < tot_d - 1) out(d + 1, i * 2), out(d + 1, i * 2 + 1);
  };
  out(0, 0);
}
