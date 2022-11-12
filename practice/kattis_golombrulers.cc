#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  while (getline(cin, s)) {
    istringstream is(s);
    int n = 0;
    set<int> ex;
    vector<int> tk;
    bool f = 0;
    int mx = 0;
    while (true) {
      int x;
      is >> x;
      if (is.fail()) break;
      n++;
      for (auto y : tk) {
        int an = abs(y - x);
        if (ex.count(an)) {
          cout << "not a ruler\n";
          f = 1;
          break;
        }
        ex.insert(an);
      }
      if (f) break;
      tk.push_back(x);
      mx = max(mx, x);
    }
    if (f) continue;
    vector<int> mis;
    for (int i = 1; i <= mx; i++)
      if (!ex.count(i)) mis.push_back(i);
    if (mis.size()) {
      cout << "missing";
      for (auto x : mis) cout << " " << x;
      cout << "\n";
    } else {
      cout << "perfect\n";
    }
  }
}
