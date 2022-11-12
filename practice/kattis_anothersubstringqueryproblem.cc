// #define SYNC_IO 01 // Synchronize cin and cout
// #define TRACE_COUT 01 // Use cout for trace and redirect cerr to cout
// #define NO_MAIN 01 // Do not declare the main function
// #define LOCAL 0 // If 0 or not set, "comment" all cerr and trace

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

static auto _init = ([]() {
#if !SYNC_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
    return 0;
})();

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

const ll POLY_MOD = 3037000493;

vector<array<ll, 2>> poly_pows{{1, 1}, {127, 131}};

struct poly_hashed {
    int _size;
    vector<array<ll, 2>> _pre;
    poly_hashed(string& s) : _size(int(s.size())), _pre(_size + 1) {
        int i = int(poly_pows.size());
        poly_pows.resize(_size + 1);
        for (; i <= _size; i++)
            for (int j = 0; j < 2; j++)
                poly_pows[i][j] =
                    poly_pows[i - 1][j] * poly_pows[1][j] % POLY_MOD;
        for (i = 0; i < _size; i++)
            for (int j = 0; j < 2; j++)
                _pre[i + 1][j] =
                    (_pre[i][j] * poly_pows[1][j] + s[i]) % POLY_MOD;
    }
    /** [include begin, exclude end) */
    ull hash_substring(int begin, int end) {
        array<ll, 2> h;
        for (int j = 0; j < 2; j++) {
            h[j] = (_pre[end][j] - _pre[begin][j] * poly_pows[end - begin][j]);
            h[j] %= POLY_MOD;
            if (h[j] < 0) h[j] += POLY_MOD;
        }
        return (ull(h[1]) << 32) | h[0];
    }
    /** [include begin, exclude begin+count) */
    ull hash_substr(int begin, int count) {
        return hash_substring(begin, begin + count);
    }
};

ull poly_hash(string& s) {
    array<ll, 2> h{0, 0};
    for (char c : s)
        for (int j = 0; j < 2; j++)
            h[j] = (h[j] * poly_pows[1][j] + c) % POLY_MOD;
    return (ull(h[1]) << 32) | h[0];
}

void solve(int /* case_id */) {
    string s;
    cin >> s;
    int n = int(s.size());
    poly_hashed hs(s);
    int q;
    cin >> q;
    vector<int> ans(q, -1);
    // query_size->{ query_hash->{(-occ_id,query_id)} }
    vector<map<ull, priority_queue<array<int, 2>>>> cq(n + 1);
    for (int i = 0; i < q; i++) {
        string t;
        int k;
        cin >> t >> k;
        if (t.size() > n) continue;
        ull qh = poly_hash(t);
        cq[int(t.size())][qh].push({-k, i});
    }
    for (int c = 1; c <= n; c++) {
        if (!cq[c].size()) continue;
        map<ull, int> o;
        for (int b = 0; b + c <= n; b++) {
            ull h = hs.hash_substr(b, c);
            auto it = cq[c].find(h);
            if (it == cq[c].end()) continue;
            o[h]++;
            while (it->second.size() && o[h] == -it->second.top()[0]) {
                ans[it->second.top()[1]] = b + 1;
                it->second.pop();
            }
            if (it->second.empty()) {
                cq[c].erase(h);
                if (!cq[c].size()) break;
            }
        }
    }
    for (auto x : ans) cout << x << "\n";
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
