// #define SYNC_IO 01
// #define TRACE_COUT 01
// #define LOCAL 0

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;

#define len(x) (int)(x).size()

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

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <class... T>
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

template <typename TFirst, typename TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x) {
    return out << "{" << x.first << ", " << x.second << "}";
}

template <class... T>
ostream& operator<<(ostream& out, const tuple<T...> x) {
    out << "{";
    string delim;
    apply([&](auto&... y) { (..., (out << delim << y, delim = ", ")); }, x);
    return out << "}";
}

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

#pragma endregion }

#define fail                    \
    {                           \
        cout << "impossible\n"; \
        return;                 \
    }

void solve(int /* case_id */) {
    int n;
    cin >> n;
    auto chi = vector(n, vector<int>());
    auto par = vector(n, -1);
    auto in = vector(n, 0);
    for (int i = 1; i < n; i++) {
        cin >> par[i], par[i]--;
        chi[par[i]].push_back(i);
        in[par[i]]++;
    }
    auto flow = vector(n, 0ll);
    for (int i = 0; i < n; i++) cin >> flow[i];

    auto lb = vector(n, 0ll);
    deque<int> bfs;
    for (int i = 0; i < n; i++) {
        if (!in[i]) {
            lb[i] = max(flow[i], 1ll);
            bfs.push_back(i);
        }
    }
    auto has_unk = vector(n, false);
    while (len(bfs)) {
        int i = bfs.front();
        bfs.pop_front();
        if (flow[i])
            lb[i] = flow[i];
        else if (chi[i].size() && !has_unk[i])
            flow[i] = lb[i];
        int p = par[i];
        if (p == -1) continue;
        lb[p] += lb[i];
        if (flow[p] && lb[p] > flow[p]) fail;
        if (!flow[i]) has_unk[p] = true;
        in[p]--;
        if (!in[p]) bfs.push_back(p);
    }

    for (int i : in)
        if (i) fail;

    bfs.push_back(0);
    while (len(bfs)) {
        int i = bfs.front();
        bfs.pop_front();
        ll used = 0, tot_lb = 0;
        vector<int> unk;
        for (int c : chi[i]) {
            if (flow[c])
                used += flow[c];
            else {
                unk.push_back(c);
                tot_lb += lb[c];
            }
            bfs.push_back(c);
        }
        if (len(unk) == 1)
            flow[unk[0]] = flow[i] - used;
        else if (tot_lb == flow[i] - used)
            for (int c : unk) flow[c] = lb[c];
        else if (len(unk))
            fail;
    }

    bfs.push_back(0);
    while (len(bfs)) {
        int i = bfs.front();
        bfs.pop_front();
        if (!flow[i]) fail;
        if (chi[i].empty()) continue;
        ll tot = 0;
        for (int c : chi[i]) {
            tot += flow[c];
            bfs.push_back(c);
        }
        if (tot != flow[i]) fail;
    }

    for (ll f : flow) cout << f << "\n";
}

int main() {
    int num_cases = 1;
    // cin >> num_cases;
    for (int case_id = 0; case_id < num_cases; case_id++) {
        // cout << "Case #" << case_id + 1 << ": ";
        solve(case_id);
    }
}
