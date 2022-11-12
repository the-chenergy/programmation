// #define SYNC_IO 01
// #define TRACE_COUT 01
#define LOCAL 0

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

void _init() __attribute__((constructor));

void _init() {
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

#pragma endregion }

void solve(int /* case_id */) {
    vector<string> its;
    map<string, int> sti;
    map<string, vector<int>> pat;
    vector<vector<int>> adj;
    while (1) {
        string word;
        getline(cin, word);
        if (word.empty()) break;
        int word_i = (int)its.size();
        sti[word] = word_i;
        its.push_back(word);
        adj.emplace_back();
        for (int i = 0; i < (int)word.size(); i++) {
            string p = word.substr(0, i) + "." + word.substr(i + 1);
            if (pat.count(p)) {
                for (auto j : pat[p]) {
                    adj[j].push_back(word_i);
                    adj.back().push_back(j);
                }
            }
            pat[p].push_back(word_i);
        }
    }
    int n = (int)its.size();
    auto no = [&]() { cout << "No solution.\n\n"; };
    while (1) {
    next_query:;
        string src, tar;
        cin >> src >> tar;
        if (cin.fail()) break;
        if (!sti.count(src) || !sti.count(tar)) {
            no();
            continue;
        }
        int si = sti[src], ti = sti[tar];
        trace(src, si, tar, ti);
        vector<int> par(n, -1);
        par[si] = n;
        deque<int> bfs{si};
        while (bfs.size()) {
            int cur = bfs.front();
            bfs.pop_front();
            for (int nxt : adj[cur]) {
                if (par[nxt] >= 0) continue;
                par[nxt] = cur;
                if (nxt == ti) {
                    cur = ti;
                    deque<int> ans;
                    while (cur != n) {
                        trace(cur);
                        ans.push_front(cur);
                        cur = par[cur];
                    }
                    for (auto i : ans) cout << its[i] << "\n";
                    cout << "\n";
                    goto next_query;
                }
                bfs.push_back(nxt);
            }
        }
        no();
    }
}

int main() {
    int num_cases = 1;
    // cin >> num_cases;
    for (int case_id = 0; case_id < num_cases; case_id++) {
        // cout << "Case #" << case_id + 1 << ": ";
        solve(case_id);
    }
}
