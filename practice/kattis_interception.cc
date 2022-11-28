// #define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use stdout for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define LOCAL 0  // If 0 or not set, "comment" all trace and eprintf

#pragma region programmation {
#pragma region common {
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

// Example: sort(all(A), comparing(x, len(x.second)))
#define comparing(x, ...)                               \
    [&](auto& _l, auto& _r) {                           \
        auto _f = [&](auto& x) { return __VA_ARGS__; }; \
        return _f(_l) < _f(_r);                         \
    }

#define sum(a, x, ...) \
    accumulate(all(a), 0, [&](auto _s, auto& x) { return _s + (__VA_ARGS__); })

#define first_where(lb, ub, i, ...)                                           \
    [&]() {                                                                   \
        auto _lb = lb, _ub = ub, i = _lb;                                     \
        while (_lb < _ub)                                                     \
            i = _lb + (_ub - _lb) / 2, (__VA_ARGS__) ? _ub = i : _lb = i + 1; \
        return _lb;                                                           \
    }();

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
// Outputs to both console and file. Access original cout with _cout.
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
    b = max(0, min(len(x), b)), e = max(b, min(len(x), e));
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
// view(X, a, b, ...) prints X[a:b, ...] to cerr
#    define view(...) (void)0
#    define _local while (false)
#endif

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif
#pragma endregion common }

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
// Additional library code

#pragma GCC diagnostic pop
#pragma endregion programmation }

int n, m, cross[4];
vector<array<int, 3>> paths;
vector<tuple<int, bool, int>> wings[4];  // {x, is_begin, i_path}
vector<int> wing_cuts[4];
bitset<500000> open;
vector<int> opened;
// unordered_set<int> open;

void clear_opened() {
    // open.clear();
    for (auto x : opened) open[x] = false;
    opened.clear();
}

void intercept(vector<int>& out_cuts, vector<tuple<int, bool, int>>& end_pts,
               int start = -1E9) {
    int l = len(end_pts);
    int si = first_where(0, l, i, get<0>(end_pts[i]) >= start);
    for (int i = 0; i < l; i++) {
        auto [x, o, p] = end_pts[(si + i) % l];
        if (o)
            open[p] = true, opened.push_back(p);
        else if (open[p])
            out_cuts.push_back(x), clear_opened();
        // if (o)
        //     open.insert(p);
        // else if (open.count(p))
        //     out_cuts.push_back(x), open.clear();
    }
}

void solve(int /* case_id */) {
    cin >> n >> m >> cross[0] >> cross[1];
    // _local if (cin.fail()) _cout.setstate(ios::failbit), exit(0);
    cross[2] = -(cross[1] + 1), cross[3] = -(cross[0] + 1);
    paths.resize(m);
    for (auto& [a, b, c] : paths) {
        cin >> a >> b;
        if (a % 2 == 0) a *= -1;
        if (b % 2 == 0) b *= -1;
        if (a > b) swap(a, b);
        if (a % 2 != b % 2)
            cin >> c;
        else
            c = 0;
    }
    stable_sort(all(paths));
    trace("done reading paths");

    for (auto& w : wings) w.clear();
    for (int i = 0; i < m; i++) {
        auto [a, b, c] = paths[i];
        if (c) continue;
        if (a % 2) {
            if (b <= cross[0])
                wings[0].emplace_back(a, 1, i), wings[0].emplace_back(b, 0, i);
            else if (a >= cross[1])
                wings[1].emplace_back(-b, 1, i),
                    wings[1].emplace_back(-a, 0, i);
        } else {
            if (b <= cross[2])
                wings[2].emplace_back(a, 1, i), wings[2].emplace_back(b, 0, i);
            else if (a >= cross[3])
                wings[3].emplace_back(-b, 1, i),
                    wings[3].emplace_back(-a, 0, i);
        }
    }
    trace("done building wings", len(wings));
    for (int i = 0; i < 4; i++) {
        clear_opened();
        // open.clear();
        wing_cuts[i].clear();
        stable_sort(all(wings[i]));
        intercept(wing_cuts[i], wings[i]);
        if (i == 1 || i == 3)
            for (auto& x : wing_cuts[i]) x *= -1;
        trace("  done intercepting wing", i, len(wing_cuts[i]));
    }
    int n_wing_cuts = sum(wing_cuts, w, len(w));
    trace("done intercepting all wings", n_wing_cuts);

    vector<array<int, 2>> ans;
    vector<tuple<int, bool, int>> body, body0;
    for (int bridge = 0; bridge < 16; bridge++) {
        bool skip = false;
        for (int i = 0; i < 4; i++)
            skip |= (bridge & (1 << i)) && len(wing_cuts[i]) &&
                    wing_cuts[i].back() == cross[i];
        if (skip) {
            trace("  skipped", bridge);
            continue;
        }
        for (int i = 0; i < 4; i++)
            if (bridge & (1 << i))
                wing_cuts[i].push_back(cross[i]), n_wing_cuts++;

        clear_opened();
        // open.clear();
        if (!bridge) {
            for (int i = 0; i < m; i++) {
                auto [a, b, c] = paths[i];
                if (c) {
                    if (len(wing_cuts[2]) && a < wing_cuts[2].back()) continue;
                    if (len(wing_cuts[3]) && a > wing_cuts[3].back()) continue;
                    if (len(wing_cuts[0]) && b < wing_cuts[0].back()) continue;
                    if (len(wing_cuts[1]) && b > wing_cuts[1].back()) continue;
                    body.emplace_back(min(max(a, cross[2]), cross[3]),
                                      c == cross[0], i);
                    body.emplace_back(min(max(b, cross[0]), cross[1]),
                                      c == cross[1], i);
                    if (c == cross[1] && !open[i])
                        open[i] = true, opened.push_back(i);
                    // if (c == cross[1]) open.insert(i);
                } else if (a % 2) {
                    if (len(wing_cuts[0]) && a < wing_cuts[0].back()) continue;
                    if (len(wing_cuts[1]) && b > wing_cuts[1].back()) continue;
                    body.emplace_back(max(a, cross[0]), 1, i);
                    body.emplace_back(min(b, cross[1]), 0, i);
                } else {
                    if (len(wing_cuts[2]) && a < wing_cuts[2].back()) continue;
                    if (len(wing_cuts[3]) && b > wing_cuts[3].back()) continue;
                    body.emplace_back(max(a, cross[2]), 1, i);
                    body.emplace_back(min(b, cross[3]), 0, i);
                }
            }
            stable_sort(all(body));
            body0 = body;
        } else {
            body.clear();
            for (auto [x, o, i] : body0) {
                auto [a, b, c] = paths[i];
                if (c) {
                    if (len(wing_cuts[2]) && a < wing_cuts[2].back()) continue;
                    if (len(wing_cuts[3]) && a > wing_cuts[3].back()) continue;
                    if (len(wing_cuts[0]) && b < wing_cuts[0].back()) continue;
                    if (len(wing_cuts[1]) && b > wing_cuts[1].back()) continue;
                    if (c == cross[1] && !open[i])
                        open[i] = true, opened.push_back(i);
                    // if (c == cross[1]) open.insert(i);
                } else if (a % 2) {
                    if (len(wing_cuts[0]) && a < wing_cuts[0].back()) continue;
                    if (len(wing_cuts[1]) && b > wing_cuts[1].back()) continue;
                } else {
                    if (len(wing_cuts[2]) && a < wing_cuts[2].back()) continue;
                    if (len(wing_cuts[3]) && b > wing_cuts[3].back()) continue;
                }
                body.emplace_back(x, o, i);
            }
        }
        trace("  done building body", bridge, len(body));
        vector<int> body_cuts;
        intercept(body_cuts, body);
        trace("  done intercepting body once", len(body_cuts));
        if (len(body_cuts)) {
            body_cuts = {body_cuts.back()}, clear_opened();
            // body_cuts = {body_cuts.back()}, open.clear();
            intercept(body_cuts, body, body_cuts.back());
            trace("  done intercepting body twice", len(body_cuts));
        }
        if (!bridge || len(body_cuts) + n_wing_cuts < len(ans)) {
            ans.clear();
            for (auto x : body_cuts) {
                if (x == cross[0])
                    ans.push_back({cross[0], cross[0] + 1});
                else if (x == cross[2])
                    ans.push_back({cross[1], cross[1] + 1});
                else
                    ans.push_back({abs(x), abs(x - 2)});
            }
            for (auto& w : wing_cuts) {
                for (auto x : w) {
                    x = abs(x);
                    ans.push_back({x, x + (x >= cross[1] ? 2 : -2)});
                }
            }
            trace("  done updating ans", len(ans));
        }

        for (int i = 0; i < 4; i++)
            if (bridge & (1 << i)) wing_cuts[i].pop_back(), n_wing_cuts--;
    }

    cout << len(ans) << "\n";
    for (auto [a, b] : ans) {
        if (a > b) swap(a, b);
        cout << a << " " << b << "\n";
    }
}

void solve_suite() {
    // _local freopen("./sandbox/i.txt", "r", stdin);
    // cout.open("./sandbox/o.txt");

    int num_cases = 1 << 0;
    // _local num_cases = 1E9;
    // cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        // _local cout << "Case #" << case_id << ": ";
        solve(case_id);
        // cout << "\n";
        // _local _cout << endl;

        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC);
    }
}
