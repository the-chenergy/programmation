#include <bits/stdc++.h>
using namespace std;

int main() {
    int l, r, t, b;
    l = 60, r = 94, b = -171, t = -136;
    if (0) {
        l = 20, r = 30, b = -10, t = -5;
    }
    int ans = 0;
    for (int sdx = 0; sdx <= 420; ++sdx) {
        for (int sdy = -420; sdy <= 999; ++sdy) {
            int dx = sdx, dy = sdy, x = 0, y = 0, mxy = 0, ok = 0;
            for (int i = 0; i < 420; ++i) {
                x += dx, y += dy, mxy = max(mxy, y);
                if (x >= l && x <= r && y >= b && y <= t) {
                    ok = 1;
                    break;
                }
                dx -= (dx > 0) - (dx < 0);
                --dy;
            }
            if (ok) {
                ++ans;
            }
        }
    }
    cout << ans << "\n";
}
