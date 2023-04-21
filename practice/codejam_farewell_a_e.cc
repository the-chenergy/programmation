/* Solution to "Untie", problem E from the Google Code Jam Farewell Round A.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95b94/0000000000cad9c1)

   DP was apparently so unnecessary. But I did it anyway and let the state be
   (cur_i, cur_choice, first_choice).
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    string a;
    cin >> a;
    for (auto& c : a) {
        c = c == 'R' ? 0 : c == 'P' ? 1 : 2;
    }
    int n = (int)a.size();

    const int N = 1001;
    static int dp[N][3][3];

    for (int p : {0, 1, 2}) {
        for (int f : {0, 1, 2}) {
            dp[n - 1][p][f] = a[n - 1] == p || a[n - 1] == f;
        }
    }
    for (int i = n - 2; i >= 1; i--) {
        for (int p : {0, 1, 2}) {
            for (int f : {0, 1, 2}) {
                auto& ans = dp[i][p][f];
                ans = INT_MAX / 2;
                if (p != 0) ans = dp[i + 1][0][f] + (a[i] != 0);
                if (p != 1) ans = min(ans, dp[i + 1][1][f] + (a[i] != 1));
                if (p != 2) ans = min(ans, dp[i + 1][2][f] + (a[i] != 2));
            }
        }
    }
    int ans = INT_MAX / 2;
    for (int f : {0, 1, 2}) {
        ans = min(ans, dp[1][f][f] + (a[0] != f));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int cases;
    cin >> cases;
    for (int i = 1; i <= cases; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
}
