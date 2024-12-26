#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    map<string, string> g;
    while (1) {
        string t, u;
        cin >> t >> u >> u;
        if (!cin) {
            break;
        }
        g[t] = u;
    }
    map<tuple<string, int, char>, long long> dp;
    for (char c = 'A'; c <= 'Z'; ++c) {
        for (char d = 'A'; d <= 'Z'; ++d) {
            string t;
            t += c;
            t += d;
            ++dp[{t, 0, c}];
            ++dp[{t, 0, d}];
        }
    }
    for (int st = 1; st <= 40; ++st) {
        for (char c = 'A'; c <= 'Z'; ++c) {
            for (char d = 'A'; d <= 'Z'; ++d) {
                string t = string() + c + d;
                if (!g.count(t)) {
                    ++dp[{t, st, c}];
                    ++dp[{t, st, d}];
                    continue;
                }
                auto e = g[t][0];
                for (char f = 'A'; f <= 'Z'; ++f) {
                    dp[{t, st, f}] += dp[{string() + t[0] + e, st - 1, f}] + dp[{string() + e + t[1], st - 1, f}];
                }
                --dp[{t, st, e}];
            }
        }
    }
    map<char, long long> c;
    for (int i = 0; i < (int)s.size() - 1; ++i) {
        for (char d = 'A'; d <= 'Z'; ++d) {
            c[d] += dp[{s.substr(i, 2), 40, d}];
        }
        if (i) {
            --c[s[i]];
        }
    }
    long long mx = 0, mn = LLONG_MAX / 2;
    for (auto [x, y] : c) {
        if (y) {
            mx = max(mx, y);
            mn = min(mn, y);
        }
    }
    cout << mx - mn << "\n";
}
