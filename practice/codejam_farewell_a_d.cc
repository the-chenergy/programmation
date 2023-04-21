/* Solution to "ASCII Art", problem D from the Google Code Jam Farewell Round A.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95b94/0000000000cad9c2)
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    long long lo = 0, hi = INT_MAX / 2 / 26;
    while (hi - lo > 1) {
        long long up = (lo + hi) / 2;
        long long tot = (1 + up) * up / 2 * 26;
        (tot < n ? lo : hi) = up;
    }

    long long tot = (1 + lo) * lo / 2 * 26;
    cout << char((n - tot - 1) / (lo + 1) + 'A') << "\n";
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
