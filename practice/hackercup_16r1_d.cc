#define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01  // Do not declare the main function
// #define LOCAL 0  // If 0 or not set, "comment" all cerr and trace

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;

#define len(x) int(size(x))

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

int n, lgn;
vector<vector<bool>> beat;

bool match(int winners, int losers) {
    vector<int> w2l(n, -1), l2w(n, -1);
    vector<bool> vis(n);

    function<bool(int)> dfs = [&](int w) -> bool {
        for (int l = 0; l < n; l++) {
            if (!((losers >> l) & 1) || !beat[w][l] || vis[l]) continue;
            vis[l] = 1;
            if (l2w[l] == -1 || dfs(l2w[l])) {
                w2l[w] = l;
                l2w[l] = w;
                return true;
            }
        }
        return false;
    };

    int matched = 0;
    for (int w = 0; w < n; w++) {
        if (!((winners >> w) & 1)) continue;
        fill(vis.begin(), vis.end(), false);
        if (dfs(w)) matched++;
    }
    return matched == int(__builtin_popcount(winners));
}

vector<int> mem;
int max_score(int tar, int rem) {
    if (__builtin_popcount(rem) == 1) return 0;
    if (mem[rem] >= 0) return mem[rem];
    int nw = __builtin_popcount(rem) / 2, ans = 0, mxa = 32 - __builtin_clz(nw);
    for (int y = (1 << (nw - 1)) - 1, ry = 1, c, r; (ry || y) && y < rem;
         ry = 0, c = y & -y, r = y + c, y = (((r ^ y) >> 2) / c) | r) {
        int winners = y | (1 << tar);
        if (__builtin_popcount(winners) != nw || (rem | winners) != rem)
            continue;
        if (!match(winners, rem ^ winners)) continue;
        ans = max(ans, 1 + max_score(tar, winners));
        if (ans == mxa) break;
    }
    return mem[rem] = ans;
}

int max_rank(int tar) {
    mem.assign(1 << n, -1);
    int ans = max_score(tar, (1 << n) - 1);
    if (ans == lgn) return 1;
    return (1 << (lgn - 1 - ans)) + 1;
}

int min_rank(int tar) {
    bool can_lose = false;
    for (int i = 0; i < n; i++) can_lose |= beat[i][tar];
    return can_lose ? n / 2 + 1 : 1;
}

// https://www.facebook.com/codingcompetitions/hacker-cup/2016/round-1/problems/D
void solve(int /* case_id */) {
    cin >> n, lgn = 31 - __builtin_clz(n);
    beat.assign(n, vector(n, false));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            beat[i][j] = x;
        }
    }
    for (int i = 0; i < n; i++)
        cout << max_rank(i) << " " << min_rank(i) << "\n";
}

void solve_suite() {
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ":\n";
        solve(case_id);
    }
}
