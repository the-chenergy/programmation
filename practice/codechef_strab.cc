/* Solution to "How to Write a Message", a problem from the CodeChef March
   Cook-Off 2015 (https://www.codechef.com/problems/STRAB).

   Let f(i, P) be the number of ways to fill in Message[i..N) given P being the
   previous longest substring containing only 'A' and 'B'. For example, if the
   message so far is "ABCABBA", the number of ways to finish off the message
   would be f(7, "ABBA"). Compress P into binary with a leading one
   (ex: "ABBA" => 10110), and confine its length to be at most M (plus 1). Now
   this becomes a straightforward bit-mask DP in O(N 2**(M + 1)). */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int lo = 0, hi = 0;
        for (int i = 0; i < m; i++) {
            char c;
            cin >> c;
            lo = lo * 2 + (c == 'B');
        }
        for (int i = 0; i < m; i++) {
            char c;
            cin >> c;
            hi = hi * 2 + (c == 'B');
        }
        const long long mod = 1E9 + 7;
        static long long dp[2][1 << 20];
        fill_n(dp[n & 1], 1 << (m + 1), 1);
        for (int x = lo; x <= hi; x++) dp[n & 1][1 << m | x] = 0;
        for (int i = n - 1; i >= 0; i--) {
            for (int x = 1; x < 1 << (m + 1); x++) {
                auto& ans = dp[i & 1][x] = 0;
                int y = x;
                if (__lg(y) == m) {
                    y ^= 1 << m;
                    if (y >= lo && y <= hi) continue;
                    y = y << 1 | 1 << m;
                } else {
                    y <<= 1;
                }
                ans += dp[~i & 1][1] * 24LL;
                ans += dp[~i & 1][y];
                ans += dp[~i & 1][y | 1];
                ans %= mod;
            }
        }
        cout << dp[0][1] << "\n";
    }
}
