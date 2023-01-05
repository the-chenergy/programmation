// Solution to Harvard, a problem from the ICPC 2013 World Finals
// (https://open.kattis.com/problems/harvard)
// #combinatorics #dfs #simulation #memoization
//
// The problem is asking us to, given a sequence of variable accesses, find the
// best variable-to-memory-address assignment as measured by minimizing the
// number of times the program needs to switch the active bank (which let's call
// a "bank miss"). There are B banks, one of which is the default bank. Since
// there are S spaces per bank, we can treat S variables as immune to bank
// misses. So all we need to do then is group the rest of (V-S) variables (V is
// the number of variables in the program) into at most (B-1) groups, with each
// group having S items or less, such that we minimize the number of inter-group
// accesses, which is exactly what a bank miss would look like after grouping.
//
// The above idea translates into the following pseudo-code:
//   - Read the input and count how many variables there are (V).
//   - Count the number of variables accesses. This will be a constant that
//     can't be improved.
//   - Generate all ways to select S of the V variables to be immune. For each
//     of them:
//       - Run the program once and record how many times variable j is accessed
//         right after variable i, where i,j < V and are non-immune. This can be
//         formatted as a matrix where M[i][j] gives you j-accesses after i.
//       - Generate all "reasonable" ways to partition the remaining (V-S)
//         variables into at most (B-1) groups of S or less variables each.
//       - For each of those partitions, count the number of inter-group
//         accesses, which using the matrix notation will be the sum of M[i][j]
//         where group(i) != group(j). Record the minimum found as the answer A.
//   - The answer will be the recorded answer A + number of variables accesses.
//
// (By "reasonable" I meant in the partitions we generate, there aren't any
// partitions where one is strictly better than another. For example, if there
// were 3 non-immune banks with 4 spaces each, we wouldn't include {2, 2, 4} in
// the search since {4, 4} is also valid and strictly more efficient. That way
// we can cut down our search space, but there are definitely more ways to be
// more efficient that I didn't come up with.)

// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

#pragma region programmation {
#pragma region common {  // clang-format off
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#ifndef DEBUG
#    define DEBUG 0
#endif
#if DEBUG
#    define _GLIBCXX_DEBUG 1
#    define _GLIBCXX_DEBUG_PEDANTIC 1
#    define _FORTIFY_SOURCE 2
#    pragma GCC optimize("trapv")
#    if TRACE_COUT
#        define eprintf printf
#    else
#        define eprintf(...) fprintf(stderr, __VA_ARGS__)  // printf into cerr
#    endif
#    define trace(...) (_trace(#__VA_ARGS__, __VA_ARGS__), 0)  // trace(x, ...) -> prints "x: {x}, ..." to cerr
#    define view(...) (_view(__VA_ARGS__), trace(""), 0)  // view(X, b1, e1, ...) prints X[b1:e1, ...] to cerr
#    define debug
#else
#    define eprintf(...) (void)0
#    define trace(...) ((void)0, 0)
#    define view(...) ((void)0, 0)
#    define debug while (0)
#endif
#include <bits/stdc++.h>
#define rep(i, b, e) for (int i = b; i < (e); i++)
#define trav(x, a) for (auto& x : a)
#define all(x) begin(x), end(x)
#define sz len
#define _print_vector_impl s << "{"; string d; for (auto&& y : x) s << d << y, d = ", "; return s << "}";
using namespace std; using ll = long long; using ull = unsigned long long; using ld = long double; using vi = vector<int>; using pii = pair<int, int>; template <typename T> int len(const T& x) { return int(x.size()); } template <typename T, size_t l> int len(const T (&)[l]) { return l; } template <typename T, typename S> bool amax(T& t, S s) { return t < s && (t = s, 1); } template <typename T, typename S> bool amin(T& t, S s) { return s < t && (t = s, 1); } int num_cases = 1, case_id; namespace std { template <typename T, size_t l> ostream& operator<<(ostream& s, const array<T, l>& x); template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x); template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x); template <typename C, typename T = enable_if_t<!is_same<C, string>::value, typename C::value_type>> ostream& operator<<(ostream& s, const C& x) { _print_vector_impl } template <typename T, size_t l, enable_if_t<!is_same<T, char>::value, int> = 0> ostream& operator<<(ostream& s, const T (&x)[l]) { _print_vector_impl } template <typename T, size_t l> ostream& operator<<(ostream& s, const std::array<T, l>& x) { _print_vector_impl } template <typename F, typename S> ostream& operator<<(ostream& s, const pair<F, S>& x) { return s << "{" << x.first << ", " << x.second << "}"; } template <typename... T> ostream& operator<<(ostream& s, const tuple<T...>& x) { s << "{"; string d; apply([&](auto&&... y) { (..., (s << d << y, d = ", ")); }, x); return s << "}"; } } struct _teed_cout { bool _b = 0; ofstream _f; void open(const char* s) { _f.open(s), _b = 1; } template <typename T> _teed_cout& operator<<(const T& x) { return cout << x, _b && (_f << x), *this; } } _teed_cout; ostream& _cout = cout;
#if TRACE_COUT
#    define _trace_out cout
#else
#    define _trace_out cerr
#    define cout _teed_cout  // Outputs to both console and file. Access original cout via _cout.
#endif
template <typename T> void _trace(const char* l, const T& x) { if (l[0] != '"') _trace_out << l + (l[0] == ' ') << ": "; _trace_out << x << "\n"; } template <typename T, typename... A> void _trace(const char* l, const T& x, const A&... a) { if (l[0] == ' ') l++; size_t s = strchr(l, ',') - l; if (l[0] != '"') _trace_out.write(l, s) << ": "; _trace_out << x << ", ", _trace(l + s + 1, a...); } template <typename T> void _view(const T& x) { _trace_out << x; } template <typename T, typename... R> void _view(const T& x, int b, int e, R... r) { b < 0 && (b += len(x)), e < 0 && (e += len(x)); b = min(max(b, 0), len(x)), e = min(max(e, b), len(x)); auto it = begin(x); advance(it, b); _trace_out << "{"; for (int i = b; i < e; it++, i++) { if (i != b) _trace_out << ", "; _view(*it, r...); } _trace_out << "}"; }
#if !SYNC_IO
void _init() __attribute__((constructor)); void _init() { ios::sync_with_stdio(0), cin.tie(0); }
#endif
#if !NO_MAIN
void solve_suite(); int main() { solve_suite(); }
#endif
#pragma endregion common }  // clang-format on

// Additional library code

#pragma GCC diagnostic pop
#pragma endregion programmation }

void next_subset(int& x) {
    int c = x & -x, r = x + c;
    x = (((r ^ x) >> 2) / c) | r;
}

const int eop = 99, mxv = 13;
int b, s, n, v, def, pc, la, _ac, _rc;
vector<int> prog;
ll n_acc;

void read() {
    cin >> b >> s;
    if (0 || !cin) exit(0);
    string ln;
    getline(cin, ln), getline(cin, ln);
    stringstream ss(ln);
    prog.clear();
    v = 0, n_acc = 0;
    deque<ll> lcs;
    ll acc = 1;
    for (char t; ss >> t;) {
        if (t == 'E') {
            prog.push_back(eop);
            acc /= lcs.back();
            lcs.pop_back();
            continue;
        }
        int x;
        ss >> x;
        if (t == 'R')
            prog.push_back(-x), acc *= x, lcs.push_back(x);
        else
            prog.push_back(x), v |= 1 << x, n_acc += acc;
    }
    prog.push_back(eop);
    n = len(prog);

    // Compress variable names
    vector<int> vs;
    for (int i = 0; i < 32; i++)
        if (v & 1 << i) vs.push_back(i);
    for (auto& x : prog)
        if (x != eop && x >= 0) x = int(lower_bound(all(vs), x) - begin(vs));
    v = len(vs);
}

using transition = array<array<ll, mxv>, mxv + 1>;
void add_transition(transition& t, transition& u, ll mul = 1) {
    for (int i = 0; i <= v; i++)
        for (int j = 0; j < v; j++) t[i][j] += u[i][j] * mul;
}

map<pair<int, int>, tuple<int, int, transition>> run_mem;
transition run(int n_rep, bool is_rep = false) {
    // trace("run", pc, la, n_rep, is_rep);
    if (!is_rep) {
        if (auto it = run_mem.find({pc, la}); it != end(run_mem)) {
            auto [npc, nla, t] = it->second;
            // trace("  mem", pc, la, npc, nla, t);
            pc = npc;
            if (nla < v) la = nla;
            return t;
        }
    }
    int opc = pc, ola = la;
    transition t{};
    while (prog[pc] != eop) {
        if (prog[pc] < 0) {
            pc++;
            transition u = run(-prog[pc - 1]);
            add_transition(t, u);
        } else {
            if (int a = prog[pc]; !(def & 1 << a) && la != a) {
                // trace("   acc", la, a);
                t[la][a]++, la = a;
            }
        }
        pc++;
    }
    if (n_rep > 1) {
        // trace("  rep", pc, la, t, opc);
        pc = opc;
        transition u = run(1, true);
        add_transition(t, u, n_rep - 1);
    }
    if (!is_rep) run_mem[{opc, ola}] = {pc, la, t};
    // trace("  done", pc, la, t, opc, ola);
    return t;
}

using assignment = vi;
// using assignment = array<int, mxv>;
ll measure_assignment(transition& trans, assignment& asg) {
    _ac++;
    // trace("asg", def, asg);
    ll tot = 0;
    for (int i = 0; i <= v; i++) {
        if (def & 1 << i) continue;
        for (int j = 0; j < v; j++) {
            if (i == j || def & 1 << j || (i < v && asg[i] == asg[j])) continue;
            tot += trans[i][j];
            // if (trans[i][j]) trace("  ", i, j, trans[i][j]);
        }
    }
    return tot;
}

using part = map<int, int>;
vector<part> parts;
vector<part> gen_parts() {
    if (s >= v) return {};
    int r = v - s;
    if (s == 1) return {{{1, r}}};
    // Generate all non-decreasing lists of L (1 <= L <= b) numbers, where each
    // number is between 1 and s and the sum of a list is r.
    deque<pair<int, vector<int>>> dfs{{}};
    set<vector<int>> res;
    while (len(dfs)) {
        auto [t, p] = dfs.back();
        dfs.pop_back();
        for (int i = 0; i < len(p); i++) {
            if (p[i] == s) continue;
            if (i && p[i] == p[i - 1]) continue;
            auto q = p;
            q[i]++;
            if (t + 1 == r)
                res.insert(q);
            else
                dfs.push_back({t + 1, q});
        }
        int nl = p.empty() || p.back() == s ? min(r - t, 2) : 2;
        if (len(p) < b && (t + nl <= r)) {
            p.push_back(nl);
            if (t + nl == r)
                res.insert(p);
            else
                dfs.push_back({t + 2, p});
        }
    }
    vector<part> ret;
    for (auto p : res) {
        bool ok = true;
        part rp;
        for (int i = 0; i < len(p) - 1; i++) {
            auto q = p;
            q.erase(begin(q) + i);
            q[i] = p[i] + p[i + 1];
            // trace(p, q, res);
            if (res.count(q)) {
                ok = false;
                break;
            }
            rp[p[i]]++;
        }
        if (!ok) continue;
        rp[p.back()]++, ret.push_back(rp);
    }
    return ret;
}

using B = bitset<mxv>;
ll ans;
void measure_defaults(int _def) {
    _rc++;
    def = _def, la = v, pc = 0, run_mem.clear();
    auto t = run(1);
    if (parts.empty()) {  // All in bank 0
        ans = 0;
        return;
    }
    for (auto sp : parts) {
        deque<tuple<part, int, int, assignment>> dfs{
            {sp, 0, ((1 << v) - 1) & ~def, assignment(v)}};
        while (len(dfs)) {
            auto [p, k, u, a] = dfs.back();
            // trace("gen asg", p, k, B(u), a);
            dfs.pop_back();
            int ulb = __builtin_ctz(u);
            a[ulb] = k;
            u &= ~(1 << ulb);
            for (auto [l, c] : p) {
                auto q = p;
                q[l]--;
                if (!q[l]) q.erase(l);
                // trace("  lc", p, q, l, c, ulb, B(u));
                if (l == 1) {
                    if (!u)
                        amin(ans, measure_assignment(t, a));
                    else
                        dfs.push_back({q, k + 1, u, a});
                    continue;
                }
                for (int x = ((1 << (l - 1)) - 1) << ulb; x <= u;
                     next_subset(x)) {
                    if (x & ~u) continue;
                    for (int i = 0; i < v; i++)
                        if (x & 1 << i) a[i] = k;
                    int w = u ^ x;
                    // trace("    ss", B(u), B(x), B(w), a);
                    if (!w)
                        amin(ans, measure_assignment(t, a));
                    else
                        dfs.push_back({q, k + 1, w, a});
                }
            }
        }
    }
}

void measure() {
    parts = gen_parts();
    trace(len(parts), parts);
    ans = 4E18, _ac = _rc = 0;
    for (int d = (1 << min(s, v)) - 1; d < (1 << v); next_subset(d))
        measure_defaults(d);
}

void solve() {
    read(), b--;
    trace(b, s, n, v, n_acc), trace(prog);

    measure();
    trace(ans, _ac, _rc);
    cout << ans + n_acc;
}

void solve_suite() {
    debug if (0) {
        b = 4, v = 13;
        for (s = int(ceil(v / b)); s <= 13; s++) {
            auto p = gen_parts();
            trace(b, s, v, len(p), p);
        }
        exit(3);
    }
    debug freopen("./sandbox/i.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ": ";
        solve();
        cout << "\n";
        eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
