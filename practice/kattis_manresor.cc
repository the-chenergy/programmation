/* Solution to "Once in a Blue Moon", a problem from the
   Programmeringsolympiadens final 2019.
   (https://open.kattis.com/problems/manresor)

   The recurrence relation should be fairly straightforward:
   dp[i] = min(price[j] / ? + dp[i + valid[j]] for ticket j)

   Use a monotonic queue to find that minimum across future days. O(D * M) where
   D is the last traveling day. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;
    const int mxd = 500000;
    static char visit[mxd + 1];
    int last = 0;
    for (int i = 0; i < n; i++) {
        int d;
        cin >> d, d--;
        visit[d] = 1;
        last = d;
    }
    static int valid[10];
    static long long price[10];
    for (int i = 0; i < m; i++) cin >> valid[i];
    for (int i = 0; i < m; i++) cin >> price[i];
    static char work[mxd + 1];
    for (int i = 0; i < k; i++) {
        int d;
        cin >> d, d--;
        work[d] = 1;
    }

    static long long dp[mxd + 1];
    static array<deque<long long>, 10> q;
    for (int i = 0; i < m; i++) q[i] = deque<long long>(valid[i] + 1, 0);
    for (int i = last; i >= 0; i--) {
        dp[i] = visit[i] ? LLONG_MAX / 2 : dp[i + 1];
        for (int j = 0; j < m; j++) {
            if (q[j].front() ==
                (i + valid[j] + 1 > mxd ? 0 : dp[i + valid[j] + 1])) {
                q[j].pop_front();
            }
            dp[i] = min(dp[i], price[j] / (work[i] + 1) + q[j].front());
        }
        for (int j = 0; j < m; j++) {
            while (q[j].size() && dp[i] < q[j].back()) q[j].pop_back();
            q[j].push_back(dp[i]);
        }
    }
    cout << dp[0] << "\n";
}
