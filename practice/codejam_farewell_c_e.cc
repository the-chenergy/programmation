/* Solution to "Game Sort: Part 2", problem E from the Google Code Jam Farewell
   Round C.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95433/0000000000cad339)

   Annoying.

   Can't imagine how IMPOSSIBLE\n this problem was in live contest with the
   hidden verdict.
*/

#include <bits/stdc++.h>
using namespace std;

static void solve(int /* case_id */) {
    int p, n;
    string s;
    cin >> p >> s;
    n = (int)s.size();

    auto ans = [&](int y) { cout << (y ? "POSSIBLE\n" : "IMPOSSIBLE\n"); };

    if (p == n) {
        for (int k = 1; k < n; k++) {
            if (s[k - 1] > s[k]) {
                ans(1);
                for (auto c : s) cout << c << " ";
                cout << "\n";
                return;
            }
        }
        ans(0);
        return;
    }

    if (p >= 3) {
        if (s[0] == s[1] && s[1] >= s[2]) {
            ans(1);
            cout << s.substr(0, 2) << " " << s[2] << " ";
            int i = 3;
            p -= 3;
            for (; p; p--, i++) cout << s[i] << " ";
            cout << s.substr(i) << "\n";
            return;
        }
        if (s[n - 3] == s[n - 2] && s[n - 2] == s[n - 1]) {
            ans(1);
            int i = 0;
            p -= 3;
            for (; p; p--, i++) cout << s[i] << " ";
            cout << s.substr(i, n - 3 - i) << " " << s.substr(n - 3, 2) << " "
                 << s[n - 1] << "\n";
            return;
        }
        if (s[n - 3] > s[n - 2] && s[n - 2] == s[n - 1]) {
            ans(1);
            int i = 0;
            p -= 3;
            for (; p; p--, i++) cout << s[i] << " ";
            cout << s.substr(i, n - 3 - i) << " " << s[n - 3] << " "
                 << s.substr(n - 2) << "\n";
            return;
        }
        if (s[0] > s[1]) {
            ans(1);
            cout << s[0] << " " << s[1] << " ";
            int i = 2;
            p -= 3;
            for (; p; p--, i++) cout << s[i] << " ";
            cout << s.substr(i) << "\n";
            return;
        }
        if (s[n - 2] > s[n - 1]) {
            ans(1);
            int i = 0;
            p -= 3;
            for (; p; p--, i++) cout << s[i] << " ";
            cout << s.substr(i, n - 2 - i) << " " << s[n - 2] << " " << s[n - 1]
                 << "\n";
            return;
        }
    }

    if (p >= 4) {
        for (int k = 2; k < n - 1; k++) {
            if (s[k - 1] > s[k]) {
                ans(1);
                int i = 0;
                p -= 4;
                for (; p && i < k - 1; p--, i++) cout << s[i] << " ";
                cout << s.substr(i, k - 1 - i) << " " << s[k - 1] << " " << s[k]
                     << " ";
                p += i == k - 1;
                i = k + 1;
                for (; p; p--, i++) cout << s[i] << " ";
                cout << s.substr(i, n - i) << "\n";
                return;
            }
        }
        for (int k = 1; k + 3 <= n - 1; k++) {
            if (s[k] == s[k + 1] && s[k + 1] == s[k + 2]) {
                ans(1);
                int i = 0;
                p -= 4;
                for (; p && i < k; p--, i++) cout << s[i] << " ";
                cout << s.substr(i, k - i) << " " << s.substr(k, 2) << " "
                     << s[k + 2] << " ";
                p += i == k;
                i = k + 3;
                for (; p; p--, i++) cout << s[i] << " ";
                cout << s.substr(i, n - i) << "\n";
                return;
            }
        }
        ans(0);
        return;
    }

    static int ct_l[100001][26], ct_r[100001][26];
    memset(ct_l[0], 0, sizeof(ct_l[0]));
    ct_l[0][s[0] - 'A']++;
    for (int i = 1; i < n; i++) {
        memcpy(ct_l[i], ct_l[i - 1], sizeof(ct_l[0]));
        ct_l[i][s[i] - 'A']++;
    }
    memset(ct_r[n], 0, sizeof(ct_r[0]));
    for (int i = n - 1; i >= 0; i--) {
        memcpy(ct_r[i], ct_r[i + 1], sizeof(ct_r[0]));
        ct_r[i][s[i] - 'A']++;
    }

    for (int k = n - 1; k > 0;) {
        int j = k - 1;
        while (j > 0 && s[j] == s[k]) j--;
        int ok = [&]() -> int {
            int t = s[k] - 'A';
            for (int c = t - 1; c >= 0; c--)
                if (ct_l[j][c]) return 0;
            if (!(ct_l[j][t] < k - j || (ct_l[j][t] == k - j && j + 1 > k - j)))
                return 0;
            for (int c = t + 1; c < 26; c++)
                if (ct_l[j][c]) return 1;
            return 0;
        }();
        if (ok) {
            ans(1);
            cout << s.substr(0, j + 1) << " " << s.substr(j + 1, k - j) << " "
                 << s.substr(k + 1) << "\n";
            return;
        }
        if (p == 2) break;
        k = j;
    }
    for (int k = 0; k < n - 1;) {
        int j = k + 1;
        while (j < n - 1 && s[j] == s[k]) j++;
        int ok = [&]() -> int {
            int t = s[k] - 'A';
            for (int c = t + 1; c < 26; c++)
                if (ct_r[j][c]) return 0;
            return ct_r[j][t] < j - k;
        }();
        if (ok) {
            ans(1);
            cout << s.substr(0, k) << " " << s.substr(k, j - k) << " "
                 << s.substr(j) << "\n";
            return;
        }
        if (p == 2) break;
        k = j;
    }

    for (int mn = s[0] - 'A', k = 1; k < n; k++) {
        int ok = [&]() -> int {
            for (int c = mn; c < 26; c++)
                if (ct_r[k][c]) return 0;
            return 1;
        }();
        if (ok) {
            assert(p == 2);
            ans(1);
            cout << s.substr(0, k) << " " << s.substr(k) << "\n";
            return;
        }
        mn = min(mn, s[k] - 'A');
    }

    ans(0);
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
