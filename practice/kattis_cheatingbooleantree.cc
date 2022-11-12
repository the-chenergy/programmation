#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;
const int INF = 1e5;
void run_test(int test_id) {
  int n_nodes, desire;
  cin >> n_nodes >> desire;
  int n_internal = (n_nodes - 1) / 2;
  vector<int> op(n_nodes);
  vector<int> changeable(n_nodes);
  vector<vector<int>> cheat(n_nodes, vector<int>(2, INF));  // [node_i][desire]
  for (int i = 0; i < n_nodes; ++i) {
    if (i < n_internal) {
      cin >> op[i] >> changeable[i];
    } else {
      int value;
      cin >> value;
      cheat[i][0] = value == 0 ? 0 : INF;
      cheat[i][1] = value == 1 ? 0 : INF;
    }
  }
  for (int i = n_internal - 1; i >= 0; --i) {
    if (op[i]) {
      cheat[i][0] = min(cheat[i * 2 + 1][0], cheat[i * 2 + 2][0]);
      cheat[i][1] = cheat[i * 2 + 1][1] + cheat[i * 2 + 2][1];
      if (changeable[i]) {
        cheat[i][0] =
            min(cheat[i][0], 1 + cheat[i * 2 + 1][0] + cheat[i * 2 + 2][0]);
        cheat[i][1] =
            min(cheat[i][1], 1 + min(cheat[i * 2 + 1][1], cheat[i * 2 + 2][1]));
      }
    } else {
      cheat[i][0] = cheat[i * 2 + 1][0] + cheat[i * 2 + 2][0];
      cheat[i][1] = min(cheat[i * 2 + 1][1], cheat[i * 2 + 2][1]);
      if (changeable[i]) {
        cheat[i][0] =
            min(cheat[i][0], 1 + min(cheat[i * 2 + 1][0], cheat[i * 2 + 2][0]));
        cheat[i][1] =
            min(cheat[i][1], 1 + cheat[i * 2 + 1][1] + cheat[i * 2 + 2][1]);
      }
    }
  }
  int ans = cheat[0][desire];
  if (ans < INF)
    cout << ans;
  else
    cout << "IMPOSSIBLE";
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int num_tests;
  cin >> num_tests;
  for (int test_id = 0; test_id < num_tests; ++test_id) {
    cout << "Case #" << test_id + 1 << ": ";
    run_test(test_id);
    cout << "\n";
  }
}
