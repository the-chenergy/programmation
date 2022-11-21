#define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01  // Do not declare the main function
#define LOCAL 0  // If 0 or not set, "comment" all cerr and trace

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define len(x) int(size(x))

#if !LOCAL
#define cerr \
    if (false) cerr
#define eprintf \
    if (false) printf
#if TRACE_COUT
#define cout \
    if (false) cout
#endif
#else
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#ifdef TRACE_COUT
#define cerr cout
#endif
#endif

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
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <typename... T>
ostream& operator<<(ostream& out, const tuple<T...> x);

template <typename TContainer, typename T = typename enable_if<
                                   !is_same<TContainer, string>::value,
                                   typename TContainer::value_type>::type>
ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename T, size_t size>
ostream& operator<<(ostream& out, const std::array<T, size>& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x) {
    return out << "{" << x.first << ", " << x.second << "}";
}

template <typename... T>
ostream& operator<<(ostream& out, const tuple<T...> x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}
}  // namespace std

template <typename TArg1>
void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') cerr << labels + (labels[0] == ' ') << ": ";
    cerr << arg1 << "\n";
}

template <typename TArg1, typename... TArgs>
void _trace(const char* labels, const TArg1& arg1, const TArgs&... args) {
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

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<double> vd;
bool zero(double x) { return fabs(x) < 1e-10; }
double MinCostMatching(const vector<vd>& cost, vi& L, vi& R) {
    int n = sz(cost), mated = 0;
    vd dist(n), u(n), v(n);
    vi dad(n), seen(n);
    rep(i, 0, n) {
        u[i] = cost[i][0];
        rep(j, 1, n) u[i] = min(u[i], cost[i][j]);
    }
    rep(j, 0, n) {
        v[j] = cost[0][j] - u[0];
        rep(i, 1, n) v[j] = min(v[j], cost[i][j] - u[i]);
    }
    L = R = vi(n, -1);
    rep(i, 0, n) rep(j, 0, n) {
        if (R[j] != -1) continue;
        if (zero(cost[i][j] - u[i] - v[j])) {
            L[i] = j;
            R[j] = i;
            mated++;
            break;
        }
    }
    for (; mated < n; mated++) {  // un t i l so lution is f eas i b l e
        int s = 0;
        while (L[s] != -1) s++;
        fill(all(dad), -1);
        fill(all(seen), 0);
        rep(k, 0, n) dist[k] = cost[s][k] - u[s] - v[k];
        int j = 0;
        for (;;) {
            j = -1;
            rep(k, 0, n) {
                if (seen[k]) continue;
                if (j == -1 || dist[k] < dist[j]) j = k;
            }
            seen[j] = 1;
            int i = R[j];
            if (i == -1) break;
            rep(k, 0, n) {
                if (seen[k]) continue;
                auto new_dist = dist[j] + cost[i][k] - u[i] - v[k];
                if (dist[k] > new_dist) {
                    dist[k] = new_dist;
                    dad[k] = j;
                }
            }
        }
        rep(k, 0, n) {
            if (k == j || !seen[k]) continue;
            auto w = dist[k] - dist[j];
            v[k] += w, u[R[k]] -= w;
        }
        u[s] += dist[j];
        while (dad[j] >= 0) {
            int d = dad[j];
            R[j] = R[d];
            L[R[j]] = j;
            j = d;
        }
        R[j] = s;
        L[s] = j;
    }
    auto value = vd(1)[0];
    rep(i, 0, n) value += cost[i][L[i]];
    return value;
}

int n, k;
double pen;
vector<vector<double>> cost;
vector<vector<int>> adj;
vector<vector<double>> dp;

void dfs(int u, int par) {
    int n_chi = 0;
    for (auto v : adj[u]) {
        if (v == par) continue;
        n_chi++;
        for (auto w : adj[v]) {
            if (w == u) continue;
            dfs(w, v);
            for (int x = 0; x < k; x++) cost[v][x] += dp[w][x];
        }
    }
    if (!n_chi) return;

    for (int p = 0; p < (par == -1 ? 1 : k); p++) {
        double w_pen = pen;
        for (auto v : adj[u])
            if (v != par) w_pen += *min_element(cost[v].begin(), cost[v].end());

        if (len(adj[u]) > k) {
            dp[u][p] = w_pen;
            continue;
        }

        vector<vector<double>> cs;
        for (auto v : adj[u]) {
            if (v == par) continue;
            cs.push_back({});
            for (int x = 0; x < k; x++)
                if (par == -1 || x != p) cs.back().push_back(cost[v][x]);
        }
        while (len(cs) < len(cs[0])) cs.push_back(vector(len(cs[0]), 0.));
        vector<int> l, r;
        double no_pen = MinCostMatching(cs, l, r);
        dp[u][p] = min(w_pen, no_pen);
    }
}

void solve(int /* case_id */) {
    cin >> n >> k >> pen;
    cost.assign(n, vector(k, 0.));
    for (int u = 0; u < n; u++)
        for (int x = 0; x < k; x++) cin >> cost[u][x];
    adj.assign(n, {});
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v, u--, v--;
        adj[u].push_back(v), adj[v].push_back(u);
    }

    if (n == 1) {
        cout << *min_element(cost[0].begin(), cost[0].end());
        return;
    }

    dp.assign(n, vector(k, 0.));
    dfs(0, -1);
    dfs(adj[0][0], -1);
    cout << ll(dp[0][0] + dp[adj[0][0]][0]);
}

void solve_suite() {
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";
        fprintf(stderr, "(Run time: %.2LF s)\n",
                ld(clock()) / case_id / CLOCKS_PER_SEC);
    }
}
