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
    int n;
    cin >> n;
    vector<int> dis(n);
    for (int i = 0; i < n; i++) cin >> dis[i];
    int mxh = 1001;
    vector<vector<int>> dp(n + 1, vector<int>(mxh, 1e9));
    vector<vector<char>> ans(n + 1, vector<char>(mxh, 'U'));
    dp[n][0] = 0;
    for (int i = n - 1; i >= 0; i--) {
      for (int h = 0; h < mxh; h++) {
        int& dpi = dp[i][h];
        dpi = max(h, dp[i + 1][h + dis[i]]);
        if (h - dis[i] >= 0) {
          int dpd = max(h, dp[i + 1][h - dis[i]]);
          if (dpd <= dpi) dpi = dpd, ans[i][h] = 'D';
        }
      }
    }
    if (dp[0][0] > mxh) {
      cout << "IMPOSSIBLE\n";
      continue;
    }
    int h = 0;
    for (int i = 0; i < n; i++) {
      cout << ans[i][h];
      if (ans[i][h] == 'U')
        h += dis[i];
      else
        h -= dis[i];
    }
    cout << "\n";
  }
}
