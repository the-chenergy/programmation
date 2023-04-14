/**
    Solution to "Memory Device", a problem from NUS Competitive Programming.

    Use a BST to record, for each free block size, what are the starting indices
    to free blocks with that size. (E.g. {3 -> {0, 42}} means there are two free
    blocks with size three, one starting at 0 and one at 42.)

    Use a segment tree to record the smallest index for each free block size.
    This can be maintained by reaching into the BST and getting the minimum
    index for a particular size. (E.g. {inf, inf, 42, inf, 7} means the first
    free block of size 2 starts at index 42, the first block of size 4 starts at
    7, and there are no free blocks of sizes 1 and 3.) This way we can query
    (l, n) to find the first free block of size at least l.

    Use another BST to record the free blocks themselves, represented by a
    sequence of non-overlapping intervals. Now the deallocation step is
    basically inserting an interval and updating the other data structures while
    resolving the overlaps.

    All operations here should be O(log N). The deallocation step does require
    us to linearly traverse and merge any overlapping free blocks, which sounds
    like O(N). However that would require O(N) allocation/deallocation steps in
    order to get that many free blocks in the first place, meaning the
    deallocation actually takes O((log N + Q) / Q) or still O(log N) amortized.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    const int N = 300'001, inf = 1E9;

    static int st[2 * N];
    static set<int> ind[N];
    static set<pair<int, int>> fre;

    int n, q;
    cin >> n >> q;

    memset(st, 63, sizeof(st));
    auto upd = [&](int i, int x) -> void {
        for (st[i += n + 1] = x; i /= 2;) st[i] = min(st[i * 2], st[i * 2 + 1]);
    };
    auto que = [&](int b, int e) -> int {
        int ans = inf;
        for (b += n + 1, e += n + 1; b < e; b /= 2, e /= 2) {
            if (b % 2) ans = min(ans, st[b++]);
            if (e % 2) ans = min(ans, st[--e]);
        }
        return ans;
    };

    for (int l = 0; l <= n; l++) ind[l].insert(inf);
    ind[n].insert(0);
    upd(n, 0);
    fre.insert({0, n});

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l;
            cin >> l;
            int b = que(l, n + 1);
            if (b >= inf) {
                cout << "-1\n";
                continue;
            }
            cout << b << "\n";
            auto it = fre.lower_bound({b, 0});
            int e = it->second;
            ind[e - b].erase(b);
            upd(e - b, *ind[e - b].begin());
            fre.erase(it);
            if (e - (b + l)) {
                ind[e - (b + l)].insert(b + l);
                upd(e - (b + l), *ind[e - (b + l)].begin());
                fre.insert({b + l, e});
            }
        } else {
            int b, l, was = 0;
            cin >> b >> l;
            int e = b + l;
            auto it = fre.lower_bound({b, e});
            while (it != fre.end() && it->first <= e) {
                auto [ob, oe] = *it;
                was += min(e, oe) - ob;
                ind[oe - ob].erase(ob);
                upd(oe - ob, *ind[oe - ob].begin());
                e = max(e, oe);
                it = fre.erase(it);
            }
            if (it != fre.begin() && (--it)->second >= b) {
                auto [ob, oe] = *it;
                was += min(e, oe) - max(b, ob);
                ind[oe - ob].erase(ob);
                upd(oe - ob, *ind[oe - ob].begin());
                b = min(b, ob);
                e = max(e, oe);
                fre.erase(it);
            }
            cout << l - was << "\n";
            ind[e - b].insert(b);
            upd(e - b, *ind[e - b].begin());
            fre.insert({b, e});
        }
    }
}
