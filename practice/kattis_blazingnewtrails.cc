// Solution to Blazing New Trails, a problem from the NAIPC 2017
// (https://open.kattis.com/problems/blazingnewtrails)
//
// The problem could be simplified as "given an undirected graph with each edge
// being either black or white, find the minimum-weighted spanning tree
// that contains exactly W white edges." There are probably some better ways
// of doing this, but I went for this approach which turned out to be
// ridiculously cancerous to code.
//
// First, find the regular MST ignoring the W-white-edges constraint. This could
// be done the usual way by a Kruskal's algorithm with a Union-Find. Now let's
// say this MST has x more white edges than the required W. This would mean we
// need to replace x white edges in the MST with black ones. How do we find the
// optimal selection of black edges then? For each black edge, we can try adding
// it to the MST, which forms a cycle. We can then find the maximum weighted
// white edge in that cycle and pretend to remove it. This action would increase
// the total weight by (cost of the white edge - cost of the black edge), so we
// can basically sort this weight-increase for all the remaining un-added black
// edges and pick the first x to do the replacement. The problem then is how do
// we keep track of all the updates to the tree? Well you bet I found a
// convenient library for that called the AAA Tree, which supports O(log n) tree
// modification and path queries. (Credit goes to mzhang2021 on GitHub:
// https://github.com/mzhang2021/cp-library/blob/master/implementations/graphs/TopTree.h)
//
// Ridiculous.

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
 * Author: Lukas Polacek
 * Date: 2009-10-26
 * License: CC0
 * Source: folklore
 * Description: Disjoint-set data structure.
 * Time: $O(\alpha(N))$
 */
struct UF {
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (e[a] > e[b]) swap(a, b);
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

/**
 * Description: The ultimate link cut tree supporting all path/subtree lazy
 * updates and aggregates. Also known as AAA tree. Nodes are 1-indexed. Note
 * that lazy style is different from my usual style, lazy on node means value is
 * already updated instead of pending update. Only modifications required
 * are: 1. Data struct, 2. Set MAX to 2n, 3. Populate freeList with n nodes at
 * the start. Source: https://www.cnblogs.com/clrs97/p/4403244.html
 * Verification: https://dmoj.ca/problem/ds5
 * Time: O(log n)
 */

const int MAX = 1.4E6 + 5;

struct Data {
    ll sum, mn, mx, sz_;

    Data() : sum(0), mn(INT_MAX), mx(0), sz_(0) {}

    Data(ll val) : sum(val), mn(val), mx(val), sz_(1) {}

    Data(ll _sum, ll _mn, ll _mx, ll _sz)
        : sum(_sum), mn(_mn), mx(_mx), sz_(_sz) {}
};

struct Lazy {
    ll a, b;

    Lazy(ll _a = 1, ll _b = 0) : a(_a), b(_b) {}

    bool lazy() { return a != 1 || b != 0; }
};

Data operator+(const Data& a, const Data& b) {
    return Data(a.sum + b.sum, min(a.mn, b.mn), max(a.mx, b.mx), a.sz_ + b.sz_);
}

Data& operator+=(Data& a, const Data& b) { return a = a + b; }

Lazy& operator+=(Lazy& a, const Lazy& b) {
    return a = Lazy(a.a * b.a, a.b * b.a + b.b);
}

ll& operator+=(ll& a, const Lazy& b) { return a = a * b.a + b.b; }

Data& operator+=(Data& a, const Lazy& b) {
    return a.sz_ ? a = Data(a.sum * b.a + a.sz_ * b.b, a.mn * b.a + b.b,
                            a.mx * b.a + b.b, a.sz_)
                 : a;
}

struct Node {
    int p, ch[4];
    ll val;
    Data path, sub, all_;
    Lazy plazy, slazy;
    bool flip, fake;

    Node()
        : p(0),
          ch(),
          path(),
          sub(),
          all_(),
          plazy(),
          slazy(),
          flip(false),
          fake(true) {}

    Node(ll _val) : Node() {
        val = _val;
        path = all_ = Data(val);
        fake = false;
    }
} tr[MAX];
vector<int> freeList;

void pushFlip(int u) {
    if (!u) return;
    swap(tr[u].ch[0], tr[u].ch[1]);
    tr[u].flip ^= true;
}

void pushPath(int u, const Lazy& lazy) {
    if (!u || tr[u].fake) return;
    tr[u].val += lazy;
    tr[u].path += lazy;
    tr[u].all_ = tr[u].path + tr[u].sub;
    tr[u].plazy += lazy;
}

void pushSub(int u, bool o, const Lazy& lazy) {
    if (!u) return;
    tr[u].sub += lazy;
    tr[u].slazy += lazy;
    if (!tr[u].fake && o)
        pushPath(u, lazy);
    else
        tr[u].all_ = tr[u].path + tr[u].sub;
}

void push(int u) {
    if (!u) return;
    if (tr[u].flip) {
        pushFlip(tr[u].ch[0]);
        pushFlip(tr[u].ch[1]);
        tr[u].flip = false;
    }
    if (tr[u].plazy.lazy()) {
        pushPath(tr[u].ch[0], tr[u].plazy);
        pushPath(tr[u].ch[1], tr[u].plazy);
        tr[u].plazy = Lazy();
    }
    if (tr[u].slazy.lazy()) {
        pushSub(tr[u].ch[0], false, tr[u].slazy);
        pushSub(tr[u].ch[1], false, tr[u].slazy);
        pushSub(tr[u].ch[2], true, tr[u].slazy);
        pushSub(tr[u].ch[3], true, tr[u].slazy);
        tr[u].slazy = Lazy();
    }
}

void pull(int u) {
    if (!tr[u].fake)
        tr[u].path = tr[tr[u].ch[0]].path + tr[tr[u].ch[1]].path + tr[u].val;
    tr[u].sub = tr[tr[u].ch[0]].sub + tr[tr[u].ch[1]].sub +
                tr[tr[u].ch[2]].all_ + tr[tr[u].ch[3]].all_;
    tr[u].all_ = tr[u].path + tr[u].sub;
}

void attach(int u, int d, int v) {
    tr[u].ch[d] = v;
    tr[v].p = u;
    pull(u);
}

int dir(int u, int o) {
    int v = tr[u].p;
    return tr[v].ch[o] == u ? o : tr[v].ch[o + 1] == u ? o + 1 : -1;
}

void rotate(int u, int o) {
    int v = tr[u].p, w = tr[v].p, du = dir(u, o), dv = dir(v, o);
    if (dv == -1 && o == 0) dv = dir(v, 2);
    attach(v, du, tr[u].ch[du ^ 1]);
    attach(u, du ^ 1, v);
    if (~dv)
        attach(w, dv, u);
    else
        tr[u].p = w;
}

void splay(int u, int o) {
    push(u);
    while (~dir(u, o) && (o == 0 || tr[tr[u].p].fake)) {
        int v = tr[u].p, w = tr[v].p;
        push(w);
        push(v);
        push(u);
        int du = dir(u, o), dv = dir(v, o);
        if (~dv && (o == 0 || tr[w].fake)) rotate(du == dv ? v : u, o);
        rotate(u, o);
    }
}

void add(int u, int v) {
    if (!v) return;
    for (int i = 2; i < 4; i++)
        if (!tr[u].ch[i]) {
            attach(u, i, v);
            return;
        }
    int w = freeList.back();
    freeList.pop_back();
    attach(w, 2, tr[u].ch[2]);
    attach(w, 3, v);
    attach(u, 2, w);
}

void recPush(int u) {
    if (tr[u].fake) recPush(tr[u].p);
    push(u);
}

void rem(int u) {
    int v = tr[u].p;
    recPush(v);
    if (tr[v].fake) {
        int w = tr[v].p;
        attach(w, dir(v, 2), tr[v].ch[dir(u, 2) ^ 1]);
        if (tr[w].fake) splay(w, 2);
        freeList.push_back(v);
    } else {
        attach(v, dir(u, 2), 0);
    }
    tr[u].p = 0;
}

int par(int u) {
    int v = tr[u].p;
    if (!tr[v].fake) return v;
    splay(v, 2);
    return tr[v].p;
}

int access(int u) {
    int v = u;
    splay(u, 0);
    add(u, tr[u].ch[1]);
    attach(u, 1, 0);
    while (tr[u].p) {
        v = par(u);
        splay(v, 0);
        rem(u);
        add(v, tr[v].ch[1]);
        attach(v, 1, u);
        splay(u, 0);
    }
    return v;
}

void reroot(int u) {
    access(u);
    pushFlip(u);
}

void link(int u, int v) {
    reroot(u);
    access(v);
    add(v, u);
}

void cut(int u, int v) {
    reroot(u);
    access(v);
    tr[v].ch[0] = tr[u].p = 0;
    pull(v);
}

#pragma GCC diagnostic pop
#pragma endregion programmation }

int n, m, k, w, ms;
bool spe[200000];
vector<tuple<ll, int, int, bool>> edges;
UF uf(0);
ll ans;
bool ae[500000];  // added_edges
vi ue;            // unused_edges
using T = tuple<ll, int, ll>;
priority_queue<T, vector<T>, greater<T>> pq;  // {dif_cost, cand_ei, mxx_code}

void reset() {
    freeList.clear();
    for (int i = n + m + 1; i < MAX; i++) freeList.push_back(i);
    memset(spe, false, sizeof(spe));
    edges = {{}};
    uf.e.assign(n + 1, -1);
    ans = 0, ms = 0;
    memset(ae, false, sizeof(ae));
    ue.clear();
    pq = decltype(pq)();
}

const ll _cl = 32;
ll enc(ll c, int ei) { return c << _cl | ei; }
pair<ll, int> dec(ll x) { return {x >> _cl, x & ((1LL << _cl) - 1)}; }

void read() {
    cin >> n;
    if (n < 0) cin >> n;
    if (0 || !cin) exit(0);
    cin >> m >> k >> w;
    reset();
    for (int i = 0; i < k; i++) {
        int u;
        cin >> u;
        spe[u] = true;
    }
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        if (u > v) swap(u, v);
        edges.emplace_back(c, u, v, spe[u] ^ spe[v]);
    }
    sort(all(edges));
}

ll path_max(int u, int v) {
    reroot(u), access(v);
    // trace("    pmx", u, v, tr[v].path.sum);
    return tr[v].path.mx;
}

#define respond(a, b) return (void)(cout << a << "\n", _t && trace(b))

void solve() {
    bool _t = 01;

    read();
    if (m < n - 1) respond(-1, "too few edges");

    for (int i = 1; i <= n; i++) tr[i] = Node(0);
    _t&& trace("mst start", n, m, k, w, edges);
    for (int i = 1; i <= m; i++) {
        auto [c, u, v, b] = edges[i];
        if (ms == n - 1 || !uf.join(u, v)) {
            ue.push_back(i);
            continue;
        }
        ae[i] = true, ans += c, w -= b, ms++;
        _t&& trace("  mst", i, c, u, v, b);
    }
    _t&& trace("mst done prep start", ans, w, ue);
    if (ms < n - 1) respond(-1, "not connected");
    if (!w) respond(ans, "luckily early");

    for (int i = 1; i <= m; i++) {
        auto [c, u, v, b] = edges[i];
        ll x = (w > 0) ^ b ? enc(c, i) : 0;
        _t&& trace("  create", i, c, u, v, b, !!x);
        tr[n + i] = Node(x);
        if (ae[i]) {
            link(u, n + i), link(n + i, v);
            _t&& trace("  link", u, v);
        }
    }

    for (auto i : ue) {
        auto [c, u, v, b] = edges[i];
        if ((w > 0) ^ b) continue;
        ll mxx = path_max(u, v);
        if (!mxx) continue;
        auto [tc, ti] = dec(mxx);
        pq.push({c - tc, i, mxx});
        _t&& trace("  cand", i, c, u, v, b, tc, ti, c - tc);
    }

    while (len(pq)) {
        auto [dc, ci, mxx] = pq.top();
        pq.pop();
        auto [c, u, v, b] = edges[ci];
        trace("  proc", dc, ci, c, u, v, b);
        if (ll nmx = path_max(u, v); nmx != mxx) {
            if (!nmx) {
                _t&& trace("    skip", u, v);
                continue;
            }
            auto [tc, ti] = dec(nmx);
            pq.push({c - tc, ci, nmx});
            _t&& trace("    upd", tc, ti, c - tc);
            continue;
        }
        ans += dc, b ? w-- : w++;
        if (!w) respond(ans, "yay");
        int ti = dec(mxx).second;
        auto [tc, tu, tv, tb] = edges[ti];
        cut(tu, n + ti), cut(n + ti, tv);
        _t&& trace("    cut", ti, tc, tu, tv, tb);
        link(u, n + ci), link(n + ci, v);
        _t&& trace("    link", ans, w);
    }
    respond(-1, "too few or too many special edges");
}

void solve_suite() {
    debug freopen("./sandbox/i4.txt", "r", stdin);
    debug cout.open("./sandbox/o.txt");
    // cin >> num_cases;
    debug num_cases = 1E9;
    for (case_id = 1; case_id <= num_cases; case_id++) {
        // debug cerr.clear(case_id == 16 ? _S_goodbit : _S_failbit);
        debug _cout.clear(cerr ? _S_goodbit : _S_failbit);
        debug cout << "Case #" << case_id << ": ";
        solve();
        // cout << "\n";
        // eprintf("(%.2LF s)\n", ld(clock()) / CLOCKS_PER_SEC / case_id);
    }
}
