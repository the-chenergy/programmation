#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int m1, n1, k1, m2, n2, k2;
    cin >> m1 >> n1 >> k1 >> m2 >> n2 >> k2;
    int mxn = max(n1, n2), mxk = max(k1, k2);
    vector<vector<int>> adj1(mxn + 1, vector<int>(mxk, mxn));
    for (int i = 0; i < m1; i++) {
      int a, b, k;
      cin >> a >> b >> k;
      adj1[a][k] = b;
    }
    vector<vector<int>> adj2(mxn + 1, vector<int>(mxk, mxn));
    for (int i = 0; i < m2; i++) {
      int a, b, k;
      cin >> a >> b >> k;
      adj2[a][k] = b;
    }
    // Check if two DFAs are equivalent in O(n1 * n2 * max(k1, k2)).
    // Use mxn as the blackhole.
    vector<vector<bool>> vis(mxn + 1, vector<bool>(mxn + 1));
    vis[0][0] = 1;
    vector<array<int, 2>> search = {{0, 0}};
    while (search.size()) {
      auto [ci, cj] = search.back();
      search.pop_back();
      for (int k = 0; k < mxk; k++) {
        int i = adj1[ci][k], j = adj2[cj][k];
        if ((i == n1 - 1) != (j == n2 - 1)) {
          cout << "not eligible\n";
          goto nxt;
        }
        if (vis[i][j]) continue;
        vis[i][j] = 1;
        search.push_back({i, j});
      }
    }
    cout << "eligible\n";
  nxt:;
  }
}
