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
    array<array<int, 2>, 2> s, p;
    cin >> s[0][0] >> s[0][1] >> p[0][0] >> p[0][1];
    cin >> s[1][0] >> s[1][1] >> p[1][0] >> p[1][1];
    int g = gcd(p[0][0], gcd(p[0][1], gcd(p[1][0], p[1][1])));
    for (int y = 0; y < 2; y++)
      for (int x = 0; x < 2; x++) s[y][x] %= g;
    for (int y = 0; y < 2; y++) {
      for (int x = 0; x < 2; x++) {
        auto t = s;
        for (int yy = 0; yy < 2; yy++)
          for (int xx = 0; xx < 2; xx++)
            t[yy][xx] = (t[yy][xx] - s[y][x] + g) % g;
        if ((t[!y][x] + t[y][!x]) % g == t[!y][!x]) {
          cout << "Yes\n";
          goto nxt;
        }
      }
    }
    cout << "No\n";
  nxt:;
  }
}
