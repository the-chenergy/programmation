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

int n;
map<ll, set<ll>> hxs;
ll ans;
const ll MOD = ll(1E9) + 7;

void snake(map<ll, set<ll>>::iterator hit, ll bx, ll ex) {
    if (hit == hxs.begin()) return;
    hit--;
    ll a = 0, b = 0, px = bx, ct = 0;
    for (auto it = hit->second.lower_bound(bx);
         it != hit->second.end() && *it < ex; it++, ct++) {
        (a += *it) %= MOD, (b += (*it * *it) % MOD) %= MOD;
        snake(hit, px, *it), px = *it;
    }
    snake(hit, px, ex);
    (b *= ct) %= MOD, (a *= a) %= MOD;
    (ans += ((b - a) % MOD + MOD) % MOD) %= MOD;
}

void solve(int /* case_id */) {
    cin >> n;
    hxs.clear();
    for (int i = 0; i < n; i++) {
        int x, h;
        cin >> x >> h;
        hxs[h].insert(x);
    }
    ans = 0;
    snake(hxs.end(), 0, MOD - 1);
    assert(ans >= 0 || (trace(ans), 0));
    cout << ans;
}

void solve_suite() {
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 1; case_id <= num_cases; case_id++) {
        cout << "Case #" << case_id << ": ";
        solve(case_id);
        cout << "\n";
    }
}
