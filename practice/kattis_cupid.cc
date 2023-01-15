// Solution to "Curious Cupid", a problem from the Hong Kong Regional 2016
// (https://open.kattis.com/problems/cupid)
//
// Use Mo's Queries.

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
/**
 * Author: Simon Lindholm
 * Date: 2019-12-28
 * License: CC0
 * Source:
 * https://github.com/hoke-t/tamu-kactl/blob/master/content/data-structures/MoQueries.h
 * Description: Answer interval or tree path queries by finding an approximate
 * TSP through the queries, and moving from one query to the next by
 * adding/removing points at the ends. If values are on tree edges, change
 * \texttt{step} to add/remove the edge $(a, c)$ and remove the initial
 * \texttt{add} call (but keep \texttt{in}). Time: O(N \sqrt Q) Status:
 * stress-tested
 */
void add(int ind, int end);  // add a[ind] (end = 0 or 1)
void del(int ind, int end);  // remove a[ind]
int calc();                  // compute current answer

vi mo(vector<pii> Q) {
    int L = 0, R = 0, blk = sqrt(50000);  // ~N/sqrt(Q)
    vi s(sz(Q)), res = s;
#define K(x) pii(x.first / blk, x.second ^ -(x.first / blk & 1))
    iota(all(s), 0);
    sort(all(s), [&](int s, int t) { return K(Q[s]) < K(Q[t]); });
    for (int qi : s) {
        pii q = Q[qi];
        while (L > q.first) add(--L, 0);
        while (R < q.second) add(R++, 1);
        while (L < q.first) del(L++, 0);
        while (R > q.second) del(--R, 1);
        res[qi] = calc();
    }
    return res;
}

vi moTree(vector<array<int, 2>> Q, vector<vi>& ed, int root = 0) {
    int N = sz(ed), pos[2] = {}, blk = 350;  // ~N/sqrt(Q)
    vi s(sz(Q)), res = s, I(N), L(N), R(N), in(N), par(N);
    add(0, 0), in[0] = 1;
    auto dfs = [&](int x, int p, int dep, auto& f) -> void {
        par[x] = p;
        L[x] = N;
        if (dep) I[x] = N++;
        for (int y : ed[x])
            if (y != p) f(y, x, !dep, f);
        if (!dep) I[x] = N++;
        R[x] = N;
    };
    dfs(root, -1, 0, dfs);
#define K(x) pii(I[x[0]] / blk, I[x[1]] ^ -(I[x[0]] / blk & 1))
    iota(all(s), 0);
    sort(all(s), [&](int s, int t) { return K(Q[s]) < K(Q[t]); });
    for (int qi : s) rep(end, 0, 2) {
            int &a = pos[end], b = Q[qi][end], i = 0;
#define step(c)          \
    {                    \
        if (in[c]) {     \
            del(a, end); \
            in[a] = 0;   \
        } else {         \
            add(c, end); \
            in[c] = 1;   \
        }                \
        a = c;           \
    }
            while (!(L[b] <= L[a] && R[a] <= R[b])) I[i++] = b, b = par[b];
            while (a != b) step(par[a]);
            while (i--) step(I[i]);
            if (end) res[qi] = calc();
        }
    return res;
}

#pragma GCC diagnostic pop
#pragma endregion programmation }

const int mxn=50000, mxk=1E6;
int n,m,k,a[mxn],b[mxn],ca[mxk],cb[mxk],c;
vector<pii>q;

void add(int ind, int end) {
    ca[a[ind]]++;
    c+=ca[a[ind]]<=cb[a[ind]];
    cb[b[ind]]++;
    c+=cb[b[ind]]<=ca[b[ind]];
}
void del(int ind, int end) {
    c-=ca[a[ind]]<=cb[a[ind]];
    ca[a[ind]]--;
    c-=cb[b[ind]]<=ca[b[ind]];
    cb[b[ind]]--;
}
int calc() {return c;}

void solve() {
    cin>>n>>m>>k;
    if (0 || !cin) exit(0);
    for(int i=0;i<n;i++)cin>>a[i];
    for(int i=0;i<n;i++)cin>>b[i];
    for(int i=0;i<m;i++) {
        int x,y;cin>>x>>y,y++;
        q.push_back({x,y});
    }
    auto ans=mo(q);
    for(auto x:ans)cout<<x<<"\n";
}

void solve_suite() {
    // debug freopen("./sandbox/i.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    // num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        // cout << "Case #" << case_id << ": ";
        solve();
        // cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
