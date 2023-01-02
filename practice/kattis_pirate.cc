// Solution to Pirate Chest, a problem from the ICPC 2013 World Finals
// (https://open.kattis.com/problems/pirate)
// #array #stack #geometry
//
// This looks like the 2D version of the "biggest rectangle made out of bars"
// problem: given a list of bars with their heights, maximize (x2 - x1) * h
// where all bars x1, ..., x2 have height >= h. This can be solved with a stack
// in O(n) by recording the next lower bars and their indices, where the
// candidate areas can then be found by multiplying the next height by the
// difference between its index and the current index.
//
// Now for a 2D solution, we can simply run the same algorithm for each [y1..y2]
// window. Since there are only O(n**2) pairs of (y1, y2), the whole algorithm
// runs in O(n**3). One extra task was finding the displacement-adjusted depths,
// where just a little bit of drawing out on paper was needed to come up with
// the correct volume formula.

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
// #    define _GLIBCXX_DEBUG 1
// #    define _GLIBCXX_DEBUG_PEDANTIC 1
// #    define _FORTIFY_SOURCE 2
// #    pragma GCC optimize("trapv")
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
#    define debug while (false)
#endif
#include <bits/stdc++.h>
#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)
#define sz len
#define _print_vector_impl s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}";
using namespace std; using ll = long long; using ull = unsigned long long; using ld = long double; using vi = vector<int>; using pii = pair<int, int>; template <typename T> int len(const T& x) { return int(x.size()); } template <typename T, size_t l> int len(const T (&)[l]) { return l; } template <typename T, typename S> bool amax(T& t, S s) { return t < s && (t = s, true); } template <typename T, typename S> bool amin(T& t, S s) { return s < t && (t = s, true); } int num_cases = 1, case_id; namespace std { template <typename T, size_t l> ostream& operator<<(ostream& s, const array<T, l>& x); template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x); template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x); template <typename C, typename T = enable_if_t<!is_same<C, string>::value, typename C::value_type>> ostream& operator<<(ostream& s, const C& x) { _print_vector_impl } template <typename T, size_t l, enable_if_t<!is_same<T, char>::value, int> = 0> ostream& operator<<(ostream& s, const T (&x)[l]) { _print_vector_impl } template <typename T, size_t l> ostream& operator<<(ostream& s, const std::array<T, l>& x) { _print_vector_impl } template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x) { return s << "{" << x.first << ", " << x.second << "}"; } template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x) { s << "{"; string d; apply([&](auto&&... y) { (..., (s << d << y, d = ", ")); }, x); return s << "}"; } } struct _teed_cout { bool _b = false; ofstream _f; void open(const char* s) { _f.open(s), _b = true; } template <typename T> _teed_cout& operator<<(const T& x) { return cout << x, _b && (_f << x), *this; } } _teed_cout; ostream& _cout = cout;
#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
#    define cout _teed_cout  // Outputs to both console and file. Access original cout via _cout.
#endif
template <typename T> void _trace(const char* l, const T& x) { if (l[0] != '"') _trace_out << l + (l[0] == ' ') << ": "; _trace_out << x << "\n"; } template <typename T, typename... A> void _trace(const char* l, const T& x, const A&... a) { if (l[0] == ' ') l++; size_t s = strchr(l, ',') - l; if (l[0] != '"') _trace_out.write(l, s) << ": "; _trace_out << x << ", ", _trace(l + s + 1, a...); } template <typename T> void _view(const T& x) { _trace_out << x; } template <typename T, typename... R> void _view(const T& x, int b, int e, R... r) { b < 0 && (b += len(x)), e < 0 && (e += len(x)); b = min(max(b, 0), len(x)), e = min(max(e, b), len(x)); auto it = begin(x); advance(it, b); _trace_out << "{"; for (int i = b; i < e; it++, i++) { if (i != b) _trace_out << ", "; _view(*it, r...); } _trace_out << "}"; }
#if !SYNC_IO
void _init() __attribute__((constructor)); void _init() { ios::sync_with_stdio(false), cin.tie(nullptr); }
#endif
#if !NO_MAIN
void solve_suite(); int main() { solve_suite(); }
#endif
#pragma endregion common }  // clang-format on

// Additional library code

#pragma GCC diagnostic pop
#pragma endregion programmation }

const ll mxn = 500, inf = /* DEBUG ? 999 : */ 1E15;
ll a, b, h, w, d[mxn][mxn], ans;
vector<ll> mnd;
deque<pair<ll, ll>> s;

void solve() {
    cin >> a;
    if (a < 0) cin >> a;
    if (0 || !cin) exit(0);
    cin >> b >> h >> w;
    if (a > b) swap(a, b);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) cin >> d[y][x];

    ans = 0;
    ll ay = 0, ax = 0, ah = 0, aw = 0, ad = 0;
    for (int sy = 0; sy < h; sy++) {
        mnd.assign(w, inf);
        for (int y = sy; y < h; y++) {
            ll c = y + 1 - sy;
            if (c > b) break;
            s = {{-1, -1}};
            trace(sy, y, mnd);
            for (ll x = 0; x <= w; x++) {
                if (x < w) amin(mnd[x], d[y][x]);
                ll r = x == w ? -1 : mnd[x], l, i = x;
                while (l = s.back().first, l > r) {
                    i = s.back().second;
                    ll t = c * min(x - i, c > a ? a : b);
                    ll u = (h * w * l - 1) / (h * w - t);
                    bool upd = amax(ans, t * u);
                    trace("    candidate", t, l, i, u, t * ll(u), upd);
                    debug if (upd) ay = sy, ax = x - t / c, ah = y + 1 - sy,
                                   aw = t / c, ad = ll(u);
                    s.pop_back();
                }
                if (l < r)
                    s.push_back({r, i}), trace("  expand", x, i, r, s, mnd);
            }
        }
    }
    cout << ans;
    debug cout << "\n" << tuple{ay, ax, ah, aw, ad};
}

void solve_suite() {
    // debug freopen("./sandbox/i.txt", "r", stdin);
    debug freopen("./sandbox/i7.txt", "r", stdin);
    debug cout.open("./sandbox/o7.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        debug cerr.clear(case_id == -1 ? _S_goodbit : _S_failbit);
        // debug _cout.clear(cerr ? _S_goodbit : _S_failbit);
        DEBUG ? void(cout << "Case #" << case_id << ": " << (solve(), "\n"))
              : solve();
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
