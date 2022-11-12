#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;

int main() {
  double rm = pow(2., 32), rd = 1. / rm;
#define R(x) (round(rm * (x)) * rd)
  int n;
  cin >> n;
  while (n--) {
    double x;
    int k;
    cin >> x >> k;
    x = R(x);
    vector<double> fs(k);
    for (auto& f : fs) cin >> f, f = 1. / f;
    sort(fs.begin(), fs.end());
    if (x <= fs.back()) {
      cout << "Nils\n";
      continue;
    }
    set<pair<double, bool>> ps = {{fs.back(), 0}};
    auto cur = ps.begin();
    while (1) {
      auto [cur_lo, cur_win] = *cur;
      if (cur_lo * fs[0] > x) break;
      if (!cur_win) {
        for (auto f : fs) {
          double lo = R(cur_lo * f);
          auto lo_it = prev(ps.upper_bound({lo, 1}));
          if (!lo_it->second)
            lo_it = lo_it->first == lo ? prev(lo_it) : ps.emplace(lo, 1).first;
          double hi = R(next(cur)->first * f);
          auto hi_it = ps.lower_bound({hi, 1});
          if (hi_it == ps.end() || hi_it->second)
            hi_it = hi_it != ps.end() && hi_it->first == hi
                        ? next(hi_it)
                        : ps.emplace(hi, 0).first;
          if (lo_it != hi_it) {
            lo_it++;
            while (lo_it != hi_it) ps.erase(lo_it++);
          }
        }
      }
      cur++;
    }
    cout << (prev(ps.lower_bound({x, 0}))->second ? "Nils\n" : "Mikael\n");
  }
}
