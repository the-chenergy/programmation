/* Solution to "Equivalent Exchange of Triangles", a problem from the CodeChef
   D'Code 2019 Div. 2 (https://www.codechef.com/problems/LEQEX).

   Record prefix sums for each color modulo 2. For each index, try finding the
   earliest moment where the prefix sum is the same, except for one color.
   O(30N) overall. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        unordered_map<int, int> seen;
        seen[0] = 0;
        int cur = 0, ans = 0;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            cur ^= 1 << x;
            seen.insert({cur, i});
            for (int y = 1; y <= 30; y++) {
                int pre = cur ^ 1 << y;
                auto it = seen.find(pre);
                if (it != seen.end()) ans = max(ans, (i - it->second) / 2);
            }
        }
        cout << ans << "\n";
    }
}
