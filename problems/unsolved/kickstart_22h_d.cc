// #define SYNC_IO 01 // Synchronize cin and cout
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

// WA
// https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb1b6/0000000000c47792
void solve(int /* case_id */) {
    int n;
    cin >> n;
    vector<int> nxt(n);
    for (int i = 0; i < n; i++) {
        int j;
        cin >> j, j--;
        nxt[i] = j;
    }
    vector<int> ans(2 * n, 1E9);
    vector<bool> vis(n, 0);
    vector<int> cs;
    for (int s = 0; s < n; s++) {
        if (vis[s]) continue;
        vis[s] = 1;
        int i = s, l = 0;
        do i = nxt[i], vis[i] = 1, l++;
        while (i != s);
        cs.push_back(l);
        ans[l] = 0;
    }
    sort(cs.begin(), cs.end());
    int d = 1;
    for (int i = cs.back() - 1; i > 0; i--) ans[i] = min(ans[i], d);
    while (cs.size() > 1) {
        if (d == 1) {
            for (int i = int(cs.size()) - 1; i > 0; i--)
                for (int j = i - 1; j >= 0; j--)
                    ans[cs[i] + cs[j]] = min(ans[cs[i] + cs[j]], d);
        } else {
            for (int i = int(cs.size()) - 2; i >= 0; i--)
                ans[cs[i] + cs.back()] = min(ans[cs[i] + cs.back()], d);
        }
        int nc = cs.back() + *(cs.end() - 2);
        ans[nc] = min(ans[nc], d);
        for (int i = nc - 1; i > 0; i--) ans[i] = min(ans[i], d + 1);
        cs.pop_back(), cs.pop_back(), cs.push_back(nc);
        d++;
    }
    for (int m = 1; m <= n; m++) cout << ans[m] << " ";
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
