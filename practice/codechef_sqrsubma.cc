/* Solution to "Square Submatrices", a problem from the CodeChef June Lunchtime
   2020 (https://www.codechef.com/problems/SQRSUBMA).

   We can formulate the phrase "square sub-matrix that sums up to X" into
   sum(A[i:i+w]) + sum(A[j:j+w]) == X / w, for any i, j, and w. Pictorially,
   (i, j) would be the top left corner of the square in the matrix, and w would
   be the length of that square.

   The above formula tells us that w needs to be a divisor of X. Since X is at
   most 10**6, the number of divisors can't be so big (at most 240 in fact), and
   we can actually just try every divisor of X. For each divisor, just check if
   there are any two windows of size w add up to (X / w). This can be done with
   a sliding window followed by a two-sum in O(N). Overall it's O(N d(X)), or
   O(N X**(1/3)) in practice.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        long long ans = 0;
        auto check = [&](int w) {
            if (w > n) return;
            int tar = x / w;
            long long cur = 0;
            for (int i = 0; i < w - 1; i++) cur += a[i];
            unordered_map<int, int> ct;
            for (int i = w - 1; i < n; i++) {
                cur += a[i];
                if (cur < tar) ct[(int)cur]++;
                cur -= a[i - w + 1];
            }
            for (auto [y, c] : ct) {
                auto it = ct.find(tar - y);
                if (it != ct.end()) ans += 1LL * c * it->second;
            }
        };

        check(1);
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) {
                check(i);
                if (i * i != x) check(x / i);
            }
        }

        cout << ans << "\n";
    }
}
