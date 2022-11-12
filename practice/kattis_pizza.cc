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
  while (n--) {
    int w, h;
    cin >> w >> h;
    vector<vector<int>> rec(h, vector<int>(w));
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        cin >> rec[y][x];
      }
    }
    vector<vector<int>> pre(h, vector<int>(w));
    for (int y = 0; y < h; y++) {
      int pre_ct = 0;
      for (int x = 0; x < w; x++) {
        if (x > 0) pre[y][x] = pre[y][x - 1] + pre_ct;
        for (int i = 0; i < h; i++) {
          pre[y][x] += rec[i][x] * abs(i - y);
          pre_ct += rec[i][x];
        }
      }
    }
    vector<vector<int>> post(h, vector<int>(w));
    for (int y = 0; y < h; y++) {
      int post_ct = 0;
      for (int x = w - 1; x >= 0; x--) {
        if (x < w - 1) post[y][x] = post[y][x + 1] + post_ct;
        for (int i = 0; i < h; i++) {
          post[y][x] += rec[i][x] * abs(i - y);
          post_ct += rec[i][x];
        }
      }
    }
    int ans = 1e9;
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        int ct = pre[y][x] + post[y][x];
        for (int i = 0; i < h; i++) ct -= rec[i][x] * abs(i - y);
        ans = min(ans, ct);
      }
    }
    cout << ans << " blocks\n";
  }
}
