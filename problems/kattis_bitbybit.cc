#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  while (true) {
    int n;
    cin >> n;
    if (!n) break;
    bitset<32> a, b;
    b = ~b;
    while (n--) {
      string op;
      cin >> op;
      if (op == "SET") {
        int x;
        cin >> x;
        a[x] = b[x] = 1;
      } else if (op == "CLEAR") {
        int x;
        cin >> x;
        a[x] = b[x] = 0;
      } else if (op == "AND") {
        int x, y;
        cin >> x >> y;
        a[x] = a[x] & a[y];
        b[x] = b[x] & b[y];
      } else {
        int x, y;
        cin >> x >> y;
        a[x] = a[x] | a[y];
        b[x] = b[x] | b[y];
      }
    }
    for (int i = 31; i >= 0; i--) {
      if (a[i] == b[i])
        cout << a[i];
      else
        cout << "?";
    }
    cout << "\n";
  }
}
