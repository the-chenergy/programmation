// Solution to Apple Market, a problem from the NAIPC 2017
// (https://open.kattis.com/problems/applemarket)
// #graph #flow #segment_tree
//
// This is a rather obvious flow problem, where we can view each store as having
// a capacity equal to how many apples it has and each customer having a
// capacity how much money they own. The only catch is this approach creates
// O(n**2 * k) edges, which is too much (potentially more than 10**8) to pass
// the memory limit.
//
// I first tried grouping the stores going to the same customers into just one
// vertex. I used hashing to check if two stores go to the same set of
// customers, and I created one vertex instead of many with the combined number
// of apples from those stores. It turned out this method still used too much
// memory as there were still O(n**2 k) edges to be created.
//
// I then tried to come up with different ways to group the stores. Eventually I
// was inspired by the idea of a segment tree (this solution), where I created
// vertices to represent individual stores, stores inside a 1*2 rectangle, a 1*4
// rectangle, and so on for each 2**a by 2**b rectangle. Now, each customer only
// needs to connect to O(log(n)**2) store vertices since we can break down their
// potentially big rectangle into smaller pieces of the right sizes. This allows
// us to advantage of the spatial feature that a customer's favorite stores are
// all adjacent to each other, cutting the number of edges down to some
// O((n**2 + k) log**2 n).
//
// I also learned to code a 2D segment tree for the first time while solving
// this problem.

// #define SYNC_IO 01  // Synchronize standard IO (cin, scanf, cout, printf)
// #define TRACE_COUT 01  // Use stdout instead of stderr for trace and eprintf
// #define NO_MAIN 01  // Do not declare the main function
// #define DEBUG 0  // If 0 or unset, disable trace, eprintf, and debug blocks

int ec;

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
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max |\text{cap}|$.
 * $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for bipartite matching.
 * Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING, stress-tested
 */
struct Dinic {
	struct Edge {
		int to, rev;
		ll c, oc;
		ll flow() { return max(oc - c, 0LL); } // if you need flows
	};
	vi lvl, ptr, q;
	vector<vector<Edge>> adj;
	Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
	void addEdge(int a, int b, ll c, ll rcap = 0) {if(!c)return;
    ec++;
    // trace("\t\tedge",a,b,c);
		adj[a].push_back({b, sz(adj[b]), c, c});
		adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
	}
	ll dfs(int v, int t, ll f) {
		if (v == t || !f) return f;
		for (int& i = ptr[v]; i < sz(adj[v]); i++) {
			Edge& e = adj[v][i];
			if (lvl[e.to] == lvl[v] + 1)
				if (ll p = dfs(e.to, t, min(f, e.c))) {
					e.c -= p, adj[e.to][e.rev].c += p;
					return p;
				}
		}
		return 0;
	}
	ll calc(int s, int t) {
		ll flow = 0; q[0] = s;
		rep(L,0,31) do { // 'int L=30' maybe faster for random data
			lvl = ptr = vi(sz(q));
			int qi = 0, qe = lvl[s] = 1;
			while (qi < qe && !lvl[t]) {
				int v = q[qi++];
				for (Edge e : adj[v])
					if (!lvl[e.to] && e.c >> (30 - L))
						q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
			}
			while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
		} while (lvl[t]);
		return flow;
	}
	bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

#pragma GCC diagnostic pop
#pragma endregion programmation }

const int mxh=50;
int h,w,k,h2,w2,s2;
ll s[mxh*2][mxh*2];
using Flow=Dinic;
Flow*flow;

int si(int y,int x){return y*w2+x;}
void add_stores(){
    for(int y=h2-1;y;y--){
        for(int x=w2-1;x;x--){
            int i=si(y,x);
            // trace("store",y,x,i);
            if(x<w){
                flow->addEdge(si(y,x*2),i,s[y][x*2]);
                flow->addEdge(si(y,x*2+1),i,s[y][x*2+1]);
                s[y][x]=s[y][x*2]+s[y][x*2+1];
            }
            else if(y<h){
                flow->addEdge(si(y*2,x),i,s[y*2][x]);
                flow->addEdge(si(y*2+1,x),i,s[y*2+1][x]);
                s[y][x]=s[y*2][x]+s[y*2+1][x];
            }
            else flow->addEdge(0,i,s[y][x]);
        }
    }
}
void add_customer(int i,int _t,int _b,int _l,int _r,ll a){
    i+=s2;
    // trace("cus",i,_t,_b,_l,_r,a);
    flow->addEdge(i,1,a);
    auto add_row=[&](int y){
        for(int l=_l+w,r=_r+w;l<r;l/=2,r/=2){
            if(l&1)flow->addEdge(si(y,l),i,min(s[y][l],a)),l++;
            if(r&1)r--,flow->addEdge(si(y,r),i,min(s[y][r],a));
        }
    };
    for(int t=_t+h,b=_b+h;t<b;t/=2,b/=2){
        if(t&1)add_row(t),t++;
        if(b&1)b--,add_row(b);
    }
}

void solve() {
    cin>>h>>w>>k;
    if (0 || !cin) exit(0);
    h2=h*2,w2=w*2,s2=h2*w2;
    for(int y=0;y<h;y++)for(int x=0;x<w;x++)cin>>s[h+y][w+x];
    flow=new Flow(s2+k);
    add_stores();
    // view(s,0,h2,0,w2);
    for(int i=0;i<k;i++){
        int t,b,l,r,a;cin>>t>>b>>l>>r>>a,t--,l--;
        add_customer(i,t,b,l,r,a);
    }
    cout<<flow->calc(0,1);
    trace("\n",ec);
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
        cout << "\n";
        eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
