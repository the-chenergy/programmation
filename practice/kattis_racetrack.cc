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
  vector<ll> pt(n);
  vector<int> pl(n);
  set<tuple<ll, ll, int, int>> q;
  for (int i = 0; i < n; i++) {
    cin >> pt[i] >> pl[i];
    q.insert({0, pt[i], i, 1});
  }
  vector<ll> ans(n);
  while (q.size()) {
    auto [to, tn, p, l] = *q.begin();
    q.erase(q.begin());
    if (l == pl[p]) {
      ans[p] = tn;
      continue;
    }
    auto it = q.lower_bound({tn, 0, 0, 0});
    ll nxt_tn = tn + pt[p];
    if (it != q.begin()) nxt_tn = max(nxt_tn, get<1>(*prev(it)));
    q.insert({tn, nxt_tn, p, l + 1});
  }
  for (auto x : ans) cout << x << "\n";
}
