// Solution to "ilove Strings", a problem from the ICPC NAQ 2021
// (https://open.kattis.com/problems/ilovestrings)
// #array #combinatorics
//
// Use the inclusion-exclusion principle -- maintain total counts of:
//   - C1: a particular consonant + a particular vowel
//   - C2: consonant + any vowels
//   - C3: any consonants + a particular vowel
//   - C4: any consonants + any vowels
//
// Sweep from left to right (or in reverse) and mix-and-match vowels, excluding
// the appropriate consonants and vowels. Something like
//     ans += left_C1[a, b] * (C4 - c2[b] + c3[a] - right_C1[a, b])
//
// Overall running time should be O(|con| * |vow| * N) or some O(420N).

#define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
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

const char vow[] = "aoeiuAOEIU",
           con[] = "pyfgcrldhtnsjkxbmwvqzPYFGCRLDHTNSJKXBMWVQZ";
const ll mod = 1E9 + 7;

string s;
int n, a[100000];
ll l[10][42], r[10][42], lc[10], rc[10], ry[10], rx[42], rs, ans;

void read() {
    // string s;
    cin >> s;
    if (0 || !cin) exit(0);
    if (s[0] == '-') cin >> s;
    n = len(s);
    for (int i = 0; i < n; i++) {
        if (int c = int(find(vow, vow + 10, s[i]) - vow); c ^ 10)
            a[i] = c + 42;
        else
            a[i] = int(find(con, con + 42, s[i]) - con);
    }
    trace(n, s), view(a, 0, n);

    debug memset(l, 0, sizeof(l)), memset(r, 0, sizeof(r)),
        memset(lc, 0, sizeof(lc)), memset(rc, 0, sizeof(rc)),
        memset(ry, 0, sizeof(ry)), memset(rx, 0, sizeof(rx)), rs = 0, ans = 0;
}

void p2__(ll (&a_)[10][42]) {
    debug for (int y = 0; y < 10; y++) for (int x = 0; x < 42;
                                            x++) if (a_[y][x])
        cerr&& eprintf("%c%c:%lli ", vow[y], con[x], a_[y][x]);
    cerr&& eprintf("\n");
}
template <size_t L>
void p__(ll (&a_)[L]) {
    debug for (int i = 0; i < int(L); i++) if (a_[i])
        cerr&& eprintf("%c:%lli ", L ^ 10 ? con[i] : vow[i], a_[i]);
    cerr&& eprintf("\n");
}
#define p2_(a_) cerr &&eprintf("%s: ", #a_), p2__(a_)
#define p_(a_) cerr &&eprintf("%s: ", #a_), p__(a_)

void solve() {
    read();

    for (int i = 0; i < n; i++) {
        int c = a[i];
        if (c >= 42)
            lc[c - 42]++;
        else
            for (int y = 0; y < 10; y++) l[y][c] += lc[y];
    }
    p2_(l);

    for (int i = n - 1; i > 0; i--) {
        if (a[i] >= 42) {
            int c = a[i] - 42;
            lc[c]--;
            rc[c]++;
            for (int y = 0; y < 10; y++)
                if (y ^ c)
                    for (int x = 0; x < 42; x++) {
                        (ans +=
                         l[y][x] *
                         (rs - ry[y] - rx[x] + r[y][x] - ry[c] + r[c][x]) %
                         mod) %= mod;
                        // if (i == 4 && l[y][x] && (ry[c] || rx[x] || r[c][x]))
                        //     trace("hi", vow[c], vow[y], con[x], rs, ry[c],
                        //           rx[x], r[c][x], rs - ry[y] - rx[x] +
                        //           r[y][x]);
                    }
        } else {
            int x = a[i];
            for (int y = 0; y < 10; y++) {
                l[y][x] -= lc[y];
                r[y][x] += rc[y];
                ry[y] += rc[y];
                rx[x] += rc[y];
                rs += rc[y];
            }
        }
        trace("----\n", s, i, s[i], rs, ans), p2_(l), p2_(r), p_(lc), p_(rc),
            p_(ry), p_(rx);
    }
    trace(ans);
    cout << ans;
}

void solve_suite() {
    debug freopen("./sandbox/i17.txt", "r", stdin);
    debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id == 63 ? _S_goodbit : _S_failbit);
        // debug _cout.clear(case_id == 63 ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
