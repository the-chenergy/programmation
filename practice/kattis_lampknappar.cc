/* Solution to "Light Switches", a problem from the Programmeringsolympiadens
   final 2019. (https://open.kattis.com/problems/lampknappar)

   I read the spoilers for this one
   (https://github.com/Kodsport/swedish-olympiad-2019/blob/master/final/spoilers.pdf,
   page 8). I would not have come up with the solution anytime soon otherwise.

   The problem can be simplified to "find a loop containing vertices 1 and N
   that uses the smallest number of unique vertices." Note the "unique"
   vertices, not the total vertices in the loop overall. Let's call this target
   loop a "min-cost loop", specifically where "cost" equals to the number of
   unique vertices. In other words, min-cost loop isn't necessarily the shortest
   loop in terms of loop length, but the loop with the minimum (L - R), where L
   is the loop length and R is the number of vertices repeated.

   The above description gives us a hint: we can build the loop by extending
   either its start or end point one step at a time, and reward whenever they
   collide. If we describe a loop with (u, v) starting at (1, 1), (u, v) would
   mean the min-cost path from u to v that goes through vertex 1, and when u = v
   then that forms a min-cost loop going through 1. So in the end we're looking
   to extend (1, 1) into (N, N), which would be our answer -- a loop starting
   and end at N going through 1.

   To extend (u, v), we can either move the path's starting point u back by one
   vertex, or the end point v forward by one vertex. If u and v do not collide,
   then it must be a new unseen vertex, so we add one to the cost. This is
   because if it's seen then there would've been a lower cost path from that
   vertex to either u or v found already. Here comes the impossible, magical,
   and mind-blowing part: we have another way to extend (u, v), and that is pay
   the cost of `dist(u, v) - 1` and flip the path into (v, u). That is, for any
   path u ~> v going through vertex 1 with cost c, if the distance from v to u
   is d, there must be a path v ~> u going through vertex 1 with cost at most
   (c + d - 1). The reasoning goes, if we can go from u to v visiting some set
   of vertices, we can definitely go from v to u visiting at most extra (d - 1)
   vertices, because in the worst case, every vertex in the shortest path v ~> u
   is unseen, and that's only (d - 1) vertices in addition to those seen in
   u ~> 1 ~> v. So the claim goes, if we are able to repeat some vertices in the
   min-cost loop, we will be able to find them sooner or later during the
   expansion search. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;
    const int N = 501;
    /* Neighbors and reverse neighbors for each vertex */
    static vector<int> nei[N], rev_nei[N];
    for (int u = 1; u <= n; u++) {
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            int v;
            cin >> v;
            nei[u].push_back(v);
            rev_nei[v].push_back(u);
        }
    }

    /* Run APSP. `dist[u][v]` records min distance (not cost) from u to v. This
       distance is an upper bound for how many unique vertices there are on the
       path u ~> v. */
    static int dist[N][N];
    memset(dist, -1, sizeof(dist));
    for (int s = 1; s <= n; s++) {
        static deque<int> bfs;
        bfs = {s};
        dist[s][s] = 0;
        while (bfs.size()) {
            auto u = bfs.front();
            bfs.pop_front();
            for (auto v : nei[u]) {
                if (~dist[s][v]) continue;
                dist[s][v] = dist[s][u] + 1;
                bfs.push_back(v);
            }
        }
    }

    if (!~dist[1][n] || !~dist[n][1]) {
        cout << "nej\n";
        exit(0);
    }

    /* Dijkstra (cost, u, v), starting at (1, 1) with target (n, n) */
    using E = tuple<int, int, int>;
    static priority_queue<E, vector<E>, greater<>> pq;
    pq.push({0, n, n});
    static int cost[N][N];
    memset(cost, 63, sizeof(cost));
    cost[n][n] = 0;
    while (1) {
        int c, u, v;
        tie(c, u, v) = pq.top();
        pq.pop();
        if (u == 1 && v == 1) {
            cout << c << "\n";
            exit(0);
        }
        if (c > cost[u][v]) continue;

        auto push = [&](int add_cost, int new_u, int new_v) {
            if (c + add_cost >= cost[new_u][new_v]) return;
            cost[new_u][new_v] = c + add_cost;
            pq.push({c + add_cost, new_u, new_v});
        };

        /* Extend the start or end point */
        for (auto new_u : rev_nei[u]) push(new_u != v, new_u, v);
        for (auto new_v : nei[v]) push(new_v != u, u, new_v);
        /* The magical flipping */
        if (u != v && ~dist[v][u]) push(dist[v][u] - 1, v, u);
    }
}
