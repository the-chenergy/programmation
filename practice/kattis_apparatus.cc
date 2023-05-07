/* Solution to "Apparatus", a problem from the Spotify Challenge 2010
   (https://open.kattis.com/problems/apparatus).

   I did this a fairly naive way: for each switch, find out which lights could
   be the corresponding one by trying all switch/light combos and checking all
   photos in O(N * N * M). These possible lights will form groups, similar to
   being joined when using a union-find, and each group produces K! orderings, K
   being the group size.

   I thought that's already fast enough if I abused C++'s bitset, and I was
   correct amazingly. But there definitely exists a more efficient way to do
   this, with a smaller big-O. Though I'm very happy that knowing bitset helped
   me "cheat" with a slow algorithm. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;

    const int N = 1000;
    static bitset<N> a[N][2];
    for (int i = 0; i < m; i++) {
        for (int j : {0, 1}) {
            for (int k = 0; k < n; k++) {
                char c;
                cin >> c;
                a[i][j][k] = c == '1';
            }
        }
        if (a[i][0].count() != a[i][1].count()) {
            cout << "0\n";
            exit(0);
        }
    }

    static bitset<N> p[N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) p[i].set(j);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][0][j]) p[j] &= a[i][1];
            else p[j] &= ~a[i][1];
        }
    }

    long long mod = 1000003;
    static long long fac[1001] = {1};
    for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;

    long long ans = 1;
    static bitset<N> seen;
    for (int i = 0; i < n; i++) {
        if (!p[i].count()) {
            cout << "0\n";
            exit(0);
        }
        if ((seen & p[i]).count()) continue;
        ans = ans * fac[p[i].count()] % mod;
        seen |= p[i];
    }
    cout << ans << "\n";
}
