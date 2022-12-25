// Solution to Group 2 of Closeness Queries
// (https://open.kattis.com/problems/closenessqueries)
//
// Same idea as in my group 1 solution, but optimized. Turned out that was the
// right idea.
//
// 200k random edges within 45k vertices should give any vertex 8
// neighbors on average. The average distance between a random pair should
// therefore be around 5 (log_8 of 45k). So a forward-backward BFS with a depth
// of 3 (distance 6) should be able to answer most queries. The rest of
// queries (d >= 7) we could use a regular BFS.
//
// Some optimization (or not?) over my old solution included:
//   - Using a bitset instead of a set<int> to mark the reachable vertices:
//   doing bitwise-& should be fast to calculate the set intersections.
//   - Instead of processing the queries in their original order, doing a DFS on
//   the queries: if (u, v) and (v, w) both exist in the queries, doing (v, w)
//   immediately following (u, v) allows us to reuse the computed reachable
//   vertices from v to match with w.
//
// Using the union-find is probably unnecessary due to the small world network.

// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

#pragma region programmation {
#pragma region common {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef DEBUG
#    define DEBUG 0
#elif DEBUG
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

// Binary search
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
    for (auto&& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename T, size_t size,
          enable_if_t<!is_same<T, char>::value, int> = 0>
ostream& operator<<(ostream& out, const T (&x)[size]) {
    out << "{";
    string delim;
    for (auto&& y : x) out << delim << y, delim = ", ";
    return out << "}";
}
template <typename T, size_t size>
ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (auto&& y : x) out << delim << y, delim = ", ";
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
    apply([&](auto&&... y) { (..., (out << delim << y, delim = ", ")); }, x);
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

#if DEBUG
// printf into cerr
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)
#    endif
// trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), 0)
// view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define view(...) (_view(__VA_ARGS__), trace(""), 0)
#    define debug
#else
#    define eprintf(...) (void)0
#    define trace(...) ((void)0, 0)
#    define view(...) ((void)0, 0)
#    define debug while (false)
#endif

int num_cases = 1, case_id;

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif
#pragma endregion common }

// Additional library code
/**
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

#pragma GCC diagnostic pop
#pragma endregion programmation }

const int mxn = /* DEBUG ? 7 : */ 45000, mxm = 200000, mxq = 10000;
using B = bitset<mxn>;
int n, m, q, qc[mxn], ans[mxq];
vi nei[mxn];
map<int, vi> qs[mxn];
UF uf(mxn);
const int mxc = 1728;
bitset<mxc> fc;
B con[mxc][3], vis, bs2;
int uc[mxn];
deque<int> sa, bfs;

void read() {
    cin >> n >> m;
    range(m) {
        int u, v;
        cin >> u >> v;
        nei[u].push_back(v), nei[v].push_back(u);
        uf.join(u, v);
    }
    cin >> q;
    range(q, i) {
        int u, v;
        cin >> u >> v;
        if (!uf.sameSet(u, v)) {
            ans[i] = -1;
            continue;
        }
        if (!qc[u]) sa.push_back(u);
        if (!qc[v]) sa.push_back(v);
        qc[u]++, qc[v]++;
        qs[u][v].push_back(i), qs[v][u].push_back(i);
    }
}

// Stops if t is found
int cc_;
int calc_con(int s, int t = -1) {
    if (~uc[s]) return uc[s];
    assert(fc.count());
    int i = int(fc._Find_first());
    uc[s] = i, fc[i] = false;
    debug amax(cc_, int(len(fc) - fc.count()));
    each(con[i], c) c.reset();
    vis.reset(), vis[s] = true;
    bfs = {s};
    range(3, d) {
        int l = len(bfs);
        range(l) {
            int u = bfs.front();
            bfs.pop_front();
            each(nei[u], v) if (!vis[v]) {
                vis[v] = true;
                con[i][d][v] = true;
                if (v == t) return i;
                bfs.push_back(v);
            }
        }
    }
    return i;
}

void free_con(int s) {
    if (!~uc[s]) return;
    // trace("free", s, uc[s]);
    fc[uc[s]] = true;
    uc[s] = -1;
}

int dist(int s, int t) {
    int si = calc_con(s, qc[s] == 1 ? t : -1);
    // trace(s, t, si, con[si]);
    range(3, i) if (con[si][i][t]) return i + 1;
    int ti = calc_con(t);
    // trace(s, t, ti, con[ti]);
    range(3, i) if ((con[si][2] & con[ti][i]).count()) return i + 4;
    return -1;
}

// Should only be used sparingly hopefully
int bc_ = 0;
int brute(int s, int t) {
    debug bc_++;
    bfs = {s};
    vis.reset(), vis[s] = true;
    for (int l, d = 1; (l = len(bfs)); d++) {
        range(l) {
            int u = bfs.front();
            bfs.pop_front();
            each(nei[u], v) {
                if (v == t) return d;
                if (vis[v]) continue;
                vis[v] = true;
                bfs.push_back(v);
            }
        }
    }
    assert(0);
}

void solve() {
    read();

    fc.set(), memset(uc, -1, sizeof(uc));
    while (len(sa)) {
        if (!(rand() & 127)) trace(len(sa));
        int s = sa.back();
        sa.pop_back();
        if (!qc[s]) continue;
        each(qs[s], t, is) if (!ans[is[0]]) {
            // trace("measure", s, t);
            int d = -1;
            d = dist(s, t);
            if (!~d) {
                // trace("  far", s, t);
                d = brute(s, t);
            }
            each(is, i) ans[i] = d;
            qc[s]--, qc[t]--;
            if (!qc[s]) free_con(s);
            if (qc[t])
                bfs.push_back(t);
            else
                free_con(t);
        }
    }

    range(q, i) {
        debug cout << "#" << i << ": ";
        cout << ans[i] << "\n";
    }
    trace(bc_, cc_);
}

void solve_suite() {
    debug freopen("./sandbox/i18.txt", "r", stdin);
    debug cout.open("./sandbox/o18.txt");
    // cin >> num_cases;
    // num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        // cout << "Case #" << case_id << ": ";
        solve();
        // cout << "\n";
        eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
