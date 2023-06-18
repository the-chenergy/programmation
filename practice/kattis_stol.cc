/* Solution to Stol. (https://open.kattis.com/problems/stol)

   Scan row by row from top to bottom. For each row, maintain P[x] := number of
   empty spaces in column x seen in a row. Now this becomes similar to the max
   area in histogram problem, which can be solved with a monotonic stack in
   O(W). Overall it's O(H * W). */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int h, w;
    cin >> h >> w;
    const int N = 1001;
    static char g[N][N];
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) cin >> g[y][x];
    }

    static int pre[N];
    int ans = 0;
    for (int y = 0; y < h; y++) {
        static deque<pair<int, int>> st(N);
        st = {};
        for (int x = 0; x <= w; x++) {
            pre[x] = x == w || g[y][x] == 'X' ? 0 : pre[x] + 1;
            int px = x;
            while (st.size() && pre[x] < st.back().first) {
                auto [p2, x2] = st.back();
                ans = max(ans, 2 * (p2 + x - x2) - 1);
                px = x2;
                st.pop_back();
            }
            st.push_back({pre[x], px});
        }
    }
    cout << ans << "\n";
}
