/* Solution to "Circle", a problem from the Croatian Regional Competition in
   Informatics 2007. https://open.kattis.com/problems/circle

   Each transformation only introduces at most two possibilities -- either the
   first chair being black or white. The rest of chairs would've been forced, as
   only there's only one possible color for the next chair to make the resulting
   XOR value after transformation. So K <= 10 transformations should end up with
   <= 1024 configurations. Generate all configs and deduplicate them by
   comparing all rotations of each config. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    using B = bitset<100>;
    B s = {};
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        s[i] = c == 'W';
    }
    for (int _i = 0; _i < k; _i++) {
        B t = {};
        for (int i = 0; i < n; i++) t[i] = s[i] ^ s[(i + 1) % n];
        s = t;
    }
    deque<B> ans = {s};
    B a, ones = {};
    for (int i = 0; i < n; i++) ones.set(i);
    for (int _i = 0; _i < k; _i++) {
        for (auto _s = ans.size(); _s--;) {
            a = ans.front();
            ans.pop_front();
            B b;
            b[0] = 0;
            for (int i = 1; i < n; i++) {
                b[i] = b[i - 1] ^ a[i - 1];
            }
            if ((b[0] ^ b[n - 1]) != a[n - 1]) continue;
            ans.push_back(b);
            ans.push_back(b ^ ones);
        }
    }
    unordered_set<B> norm;
    for (auto b : ans) {
        B c;
        int ok = 1;
        for (int r = 0; ok && r < n; r++) {
            for (int i = 0; i < n; i++) c[(i + r) % n] = b[i];
            if (norm.count(c)) {
                ok = 0;
                break;
            }
        }
        if (ok) norm.insert(b);
    }
    cout << norm.size() << "\n";
}
