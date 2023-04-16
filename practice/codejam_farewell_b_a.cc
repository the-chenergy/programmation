/* Solution to "Collecting Pancakes", problem A from the Google Code Jam
   Farewell Round B.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c9607c/0000000000cad7d1)
 */

#include <bits/stdc++.h>
using namespace std;

int num_cases, case_id;

void solve() {
    const int N = 100001;
    static long long pre[N];

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        pre[i] = pre[i - 1] + x;
    }
    int la, ra, lb, rb;
    cin >> la >> ra >> lb >> rb;

    long long ans = 0;
    for (int i = la; i <= ra; i++) {
        long long cur = LLONG_MAX / 2;
        if (rb > i) {
            int j = max(lb, i + 1);
            cur = pre[i + (j - i) / 2];
        }
        if (lb < i) {
            int j = min(rb, i - 1);
            cur = min(cur, pre[n] - pre[i - (i - j) / 2 - 1]);
        }
        ans = max(ans, cur);
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
