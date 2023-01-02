// A slow reference solution to Pirate Chest
// (https://open.kattis.com/problems/pirate)
//
// This is a O(n**4) solution I wrote as a local verifier to help debug the
// submitted O(n**3) code.

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

const int mxn = 500;
ll a, b, h, w, d[mxn][mxn], rd[1 + __lg(mxn)][mxn][1 + __lg(mxn)][mxn], ans;

// 2D range minimum queries (RMQ) data structure
// Credit: https://codeforces.com/blog/entry/45485
void init() {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) rd[0][y][0][x] = d[y][x];
        for (int j = 1; j <= __lg(w); j++)
            for (int x = 0; x + (1 << (j - 1)) < w; x++)
                rd[0][y][j][x] = min(rd[0][y][j - 1][x],
                                     rd[0][y][j - 1][x + (1 << (j - 1))]);
    }
    for (int i = 1; i <= __lg(h); i++)
        for (int y = 0; y < h; y++)
            for (int j = 0; j <= __lg(w); j++)
                for (int x = 0; x < w; x++)
                    rd[i][y][j][x] = min(rd[i - 1][y][j][x],
                                         rd[i - 1][y + (1 << (i - 1))][j][x]);
}
ll query(int by, int bx, int ey, int ex) {
    int ky = __lg(ey - by), kx = __lg(ex - bx);
    return min({
        rd[ky][by][kx][bx],
        rd[ky][by][kx][ex - (1 << kx)],
        rd[ky][ey - (1 << ky)][kx][bx],
        rd[ky][ey - (1 << ky)][kx][ex - (1 << kx)],
    });
}

void solve() {
    cin >> a;
    if (a < 0) cin >> a;
    if (0 || !cin) exit(0);
    cin >> b >> h >> w;
    if (a > b) swap(a, b);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) cin >> d[y][x];
    init();

    ans = 0;
    for (int by = 0; by < h; by++) {
        for (int ey = by + 1; ey <= h; ey++) {
            for (int bx = 0; bx < w; bx++) {
                for (int ex = bx + 1; ex <= w; ex++) {
                    int n = ey - by, m = ex - bx;
                    if (min(n, m) > a || max(n, m) > b) continue;
                    ll t = n * m, r = query(by, bx, ey, ex);
                    double u = double(h * w * r) / double(h * w - t);
                    if (fmod(u, 1) < 1E-9) u -= 1;
                    amax(ans, t * ll(u));
                }
            }
        }
    }
    cout << ans;
}

void solve_suite() {
    debug freopen("./sandbox/i4.txt", "r", stdin);
    debug cout.open("./sandbox/oe.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        DEBUG ? void(cout << "Case #" << case_id << ": " << (solve(), "\n"))
              : solve();
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
