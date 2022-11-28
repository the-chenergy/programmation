#define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use stdout for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
#define LOCAL 0  // If 0 or not set, "comment" all trace and eprintf

#pragma region {
#if LOCAL
#    define _GLIBCXX_DEBUG 1
#    define _GLIBCXX_DEBUG_PEDANTIC 1
#    define _FORTIFY_SOURCE 2
#endif

#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;

#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)

template <typename T>
int len(const T& x) {
    return int(x.size());
}

template <typename T, size_t size>
int len(const T (&)[size]) {
    return size;
}

#define sz len

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

#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
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
    _trace_out << arg1 << ", ";
    _trace(labels + first_label_size + 1, args...);
}

template <typename T>
void _view(const T& x) {
    _trace_out << x;
}

template <typename T, typename... TRange>
void _view(const T& x, int b, int e, TRange... ranges) {
    b = max(0, min(len(x), b)), e = max(b, min(len(x), e));
    string delim = "";
    auto it = begin(x);
    advance(it, b);
    auto& out = _trace_out;
    out << "{";
    for (; b < e; it++, b++) out << delim, _view(*it, ranges...), delim = ", ";
    out << "}";
}

#if LOCAL
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)
#    endif
#    define trace(...) _trace(#__VA_ARGS__, __VA_ARGS__)
#    define view(...) _view(__VA_ARGS__), trace("")
#    define _local
#else
// printf into cerr
#    define eprintf(...) (void)0
// trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define trace(...) (void)0
// view(X, a, b, ...) prints X[a:b, ...] to cerr
#    define view(...) (void)0
#    define _local while (false)
#endif

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"

// Additional library code
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
    T f(T a, T b) { return max(a, b); }  // (any associative fn)
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

#pragma endregion }

const int mxn = 1E5;
int n, ans;
double s;
vector<array<double, 2>> paths;
Tree up(mxn, 0), dn(mxn, 0);
vector<double> uyis, dyis, ys;

void vertical(double x) {
    int l = len(ys);
    vector<int> mxc(l + 1);
    for (int i = 0, prv_yii = 0; i < l; i++) {
        auto y = ys[i], uyi = y - x / s;
        int cur_yii = int(lower_bound(all(uyis), uyi) - begin(uyis));
        int c = up.query(prv_yii, cur_yii + 1);
        mxc[i + 1] = max(mxc[i], c) + 1;
        prv_yii = cur_yii;
    }
    for (int i = 0, prv_yii = 0; i <= l; i++) {
        int cur_yii;
        if (i == l) {
            cur_yii = mxn - 1;
        } else {
            auto y = ys[i], dyi = y + x / s;
            cur_yii = int(lower_bound(all(dyis), dyi) - begin(dyis));
        }
        int c = dn.query(prv_yii, cur_yii + 1);
        ans = max(ans, c + mxc[i]);
        prv_yii = cur_yii;
    }
    for (auto y : ys) {
        auto uyi = y - x / s, dyi = y + x / s;
        int uyii = int(lower_bound(all(uyis), uyi) - begin(uyis));
        int dyii = int(lower_bound(all(dyis), dyi) - begin(dyis));
        up.update(uyii, up.query(uyii, uyii + 1) + 1);
        dn.update(dyii, dn.query(dyii, dyii + 1) + 1);
    }
}

void toss() {
    stable_sort(all(paths));
    uyis.clear(), dyis.clear();
    for (auto [x, y] : paths) {
        auto uyi = y - x / s, dyi = y + x / s;
        uyis.push_back(uyi), dyis.push_back(dyi);
    }
    stable_sort(all(uyis)), stable_sort(all(dyis));
    uyis.erase(unique(all(uyis)), end(uyis));
    dyis.erase(unique(all(dyis)), end(dyis));
    up.s.assign(2 * mxn, 0), dn.s.assign(2 * mxn, 0);
    for (int i = 0; i < n; i++) {
        auto [x, y] = paths[i];
        ys.push_back(y);
        if (i < n - 1 && x == paths[i + 1][0]) continue;
        vertical(x);
        ys.clear();
    }
}

void solve(int /* case_id */) {
    cin >> n >> s;
    paths.resize(n);
    for (auto& [x, y] : paths) cin >> x >> y;
    ans = 0;
    toss();
    for (auto& [x, y] : paths) x *= -1;
    toss();
    cout << ans;
}

void solve_suite() {
    freopen("./sandbox/io.txt", "r", stdin);
    // freopen("./sandbox/o.txt", "w", stdout);

    int num_cases = 1 << 0;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";

        // fprintf(stderr, "(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
