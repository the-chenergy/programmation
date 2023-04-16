/* Solution to "Railroad Management", problem E from the Google Code Jam
   Farewell Round B.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c9607c/0000000000caccfb)
 */

#include <bits/stdc++.h>
using namespace std;

int num_cases, case_id;

void solve() {
    int n;
    cin >> n;

    const int N = 100001;
    static int d[N], deg[N];
    static long long c[N];

    fill_n(deg, n, 0);
    for (int i = 0; i < n; i++) {
        cin >> d[i], d[i]--;
        deg[d[i]]++;
    }
    for (int i = 0; i < n; i++) cin >> c[i];

    long long ans = 0;
    static deque<int> sea;
    sea = {};
    static long long wait[N];
    static char vis[N];
    fill_n(wait, n, 0);
    fill_n(vis, n, 0);
    for (int i = 0; i < n; i++) {
        if (!deg[i]) sea.push_back(i);
    }
    while (sea.size()) {
        int i = sea.front();
        sea.pop_front();
        vis[i] = 1;
        ans += max(0LL, c[i] - wait[i]);
        wait[d[i]] += c[i];
        if (!--deg[d[i]]) sea.push_back(d[i]);
    }

    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        long long tot = 0;
        int k = i;
        do {
            tot += max(0LL, c[d[k]] - wait[d[k]] - c[k]);
            k = d[k];
            vis[k] = 1;
        } while (k != i);
        long long mn = LLONG_MAX / 2;
        do {
            mn = min(mn, tot - max(0LL, c[d[k]] - wait[d[k]] - c[k]) +
                                 max(0LL, c[d[k]] - wait[d[k]]));
            k = d[k];
        } while (k != i);
        ans += mn;
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
