#include <bits/stdc++.h>
using namespace std;

int main() {
    array<int, 2> p = {4, 8};
    if (01) {
        p = {1, 6};
    }
    --p[0], --p[1];
    int r = 1;
    array<int, 2> s = {};
    int g = 0, c = 0;
    while (max(s[0], s[1]) < 1000) {
        for (int i = 0; i < 3; ++i) {
            (p[g] += r) %= 10;
            ++r;
            if (r > 100) {
                r = 1;
            }
            ++c;
        }
        s[g] += p[g] + 1;
        g ^= 1;
    }
    cout << 1LL * min(s[0], s[1]) * c << "\n";
}
