/* Solution to "Spacious Sets", problem C from the Google Code Jam
   Farewell Round B.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c9607c/0000000000cad2ce)
 */

#include <bits/stdc++.h>
using namespace std;

int num_cases, case_id;

void solve() {
    int n, k;
    cin >> n >> k;

    const int N = 100001;
    static int a[N], b[N];
    for (int i = 0; i < n; i++) cin >> a[i];
    memcpy(b, a, sizeof(a[0]) * n);
    sort(a, a + n);

    static int l[N], r[N];
    for (int i = 1; i <= n; i++) {
        int j = (int)(upper_bound(a, a + i, a[i - 1] - k) - a);
        l[i] = 1 + l[j];
    }
    r[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        int j = (int)(lower_bound(a + i + 1, a + n, a[i] + k) - a);
        r[i] = 1 + r[j];
    }

    for (int i = 0; i < n; i++) {
        int j = (int)(lower_bound(a, a + n, b[i]) - a);
        cout << l[j + 1] + r[j] - 1 << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    cin >> num_cases;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve();
    }
}
