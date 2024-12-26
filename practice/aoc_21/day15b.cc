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
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (!j) {
                if (!i) {
                    continue;
                }
                g.resize(g.size() + h);
            }
            for (int y = 0; y < h; ++y) {
                for (int x = 0; x < w; ++x) {
                    int p = i ? g[(i - 1) * h + y][j * h + x] : g[i * h + y][(j - 1) * h + x];
                    g[i * h + y].push_back(p == 9 ? 1 : p + 1);
                }
            }
        }
    }
    h *= 5, w *= 5;
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
