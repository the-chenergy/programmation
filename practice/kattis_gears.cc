#include <bits/stdc++.h>
using namespace std;

/* Chinese Remainder Theorem. Source: KACTL */
long long euclid(long long a, long long b, long long &x, long long &y) {
    if (!b) return x = 1, y = 0, a;
    long long d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}
optional<pair<long long, long long>> crt(long long a, long long m, long long b,
                                         long long n) {
    if (n > m) swap(a, b), swap(m, n);
    long long x, y, g = euclid(m, n, x, y);
    if ((a - b) % g) return {};
    x = (b - a) % n * x % n / g * m + a;
    return {{x < 0 ? x + m * n / g : x, g}};
}

int main() {
    int m;
    cin >> m;
    while (m--) {
        int n;
        cin >> n;
        int bad = 0;
        long long a = 0, x = 1;
        for (int i = 0; i < n; i++) {
            long long b, y;
            cin >> y >> b;
            if (bad) continue;
            if (i % 2) b = (y - b) % y;
            auto c = crt(a, x, b, y);
            if (!c.has_value()) {
                bad = 1;
                continue;
            }
            a = c.value().first;
            x *= y / c.value().second;
        }
        if (bad) cout << "Impossible\n";
        else cout << a << "\n";
    }
}
