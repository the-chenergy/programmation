// Solution to "A Different List Game" from the Spotify Challenge 2010
// (https://open.kattis.com/problems/listgame2)
// #number_theory #prime #greedy #dp
//
// I noticed fairly quickly that this problem is essentially "finding the
// maximum number of unique subsets from a list of objects," where the list of
// object may have copies. In our case, the objects are some prime numbers,
// where for each p**b that divides X we have b copies of p. So, what we can do
// first is factorize X, then for each factor of X we either take it or lose it,
// just like in a Knapsack problem. Since the single-powers of primes are
// definitely unique so we can always take them first. The remaining factors
// which are products or powers of primes we can solve with a classic O(n**2)
// DP as there won't be that many of them anyway.

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
 * Author: chilli, Ramchandra Apte, Noam527, Simon Lindholm
 * Date: 2019-04-24
 * License: CC0
 * Source: https://github.com/RamchandraApte/OmniTemplate/blob/master/modulo.hpp
 * Description: Calculate $a\cdot b\bmod c$ (or $a^b \bmod c$) for $0 \le a, b
 * \le c \le 7.2\cdot 10^{18}$. Time: O(1) for \texttt{modmul}, O(\log b) for
 * \texttt{modpow} Status: stress-tested, proven correct Details: This runs ~2x
 * faster than the naive (__int128_t)a * b % M. A proof of correctness is in
 * doc/modmul-proof.tex. An earlier version of the proof, from when the code
 * used a * b / (long double)M, is in doc/modmul-proof.md. The proof assumes
 * that long doubles are implemented as x87 80-bit floats; if they are 64-bit,
 * as on e.g. MSVC, the implementation is only valid for $0 \le a, b \le c <
 * 2^{52} \approx 4.5 \cdot 10^{15}$.
 */
typedef unsigned long long ull;
ull modmul(ull a, ull b, ull M) {
    ll ret = a * b - M * ull(1.L / ld(M) * ld(a) * ld(b));
    return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
    ull ans = 1;
    for (; e; b = modmul(b, b, mod), e /= 2)
        if (e & 1) ans = modmul(ans, b, mod);
    return ans;
}

/**
 * Author: chilli, c1729, Simon Lindholm
 * Date: 2019-03-28
 * License: CC0
 * Source: Wikipedia, https://miller-rabin.appspot.com/
 * Description: Deterministic Miller-Rabin primality test.
 * Guaranteed to work for numbers up to $7 \cdot 10^{18}$; for larger numbers,
 * use Python and extend A randomly. Time: 7 times the complexity of $a^b \mod
 * c$. Status: Stress-tested
 */
bool isPrime(ull n) {
    if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
    ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
        s = __builtin_ctzll(n - 1), d = n >> s;
    for (ull a : A) {  // ^ count trailing zeroes
        ull p = modpow(a % n, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--) p = modmul(p, p, n);
        if (p != n - 1 && i != s) return 0;
    }
    return 1;
}

/**
 * Author: chilli, SJTU, pajenegod
 * Date: 2020-03-04
 * License: CC0
 * Source: own
 * Description: Pollard-rho randomized factorization algorithm. Returns prime
 * factors of a number, in arbitrary order (e.g. 2299 -> \{11, 19, 11\}).
 * Time: $O(n^{1/4})$, less for numbers with small factors.
 * Status: stress-tested
 *
 * Details: This implementation uses the improvement described here
 * (https://en.wikipedia.org/wiki/Pollard%27s_rho_algorithm#Variants), where
 * one can accumulate gcd calls by some factor (40 chosen here through
 * exhaustive testing). This improves performance by approximately 6-10x
 * depending on the inputs and speed of gcd. Benchmark found here:
 * (https://ideone.com/nGGD9T)
 *
 * GCD can be improved by a factor of 1.75x using Binary GCD
 * (https://lemire.me/blog/2013/12/26/fastest-way-to-compute-the-greatest-common-divisor/).
 * However, with the gcd accumulation the bottleneck moves from the gcd calls
 * to the modmul. As GCD only constitutes ~12% of runtime, speeding it up
 * doesn't matter so much.
 *
 * This code can probably be sped up by using a faster mod mul - potentially
 * montgomery reduction on 128 bit integers.
 * Alternatively, one can use a quadratic sieve for an asymptotic improvement,
 * which starts being faster in practice around 1e13.
 *
 * Brent's cycle finding algorithm was tested, but doesn't reduce modmul calls
 * significantly.
 *
 * Subtle implementation notes:
 * - we operate on residues in [1, n]; modmul can be proven to work for those
 * - prd starts off as 2 to handle the case n = 4; it's harmless for other n
 *   since we're guaranteed that n > 2. (Pollard rho has problems with prime
 *   powers in general, but all larger ones happen to work.)
 * - t starts off as 30 to make the first gcd check come earlier, as an
 *   optimization for small numbers.
 */
ull pollard(ull n) {
    auto f = [n](ull x) { return modmul(x, x, n) + 1; };
    ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
    while (t++ % 40 || __gcd(prd, n) == 1) {
        if (x == y) x = ++i, y = f(x);
        if ((q = modmul(prd, max(x, y) - min(x, y), n))) prd = q;
        x = f(x), y = f(f(y));
    }
    return __gcd(prd, n);
}
vector<ull> factor(ull n) {
    if (n == 1) return {};
    if (isPrime(n)) return {n};
    ull x = pollard(n);
    auto l = factor(x), r = factor(n / x);
    l.insert(l.end(), all(r));
    return l;
}

#pragma GCC diagnostic pop
#pragma endregion programmation }

ll n;
deque<ll> bfs;
vector<ll> com;
int fix;

ll ps[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};
void compress() {
    auto f = factor(n);
    map<ull, int> ct;
    for (auto x : f) ct[x]++;
    vi cs;
    for (auto [_, c] : ct) cs.push_back(c);
    // trace(n, ct);
    assert(len(cs) <= len(ps));
    sort(rbegin(cs), rend(cs));
    n = 1;
    for (int i = 0; i < len(cs); i++) {
        n *= ll(pow(ps[i], cs[i]));
        // if (cs[i]) trace("n divisible by prime", ps[i]);
    }
    // trace("new", n);

    bfs = {1}, com.clear();
    for (int i = 0; i < len(ps); i++) {
        for (int l = len(bfs); l--;) {
            auto x = bfs.front();
            bfs.pop_front();
            for (ll d = 1; n % d == 0; d *= ps[i]) {
                if (d > 1 && !binary_search(all(ps), x * d))
                    com.push_back(x * d);
                // if (d > ps[i]) com.push_back(x * d);
                bfs.push_back(x * d);
            }
        }
    }
    sort(all(com));
    fix = 0;
    for (int i = 0; i < len(cs); i++)
        if (cs[i]) n /= ps[i], fix++;
}

vector<map<ll, int>> mem;
int knapsack(int i, ll r) {
    if (i == len(com) || r < com[i]) return 0;
    if (auto it = mem[i].find(r); it != end(mem[i])) return it->second;
    if (!(rand() & ((1 << 20) - 1))) trace(i);
    int lose = knapsack(i + 1, r);
    int use = r % com[i] ? int(-1E9) : 1 + knapsack(i + 1, r / com[i]);
    return mem[i][r] = max(use, lose);
}

void solve() {
    cin >> n;
    if (n < 0) cin >> n;
    if (0 || !cin) exit(0);
    ll on = n;
    compress();
    trace(on, n, len(com));
    // view(com, 0, 99);

    mem.assign(len(com), {});
    cout << knapsack(0, n) + fix;
}

void solve_suite() {
    // debug freopen("./sandbox/i9.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    auto clk = clock();
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id == 9 ? _S_goodbit : _S_failbit);
        // debug _cout.clear(cerr ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        eprintf("(%.2LF s)\n", ld(clock() - clk) / CLOCKS_PER_SEC);
        clk = clock();
    }
}
