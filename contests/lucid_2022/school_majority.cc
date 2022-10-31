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

// https://www.hackerrank.com/contests/lpc-2022/challenges/lpc2022-school-majority
void solve(int /* case_id */) {
    int h, w, nt;
    cin >> h >> w >> nt;
    vector<vector<char>> g(h, vector<char>(w));
    map<array<int, 2>, char> search;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            cin >> g[y][x];
            g[y][x] = char(toupper(g[y][x]));
            if (g[y][x] != '0' && g[y][x] != '1') search[{y, x}] = g[y][x];
        }
    vector<array<int, 2>> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
    while (search.size()) {
        map<array<int, 2>, char> nxt;
        for (auto [pos, t] : search) {
            auto [cy, cx] = pos;
            g[cy][cx] = t;
            for (auto [y, x] : dirs) {
                y += cy, x += cx;
                if (y < 0 || y >= h || x < 0 || x >= w) continue;
                if (g[y][x] != '0') continue;
                if (nxt.count({y, x}) && nxt[{y, x}] <= t) continue;
                nxt[{y, x}] = t;
            }
        }
        search = move(nxt);
    }
    // char ans = 0;
    // int ct = 0;
    // for (int y = 0; y < h; y++)
    //     for (int x = 0; x < w; x++) {
    //         // assert(g[y][x] != '0');
    //         if (g[y][x] == '0' || g[y][x] == '1') continue;
    //         if (ans == g[y][x]) {
    //             ct++;
    //         } else {
    //             ct--;
    //             if (ct < 0) {
    //                 ans = g[y][x];
    //                 ct = 1;
    //             }
    //         }
    //     }
    map<char, int> ct;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (g[y][x] != '0' && g[y][x] != '1') ct[g[y][x]]++;
    char ans = 0;
    int c = 0;
    for (auto [x, y] : ct)
        if (y > c) ans = x, c = y;
    cout << ans;
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
