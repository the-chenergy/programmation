// #define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use stdout for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define LOCAL 0  // If 0 or not set, "comment" all trace and eprintf

#pragma region programmation {
#pragma region common {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
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
#define _overload(macro, ...) _concat(macro, _argc(__VA_ARGS__))(__VA_ARGS__)

#define _range4(b, e, d, i) for (int i = b; (d) > 0 ? i < (e) : i > (e); i += d)
#define _range1(n) _range4(0, n, 1, _i)
#define _range2(n, i) _range4(0, n, 1, i)
#define _range3(b, e, i) _range4(b, e, 1, i)
// range([begin=0], end, [step=1], i) -> for i in range(begin, end, step)
#define range(...) _overload(_range, __VA_ARGS__)

#define _each2(a, x) for (auto& x : a)
#define _each_(a, ...) for (auto& [__VA_ARGS__] : a)
#define _argc2(...) __argc(__VA_ARGS__, _, _, _, _, _, _, _, _, _, _, 2, 1, 0)
// each(A, ...) -> for ... in A
#define each(...) _concat(_each, _argc2(__VA_ARGS__))(__VA_ARGS__)

// enumerate(A, i, ...) -> for i, (...) in enumerate(A)
#define enumerate(a, i, ...)         \
    for (int i = 0; i != -1; i = -1) \
    each(a, __VA_ARGS__) for (int _##i = 1; _##i; _##i = 0, i++)

int _ADJ4[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
#define _adj42(dy, dx) for (auto [dy, dx] : _ADJ4)
#define _adj44(cy, cx, y, x)                                              \
    _adj42(_dy, _dx) for (int y = cy + _dy, x = cx + _dx, _##y = 1; _##y; \
                          _##y = 0)
#define _adj46(h, w, cy, cx, y, x)                                          \
    _adj42(y, x) for (y += cy, x += cx; y >= 0 && y < h && x >= 0 && x < w; \
                      y = -1)
// adj4([y_lim], [x_lim], cur_y, cur_x, y, x)
//     -> for each (y, x) adjacent to (cy, cx), with optional boundary checks
#define adj4(...) _overload(_adj4, __VA_ARGS__)

#define rep(i, b, e) _range3(b, e, i)
#define trav(x, a) _each2(a, x)
#define all(x) begin(x), end(x)
#define sz len

// Example: partition_point(all(A), selecting(x, len(x) < 2))
#define selecting(x, ...) [&](auto& x) { return __VA_ARGS__; }

// Example: sort(all(A), comparing(x, len(x)))
#define comparing(x, ...)                               \
    [&](auto& _l, auto& _r) {                           \
        auto _f = [&](auto& x) { return __VA_ARGS__; }; \
        return _f(_l) < _f(_r);                         \
    }

// Example: sum(A, x, len(x))
#define sum(a, x, ...)                             \
    accumulate(all(a), decltype(a)::value_type(0), \
               [&](auto _s, auto& x) { return _s + (__VA_ARGS__); })

// Example: first_where(0, len(A), i, len(A[i]) >= 2)
#define first_where(b, e, i, ...)                                        \
    [&]() {                                                              \
        auto _b = b, _e = e, i = b;                                      \
        while (_b < _e)                                                  \
            i = _b + (_e - _b) / 2, (__VA_ARGS__) ? _e = i : _b = i + 1; \
        return _b;                                                       \
    }()

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
const ostream& _cout = cout;

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
    _trace_out << arg1 << ", ";
    _trace(labels + first_label_size + 1, args...);
}

template <typename T>
void _view(const T& x) {
    _trace_out << x;
}

template <typename T, typename... TRange>
void _view(const T& x, int b, int e, TRange... ranges) {
    if (b < 0) b += len(x);
    if (e < 0) e += len(x);
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
#    define _local
#else
// printf into cerr
#    define eprintf(...) (void)0
// trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define trace(...) (void)0
// view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define view(...) (void)0
#    define _local while (false)
#endif

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif
#pragma endregion common }

// Additional library code

#pragma GCC diagnostic pop
#pragma endregion programmation }

int g, w, d, l, p, unk, us;

void read(int& tar, int i) {
    string s;
    cin >> s;
    if (s == "?")
        unk++, tar = -1, us |= 1 << i;
    else
        tar = stoi(s);
}

void print_ans() { cout << g << " " << w << " " << d << " " << l << " " << p; }

void print_ans(array<int, 5> a) { each(a, x) cout << x << " "; }

bool verify(array<int, 5>& a) {
    range(4, i) if (a[i] < 0 || a[i] > 100) return false;
    if (a[4] < 0 || a[4] > 300) return false;
    return a[0] == a[1] + a[2] + a[3] && a[4] == a[1] * 3 + a[2];
}

bool check2(array<int, 5>& a, int u) {
    int lu = __builtin_ctz(u), hu = __lg(u);
    range(101, x) {
        a[lu] = x;
        if (hu == 4)
            a[4] = a[1] * 3 + a[2];
        else if (hu == 3)
            a[3] = a[0] - a[1] - a[2];
        else if (hu == 2)
            a[2] = a[0] - a[1] - a[3];
        else if (hu == 1)
            a[1] = a[0] - a[2] - a[3];
        else
            assert(0);
        if (x == 0) trace("  ", lu, hu, x, a);
        if (verify(a)) return true;
    }
    return false;
}

void solve(int /* case_id */) {
    unk = 0, us = 0;
    read(g, 0), read(w, 1), read(d, 2), read(l, 3), read(p, 4);
    if (!unk) return print_ans();
    assert(unk < 5);
    if (unk == 4) {
        if (p == 296)
            cout << "100 98 2 0 296";
        else if (p == 298)
            cout << "100 99 1 0 298";
        else if (p == 300)
            cout << "100 100 0 0 300";
        else if (w == 100)
            cout << "100 100 0 0 300";
        else if (d == 100)
            cout << "100 0 100 0 100";
        else if (l == 100)
            cout << "100 0 0 100 0";
        else if (g == 0)
            cout << "0 0 0 0 0";
        else
            while (1)
                ;
        return;
    }
    if (unk == 2) {
        array<int, 5> a = {g, w, d, l, p};
        assert(check2(a, us));
        print_ans(a);
        return;
    }
    if (unk == 1) {
        if (g < 0)
            g = w + d + l, print_ans();
        else if (w < 0)
            w = g - d - l, print_ans();
        else if (d < 0)
            d = g - w - l, print_ans();
        else if (l < 0)
            l = g - d - w, print_ans();
        else if (p < 0)
            p = 3 * w + d, print_ans();
        return;
    }
    assert(unk == 3);
    array<int, 5> a = {g, w, d, l, p};
    int i = __builtin_ctz(us), u = us & ~(1 << i);
    range(101, x) {
        a[i] = x;
        trace(i, a[i], x, u);
        if (check2(a, u)) {
            print_ans(a);
            return;
        }
    }
    assert(0);
}

void solve_suite() {
    _local freopen("./sandbox/ia.txt", "r", stdin);
    // cout.open("./sandbox/o.txt");

    int num_cases = 1 << 0;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        // cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";

        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
