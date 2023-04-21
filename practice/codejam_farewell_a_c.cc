/* Solution to "Rainbow Sort", problem C from the Google Code Jam Farewell Round
   A.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95b94/0000000000cada38)
*/

#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (a.size() && x == a.back()) continue;
        a.push_back(x);
    }

    unordered_set<int> s(a.begin(), a.end());
    if (s.size() != a.size()) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (auto x : a) cout << x << " ";
    cout << "\n";
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
