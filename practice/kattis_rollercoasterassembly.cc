/* Solution to "Roller Coaster Assembly", a problem from the LTH Challenge 2021
   (https://open.kattis.com/problems/rollercoasterassembly).

   Not too difficult to come up with the following:
       f(i) := max(
           A[i] + c(i, j) + f(j + 1) for j > i and B[j] >= A[i],
           B[j] + c(i, j) + f(j + 1) for j > i and B[j] < A[i]
       )
   where c(i, j) := min(B[i], A[i + 1]) + ... + min(B[j - 1], A[j]).

   So, two lazy sparse segment trees will do it. One includes B[i] as we sweep
   from right to left, ane one doesn't. Look up both with A[i] being the cutting
   point to determine dp[i]. */

#include <bits/stdc++.h>
using namespace std;

#pragma region
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"

/* Source: KACTL */

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

using T = long long;
const T inf = 1E18;

/**
 * Author: Simon Lindholm
 * Date: 2016-10-08
 * License: CC0
 * Source: me
 * Description: Segment tree with ability to add or set values of large
 * intervals, and compute max of intervals. Can be changed to other things. Use
 * with a bump allocator for better performance, and SmallPtr or implicit
 * indices to save memory. Time: O(\log N). Usage: Node* tr = new Node(v, 0,
 * sz(v)); Status: stress-tested a bit
 */
struct Node {
    Node *l = 0, *r = 0;
    T lo, hi, mset = inf, madd = 0, val = -inf;
    Node(T lo, T hi) : lo(lo), hi(hi) {}  // Large interval of -inf
    Node(vi& v, T lo, T hi) : lo(lo), hi(hi) {
        if (lo + 1 < hi) {
            T mid = lo + (hi - lo) / 2;
            l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
            val = max(l->val, r->val);
        } else val = v[lo];
    }
    T query(T L, T R) {
        if (R <= lo || hi <= L) return -inf;
        if (L <= lo && hi <= R) return val;
        push();
        return max(l->query(L, R), r->query(L, R));
    }
    void set(T L, T R, T x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) mset = val = x, madd = 0;
        else {
            push(), l->set(L, R, x), r->set(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void add(T L, T R, T x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf) mset += x;
            else madd += x;
            val += x;
        } else {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = max(l->val, r->val);
        }
    }
    void push() {
        if (!l) {
            T mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
        if (mset != inf) l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
        else if (madd) l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    }
};

#pragma GCC diagnostic pop
#pragma endregion

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;
    vector<pair<long long, long long>> a(n);
    for (auto& [x, y] : a) cin >> x >> y;

    vector<long long> lim(n);
    for (int i = 1; i < n; i++) lim[i] = min(a[i].first, a[i - 1].second);

    Node hi(0, inf), lo(0, inf);
    vector<long long> dp(n + 1, 0);
    dp[n - 1] = -inf;
    for (int i = n - 2; i >= 0; i--) {
        auto [x, y] = a[i];
        hi.add(0, inf, lim[i + 1]);
        hi.set(a[i + 1].second, a[i + 1].second + 1, lim[i + 1] + dp[i + 2]);
        lo.add(0, inf, lim[i + 1]);
        lo.set(a[i + 1].second, a[i + 1].second + 1,
               lim[i + 1] + dp[i + 2] + a[i + 1].second);
        dp[i] = max(x + hi.query(x, inf), lo.query(0, x));
    }
    cout << dp[0] << "\n";
}
