// #define SYNC_IO 01
// #define TRACE_COUT 01
// #define LOCAL 0

#pragma region {
#include <bits/stdc++.h>

using namespace std;

using uint = unsigned int;
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

template <class T, size_t size>
ostream& operator<<(ostream& out, const array<T, size>& x);

template <class TFirst, class TSecond>
ostream& operator<<(ostream& out, const pair<TFirst, TSecond> x);

template <class... T>
ostream& operator<<(ostream& out, const tuple<T...> x);

template <class TContainer,
          class T = class enable_if<!is_same<TContainer, string>::value,
                                    class TContainer::value_type>::type>
ostream& operator<<(ostream& out, const TContainer& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <class T, size_t size>
ostream& operator<<(ostream& out, const array<T, size>& x) {
    out << "{";
    string delim;
    for (const T& y : x) out << delim << y, delim = ", ";
    return out << "}";
}

template <class TFirst, class TSecond>
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

template <class TArg1>
static void _trace(const char* labels, const TArg1& arg1) {
    if (labels[0] != '"') cerr << labels + (labels[0] == ' ') << ": ";
    cerr << arg1 << "\n";
}

template <class TArg1, class... TArgs>
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

#define fail return (void)(cout << "Impossible\n");

vector<vector<int>> small_ans{
    {0},          {},
    {2},          {},
    {2, 2},       {},
    {2, 2, 2},    {},
    {2, 2, 2, 2}, {9},
    {10},         {2, 9},
    {12},         {2, 2, 9},
    {2, 12},      {2, 2, 2, 9},
    {2, 2, 12},   {2, 2, 2, 2, 9},
    {9, 9},       {9, 10},
    {10, 10},     {9, 12},
    {10, 12},     {2, 9, 12},
    {12, 12},     {2, 2, 9, 12},
};

void solve_small(int n, int k) {
    if (small_ans[n].empty() || len(small_ans[n]) > k) fail;
    for (int i = 0; i < k; i++)
        cout << (i < len(small_ans[n]) ? small_ans[n][i] : 0) << " ";
    cout << "\n";
}

void solve(int /* case_id */) {
    ll n;
    int k;
    cin >> n >> k;
    if (n < (ll)len(small_ans)) return solve_small((int)n, k);

    int l = min(k, 3);
    using ans_t = array<ll, 3>;
    using rem_t = array<int, 3>;
    ans_t ans;
    ans.fill(0);
    vector<bool> vis(1 << 26);
    function<bool(int, int, rem_t)> search = [&](int i, int carry,
                                                 rem_t rem) -> bool {
        for (int j = 0; j < l; j++)
            if (rem[j] > i + 1) return false;
        if (i < 0) return carry == 0;

        int state = (carry << 24) | (i << 18) | ((rem[0] & 63) << 12) |
                    ((rem[1] & 63) << 6) | (rem[2] & 63);
        trace("eval", i, carry, rem, bitset<25>(state));
        if (vis[state]) return false;
        for (int s = 0; s < 1 << (l + 1); s++) {
            if (__builtin_popcount(s) != ((carry << 1) | ((n >> i) & 1)))
                continue;
            rem_t new_rem = rem;
            bool ok = true;
            for (int j = 0; j < l; j++) {
                if ((s >> j) & 1) {
                    if (!rem[j] || (rem[j] < 0 && ((i + 1) & 1))) {
                        ok = false;
                        break;
                    }
                    if (rem[j] > 0)
                        new_rem[j]--;
                    else
                        new_rem[j] = i / 2;
                }
            }
            if (!ok) continue;
            if (search(i - 1, (s >> l) & 1, new_rem)) {
                for (int j = 0; j < l; j++) ans[j] |= ((s >> j) & 1ll) << i;
                trace("  done", i, carry, rem);
                return true;
            }
        }
        if (l == 3 && carry && ~(n >> i) & 1 && search(i - 1, 2, rem)) {
            trace("  done (sneakily)", i, carry, rem);
            return true;
        }
        vis[state] = true;
        return false;
    };
    int lg = 63 - __builtin_clzll(n);
    if (!search(lg, 0, {-1, -1, -1})) fail;
    if (k == 2) assert(ans[2] == 0ll);
    if (accumulate(ans.begin(), ans.end(), 0ll) != n) {
        cout << setprecision(333333) << fixed;
        while (1) cout << 1e300;
    }
    for (int i = 0; i < k; i++) {
        if (i < l && ans[i] > 0) {
            // if (__builtin_popcountll(ans[i]) * 2 !=
            //     64 - __builtin_clzll(ans[i])) {
            //     cout << setprecision(333333) << fixed;
            //     while (1) cout << 3.;
            // }
            assert(__builtin_popcountll(ans[i]) * 2 ==
                   64 - __builtin_clzll(ans[i]));
        }
        cout << (i < l ? ans[i] : 0) << " ";
    }
    cout << "\n";
}

int main() {
    int num_cases = 1;
    cin >> num_cases;
    for (int case_id = 0; case_id < num_cases; case_id++) {
        // cout << "Case #" << case_id + 1 << ": ";
        solve(case_id);
    }
}
