/* Solution to "SMS Typing" (https://open.kattis.com/problems/sms).

   This is an interesting (double-)trie problem. The idea should be fairly
   straightforward and easy to come up with: use one trie to store the
   dictionary words, mapping each word into number keys and therefore finding
   its order in the IME list. Then use another trie, flattening the keys into
   plain english letters, to record how many key presses are needed to type each
   word. This allows efficient look-ups while we do the backward DP. The running
   time overall should be O(D + LK), where D is the total number of letters in
   the dictionary, K is the total in the queries, and L is the maximum word
   length. Essentially this solution got away with the very short word length L.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;

    static int t1[2000001][9], t1s = 1, t1ds;
    static vector<string> t1d[200001];
    static string s;
    const int ctk[] = {0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4,
                       4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 7};
    for (int i = 0; i < n; i++) {
        cin >> s;
        int u = 0;
        for (auto c : s) {
            auto& v = t1[u][ctk[c - 'a']];
            if (!v) v = t1s++;
            u = v;
        }
        int& d = t1[u][8];
        if (!d) d = ++t1ds;
        t1d[d - 1].push_back(s);
    }

    static int t2[2000001][27], t2s = 1;
    for (int i = 0; i < t1ds; i++) {
        auto& d = t1d[i];
        int l = (int)d.size();
        for (int j = 0; j <= l / 2; j++) {
            int u = 0;
            for (auto c : d[j]) {
                auto& v = t2[u][c - 'a'];
                if (!v) v = t2s++;
                u = v;
            }
            t2[u][26] = j + 1;
        }
        for (int j = l - 1; j > l / 2; j--) {
            int u = 0;
            for (auto c : d[j]) {
                auto& v = t2[u][c - 'a'];
                if (!v) v = t2s++;
                u = v;
            }
            t2[u][26] = -(l - j);
        }
    }

    int q;
    cin >> q;
    while (q--) {
        cin >> s;
        int m = (int)s.size();
        static tuple<long long, int, int> dp[500001];
        dp[m] = {0, 0, 0};
        for (int i = m - 1; i >= 0; i--) {
            auto& ans = dp[i] = {LLONG_MAX / 2, 0, 0};
            int u = 0;
            for (int j = i; j < m; j++) {
                u = t2[u][s[j] - 'a'];
                if (!u) break;
                if (int p = t2[u][26]; p) {
                    int pa = p < 0 ? -p : p - 1;
                    ans = min(ans,
                              tuple{1 + (j + 1 - i) + pa + get<0>(dp[j + 1]),
                                    j + 1, p});
                }
            }
        }

        assert(get<0>(dp[0]) < LLONG_MAX / 2);
        for (int i = 0; i < m;) {
            if (i) cout << "R";
            auto [_, j, p] = dp[i];
            for (; i < j; i++) cout << ctk[s[i] - 'a'] + 2;
            int pa = p < 0 ? -p : p - 1;
            if (pa) cout << (p < 0 ? "D" : "U") << "(" << pa << ")";
        }
        cout << "\n";
    }
}
