#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;
struct segment_tree {
  using value_t = int;
  // using value_t = ll;
  const value_t DEFAULT_VALUE = 0;
  // const value_t DEFAULT_VALUE = INT_MAX;
  // const value_t DEFAULT_VALUE = INT_MIN;
  // const value_t DEFAULT_VALUE = ;
  value_t _get(value_t x, value_t y) {
    // return min(x, y);
    // return max(x, y);
    // return gcd(x, y);
    return x + y;
  }
  int size;
  vector<value_t> _data;
  segment_tree(int size) : size(size), _data(2 * size, DEFAULT_VALUE) {}
  void update(int index, value_t new_value) {
    for (_data[index += size] = new_value; index /= 2;)
      _data[index] = _get(_data[index * 2], _data[index * 2 + 1]);
  }
  value_t query(int begin, int end) {
    value_t res_a = DEFAULT_VALUE, res_b = DEFAULT_VALUE;
    for (begin += size, end += size; begin < end; begin /= 2, end /= 2) {
      if (begin % 2) res_a = _get(res_a, _data[begin++]);
      if (end % 2) res_b = _get(_data[--end], res_b);
    }
    return _get(res_a, res_b);
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n;
  cin >> n;
  segment_tree n_moved(n);
  vector<int> val_i(n);
  for (int i = 0; i < n; i++) {
    int val;
    cin >> val;
    val--;
    val_i[val] = i;
  }
  int lo = 0, hi = n - 1;
  bool move_lo = 1;
  while (lo <= hi) {
    if (move_lo) {
      int i = val_i[lo];
      cout << i - n_moved.query(0, i) << "\n";
      n_moved.update(i, 1);
      lo++;
    } else {
      int i = val_i[hi];
      cout << n - 1 - i - n_moved.query(i + 1, n) << "\n";
      n_moved.update(i, 1);
      hi--;
    }
    move_lo ^= 1;
  }
}
