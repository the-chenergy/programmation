// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
#define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

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

int _ADJ4_DIRS[5][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {0, 0}};
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

#pragma GCC diagnostic pop
#pragma endregion programmation }

const int mxh = 25, mxw = 3000;

map<int, set<pii>> br, bc;
int h, w;

void read() {
    string row;
    getline(cin, row);
    int y = 0;
    for (; getline(cin, row); y++) {
        if (row[1] == '#') break;
        enumerate(row, x, c) {
            if (c == '<')
                br[y].emplace(-1, x - 1);
            else if (c == '>')
                br[y].emplace(1, x - 1);
            else if (c == '^')
                bc[x - 1].emplace(-1, y);
            else if (c == 'v')
                bc[x - 1].emplace(1, y);
        }
        w = len(row) - 2;
    }
    h = y;
    trace(br, bc);
}

vector<vector<vector<char>>> has_;
bool has(int y, int x, int t) {
    if ((y == -1 && x == 0) || (y == h && x == w - 1)) return false;
    t %= h * w;
    if (~has_[y][x][t]) return has_[y][x][t];
    return (has_[y][x][t] = br[y].count({-1, (x + t) % w}) ||
                            br[y].count({1, ((x - t) % w + w) % w}) ||
                            bc[x].count({-1, (y + t) % h}) ||
                            bc[x].count({1, ((y - t) % h + h) % h}));
}

array<vector<vector<vector<int>>>, 3> f_;
// vector<vector<vector<array<int, 3>>>> p_;
// int cc = 0;
// int f(int y, int x, int t) {
//     ++cc;
//     (rand() % 2000 == 0) && (trace(cc, y, x, t));
//     if (y == h - 1 && x == w - 1) return 1;

//     int t_ = t % (h * w);
//     if (f_[y][x][t_] < int(1.06E9)) return f_[y][x][t_];

//     f_[y][x][t_] = 1E9;
//     if (has(y, x, t)) return 1E9;

//     int ans = 1E9;
//     adj4(h, w, y, x, ny, nx) amin(ans, 1 + f(ny, nx, t + 1));
//     amin(ans, 1 + f(y, x, t + 1));
//     return f_[y][x][t_] = ans;
// }

void pb(int t) {
    trace(t);
    range(h, y) {
        range(w, x) cerr << (has(y, x, t) ? '*' : '.');
        cerr << "\n";
    }
    cerr << "\n";
}

// void pa(int y, int x, int t) {
//     if (y == h - 1 && x == w - 1) {
//         trace("done", y, x, t);
//         return;
//     }
//     array<int, 3> ans = {1 + f(y, x, t + 1), y, x};
//     adj4(h, w, y, x, ny, nx) amin(ans, array{1 + f(ny, nx, t + 1), ny, nx});
//     trace(y, x, t, ans);
//     pa(ans[1], ans[2], t + 1);
// }

void solve() {
    read();
    int m = h * w;

    has_.assign(h, vector(w, vector(m, char(-1))));
    each(f_, f__) f__.assign(h + 2, vector(w, vector(m, int(1.06E9))));

    // int ans = 1E9;
    // range(m, t) if (!has(0, 0, t)) amin(ans, t + 1 + f(0, 0, t));
    // cout << ans << "\n";
    // return;

    // debug pa(0, 0, 1);
    // debug range(18, t) pb(t);

    deque<array<int, 3>> bfs;
    int t = -1;
    while (t < h * w || len(bfs)) {
        t++;
        int l = len(bfs);
        trace(t, l, m * m);
        range(l) {
            auto [cr, cy, cx] = bfs.front();
            bfs.pop_front();
            int r = cr;
            if (cy == -1 && cx == 0)
                r += cr == 1;
            else if (cy == h && cx == w - 1)
                r += cr == 0;
            // adj4(h, w, cy, cx, y, x) {
            each(_ADJ4_DIRS, dy, dx) {
                int y = dy + cy, x = dx + cx;
                if (!((y == -1 && x == 0) || (y == h && x == w - 1)) &&
                    (y < 0 || x < 0 || y >= h || x >= w))
                    continue;
                if (has(y, x, t)) {
                    trace("  can't", cy, cx, y, x);
                    continue;
                }
                if (cr == 2 && y == h && x == w - 1) {
                    cout << t << "\n";
                    return;
                }
                if (t >= f_[r][y + 1][x][t % (m)]) {
                    trace("  skip", cy, cx, y, x);
                    continue;
                }
                assert(f_[r][y + 1][x][t % (m)] >= 1E9 || trace(y, x, t));
                f_[r][y + 1][x][(t % (m))] = t;
                // p_[y][x][t % (m)] = {cy, cx, t - 1};
                bfs.push_back({r, y, x});
                trace("  push", cy, cx, y, x);
            }
        }
        if (t < h * w && !has(-1, 0, t)) {
            trace("add");
            bfs.push_back({0, -1, 0});
            f_[0][1][0][t] = t;
        }
    }
}

void solve_suite() {
    freopen("./sandbox/ix.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    // num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        // cout << "Case #" << case_id << ": ";
        solve();
        // cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
