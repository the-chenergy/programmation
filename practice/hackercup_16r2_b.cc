// #define SYNC_IO 01  // Synchronize cin and cout
// #define TRACE_COUT 01  // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01  // Do not declare the main function
// #define LOCAL 0  // If 0 or not set, "comment" all cerr and trace

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

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

const int mxn = 3001;
const auto fac = []() {
    auto ans = array<ld, mxn>();
    for (int i = 1; i < mxn; i++) ans[i] = ans[i - 1] + log2(i);
    return ans;
}();

ld nck(int n, int k) { return fac[n] - fac[n - k] - fac[k]; }

int n, k;
ld p = log2(.9), q = log2(.1);

ld bin(int tot, int suc) {
    return exp2(nck(tot, suc) + p * suc + q * (tot - suc));
}

void solve(int /* case_id */) {
    cin >> n >> k >> p;
    q = log2(1 - p), p = log2(p);
    vector<ld> pr(n + 1), dp(n + 1);
    for (int s = k; s <= n; s++)
        for (int i = k; i <= s; i++) pr[s] += bin(s, i);
    for (int r = k; r <= n; r++)
        for (int s = k; s <= r; s++) dp[r] = max(dp[r], dp[r - s] + pr[s]);
    cout << dp[n];
}

void solve_suite() {
    cout << setprecision(16);
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";
    }
}
