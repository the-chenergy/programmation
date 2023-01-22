// Solution to Candies, problem D from the Google Kick Start 2020 Round C
// (https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ff43/0000000000337b4d)
// #array #prefix_array #segment_tree
//
// The idea is to use the segment tree, but one tree probably isn't enough to
// deal with both the sign flipping and the progressive sums. I used multiple
// trees and combined values from them to answer each query.
//
// My strategy was to maintain the following four segment trees. All four should
// support range sum queries, while the first two support range updates and the
// last two support single-item updates.
//   1. sum(A[1..n]), sum(A[3..n]), sum(A[3..n]), sum(A[5..n]), sum(A[5..n])...
//   2. sum(A[2..n]), sum(A[4..n]), sum(A[4..n]), sum(A[6..n]), sum(A[6..n])...
//   3. A[1], 0, A[3], 0, A[5], 0, ...
//   4. A[2], 0, A[4], 0, A[6], 0, ...
//
// Now to retrieve (A[l] - 2 * A[l+1] + 3 * A[l+2] - ...) for any interval, take
// the appropriate range sums and add or subtract them depending on the parity.
// For example when l is odd, the result should be a range sum from tree #1,
// minus a range sum from tree #3 times the window size, minus a range sum from
// tree #2, plus a range sum from tree #4 times the window size. (Details need
// to be worked out to avoid index errors.)
//
// To update a single element, just update trees #1 and #3 if the index is odd
// and #2 and #4 if even. For trees #1 and #2 we need to update the range(0, i)
// to maintain the aggregated values.
//
// If done correctly every operation should be O(log N). So the total running
// time is O((N + Q) log N) with extra pain to code it up.

// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

bool _v = false;

#pragma region programmation {
#pragma region common {  // clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef DEBUG
#    define DEBUG 0
#endif
#if DEBUG
#    define _GLIBCXX_DEBUG 1
#    define _GLIBCXX_DEBUG_PEDANTIC 1
#    define _FORTIFY_SOURCE 2
#    pragma GCC optimize("trapv")
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)  // printf into cerr
#    endif
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), 0)  // trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define view(...) (_view(__VA_ARGS__), trace(""), 0)  // view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define debug
#else
#    define eprintf(...) (void)0
#    define trace(...) ((void)0, 0)
#    define view(...) ((void)0, 0)
#    define debug while (0)
#endif
#include <bits/stdc++.h>
#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)
#define sz len
#define _print_vector_impl s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}";
using namespace std; using ll = long long; using ull = unsigned long long; using ld = long double; using vi = vector<int>; using pii = pair<int, int>; template <typename T> int len(const T& x) { return int(x.size()); } template <typename T, size_t l> int len(const T (&)[l]) { return l; } template <typename T, typename S> bool amax(T& t, S s) { return t < s && (t = s, 1); } template <typename T, typename S> bool amin(T& t, S s) { return s < t && (t = s, 1); } int num_cases = 1, case_id; namespace std { template <typename T, size_t l> ostream& operator<<(ostream& s, const array<T, l>& x); template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x); template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x); template <typename C, typename T = enable_if_t<!is_same<C, string>::value, typename C::value_type>> ostream& operator<<(ostream& s, const C& x) { _print_vector_impl } template <typename T, size_t l, enable_if_t<!is_same<T, char>::value, int> = 0> ostream& operator<<(ostream& s, const T (&x)[l]) { _print_vector_impl } template <typename T, size_t l> ostream& operator<<(ostream& s, const std::array<T, l>& x) { _print_vector_impl } template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x) { return s << "{" << x.first << ", " << x.second << "}"; } template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x) { s << "{"; string d; apply([&](auto&&... y) { (..., (s << d << y, d = ", ")); }, x); return s << "}"; } } struct _teed_cout { bool _b = 0; ofstream _f; void open(const char* s) { _f.open(s), _b = 1; } template <typename T> _teed_cout& operator<<(const T& x) { return cout << x, _b && (_f << x), *this; } } _teed_cout; ostream& _cout = cout;
#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
#    define cout _teed_cout  // Outputs to both console and file. Access original cout via _cout.
#endif
template <typename T> void _trace(const char* l, const T& x) { if (l[0] != '"') _trace_out << l + (l[0] == ' ') << ": "; _trace_out << x << "\n"; } template <typename T, typename... A> void _trace(const char* l, const T& x, const A&... a) { if (l[0] == ' ') l++; size_t s = strchr(l, ',') - l; if (l[0] != '"') _trace_out.write(l, s) << ": "; _trace_out << x << ", ", _trace(l + s + 1, a...); } template <typename T> void _view(const T& x) { _trace_out << x; } template <typename T, typename... R> void _view(const T& x, int b, int e, R... r) { b < 0 && (b += len(x)), e < 0 && (e += len(x)); b = min(max(b, 0), len(x)), e = min(max(e, b), len(x)); auto it = begin(x); advance(it, b); _trace_out << "{"; for (int i = b; i < e; it++, i++) { if (i != b) _trace_out << ", "; _view(*it, r...); } _trace_out << "}"; }
#if !SYNC_IO
void _init() __attribute__((constructor)); void _init() { ios::sync_with_stdio(0), cin.tie(0); }
#endif
#if !NO_MAIN
void solve_suite(); int main() { solve_suite(); }
#endif
#pragma endregion common }  // clang-format on

// Additional library code
/**
 * Author: Simon Lindholm
 * Date: 2015-09-12
 * License: CC0
 * Source: me
 * Description: When you need to dynamically allocate many objects and don't
 * care about freeing them. "new X" otherwise has an overhead of something like
 * 0.05us + 16 bytes per allocation. Status: tested
 */
// Either globally or in a single class:
static char buf[450 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*)&buf[i -= s];
}
void operator delete(void*) {}
void operator delete(void*, std::size_t) {}

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
const ll inf = 1e18;
struct Node {
    Node *l = 0, *r = 0;
    int lo, hi;
    ll mset = inf, madd = 0, val = 0;
    Node(int lo, int hi) : lo(lo), hi(hi) {}
    ll query(int L, int R) {
        if (R <= lo || hi <= L) return 0;
        if (L <= lo && hi <= R) return val;
        push();
        // if (_v) trace(L, R, l->query(L, R), r->query(L, R));
        return l->query(L, R) + r->query(L, R);
    }
    void set(int L, int R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R)
            mset = x, val = x * (hi - lo), madd = 0;
        else {
            push(), l->set(L, R, x), r->set(L, R, x);
            val = l->val + r->val;
        }
    }
    void add(int L, int R, ll x) {
        if (R <= lo || hi <= L) return;
        if (L <= lo && hi <= R) {
            if (mset != inf)
                mset += x;  //* (hi - lo);
            else
                madd += x;
            val += x * (hi - lo);
        } else {
            push(), l->add(L, R, x), r->add(L, R, x);
            val = l->val + r->val;
        }
    }
    void push() {
        if (!l) {
            int mid = lo + (hi - lo) / 2;
            l = new Node(lo, mid);
            r = new Node(mid, hi);
        }
        if (mset != inf)
            l->set(lo, hi, mset), r->set(lo, hi, mset), mset = inf;
        else if (madd)
            l->add(lo, hi, madd), r->add(lo, hi, madd), madd = 0;
    }
};

/**
 * Author: Lucian Bicsi
 * Date: 2017-10-31
 * License: CC0
 * Source: folklore
 * Description: Zero-indexed max-tree. Bounds are inclusive to the left and
 * exclusive to the right. Can be changed by modifying T, f and unit. Time:
 * O(\log N) Status: stress-tested
 */
struct Tree {
    typedef int T;
    static constexpr T unit = 0;
    T f(T a, T b) { return a + b; }  // (any associative fn)
    vector<T> s;
    int n;
    Tree(int n = 0, T def = unit) : s(2 * n, def), n(n) {}
    void update(int pos, T val) {
        for (s[pos += n] = val; pos /= 2;)
            s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
    }
    T query(int b, int e) {  // query [b, e)
        T ra = unit, rb = unit;
        for (b += n, e += n; b < e; b /= 2, e /= 2) {
            if (b % 2) ra = f(ra, s[b++]);
            if (e % 2) rb = f(s[--e], rb);
        }
        return f(ra, rb);
    }
};

#pragma GCC diagnostic pop
#pragma endregion programmation }

const int mxn = 200009;
Node* ept = new Node(0, mxn);
Node* opt = new Node(0, mxn);
Tree est(0), ost(0);
vector<ll> arr;
int n, q;

void clear() {
    ept->set(0, n, 0), opt->set(0, n, 0);
    est.s.assign(2 * n, est.unit), ost.s.assign(2 * n, ost.unit);
    est.n = ost.n = n;
    arr.assign(n, 0);
}

void print_() {
    if (!DEBUG) return;
    vector<ll> ept_, est_, opt_, ost_;
    for (int i = 0; i < n; i++) {
        ept_.push_back(ept->query(i, i + 1));
        opt_.push_back(opt->query(i, i + 1));
        est_.push_back(est.query(i, i + 1));
        ost_.push_back(ost.query(i, i + 1));
    }
    trace(arr, ept_, est_, opt_, ost_);
}

void update(int i, int x) {
    trace("update", i, x);
    if (i % 2) {
        opt->add(0, i + 1, x - arr[i]);
        ost.update(i, x);
    } else {
        ept->add(0, i + 1, x - arr[i]);
        est.update(i, x);
    }
    arr[i] = x;
}

ll query(int b, int e) {
    trace("query", b, e);
    ll a;
    int la, ls;
    la = (e + 1 - b + 1) & ~1, ls = (e + 1 - b) & ~1;
    if (b % 2) {
        a = opt->query(b, n);
        // ll $ = opt->query(1, 2) + opt->query(2, 3) + opt->query(3, 4) +
        //        opt->query(4, 5);
        // if (case_id == 1 && b == 1 && e == 3) _v = 1;
        // trace(a, $, opt->query(1, 5));
        // trace(a);
        // _v = 0;
        a -= opt->query(b + la, n);
        // trace(a);
        a -= ll(ost.query(e + 1, n)) * la;
        // trace(a, ost.query(e + 1, n));
        a -= ept->query(b, n);
        // trace(a, ept->query(1, 5));
        a += ept->query(b + ls, n);
        // trace(a);
        a += ll(est.query(e + 1, n)) * ls;
        // trace(a);
    } else {
        a = ept->query(b, n);
        trace(a, b);
        a -= ept->query(b + la, n);
        trace(a, (e - 1) / 2 * 2);
        a -= ll(est.query(e + 1, n)) * la;
        trace(a);
        a -= opt->query(b, n);
        trace(a);
        a += opt->query(b + ls, n);
        trace(a);
        a += ll(ost.query(e + 1, n)) * ls;
    }
    trace("query done", b, e, a);
    return a;
}

void solve() {
    cin >> n >> q;
    if (0 || !cin) exit(0);
    clear();
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        update(i, x);
    }
    print_();
    ll ans = 0;
    for (int i = 0; i < q; i++) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        trace("------------\n", i, c, a, b);
        if (c == 'Q')
            ans += query(a - 1, b - 1);
        else
            update(a - 1, b);
        print_();
    }
    cout << ans;
}

void solve_suite() {
    debug freopen("./sandbox/i.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    cin >> num_cases;
    // num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
