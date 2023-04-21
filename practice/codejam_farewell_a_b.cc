/* Solution to "Illumination Optimization", problem B from the Google Code Jam
   Farewell Round A.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95b94/0000000000cad086)
*/

#include <bits/stdc++.h>
using namespace std;

static void solve(int /* case_id */) {
    long long m, r;
    int n;
    cin >> m >> r >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        a[i] = x - r;
    }

    if (a[0] > 0 || a.back() + 2 * r < m) {
        cout << "IMPOSSIBLE\n";
        return;
    }

    int ans = 1;
    auto cur = prev(upper_bound(a.begin(), a.end(), 0));
    while (*cur + 2 * r < m) {
        auto nxt = upper_bound(cur + 1, a.end(), *cur + 2 * r);
        if (nxt == cur + 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        cur = prev(nxt);
        ans++;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int cases;
    cin >> cases;
    for (int i = 1; i <= cases; i++) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
}
