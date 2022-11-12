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

const int MAX_N = 400;
const ll MOD = ll(1E9) + 7;

const auto FAC = []() {
    array<ll, MAX_N + 1> ans;
    ans[0] = 1;
    for (int i = 1; i <= MAX_N; i++) ans[i] = (ans[i - 1] * i) % MOD;
    return ans;
}();

ll mod_pow(ll b, ll p) {
    ll ans = 1;
    while (p) {
        if (p % 2) ans = ans * b % MOD;
        b = b * b % MOD;
        p /= 2;
    }
    return ans;
}
int n;
string s;

// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb4d1/0000000000b20d16
void solve(int /* case_id */) {
    cin >> n >> s;
    /*
    pal(b,c,l)=
         pal(b+1,c-1,l)
        +pal(b,c-1,l)
        -pal(b+1,c-2,l)
        +(s[b]==s[b+c-1])*pal(b+1,c-2,l-2)
    */
    auto pal = vector(n + 1, vector(n + 1, vector(n, 0LL)));
    for (int b = 0; b <= n; b++)
        for (int c = 0; b + c <= n; c++) pal[b][c][0] = 1;
    for (int b = 0; b < n; b++) pal[b][1][1] = 1;
    for (int c = 1; c <= n; c++) {
        for (int l = 1; l < n; l++) {
            for (int b = n - c; b >= 0; b--) {
                ll p = 0;
                if (b < n) (p += pal[b + 1][c - 1][l]) %= MOD;
                (p += pal[b][c - 1][l]) %= MOD;
                if (b < n && c >= 2)
                    ((p -= pal[b + 1][c - 2][l]) += MOD) %= MOD;
                if (b < n && c >= 2 && l >= 2 && s[b] == s[b + c - 1])
                    (p += pal[b + 1][c - 2][l - 2]) %= MOD;
                (pal[b][c][l] += p) %= MOD;
                assert(pal[b][c][l] >= 0);
            }
        }
    }
    ll ans = 0;
    for (int l = 0; l < n; l++) {
        ll ways = FAC[l] * FAC[n - l] % MOD;
        (ways *= pal[0][n][l]) %= MOD;
        (ans += ways) %= MOD;
        assert(ways >= 0 && ans >= 0);
    }
    cout << (ans * mod_pow(FAC[n], MOD - 2)) % MOD;
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
