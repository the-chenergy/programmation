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
    for (int i = 0; i < 10; ++i) {
        map<int, string> ins;
        for (int j = 0; j + 2 <= (int)s.size(); ++j) {
            auto t = s.substr(j, 2);
            if (g.count(t)) {
                ins[j] = g[t];
            }
        }
        string t;
        for (int j = 0; j < (int)s.size(); ++j) {
            t += s[j];
            if (ins.count(j)) {
                t += ins[j];
            }
        }
        s = t;
    }
    map<char, int> c;
    for (auto x : s) {
        ++c[x];
    }
    vector<int> f;
    for (auto [x, y] : c) {
        f.push_back(y);
    }
    sort(f.begin(), f.end());
    cout << f.back() - f[0] << "\n";
}
