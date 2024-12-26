#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<vector<int>> g;
    for (string s; cin >> s;) {
        g.emplace_back();
        for (auto x : s) {
            g.back().push_back(x - '0');
        }
    }
    int h = (int)g.size(), w = (int)g[0].size();
    priority_queue<array<int, 3>> q;
    q.push({0, 0, 0});
    auto b = vector(h, vector(w, INT_MAX / 2));
    b[0][0] = 0;
    while (q.size()) {
        auto [c, y, x] = q.top();
        q.pop();
        c *= -1;
        if (y == h - 1 && x == w - 1) {
            cout << c << "\n";
            exit(0);
        }
        if (c > b[y][x]) {
            continue;
        }
        static int ds[][2] = {0, 1, 1, 0, 0, -1, -1, 0};
        for (auto [ay, ax] : ds) {
            ay += y, ax += x;
            if (ay < 0 || ay >= h || ax < 0 || ax >= w) {
                continue;
            }
            int c2 = c + g[ay][ax];
            if (b[ay][ax] <= c2) {
                continue;
            }
            b[ay][ax] = c2;
            q.push({-c2, ay, ax});
        }
    }
}
