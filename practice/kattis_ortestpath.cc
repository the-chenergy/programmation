/* Solution to "Ortest Path", a problem from the LTH Challenge 2021
   (https://open.kattis.com/problems/ortestpath).

   Quite an involved problem.

   First, find all the bi-connected components (which I'll call bi-comps) in the
   graph. Reduce each bi-comp into a vertex, and link each bi-comp to adjacent
   bi-comps with the vertices that they share. This way we've created a bi-comp
   graph, and this graph is always acyclic (a tree). That is useful because now
   we can find the shortest path between a source bi-comp and the target bi-comp
   (any bi-comp that includes s or t), and the bi-comps on that path will be the
   only bi-comps touched by any path from s to t. This lets us filter out all
   useless one-edges that can't be used because no s-t path includes them.

   Inside a bi-comp, there is always a path between any two vertices that goes
   through any given edge. So, we can go through all the bi-comps visited in the
   s-t path in the bi-comp graph and see if any of them involves a one-edge.
   (For the purpose of this problem, we'll count all bridges also as bi-comps
   with just one edge). If there is at least one bi-comp with a one-edge, we
   know there has to be a way to use it in the path -- we just need to find a
   path between the exiting vertices (any vertices we used to connect that
   bi-comp with neighboring bi-comps visited in the s-t path) that uses the
   one-edge. For the other bi-comps we can just find any path between the
   exiting vertices and don't care about what edges we use.

   Now, to find the required path going through that one-edge, we can use the
   help from a network flow. Suppose the exiting vertices are u and v and the
   one-edge connects a and b. This means we'd like to find a path of either the
   form u ~> a -> b ~> v or u ~> b -> a ~> v, and here's the way we do this.
   Create a new imaginary source s' and target t'. Connect s' to u and v and t'
   to a and b. Create two new imaginary vertices for each vertex in the original
   graph, one sender and one receiver. Link only receivers to senders according
   to the original edges, and link each vertex's sender to receiver. All edges
   have capacity 1, which ensures that every vertex is used at most once. Now
   the flow of this graph should give us the path, if we go along only the edges
   with flow.

   The overall run time should be some O(V + E √E). Dinic's should run in
   O(E √E) for a unit-capacity graph according to the docs below, and everything
   else should be O(V + E).
 */

#include <bits/stdc++.h>
using namespace std;

#if !LOCAL
#    define cerr 0 && cerr
#endif

#pragma region  // Source: KACTL

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

/**
 * Author: Simon Lindholm
 * Date: 2017-04-17
 * License: CC0
 * Source: folklore
 * Description: Finds all biconnected components in an undirected graph, and
 *  runs a callback for the edges in each. In a biconnected component there
 *  are at least two distinct paths between any two nodes. Note that a node can
 *  be in several components. An edge which is not in a component is a bridge,
 *  i.e., not part of any cycle.
 * Usage:
 *  int eid = 0; ed.resize(N);
 *  for each edge (a,b) {
 *    ed[a].emplace_back(b, eid);
 *    ed[b].emplace_back(a, eid++); }
 *  bicomps([\&](const vi\& edgelist) {...});
 * Time: O(E + V)
 * Status: tested during MIPT ICPC Workshop 2017
 */
vi num, st;
vector<vector<pii>> ed;
int Time;
template <class F>
int dfs(int at, int par, F& f) {
    int me = num[at] = ++Time, e, y, top = me;
    for (auto pa : ed[at])
        if (pa.second != par) {
            tie(y, e) = pa;
            if (num[y]) {
                top = min(top, num[y]);
                if (num[y] < me) st.push_back(e);
            } else {
                int si = sz(st);
                int up = dfs(y, e, f);
                top = min(top, up);
                if (up == me) {
                    st.push_back(e);
                    f(vi(st.begin() + si, st.end()));
                    st.resize(si);
                } else if (up < me) st.push_back(e);
                else { /* e is a bridge */ f({e});
                }
            }
        }
    return top;
}

template <class F>
void bicomps(F f) {
    num.assign(sz(ed), 0);
    rep(i, 0, sz(ed)) if (!num[i]) dfs(i, -1, f);
}

/**
 * Author: chilli
 * Date: 2019-04-26
 * License: CC0
 * Source: https://cp-algorithms.com/graph/dinic.html
 * Description: Flow algorithm with complexity $O(VE\log U)$ where $U = \max
 * |\text{cap}|$. $O(\min(E^{1/2}, V^{2/3})E)$ if $U = 1$; $O(\sqrt{V}E)$ for
 * bipartite matching. Status: Tested on SPOJ FASTFLOW and SPOJ MATCHING,
 * stress-tested
 */
struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); }  // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
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
        ll flow = 0;
        q[0] = s;
        rep(L, 0, 31) do {  // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t]) {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
        }
        while (lvl[t])
            ;
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

#pragma endregion

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<tuple<int, int, int>> edges;
    vector<vector<int>> nei(n);
    ed.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        edges.push_back({u, v, x});
        ed[u].push_back({v, i});
        ed[v].push_back({u, i});
        nei[u].push_back(v);
        nei[v].push_back(u);
    }

    vector<unordered_set<int>> comps(n);
    vector<int> comp_val, one_edge;
    vector<vector<int>> comp_edges;
    vector<unordered_map<int, int>> nei_comp;
    int cur_comp = -1;
    unordered_set<int> src_comps, tar_comps;
    deque<int> search;
    vector<char> seen_comp;
    vector<int> prev_comp;
    bicomps([&](vector<int> es) {
        cur_comp++;
        comp_edges.push_back(es);
        comp_val.push_back(0);
        nei_comp.push_back({});
        seen_comp.push_back(0);
        prev_comp.push_back(-1);
        one_edge.push_back(-1);
        int has_src = 0, has_tar = 0;
        cerr << "Comp #" << cur_comp << ": ";
        for (auto e : es) {
            auto [u, v, x] = edges[e];
            cerr << "(" << u << " " << v << ") ";
            for (auto c : comps[u]) {
                if (c == cur_comp) continue;
                nei_comp.back()[c] = nei_comp[c][cur_comp] = u;
            }
            for (auto c : comps[v]) {
                if (c == cur_comp) continue;
                nei_comp.back()[c] = nei_comp[c][cur_comp] = v;
            }
            comps[u].insert(cur_comp);
            comps[v].insert(cur_comp);
            if (x) {
                comp_val.back() = 1;
                one_edge.back() = e;
            }
            has_src |= u == s || v == s;
            has_tar |= u == t || v == t;
        }
        cerr << "\n";
        if (has_src) {
            src_comps.insert(cur_comp);
            search.push_back(cur_comp);
            seen_comp.back() = 1;
        }
        if (has_tar) tar_comps.insert(cur_comp);
    });
    if (cerr) {
        cerr << "Source comps: ";
        for (auto x : src_comps) cerr << x << " ";
        cerr << "\nTarget comps: ";
        for (auto x : tar_comps) cerr << x << " ";
        cerr << "\nComp neighbors:\n";
        for (int i = 0; i < cur_comp; i++) {
            cerr << "\tComp #" << i << ": ";
            for (auto [j, x] : nei_comp[i])
                cerr << "(" << j << " " << x << ") ";
            cerr << "\n";
        }
    }

    cerr << "BFS...\n";
    int tar = -1;
    while (search.size()) {
        int c = search.front();
        cerr << "\tc=" << c << "\n";
        if (tar_comps.count(c)) {
            tar = c;
            break;
        }
        search.pop_front();
        for (auto [d, x] : nei_comp[c]) {
            if (seen_comp[d]) continue;
            cerr << "\t\td=" << d << " x=" << x << "\n";
            seen_comp[d] = 1;
            prev_comp[d] = c;
            search.push_back(d);
        }
    }
    cerr << "tar=" << tar << "\n";
    if (!~tar) {
        cout << "-1\n";
        exit(0);
    }

    int c = tar, u = t, found = 0;
    vector<int> ans = {t};
    for (int d = -2, v = -2; ~d; c = d, u = v) {
        d = prev_comp[c], v = ~d ? nei_comp[c][d] : s;
        cerr << "c=" << c << " d=" << d << " u=" << u << " v=" << v << "\n";
        auto& comp = comp_edges[c];
        if (comp.size() == 1) {
            found |= comp_val[c];
            auto [a, b, _] = edges[comp[0]];
            assert((a == u && b == v) || (a == v && b == u));
            ans.push_back(v);
            continue;
        }

        if (found || !comp_val[c]) {
            unordered_map<int, int> par;
            par[u] = -1;
            search = {u};
            while (search.size()) {
                int x = search.front();
                if (x == v) break;
                search.pop_front();
                for (auto y : nei[x]) {
                    if (par.count(y)) continue;
                    par[y] = x;
                    search.push_back(y);
                }
            }
            vector<int> add;
            int x = v;
            while (x != u) {
                add.push_back(x);
                x = par[x];
            }
            ans.insert(ans.end(), add.rbegin(), add.rend());
            continue;
        }

        found = 1;
        int a, b;
        tie(a, b, ignore) = edges[one_edge[c]];
        cerr << "\tFancy connect: a=" << a << " b=" << b << "\n";
        Dinic dinic(2 * n + 2);
        /* 2 * n = source, 2 * n + 1 = target; go from u and v to a and b */
        for (int i = 0; i < n; i++) dinic.addEdge(2 * i, 2 * i + 1, 1);
        dinic.addEdge(2 * n, 2 * u, 1);
        dinic.addEdge(2 * n, 2 * v, 1);
        dinic.addEdge(2 * a + 1, 2 * n + 1, 1);
        dinic.addEdge(2 * b + 1, 2 * n + 1, 1);
        for (auto e : comp) {
            auto [x, y, _] = edges[e];
            dinic.addEdge(2 * x + 1, 2 * y, 1);
            dinic.addEdge(2 * y + 1, 2 * x, 1);
        }
        ll flow = dinic.calc(2 * n, 2 * n + 1);
        assert(flow == 2);
        auto add_found_path = [&](int start, vector<int>& add_to) {
            cerr << "\tGoing from " << start << "\n";
            int x = 2 * start;
            while (x / 2 != a && x / 2 != b) {
                int y = -1;
                for (auto& e : dinic.adj[x]) {
                    if (e.flow() == 1) {
                        y = e.to;
                        break;
                    }
                }
                cerr << x << " (" << x / 2 << ") " << y << " (" << y / 2
                     << ")\n";
                assert(~y);
                if (y / 2 != x / 2) add_to.push_back(y / 2);
                x = y;
            }
        };
        add_found_path(u, ans);
        vector<int> add;
        add_found_path(v, add);
        ans.insert(ans.end(), add.rbegin(), add.rend());
        ans.push_back(v);
    }

    if (!found) {
        cout << "-1\n";
        exit(0);
    }

    for (auto it = ans.rbegin(); it != ans.rend(); it++) cout << *it << " ";
    cout << "\n";
}
