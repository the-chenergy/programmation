/* Solution to "Intruder Outsmarting", problem B from the Google Code Jam
   Farewell Round B.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c9607c/0000000000cad13d)
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
using ll = long long;
ll euclid(ll a, ll b, ll& x, ll& y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}

int num_cases, case_id;

void solve() {
    int w, n, d;
    cin >> w >> n >> d;

    const int N = 100001;
    static int a[N];
    for (int i = 0; i < w; i++) cin >> a[i], a[i]--;

    long long x, y;
    euclid(d, n, x, y);
    x = (x + n) % n;
    int g = __gcd(n, d);

    long long ans = 0;
    for (int i = 0, j = w - 1; i < w / 2; i++, j--) {
        if (a[i] % g != a[j] % g) {
            cout << "IMPOSSIBLE\n";
            return;
        }

        ans += min(x * (a[i] - a[j] + n) % n / g % n,
                   x * (a[j] - a[i] + n) % n / g % n);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> num_cases;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve();
    }
}
