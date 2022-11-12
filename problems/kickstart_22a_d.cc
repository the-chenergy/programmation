// #define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01 // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01 // Do not declare the main function
// #define LOCAL 0  // If 0 or not set, "comment" all cerr and trace

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

auto FAC = array{1,    1,     2,      6,       24,       120,      720,
                 5040, 40320, 362880, 3628800, 39916800, 479001600};

ll nck(int n, int k) { return FAC[n] / FAC[n - k] / FAC[k]; }

ll pow10(int p) { return ll(pow(10, p)); }

const int MXP = 14;

auto interesting = ([]() {
    auto ans = array<vector<array<int, 11>>, MXP>();
    auto ct0 = array<int, 11>();
    deque<pair<int, array<int, 11>>> dfs{{0, ct0}};
    while (dfs.size()) {
        auto [i, ct] = dfs.back();
        dfs.pop_back();
        for (int j = i; j <= 9; j++) {
            auto nct = ct;
            nct[j]++, nct.back()++;
            if (nct.back() < MXP - 1) dfs.emplace_back(j, nct);
            if (nct[0] == nct.back()) continue;  // string of zeros
            ll sum = 0, prod = 1;
            for (int d = 0; d <= 9; d++) {
                sum += d * nct[d];
                prod *= ll(pow(d, nct[d]));
            }
            if (prod % sum == 0) ans[nct.back()].push_back(nct);
        }
    }
    return ans;
})();

ll digits(array<int, 11>& ct, int omit) {
    ll ans = 1;
    int rem = ct.back() - (omit <= 9);
    for (int d = 0; rem && d <= 9; d++) {
        int c = ct[d] - (d == omit);
        if (!c) continue;
        ans *= nck(rem, c);
        rem -= c;
    }
    return ans;
}

ll combo(array<int, 11>& ct, ll n, bool lz);

auto combo_p = ([]() {
    vector<ll> ans{0};
    for (int p = 1; p < MXP - 1; p++) {
        ll a = 0;
        for (auto& ct : interesting[p]) a += combo(ct, pow10(p), 0);
        ans.push_back(ans.back() + a);
    }
    return ans;
})();

ll combo(array<int, 11>& ct, ll n, bool lz = 0) {
    int p = ct.back();
    if (p == 0) return 0;
    if (!lz && n < pow10(p - 1)) return 0;
    int tar = int(min(ll(n / pow10(p - 1)), 10LL));
    ll ans = 0;
    for (int d = !lz; d < tar; d++) {
        if (!ct[d]) continue;
        ans += digits(ct, d);
    }
    if (tar <= 9 && ct[tar]) {
        auto nct = ct;
        nct[tar]--, nct.back()--;
        n %= pow10(p - 1);
        ans += combo(nct, n, 1);
    }
    return ans;
}

ll interest(ll n) {
    int p = int(log10(n));
    ll ans = combo_p[p];
    for (auto& ct : interesting[p + 1]) ans += combo(ct, n);
    return ans;
}

// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb33e/00000000009e73ea
void solve(int /* case_id */) {
    ll a, b;
    cin >> a >> b;
    cout << interest(b + 1) - interest(a);
}

void solve_suite() {
    auto t = clock();
    // for (ll a = 8; a <= 13; a++) trace(a, interest(a));
    // return;
    // return trace(interest(10));
    // return trace(combo_p);
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";
    }
    t = clock() - t;
    trace(t * 1.0 / CLOCKS_PER_SEC);
}
