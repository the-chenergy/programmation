#define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define LOCAL 0  // If 0 or unset, disable trace, eprintf, and local blocks

#pragma region programmation {
#pragma region common {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
// #if LOCAL
// #    define _GLIBCXX_DEBUG 1
// #    define _GLIBCXX_DEBUG_PEDANTIC 1
// #    define _FORTIFY_SOURCE 2
// #endif

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

template <typename T>
int len(const T& x) {
    return int(x.size());
}
template <typename T, size_t size>
int len(const T (&)[size]) {
    return size;
}

#define __argc(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, n, ...) n
#define _argc(...) __argc(__VA_ARGS__, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define _concat(x, y) __CONCAT(x, y)

#define _range4(b, e, d, i) \
    for (auto i = b; (d) > 0 ? i < (e) : i > (e); i += d)
#define _range1(n) _range4(0, n, 1, _i)
#define _range2(n, i) _range4(0, n, 1, i)
#define _range3(b, e, i) _range4(b, e, 1, i)
// range([begin=0], end, [step=1], i) -> for i in range(begin, end, step)
#define range(...) _concat(_range, _argc(__VA_ARGS__))(__VA_ARGS__)

#define _each2(a, x) for (auto& x : a)
#define _each_(a, ...) for (auto& [__VA_ARGS__] : a)
#define _argc2(...) __argc(__VA_ARGS__, _, _, _, _, _, _, _, _, _, _, 2, 1, 0)
// each(A, ...) -> for ... in A
#define each(...) _concat(_each, _argc2(__VA_ARGS__))(__VA_ARGS__)

// enumerate(A, i, ...) -> for i, (...) in enumerate(A)
#define enumerate(a, i, ...)         \
    for (int i = 0; i != -1; i = -1) \
    each(a, __VA_ARGS__) for (int _##i = 1; _##i; _##i = 0, i++)

int _ADJ4_DIRS[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
#define _adj42(dy, dx) for (auto [dy, dx] : _ADJ4_DIRS)
#define _adj44(cy, cx, y, x)                                              \
    _adj42(_dy, _dx) for (int y = cy + _dy, x = cx + _dx, _##y = 1; _##y; \
                          _##y = 0)
#define _adj46(h, w, cy, cx, y, x) \
    _adj42(y, x) for (y += cy, x += cx; ~y && ~x && y != h && x != w; y = -1)
// adj4([y_lim], [x_lim], cur_y, cur_x, y, x)
//     -> for each (y, x) adjacent to (cy, cx), with optional boundary checks
#define adj4(...) _concat(_adj4, _argc(__VA_ARGS__))(__VA_ARGS__)

#define rep(i, b, e) _range3(b, e, i)
#define trav(x, a) _each2(a, x)
#define all(x) begin(x), end(x)
#define sz len

template <typename TT, typename TS>
bool amax(TT& t, TS s) {
    return t < s && (t = s, true);
}
template <typename TT, typename TS>
bool amin(TT& t, TS s) {
    return s < t && (t = s, true);
}

// Example: partition_point(all(A), selecting(x, len(x) < 2))
#define selecting(x, ...) [&](auto& x) { return __VA_ARGS__; }

// Example: sort(all(A), comparing(x, len(x)))
#define comparing(x, ...)                               \
    [&](auto& _l, auto& _r) {                           \
        auto _f = [&](auto& x) { return __VA_ARGS__; }; \
        return _f(_l) < _f(_r);                         \
    }

// Example: accumulate(all(A), 0LL, adding(x, len(x)))
#define adding(x, ...) [&](auto _s, auto& x) { return _s + (__VA_ARGS__); }

// Example: first_where(0, len(A), i, len(A[i]) >= 2)
#define first_where(b, e, i, ...)                                        \
    [&](decltype(e) _b, decltype(e) _e, decltype(e) i) {                 \
        while (_b < _e)                                                  \
            i = _b + (_e - _b) / 2, (__VA_ARGS__) ? _e = i : _b = i + 1; \
        return _b;                                                       \
    }(b, e, 0)

void _init() __attribute__((constructor));
void _init() {
#if !SYNC_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
#endif
}

namespace std {
template <typename T, size_t size>
ostream& operator<<(ostream& out, const array<T, size>& x);
template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond>& x);
template <typename... T>
ostream& operator<<(ostream& out, const tuple<T...>& x);

template <typename TContainer,
          typename T = enable_if_t<!is_same<TContainer, string>::value,
                                   typename TContainer::value_type>>
ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (auto& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename T, size_t size,
          enable_if_t<!is_same<T, char>::value, int> = 0>
ostream& operator<<(ostream& out, const T (&x)[size]) {
    out << "{";
    string delim;
    for (auto& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename T, size_t size>
ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (auto& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond>& x) {
    return out << "{" << x.first << ", " << x.second << "}";
}
template <typename... T>
ostream& operator<<(ostream& out, const tuple<T...>& x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}
}  // namespace std

struct _teed_cout {
    bool _opened = false;
    ofstream _file_out;
    void open(const char* path) { _file_out.open(path), _opened = true; }
    template <typename T>
    _teed_cout& operator<<(const T& x) {
        return cout << x, _opened && (_file_out << x), *this;
    }
} _teed_cout;
ostream& _cout = cout;

#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
// Outputs to both console and file. Access original cout via _cout.
#    define cout _teed_cout
#endif

template <typename TArg1>
void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') _trace_out << labels + (labels[0] == ' ') << ": ";
    _trace_out << arg1 << "\n";
}

template <typename TArg1, typename... TArgs>
void _trace(const char* labels, const TArg1& arg1, const TArgs&... args) {
    if (labels[0] == ' ') labels++;
    size_t first_label_size = strchr(labels, ',') - labels;
    if (labels[0] != '"') _trace_out.write(labels, first_label_size) << ": ";
    _trace_out << arg1 << ", ", _trace(labels + first_label_size + 1, args...);
}

template <typename T>
void _view(const T& x) {
    _trace_out << x;
}

template <typename T, typename... TRange>
void _view(const T& x, int b, int e, TRange... ranges) {
    b < 0 && (b += len(x)), e < 0 && (e += len(x));
    b = min(max(b, 0), len(x)), e = min(max(e, b), len(x));
    auto it = begin(x);
    advance(it, b);
    _trace_out << "{";
    for (int i = b; i < e; it++, i++) {
        if (i != b) _trace_out << ", ";
        _view(*it, ranges...);
    }
    _trace_out << "}";
}

#if LOCAL
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)
#    endif
#    define trace(...) _trace(#__VA_ARGS__, __VA_ARGS__)
#    define view(...) _view(__VA_ARGS__), trace("")
#    define local
#else
// printf into cerr
#    define eprintf(...) (void)0
// trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define trace(...) (void)0
// view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define view(...) (void)0
#    define local while (false)
#endif

int num_cases = 1, case_id;

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif
#pragma endregion common }

// Additional library code
/**
 * Author: Unknown
 * Date: 2002-09-15
 * Source: predates tinyKACTL
 * Description: Finds two integers $x$ and $y$, such that $ax+by=\gcd(a,b)$. If
 * you just need gcd, use the built in \texttt{\_\_gcd} instead.
 * If $a$ and $b$ are coprime, then $x$ is the inverse of $a \pmod{b}$.
 */
ll euclid(ll a, ll b, ll& x, ll& y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a / b * x, d;
}
/**
 * Author: Simon Lindholm
 * Date: 2019-05-22
 * License: CC0
 * Description: Chinese Remainder Theorem.
 *
 * \texttt{crt(a, m, b, n)} computes $x$ such that $x\equiv a \pmod m$, $x\equiv
 * b \pmod n$. If $|a| < m$ and $|b| < n$, $x$ will obey $0 \le x <
 * \text{lcm}(m, n)$. Assumes $mn < 2^{62}$. Time: $\log(n)$ Status: Works
 */
ll crt(ll a, ll m, ll b, ll n) {
    if (n > m) swap(a, b), swap(m, n);
    ll x, y, g = euclid(m, n, x, y);
    assert((a - b) % g == 0);  // else no solution
    x = (b - a) % n * x % n / g * m + a;
    return x < 0 ? x + m * n / g : x;
}

#pragma GCC diagnostic pop
#pragma endregion programmation }

ll a, b, c, x, y, z, r, s, t;

void solve() {
    cin >> a >> b >> c >> x >> y >> z >> r >> s >> t;
    if (0 || cin.fail()) exit(0);
    if ((x - r <= 0 || x + r >= a) && (y - s <= 0 || y + s >= b) &&
        (z - t <= 0 || z + t >= c)) {
        cout << 0;
        return;
    }
    ll ans = 4E18;
    range(-s, s + 1, j) range(-t, t + 1, k) {
        ll xx = (x - r) % a, yy = (y + j) % b, zz = (z + k) % c;
        xx < 0 && (xx += a), yy < 0 && (yy += b), zz < 0 && (zz += c);
        ans = min(ans, crt(crt(xx, a, yy, b), a * b, zz, c));
    }
    range(-r, r + 1, i) range(-t, t + 1, k) {
        ll xx = (x + i) % a, yy = (y - s) % b, zz = (z + k) % c;
        xx < 0 && (xx += a), yy < 0 && (yy += b), zz < 0 && (zz += c);
        ans = min(ans, crt(crt(xx, a, yy, b), a * b, zz, c));
    }
    range(-r, r + 1, i) range(-s, s + 1, j) {
        ll xx = (x + i) % a, yy = (y + j) % b, zz = (z - t) % c;
        xx < 0 && (xx += a), yy < 0 && (yy += b), zz < 0 && (zz += c);
        ans = min(ans, crt(crt(xx, a, yy, b), a * b, zz, c));
    }
    cout << ans;
}

void solve_suite() {
    local freopen("./sandbox/i2.txt", "r", stdin);
    local cout.open("./sandbox/o.txt");
    num_cases = 1 << 0;
    // cin >> num_cases;
    local num_cases = 1E9;
    // local debug_id = , _cout.setstate(_S_failbit), cerr.setstate(_S_failbit);
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // local if (case_id == ) _cout.clear(), cerr.clear();
        // else _cout.setstate(_S_failbit), cerr.setstate(_S_failbit);
        local cout << "Case #" << case_id << ": ";
        solve();
        local cout << "\n";
        eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
