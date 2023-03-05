// Solution to Palindromes, a problem from the Hong Kong Regional 2016
// (https://open.kattis.com/problems/palindromes)
//
// Given a string S (of length N <= 1E5), perform M (<= 1E5) offline queries
// where the result of each query [b, e] is the number of palindromes there are
// in the substring S[b:e]. Length-1 strings are counted as palindromes, but
// empty strings are not.
//
// In the following writing I'm going to restrict our discussion to targeting
// odd-length palindromes only. The complete solution which must also handle the
// even cases should be fairly similar with some careful index changes.
//
// Imagine if we have found out for each index i, the half-length (rounded up)
// of the longest palindrome in string S centered at index i, called P[i]. For
// example, given S = "aaabaaa", we have P = {1, 2, 1, 4, 1, 2, 1}. P[3] equals
// 4 because the longest palindrome centered at "b" has length 7, and
// ceil(7/2) = 4. It happens that 4 is also the number of palindromes centered
// at the "b", given we're querying the whole range.
//
// If we're querying only a portion of S instead of the full string, then there
// would be fewer palindromes centered at "b" than P[3] because part of the
// longest palindrome centered at "b" would've been "cut off" from the range. In
// general though, the number of palindromes centered at index i within a range
// [b, e] is min({P[i], i-b+1, e-i+1}). This gives us a formula for any query
// [b, e]: sum(min({P[i], i-b+1, e-i+1}) for i in [b, e]).
//
// Computing the array P can be done in O(N log N) with polynomial hashing and
// binary search: for each index i we binary search for the largest x such that
// S[i:i+x] == reversed(S[i-x:i]), where we compare the hashes of the substrings
// in O(1) time each. This should be fast enough for the problem, but in my
// solution I took from the KACTL library the Manacher's Algorithm, which can
// compute the array P in O(N) time.
//
// Now, the problem becomes we still have M queries to deal with. The formula we
// worked out earlier can only answer one query in O(N) time, so altogether O(N
// * M) is not fast enough for the input size. Though for the type of problems
// where we answer multiple range queries, there's this technique called Mo's
// Queries to do this more efficiently. I just knew this idea from before, so
// I'm going to skip all the details of how Mo's Queries works in this writing.
//
// But how does Mo's Queries help us lower our run time down to O(N √M)? In
// order for that run time to be achievable, we need to be able to design our
// states so that it's easy (more precisely in O(1) time) to add or remove
// endpoints from the active range. One idea I had was, since we know P[i] gives
// the number of palindromes centered at i unless it's being "cut off" but the
// query's range, we can keep track of which centers are currently being cut
// off. When we add or remove an endpoint, we can update that cut-off center
// set, which can be done in O(1) if we use something like a bidirectional
// hash-map to record at each index, which center points will stop being cut.
// However, we might run into problems if we have a lot of centers with their
// cut-points "piling up" at a centain index (for example, when P = {1, 2, 3, 2,
// 1}, the indices 0 and 5 both contain O(N) centers' cut-off points). If the
// queries were designed in a way that we had to frequently add or remove
// indices from those critical cut-points, our algorithm might time out.
// Although I didn't prove that this could happen.
//
// Then I realized that we don't really need to know the precise centers being
// cut, but just how many there are gives us enough information. Additionally,
// in our original formula, `min({P[i], i-b+1, e-i+1})` can actually be
// reinterpreted as `min(P[i, i is closer to b ? i-b+1 : e-i+1)`. This might
// look like a complication at first, but this way we allow the cut-off centers
// to be encoded by a numerical count. The left half of the current active range
// are closer to b, so we maintain a count of how many palindromes are cut off
// from the left. Similarly we keep a separate count for how many are cut off
// from the right. Since we're adding or removing endpoints only one at a time,
// only at most one center may "switch sides" or becoming closer to e than b,
// for example.

// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

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
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), _trace_out << "\033[39m", 0)  // trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define view(...) (_view(__VA_ARGS__), trace(""), 0)  // view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define debug
#else
#    ifndef __aarch64__
#        pragma GCC optimize("Ofast,unroll-loops")
#        pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt,tune=native")
#    endif
#    define eprintf(...) ((void)0, 0)
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

array<vi, 2> manacher(const string& s) {
    int n = sz(s);
    array<vi, 2> p = {vi(n + 1), vi(n)};
    rep(z, 0, 2) for (int i = 0, l = 0, r = 0; i < n; i++) {
        int t = r - i + !z;
        if (i < r) p[z][i] = min(t, p[z][l + t]);
        int L = i - p[z][i], R = i + p[z][i] - !z;
        while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1]) p[z][i]++, L--, R++;
        if (R > r) l = L, r = R;
    }
    return p;
}

void add(int i, int end);
void del(int i, int end);
ll calc();
vector<ll> mo(vector<pii> Q) {
    int L = 0, R = 0, blk = DEBUG ? 1 : 320;  // ~N/sqrt(Q)
    vi s(sz(Q));
    vector<ll> res(sz(Q));
#define K(x) pii(x.first / blk, x.second ^ -(x.first / blk & 1))
    iota(all(s), 0);
    sort(all(s), [&](int s, int t) { return K(Q[s]) < K(Q[t]); });
    for (int qi : s) {
        pii q = Q[qi];
        while (L > q.first) add(--L, 0);
        while (R < q.second) add(R++, 1);
        while (L < q.first) del(L++, 0);
        while (R > q.second) del(--R, 1);
        res[qi] = calc();
    }
    return res;
}

#pragma GCC diagnostic pop
#pragma endregion programmation }

#define even_ if (01)
#define odd_ if (01)

int n, m, b, e, ob, oe, le, re, lo, ro;
vi pe, po, be, ee, bo, eo;
#if DEBUG
vi se, so;
#else
vector<char> se, so;
#endif
ll ans;

void check() {
    assert(b <= e || trace(b, e));
    assert(ob < oe || trace(ob, oe));
    assert(ans >= 0 || trace(ans));
    assert(le >= 0 || trace(le));
    assert(re >= 0 || trace(re));
    assert(lo >= 0 || trace(lo));
    assert(ro >= 0 || trace(ro));
    if (!DEBUG) return;
    even_ {
        for (int i = 0; i <= b; i++) assert(se[i] == 0 || trace(i, se[i]));
        for (int i = b + 1; i <= (b + e + 1) / 2 - 1; i++)
            assert(se[i] <= 0 || trace(i, se[i]));
        for (int i = (b + e) / 2 + 1; i <= e - 1; i++)
            assert(se[i] >= 0 || trace(i, se[i]));
        for (int i = e; i < n; i++) assert(se[i] == 0 || trace(i, se[i]));
        for (int i = 0; i < n; i++) assert(be[i] >= 0 || trace(i, be[i]));
        for (int i = 0; i < n; i++) assert(ee[i] >= 0 || trace(i, ee[i]));
        for (int i = (b + e) / 2 + 1; i < n; i++)
            assert(be[i] == 0 || trace(i, be[i]));
        for (int i = 0; i <= (b + e + 1) / 2 - 1; i++)
            assert(ee[i] == 0 || trace(i, ee[i]));
    }
    odd_ {
        //
    }
}

void add(int i, int f) {
    trace("add", i, f, b, e);
    if (!f) {  // grow begin left
        even_ {
            if (b == e) {
                b--;
            } else {
                if (~(e - b) & 1) {
                    if (int c = (b + e) / 2; se[c] < 0) {
                        trace("\033[32m    sh = r  ", b, e, c, le, re, be, ee,
                              se);
                        se[c] = 1;
                        be[c - pe[c]]--, ee[c + pe[c]]++;
                        if (c + pe[c] > e) le--, re++;
                    }
                }
                trace("\033[33m    mv b l", b, e, ans, le, re, be, ee, se);
                ans += le;
                if (assert(se[b] == 0 || trace(b, se[b])), pe[b]) {
                    trace("\033[34m    mk b  ", b, e, ans, le, re, be, ee, se);
                    se[b] = -1;
                    ans++;
                    le++;
                    be[b - pe[b]]++;
                }
                b--;
                le -= be[b];
            }
        }
        odd_ {
            if (~(oe - ob) & 1) {
                if (int c = (ob + oe) / 2; so[c] < 0) {
                    trace("\033[32m    sh = r  ", ob, oe, c, lo, ro, bo, eo,
                          so);
                    so[c] = 1;
                    bo[c - po[c]]--, eo[c + po[c]]++;
                    if (c + po[c] > oe) lo--, ro++;
                }
            }
            trace("\033[33m    mv b l", ob, oe, ans, lo, ro, bo, eo, so);
            ans += lo;
            if (assert(so[ob] == 0 || trace(ob, so[ob])), po[ob]) {
                so[ob] = -1;
                ans++;
                lo++;
                bo[ob - po[ob]]++;
            }
            ob--;
            lo -= bo[ob];
        }
    } else {  // grow end right
        even_ {
            if (e == b) {
                e++;
            } else {
                if (~(e - b) & 1) {
                    if (int c = (b + e) / 2; se[c] > 0) {
                        trace("\033[32m    sh = l  ", b, e, c, le, re, be, ee,
                              se);
                        se[c] = -1;
                        be[c - pe[c]]++, ee[c + pe[c]]--;
                        if (c - pe[c] < b) le++, re--;
                    }
                }
                trace("\033[33m    mv e r", b, e, ans, le, re, be, ee, se);
                ans += re;
                if (assert(se[e] == 0 || trace(e, se[e])), pe[e]) {
                    trace("\033[34m    mk e  ", b, e, ans, le, re, be, ee, se);
                    se[e] = 1;
                    ans++;
                    re++;
                    ee[e + pe[e]]++;
                }
                e++;
                re -= ee[e];
            }
        }
        odd_ {
            if (~(oe - ob) & 1) {
                if (int c = (ob + oe) / 2; so[c] > 0) {
                    trace("\033[32m    sh = l  ", ob, oe, c, lo, ro, bo, eo,
                          so);
                    so[c] = -1;
                    bo[c - po[c]]++, eo[c + po[c]]--;
                    if (c - po[c] < ob) lo++, ro--;
                }
            }
            trace("\033[33m    mv e r", ob, oe, ans, lo, ro, bo, eo, so);
            ans += ro;
            if (assert(so[oe] == 0 || trace(oe, so[oe])), po[oe]) {
                so[oe] = 1;
                ans++;
                ro++;
                eo[oe + po[oe]]++;
            }
            oe++;
            ro -= eo[oe];
        }
    }
    even_ trace("\033[30m  $a", f, b, e, ans, le, re, be, ee, se), check();
    odd_ trace("\033[30m  $a", f, ob, oe, ans, lo, ro, bo, eo, so), check();
}

void del(int i, int f) {
    trace("del", i, f, b, e);
    if (!f) {  // shrink begin right
        even_ {
            if (b + 1 == e) {
                b++;
            } else {
                if (~(e - b) & 1) {
                    if (int c = (b + e) / 2; se[c] > 0) {
                        trace("\033[32m    sh = l  ", b, e, c, le, re, be, ee,
                              se);
                        se[c] = -1;
                        be[c - pe[c]]++, ee[c + pe[c]]--;
                        if (c - pe[c] < b) le++, re--;
                    }
                }
                trace("\033[33m    mv b r", b, e, ans, le, re, be, ee, se);
                le += be[b];
                b++;
                if (pe[b]) {
                    trace("\033[34m    rm b  ", b, e, ans, le, re, be, ee, se);
                    assert(se[b] < 0 || trace(b, se[b])), se[b] = 0;
                    ans--;
                    le--;
                    be[b - pe[b]]--;
                }
                ans -= le;
            }
        }
        odd_ {
            if (~(oe - ob) & 1) {
                if (int c = (ob + oe) / 2; so[c] > 0) {
                    trace("\033[32m    sh = l  ", ob, oe, c, lo, ro, bo, eo,
                          so);
                    so[c] = -1;
                    bo[c - po[c]]++, eo[c + po[c]]--;
                    if (c - po[c] < ob) lo++, ro--;
                }
            }
            trace("\033[33m    mv b r", b, e, ans, le, re, be, ee, se);
            lo += bo[ob];
            ob++;
            if (po[ob]) {
                assert(so[ob] < 0 || trace(ob, so[ob])), so[ob] = 0;
                ans--;
                lo--;
                bo[ob - po[ob]]--;
            }
            ans -= lo;
        }
    } else {  // shrink end left
        even_ {
            if (e - 1 == b) {
                e--;
            } else {
                if (~(e - b) & 1) {
                    if (int c = (b + e) / 2; se[c] < 0) {
                        trace("\033[32m    sh = r  ", b, e, c, le, re, be, ee,
                              se);
                        se[c] = 1;
                        be[c - pe[c]]--, ee[c + pe[c]]++;
                        if (c + pe[c] > e) le--, re++;
                    }
                }
                trace("\033[33m    mv e l", b, e, ans, le, re, be, ee, se);
                re += ee[e];
                e--;
                if (pe[e]) {
                    trace("\033[34m    rm e  ", b, e, ans, le, re, be, ee, se);
                    assert(se[e] > 0 || trace(e, se[e])), se[e] = 0;
                    ans--;
                    re--;
                    ee[e + pe[e]]--;
                }
                ans -= re;
            }
        }
        odd_ {
            if (~(oe - ob) & 1) {
                if (int c = (ob + oe) / 2; so[c] < 0) {
                    trace("\033[32m    sh = r  ", ob, oe, c, lo, ro, bo, eo,
                          so);
                    so[c] = 1;
                    bo[c - po[c]]--, eo[c + po[c]]++;
                    if (c + po[c] > oe) lo--, ro++;
                }
            }
            trace("\033[33m    mv e l", ob, oe, ans, lo, ro, bo, eo, so);
            ro += eo[oe];
            oe--;
            if (po[oe]) {
                assert(so[oe] > 0 || trace(oe, so[oe])), so[oe] = 0;
                ans--;
                ro--;
                eo[oe + po[oe]]--;
            }
            ans -= ro;
        }
    }
    even_ trace("\033[30m  $d", f, b, e, ans, le, re, be, ee, se), check();
    odd_ trace("\033[30m  $d", f, ob, oe, ans, lo, ro, bo, eo, so), check();
}

ll calc() {
    // trace("ans, calc", b, e);
    //
    return ans;
}

void prep() {
    //
    return;
    debug {
        add(0, 1);
        add(1, 1);
        add(2, 1);
        del(0, 0);
        add(3, 1);
        del(1, 0);
        add(4, 1);
        del(2, 0);
        exit(0);
    }
}

void solve() {
    string s;
    cin >> s;
    debug if (!cin) exit(0);
    n = len(s);
    be.assign(n + 1, 0), ee.assign(n + 1, 0), se.assign(n + 1, 0);
    bo.assign(n + 2, 0), eo.assign(n + 2, 0), so.assign(n + 2, 0);
    auto p = manacher(s);
    pe = move(p[0]), po = move(p[1]);
    for (int i = 0; i < n; i++) po[i]++;
    po.insert(begin(po), 0), po.push_back(0);
    cin >> m;
    debug if (m < 0) cin >> m;
    vector<pii> q(m);
    for (auto& [x, y] : q) cin >> x >> y, x--;
    trace(s), trace(p), trace(q);
    b = e = le = re = lo = ro = 0, ans = 0;
    ob = 0, oe = 1;
    prep();
    auto a = mo(q);
    for (auto x : a) cout << x << "\n";
}

void solve_suite() {
    // debug freopen("./sandbox/i4.txt", "r", stdin);
    // debug cout.open("./sandbox/o4.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id == 4 ? _S_goodbit : _S_failbit);
        debug _cout.clear(cerr ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ":\n";
        solve();
        debug cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
