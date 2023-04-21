/* Solution to "Immunization Operation", problem B from the Google Code Jam
   Farewell Round C.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95433/0000000000cacb88)

   Just maintain all the currently held and remaining unpicked-up locations
   in an ordered list. Sweep left or right and process covered items in the
   list. Each vaccine only needs to be dealt with twice (pick up and drop off)
   so overall it's O(log N) per vaccine amortized.
*/

#include <bits/stdc++.h>
using namespace std;

static void solve(int /* case_id */) {
    int n, m;
    cin >> n >> m;
    static long long drop[100001];
    static set<pair<long long, int>> hold;
    hold = {};
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        hold.insert({x, i});
    }
    for (int i = 0; i < n; i++) cin >> drop[i];
    long long x = 0;
    auto it = hold.lower_bound({0, -1});
    while (m--) {
        long long d;
        cin >> d;
        int ans = 0;
        while (d > 0 ? it != hold.end() && it->first <= x + d
                     : it != hold.begin() && prev(it)->first >= x + d) {
            int i = (d > 0 ? it : prev(it))->second;
            if (d < 0) it = hold.erase(prev(it));
            if (i >= 0) hold.insert({drop[i], ~i});
            else ans++;
            if (d > 0) it = hold.erase(it);
        }
        cout << ans << " ";
        x += d;
    }
    cout << "\n";
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
