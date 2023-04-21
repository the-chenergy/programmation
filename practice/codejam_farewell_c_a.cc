/* Solution to "Game Sort: Part 1", problem A from the Google Code Jam Farewell
   Round C.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95433/0000000000cacb87)

   Permute each string in the list to be lexicographically immediately greater
   than the previous string, and if at any point this is not possible then it's
   not possible. This is to leave the most room for future strings.

   I did the permuting part by trying to match the previous string by as much as
   possible and then pick the next greater unused character, then append the
   rest in sorted order. If it doesn't work then back up one index, matching one
   less character to the previous string before picking the next greater, until
   even the first index doesn't work.
*/

#include <bits/stdc++.h>
using namespace std;

static void solve(int /* case_id */) {
    int n;
    cin >> n;
    static string a[101];
    for (int i = 0; i < n; i++) cin >> a[i];

    int ok = [&]() -> int {
        sort(a[0].begin(), a[0].end());
        for (int i = 1; i < n; i++) {
            int done = 0;
            for (int l = (int)a[i - 1].size(); l >= 0; l--) {
                multiset<char> s(a[i].begin(), a[i].end());
                string t;
                int bad = 0;
                for (int k = 0; k <= min(l, (int)a[i - 1].size() - 1); k++) {
                    auto it = k == l ? s.upper_bound(a[i - 1][k])
                                     : s.lower_bound(a[i - 1][k]);
                    if (it == s.end()) {
                        bad = 1;
                        break;
                    }
                    auto d = *it;
                    s.erase(it);
                    t += d;
                    if (d > a[i - 1][k]) break;
                }
                if (!bad) {
                    t.insert(t.end(), s.begin(), s.end());
                    if (t >= a[i - 1]) {
                        a[i] = move(t);
                        done = 1;
                        break;
                    }
                }
            }
            if (!done) return 0;
        }
        return 1;
    }();

    if (ok) {
        cout << "POSSIBLE\n";
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << "\n";
    } else {
        cout << "IMPOSSIBLE\n";
    }
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
