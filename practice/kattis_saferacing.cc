#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  ll l, s, m = 123456789;
  cin >> l >> s;
  vector<ll> dp(l, 1);
  ll nxt = 1;
  for (int i = l - 2; i >= 0; i--) {
    dp[i] = nxt;
    nxt = (nxt + dp[i]) % m;
    if (i + s < l) nxt = (nxt - dp[i + s] + m) % m;
  }
  ll ans = 0;
  for (int i = 0; i < s; i++) ans = (ans + (i + 1) * dp[i]) % m;
  cout << ans;
}
