#define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
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
#    define trace(...) 0
#    define view(...) 0
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

using board = array<string, 8>;
// Returns should_stop_search
using move_f = function<bool(int cy, int cx, int ny, int nx)>;

board ip;

void pb(board& p) {
    each(p, row) {
        each(row, pc) cout << pc;
        cout << "\n";
    }
}

void pm(int cy, int cx, int ny, int nx) {
    cout << "abcdefgh"[cx] << "87654321"[cy] << "abcdefgh"[nx] << "87654321"[ny]
         << "\n";
}

#define each_yx(y, x) range(8, y) range(8, x)

bool trav_moves(board& p, int y, int x, move_f f);
bool check(board& p, bool wtm) {
    int ky = -1, kx = -1;
    each_yx(y, x) if (p[y][x] == (wtm ? 'k' : 'K')) {
        ky = y, kx = x;
        break;
    }
    each_yx(y, x) if (p[y][x] != '.' && !!isupper(p[y][x]) == wtm) {
        auto take_k = [&](int, int, int ny, int nx) {
            return ny == ky && nx == kx;
        };
        if ((y == 0 && p[y][x] == 'P') || (y == 7 && p[y][x] == 'p')) {
            // Promotion -- try queen and knight
            each("NQ", np) {
                p[y][x] = wtm ? np : char(tolower(np));
                if (trav_moves(p, y, x, take_k)) return true;
            }
        }
        if (trav_moves(p, y, x, take_k)) return true;
    }
    return false;
}

#define proc(cy, cx, ny, nx) \
    if (f(cy, cx, ny, nx)) return true

array<int, 2> knight_ds[] = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
                             {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

// Calls f for each "potentially legal" move by the piece at (y, x)
// Returns whether search was stopped
bool trav_moves(board& p, int y, int x, move_f f) {
    char pc = p[y][x];
    if (pc == '.') return false;
    // trace(y, x, pc);
    if (pc == 'p' || pc == 'P') {
        int dy = pc == 'P' ? -1 : 1;
        if (p[y + dy][x] == '.') {
            proc(y, x, y + dy, x);
            if (y == (pc == 'P' ? 6 : 1) && p[y + dy * 2][x] == '.')
                proc(y, x, y + dy * 2, x);  // Double move
        }
        if (x && p[y + dy][x - 1] != '.' &&
            !!isupper(p[y + dy][x - 1]) != (pc == 'P'))
            proc(y, x, y + dy, x - 1);
        if (x < 7 && p[y + dy][x + 1] != '.' &&
            !!isupper(p[y + dy][x + 1]) != (pc == 'P'))
            proc(y, x, y + dy, x + 1);

        return false;
    }
    if (pc == 'n' || pc == 'N') {
        each(knight_ds, dy, dx) {
            int ny = y + dy, nx = x + dx;
            if (ny < 0 || ny > 7 || nx < 0 || nx > 7) continue;
            if (p[ny][nx] == '.' || !!isupper(p[ny][nx]) != (pc == 'N'))
                proc(y, x, ny, nx);
        }
        return false;
    }
    char lpc = char(tolower(pc));
    bool cart = lpc == 'q' || lpc == 'k' || lpc == 'r';
    bool diag = lpc == 'q' || lpc == 'k' || lpc == 'b';
    int ran = lpc == 'k' ? 1 : 8;
    // trace(y, x, pc, lpc, cart, diag, ran);
    range(-1, 2, dy) range(-1, 2, dx) if (dy || dx) {
        // trace(pc, dy, dx, !dy || !dx, dy && dx);
        if ((!dy || !dx) && !cart) continue;
        if ((dy && dx) && !diag) continue;
        range(1, ran + 1, s) {
            int ny = y + dy * s, nx = x + dx * s;
            if (ny < 0 || ny > 7 || nx < 0 || nx > 7) break;
            if (p[ny][nx] != '.') {
                if (!!isupper(p[ny][nx]) != !!isupper(pc)) proc(y, x, ny, nx);
                break;
            }
            proc(y, x, ny, nx);
        }
    }
    return false;
}

void solve() {
    range(8, y) cin >> ip[y];
    if (0 || cin.fail()) exit(0);
    debug cout << "Initial board:\n", pb(ip);

    // Find a white move
    //   * That does not result in black checking white
    //   * That checks black
    //   * After which we cannot find a black move that does not result in white
    //     checking black
    each_yx(wy, wx) if (isupper(ip[wy][wx])) {
        auto wm = [&](int cy, int cx, int ny, int nx) {
            auto np = ip;
            np[ny][nx] = ip[cy][cx], np[cy][cx] = '.';
            if (check(np, false)) {
                debug cout << "wk in check: ", pm(cy, cx, ny, nx);
                return false;
            }
            if (!check(np, true)) {
                debug cout << "not checking bk: ", pm(cy, cx, ny, nx);
                return false;
            }
            debug cout << "try: ", pm(cy, cx, ny, nx);
            // debug pb(np);
            auto bm = [&](int cby, int cbx, int nby, int nbx) {
                auto nbp = np;
                nbp[nby][nbx] = np[cby][cbx], nbp[cby][cbx] = '.';
                if (!check(nbp, true)) {
                    debug cout << "    bk escape: ", pm(cby, cbx, nby, nbx);
                    return true;
                }
                return false;
            };
            each_yx(by, bx) if (islower(np[by][bx])) {
                if (trav_moves(np, by, bx, bm)) return false;
            }
            pm(cy, cx, ny, nx);
            return true;
        };
        if (trav_moves(ip, wy, wx, wm)) return;
    }
}

void solve_suite() {
    debug freopen("./sandbox/i.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id == 5 ? _S_goodbit : _S_failbit);
        // debug _cout.clear(case_id == 5 ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ":\n";
        solve();
        debug cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
