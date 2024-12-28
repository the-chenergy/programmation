#include <bits/stdc++.h>
using namespace std;

int main() {
    array<int, 2> p = {4, 8};
    if (01) {
        p = {1, 6};
    }
    --p[0], --p[1];
    static long long dp[10][10][31][31][2][2];
    for (int x = 0; x < 10; ++x) {
        for (int y = 0; y < 10; ++y) {
            for (int t = 21; t <= 30; ++t) {
                for (int u = 0; u < 21; ++u) {
                    dp[x][y][t][u][1][0] = dp[x][y][u][t][0][1] = 1;
                }
            }
        }
    }
    for (int t = 20; t >= 0; --t) {
        for (int u = 20; u >= 0; --u) {
            for (int x = 0; x < 10; ++x) {
                for (int y = 0; y < 10; ++y) {
                    for (int i : {1, 2, 3}) {
                        for (int j : {1, 2, 3}) {
                            for (int k : {1, 2, 3}) {
                                dp[x][y][t][u][0][0] += dp[(x + i + j + k) % 10][y][t + (x + i + j + k) % 10 + 1][u][1][0];
                                dp[x][y][t][u][0][1] += dp[(x + i + j + k) % 10][y][t + (x + i + j + k) % 10 + 1][u][1][1];
                                dp[x][y][t][u][1][0] += dp[x][(y + i + j + k) % 10][t][u + (y + i + j + k) % 10 + 1][0][0];
                                dp[x][y][t][u][1][1] += dp[x][(y + i + j + k) % 10][t][u + (y + i + j + k) % 10 + 1][0][1];
                            }
                        }
                    }
                }
            }
        }
    }
    cout << max(dp[p[0]][p[1]][0][0][0][0], dp[p[0]][p[1]][0][0][0][1]) << "\n";
}
