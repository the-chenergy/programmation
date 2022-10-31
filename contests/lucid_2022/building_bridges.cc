// #define SYNC_IO 01 // Synchronize cin and cout
// #define TRACE_COUT 01 // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01 // Do not declare the main function
// #define LOCAL 01 // If 0 or not set, "comment" all cerr and trace

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

#ifdef TRACE_COUT
#define cerr cout
#endif

#if !LOCAL
#define cerr \
    if (false) cerr
#define fprintf \
    if (false) fprintf
#if TRACE_COUT
#define cout \
    if (false) cout
#endif
#endif

static void _init() __attribute__((constructor));

static void _init() {
#if !SYNC_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
}

namespace std {
template <typename T, size_t size>
static ostream& operator<<(ostream& out, const array<T, size>& x);

template <typename TFirst, typename TSecond>
static ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <typename... T>
static ostream& operator<<(ostream& out, const tuple<T...> x);

template <typename TContainer, typename T = typename enable_if<
                                   !is_same<TContainer, string>::value,
                                   typename TContainer::value_type>::type>
static ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename T, size_t size>
static ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename TFirst, typename TSecond>
static ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x) {
    return out << "{" << x.first << ", " << x.second << "}";
}

template <typename... T>
static ostream& operator<<(ostream& out, const tuple<T...> x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}
}  // namespace std

template <typename TArg1>
static void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') cerr << labels + (labels[0] == ' ') << ": ";
    cerr << arg1 << "\n";
}

template <typename TArg1, typename... TArgs>
static void _trace(const char* labels, const TArg1& arg1,
                   const TArgs&... args) {
    if (labels[0] == ' ') labels++;
    size_t first_label_size = strchr(labels, ',') - labels;
    if (labels[0] != '"') cerr.write(labels, first_label_size) << ": ";
    cerr << arg1 << ", ";
    _trace(labels + first_label_size + 1, args...);
}

#if LOCAL
#define trace(...) _trace(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) (void)0
#endif

#if !NO_MAIN
void solve_suite();
int main() { solve_suite(); }
#endif

#pragma endregion }

struct union_find {
    vector<int> _data;
    union_find(int size) : _data(size, -1){};
    int count(int x) { return -_data[find(x)]; }
    int find(int x) { return _data[x] < 0 ? x : _data[x] = find(_data[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (-_data[x] < -_data[y]) swap(x, y);
        _data[x] += _data[y], _data[y] = x;
        return true;
    }
};

// https://www.hackerrank.com/contests/lpc-2022/challenges/lpc2022-building-bridges
void solve(int /* case_id */) {
    int h, w;
    cin >> h >> w;
    vector<vector<bool>> g(h, vector<bool>(w));
    vector<set<int>> col(w), row(h);
    bool any = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            int i;
            cin >> i;
            g[y][x] = i;
            if (i) {
                any = 1;
                col[x].insert(y);
                row[y].insert(x);
            }
        }
    if (!any) {
        cout << 0;
        return;
    }
    union_find uf(h * w);
    vector<array<int, 2>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    set<int> cc;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (!g[y][x]) continue;
            for (auto [ny, nx] : dirs) {
                ny += y, nx += x;
                if (ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
                if (!g[ny][nx]) continue;
                uf.unite(y * w + x, ny * w + nx);
            }
        }
    }
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (g[y][x]) cc.insert(uf.find(y * w + x));
    assert(cc.size() > 0u);
    // if (cc.size() == 1u) {
    //     cout << 0;
    //     return;
    // }
    trace(cc);
    map<array<int, 2>, int> eds;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            if (!g[y][x]) continue;
            auto rit = row[y].lower_bound(x);
            int c1 = uf.find(y * w + x);
            if (rit != row[y].begin()) {
                int c2 = uf.find(y * w + *prev(rit));
                if (c1 != c2) {
                    int ex = 1E9;
                    if (eds.count({c1, c2})) ex = eds[{c1, c2}];
                    eds[{c1, c2}] = min(ex, abs(x - *prev(rit)) - 1);
                }
            }
            if (next(rit) != row[y].end()) {
                int c2 = uf.find(y * w + *next(rit));
                if (c1 != c2) {
                    int ex = 1E9;
                    if (eds.count({c1, c2})) ex = eds[{c1, c2}];
                    eds[{c1, c2}] = min(ex, abs(x - *next(rit)) - 1);
                }
            }
            auto hit = col[x].lower_bound(y);
            if (hit != col[x].begin()) {
                int c2 = uf.find(*prev(hit) * w + x);
                if (c1 != c2) {
                    int ex = 1E9;
                    if (eds.count({c1, c2})) ex = eds[{c1, c2}];
                    eds[{c1, c2}] = min(ex, abs(y - *prev(hit)) - 1);
                }
            }
            if (next(hit) != col[x].end()) {
                int c2 = uf.find(*next(hit) * w + x);
                if (c1 != c2) {
                    int ex = 1E9;
                    if (eds.count({c1, c2})) ex = eds[{c1, c2}];
                    eds[{c1, c2}] = min(ex, abs(y - *next(hit)) - 1);
                }
            }
        }
    union_find uf2(h * w);
    int m = 0, ans = 0;
    vector<array<int, 3>> es;
    for (auto& [e, d] : eds) es.push_back({d, e[0], e[1]});
    sort(es.rbegin(), es.rend());
    trace(es);
    while (m < int(cc.size()) - 1 && es.size()) {
        auto [d, x, y] = es.back();
        assert(x != y);
        es.pop_back();
        if (uf2.same(x, y)) continue;
        uf2.unite(x, y);
        ans += d;
        m++;
    }
    if (m == int(cc.size()) - 1) {
        assert(m == uf2.count(*cc.begin()) - 1);
        cout << ans;
    } else
        cout << -1;
}

void solve_suite() {
    int num_cases = 1;
    // cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        // cout << "Case #" << case_id << ": ";
        solve(case_id);
        // cout << "\n";
    }
}
