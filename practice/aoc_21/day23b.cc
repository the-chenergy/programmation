#include <bits/stdc++.h>
using namespace std;

int main() {
    const int n = 23;
    static array<int, 2> g[n][n];
    [&] {
        vector<string> w = {
            "#############",
            "#...........#",
            "###C#C#B#D###",
            "  #D#C#B#A#  ",
            "  #D#B#A#C#  ",
            "  #D#A#B#A#  ",
            "  #########  ",
        };
        int loc[][2] = {0, 0, 0, 1, 0, 3, 0, 5, 0, 7, 0, 9, 0, 10, 1, 2, 1, 4, 1, 6, 1, 8, 2, 2, 2, 4, 2, 6, 2, 8, 3, 2, 3, 4, 3, 6, 3, 8, 4, 2, 4, 4, 4, 6, 4, 8};
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
    using P = array<array<int, 4>, 4>;  // p[guy_type] = sorted(rooms_with_this_guy_type)
    P T = {{{{7, 11, 15, 19}}, {{8, 12, 16, 20}}, {{9, 13, 17, 21}}, {{10, 14, 18, 22}}}};

    priority_queue<pair<int, P>> q;
    if (0) {
        P p = {{{{14, 17, 19, 22}}, {{7, 9, 13, 16}}, {{8, 12, 18, 21}}, {{10, 11, 15, 20}}}};
        q.push({0, p});
    } else {
        P p = {{{{14, 17, 20, 22}}, {{9, 13, 16, 21}}, {{7, 8, 12, 18}}, {{10, 11, 15, 19}}}};
        q.push({0, p});
    }
    // P p0 = {{{{5, 11}}, {{8, 12}}, {{9, 13}}, {{10, 14}}}};
    P p0 = {{{{0, 1, 19, 22}}, {{4, 5, 13, 16}}, {{8, 12, 18, 21}}, {{6, 11, 15, 20}}}};
    map<P, int> b = {{q.top().second, 0}};
    while (q.size()) {
        auto [c, u] = q.top();
        c *= -1;
        q.pop();
        int sus = 0;
        if (u == p0) {
            // println("Was there");
            // sus = 1;
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
        if (0 || rand() % (1 << 13) == 0) {
            println("c={} |q|={}", c, q.size());
            print("\tu=( ");
            for (int i = 0; i < 4; ++i) {
                print("{{ ");
                for (int j = 0; j < 4; ++j) {
                    print("{} ", u[i][j]);
                }
                print("}} ");
            }
            print("\n");
        }
        int h = 0, room_has_bad_guy[4] = {};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int x = u[i][j];
                h |= 1 << x;
                if (x >= 7 && dest_guy_by_room[x % 4] != i) {
                    room_has_bad_guy[x % 4] = 1;
                    // println("\tRoom {} has bad guy {} (that room is for guy type {})", x % 4, i, dest_guy_by_room[x % 4]);
                }
            }
        }
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                int x = u[i][j];
                if (sus && x == 8) {
                    println("\tHi, suspicious guy of type {} at point {}", i, x);
                    exit(1);
                }
                for (int y = 0; y < n; ++y) {
                    if (y == x || g[x][y][1] & h) {
                        continue;
                    }
                    if (y >= 7) {
                        if (x >= 7 && x % 4 == y % 4) {
                            continue;
                        }
                        if (y % 4 != dest_room_by_guy[i]) {
                            // println("\tGuy of type {} can't move from point {} to point {} because he belongs in room {}, not room {}", i, x, y, dest_room_by_guy[i], y % 4);
                            continue;
                        }
                        if (room_has_bad_guy[y % 4]) {
                            continue;
                        }
                        if ([&]() -> int {
                                for (int yy = y + 4; yy < n; yy += 4) {
                                    if (~h >> yy & 1) {
                                        return 1;
                                    }
                                }
                                return 0;
                            }()) {
                            continue;
                        }
                    } else if (x < 7) {
                        continue;
                    }
                    auto v = u;
                    v[i][j] = y;
                    sort(v[i].begin(), v[i].end());
                    if (!(v[i][0] != v[i][1] && v[i][1] != v[i][2] && v[i][2] != v[i][3])) {
                        println("\tBad: i={} j={} v[i]: {} {} {} {}", i, j, v[i][0], v[i][1], v[i][2], v[i][3]);
                        exit(1);
                    }
                    // if (v[i][0] > v[i][1]) {
                    //     swap(v[i][0], v[i][1]);
                    // }
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
