// Solution to Array Queries, problem E from the Educational Codeforces Round 19
// https://codeforces.com/contest/797/problem/E
// #binary_search
//
// Using the idea of binary lifting, we can come up with this clever solution:
// for each k, calculate J_1[i] = A[i] + k which is the target index after one
// jump. With that we can calculate J_2[i] = J_1[J_1[i]], and J_4[i] =
// J_2[J_2[i]], and so on. Now we can use binary search to find out for any
// starting index p, how many steps will it take to get past the end: start with
// J_log(N)[p], then gradually shrinking the jump distance if the current jump
// shoots too far. This solution makes good use of the power of precomputing,
// which allows us to trade a one-time O(N log N) with O(log N) queries.
// However, there could be too many possible values of k that the overall run
// time becomes O(Q * N log N).
//
// Luckily, we can let a dumber brute-force style solution help us -- when k is
// large, it won't take many jumps at all for any starting index. This means
// computing the binary jumps is not an efficient trade-off for large k's. In
// fact, when k >= sqrt(N), the number of jumps to get past is at most sqrt(N),
// making the binary lifting method strictly worse. So the final solution is,
// for k >= sqrt(N), we do the brute-force solution, and for smaller k we do the
// binary lifting. Overall run time becomes
// O(sqrt(N) * N log(N) + (Q - sqrt(N)) * sqrt(N)) in the worst case.

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

int n,q,a[100009],ans[100009],rn,j[19][100009];
vector<array<int,3>>b;

void solve() {
    cin>>n;
    if (0 || !cin) exit(0);
    rn=int(sqrt(n)*5/6);
    for(int i=1;i<=n;i++)cin>>a[i];
    cin>>q;
    for(int i=0;i<q;i++){
        int p,k;
        cin>>p>>k;
        if(k>=rn){
            int s=0;
            while(p<=n){
                s++;
                p+=a[p]+k;
            }
            ans[i]=s;
            continue;
        }
        b.push_back({k,p,i});
    }
    
    // view(a,1,n+1);
    sort(all(b));
    while(len(b)){
        if(!(rand()&127))trace(len(b));
        int k=b.back()[0],te=0,tt=0;
        j[0][n+1]=n+1;
        for(int i=1;i<=n;i++)j[0][i]=min(i+a[i]+k,n+1);
        // trace(k);
        // view(j[0],1,n+1);
        for(int e=1,t=2;t<=n;e++,t<<=1){
            j[e][n+1]=n+1;
            for(int i=1;i<=n;i++){
                int p=j[e-1][i];
                j[e][i]=p>n?n+1:j[e-1][p];
            }
            te=e,tt=t;
            // trace(te,tt);
            // view(j[e],1,n+1);
        }
        while(len(b)&&b.back()[0]==k){
            auto[_,p,i]=b.back();
            b.pop_back();
            int s=0;
            for(int e=te,t=tt;~e;e--,t>>=1){
                while(j[e][p]<=n)s+=t,p=j[e][p];
            }
            ans[i]=s+1;
        }
    }
    
    for(int i=0;i<q;i++)cout<<ans[i]<<"\n";
}

void solve_suite() {
    debug freopen("./sandbox/ia.txt", "r", stdin);
    // debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    // num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id ==  ? _S_goodbit : _S_failbit);
        // cout << "Case #" << case_id << ": ";
        solve();
        // cout << "\n";
        eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
