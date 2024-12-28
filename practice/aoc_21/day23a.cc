#include <bits/stdc++.h>
using namespace std;

int main() {
    const int n = 15;
    static array<int, 2> g[n][n];
    [&] {
        vector<string> w = {
            "#############",
            "#...........#",
            "###B#C#B#D###",
            "  #A#D#C#A#  ",
            "  #########  ",
        };
        int loc[][2] = {0, 0, 0, 1, 0, 3, 0, 5, 0, 7, 0, 9, 0, 10, 1, 2, 1, 4, 1, 6, 1, 8, 2, 2, 2, 4, 2, 6, 2, 8};
        array<int, 2> ds[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (int s = 0; s < n; ++s) {
            int sy = loc[s][0] + 1, sx = loc[s][1] + 1;
            auto f = [&](auto&& f, int y, int x, int py, int px, int d, int b) {
                if (w[y][x] == '#') {
                    return;
                }
                for (int t = 0; t < n; ++t) {
                    if (t != s && loc[t][0] + 1 == y && loc[t][1] + 1 == x) {
                        b |= 1 << t;
                        g[s][t] = {d, b};
                    }
                }
                for (auto [ay, ax] : ds) {
                    ay += y, ax += x;
                    if (ay == py && ax == px) {
                        continue;
                    }
                    f(f, ay, ax, y, x, d + 1, b);
                }
            };
            f(f, sy, sx, -1, -1, 0, 0);
        }
    }();
    int energy[] = {1, 10, 100, 1000}, dest_room_by_guy[] = {3, 0, 1, 2}, dest_guy_by_room[] = {1, 2, 3, 0};
    using P = array<array<int, 2>, 4>;  // p[guy_type] = sorted(rooms_with_this_guy_type)
    P T = {{{{7, 11}}, {{8, 12}}, {{9, 13}}, {{10, 14}}}};

    priority_queue<pair<int, P>> q;
    if (01) {
        P p = {{{{11, 14}}, {{7, 9}}, {{8, 13}}, {{10, 12}}}};
        q.push({0, p});
    } else {
        P p = {{{{12, 14}}, {{9, 13}}, {{7, 8}}, {{10, 11}}}};
        q.push({0, p});
    }
    P p0 = {{{{5, 11}}, {{8, 12}}, {{9, 13}}, {{10, 14}}}};
    map<P, int> b = {{q.top().second, 0}};
    while (q.size()) {
        auto [c, u] = q.top();
        c *= -1;
        q.pop();
        if (u == p0) {
            // println("Was there");
            // exit(1);
        }
        if (u == T) {
            println("{}", c);
            exit(0);
        }
        if (c > b[u]) {
            continue;
        }
        // println("c={} u=({{{} {}}} {{{} {}}} {{{} {}}} {{{} {}}})", c, u[0][0], u[0][1], u[1][0], u[1][1], u[2][0], u[2][1], u[3][0], u[3][1]);
        int h = 0, room_has_bad_guy[4] = {};
        for (int i = 0; i < 4; ++i) {
            for (int j : {0, 1}) {
                int x = u[i][j];
                h |= 1 << x;
                if (x >= 7 && dest_guy_by_room[x % 4] != i) {
                    room_has_bad_guy[x % 4] = 1;
                    // println("\tRoom {} has bad guy {} (that room is for guy type {})", x % 4, i, dest_guy_by_room[x % 4]);
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j : {0, 1}) {
                int x = u[i][j];
                for (int y = 0; y < n; ++y) {
                    if (y == x || g[x][y][1] & h) {
                        continue;
                    }
                    if (y >= 7) {
                        if (y % 4 != dest_room_by_guy[i]) {
                            // println("\tGuy of type {} can't move from point {} to point {} because he belongs in room {}, not room {}", i, x, y, dest_room_by_guy[i], y % 4);
                            continue;
                        }
                        if (room_has_bad_guy[y % 4]) {
                            continue;
                        }
                    } else if (x < 7) {
                        continue;
                    }
                    auto v = u;
                    v[i][j] = y;
                    if (v[i][0] > v[i][1]) {
                        swap(v[i][0], v[i][1]);
                    }
                    int nc = c + energy[i] * g[x][y][0];
                    if (b.count(v) && nc >= b[v]) {
                        continue;
                    }
                    b[v] = nc;
                    q.push({-nc, v});
                }
            }
        }
    }
}

/*
Too low:
15261
*/
