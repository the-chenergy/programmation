// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
#define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
#define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 01  // If 0 or unset, disable trace, eprintf, and debug blocks

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
#if !SYNC_IO && (!TRACE_COUT || !DEBUG)
void _init() __attribute__((constructor)); void _init() { ios::sync_with_stdio(0), cin.tie(0); }
#endif
#if !NO_MAIN
void solve_suite(); int main() { solve_suite(); }
#endif
#pragma endregion common }  // clang-format on

// Additional library code

#pragma GCC diagnostic pop
#pragma endregion programmation }

int pr[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int fac[31], sq[31];
auto $$ = []() {
    for (int i = 0; i < 10; i++) {
        for (int x = 2; x <= 30; x++)
            fac[x] |= (x % pr[i] == 0) << i, sq[x] |= x % (pr[i] * pr[i]) == 0;
    }
    return 0;
}();
const ll mod = 1E9 + 7;
ll dp[2009][2009];
class Solution {
  public:
    int squareFreeSubsets(vector<int>& nums) {
        map<int, int> fr;
        for (auto x : nums)
            if (!sq[x]) fr[x]++;
        vector<int> a;
        for (auto [x, _] : fr)
            if (x > 1) a.push_back(x);
        int n = len(a);
        // memset(dp, 0, sizeof(dp));
        for (int u = 0; u < 1 << 10; u++) dp[u][n] = 1;
        for (int i = n - 1; i >= 0; i--) {
            for (int u = 0; u < 1 << 10; u++) {
                dp[u][i] = dp[u][i + 1];
                if (u & fac[a[i]]) continue;
                (dp[u][i] += (fr[a[i]] * dp[u | fac[a[i]]][i + 1] % mod)) %=
                    mod;
            }
        }
        ll ans = dp[0][0];
        for (int i = 0, lim = fr[1]; i < lim; i++) (ans *= 2) %= mod;
        return int((ans + mod - 1) % mod);
    }
};

#if LOCAL && 01
int main() {
    Solution $s;

    auto $t = [&](vi a) {
        cout << "Case #" << ++case_id << ": ";
        cout << $s.squareFreeSubsets(a);
        cout << "\n";
    };

    $t({2, 3});
    // $t({3, 4, 4, 5});
    // $t({1});
}
#endif
