#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    static long long h[100001];
    for (int i = 0; i < n; i++) cin >> h[i];
    long long mxi = max_element(h, h + n) - h;
    if (mxi == 0) {
        cout << "1\n";
        exit(0);
    }
    long long ans = 0;
    for (long long i = mxi - 1; i >= 0; i--) {
        if (h[i] <= h[0]) continue;
        long long l = (h[i] - (h[0] + 4)) * (mxi - i) / (h[mxi] - h[i]) + 1 - i;
        ans = max(ans, l);
    }
    cout << ans << "\n";
}
