#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<string> g;
    for (string s; cin >> s;) {
        g.push_back(s);
    }
    int h = int(g.size()), w = int(g[0].size());
    int t = 0;
    while (1) {
        ++t;
        auto ng = g, g0 = g;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (g[y][x] == '>' && g[y][(x + 1) % w] == '.') {
                    swap(ng[y][x], ng[y][(x + 1) % w]);
                }
            }
        }
        g = ng;
        for (int x = 0; x < w; ++x) {
            for (int y = 0; y < h; ++y) {
                if (g[y][x] == 'v' && g[(y + 1) % h][x] == '.') {
                    swap(ng[y][x], ng[(y + 1) % h][x]);
                }
            }
        }
        g = ng;
        if (g == g0) {
            cout << t << "\n";
            exit(0);
        }
    }
}
