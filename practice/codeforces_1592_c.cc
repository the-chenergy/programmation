// Solution to Bakry and Partitioning, problem C from the Codeforces Round 746
// (Div. 2) https://codeforces.com/contest/1592/problem/C
//
// Some nice properties of xor include that (0 xor A = A) and (A xor A = 0) for
// any number A. This tells us that, no matter what the solution to a problem
// instance looks like, we can always either reduce it down to just two or three
// connected components.
//
// Consider this: let's say the correct partitioning involves dividing the tree
// into 5 components C1, ..., C5. If we combined three of the components, we
// would still end up with the same xor per component, because
// A xor A xor A = A.
//
// On the other hand, if the input tree has a total xor of zero, then we can
// just isolate any vertex at all, and the remaining tree will have total xor
// equal to that vertex's value. This is because 0 xor A = A.
//
// Therefore, if total xor (called T) is zero, it's always possible. Otherwise,
// k must be at least 3, and we can check if we can divide the tree into exactly
// three pieces with the xor equal to T. This can be done by first rooting the
// tree arbitrarily and then check if we can find either
//   (1) two non-overlapping subtrees with xor equal to T, or
//   (2) a subtree with xor 0 containing one of its subtrees with xor equal to T
//   (because now that parent subtree xor the child subtree will yield T as
//   well).

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

#pragma GCC diagnostic pop
#pragma endregion programmation }

int n, k, a[100009], t[100009], ans;
vi g[100009];

int com(int i, int p) {
    t[i] = a[i];
    for (int j : g[i])
        if (j != p) t[i] ^= com(j, i);
    return t[i];
}

int has(int i, int p) {
    int ok = 0;
    for (int j : g[i])
        if (j != p) ok += has(j, i);
    ans |= ok >= 2 || (ok && t[i] == 0);
    return ok || (p && t[i] == t[1]);
}

void solve() {
    cin >> n >> k;
    if (0 || !cin) exit(0);
    for (int i = 1; i <= n; i++) cin >> a[i];
    fill_n(g, n + 1, vi());
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v), g[v].push_back(u);
    }

    if (com(1, 0) == 0) {
        cout << "YES";
        return;
    }
    view(t, 1, n + 1);
    if (k <= 2) {
        cout << "NO";
        return;
    }

    ans = 0;
    has(1, 0);
    cout << (ans ? "YES" : "NO");
}

void solve_suite() {
    debug freopen("./sandbox/i.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        // cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
