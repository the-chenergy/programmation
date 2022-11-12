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
    string s, t;
    cin >> s >> t;
    vector<vector<int>> s_nxt(1);
    vector<int> s_par = {-1};
    int cur = 0;
    for (auto ch : s) {
      if (ch == '0') {
        s_nxt[cur].push_back(s_par.size());
        s_nxt.emplace_back();
        s_par.push_back(cur);
        cur = s_par.size() - 1;
      } else {
        cur = s_par[cur];
      }
    }
    vector<vector<int>> t_nxt(1);
    vector<int> t_par = {-1};
    cur = 0;
    for (auto ch : t) {
      if (ch == '0') {
        t_nxt[cur].push_back(t_par.size());
        t_nxt.emplace_back();
        t_par.push_back(cur);
        cur = t_par.size() - 1;
      } else {
        cur = t_par[cur];
      }
    }
    function<bool(int, int)> eq = [&](int si, int ti) -> bool {
      if (s_nxt[si].size() != t_nxt[ti].size()) return 0;
      set<int> t_used;
      for (auto s_chi : s_nxt[si]) {
        for (auto t_chi : t_nxt[ti]) {
          if (t_used.count(t_chi)) continue;
          if (eq(s_chi, t_chi)) {
            t_used.insert(t_chi);
            break;
          }
        }
      }
      return t_used.size() == s_nxt[si].size();
    };
    cout << (eq(0, 0) ? "same" : "different") << "\n";
  }
}
