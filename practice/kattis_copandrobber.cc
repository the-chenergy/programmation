/**
    Solution to "Cop and Robber", a problem from the Baltic Olympiad in
    Informatics 2014.

    This is a classic game-theory problem. The general principles go:
    (1) If a state leads to at least one losing states, then it is winning
    (2) Otherwise, if it only leads to winning states (more specifically, no
        losing _or unknown_ states), then it is losing.

    One state in our case involves the police's location (p), the robber's
    location (r), and whose go it is (g : {police -> 0, robber -> 1}). A state
    (p, r, 0) leads to all states of the form (i, r, 1), where i is a neighbor
    node of p in the map. Similar story for the robber's moves. The police can
    pass a turn though, so (p, r, 0) also leads to (p, r, 1).

    Start by marking all states to be unknown, apart from the known ones where
    p == r. Add the known states to our search. Every iteration of the search
    involves (1) taking out a known state and (2) go through its _reversed_
    neighbors and update their markings according to the above principles. A
    reversed neighbor is a state that can lead to the current state, but in our
    problem it turns out to be the same as a regular neighbor since our map is
    undirected, apart from the police's passing move.

    (Read more about the above from
    https://cp-algorithms.com/game_theory/games_on_graphs.html)

    For this problem though it's not enough to know if a state is winning; we
    also need to know its doomsday clock. This is because we are required to
    actually play the game, and if we didn't know the clocks then we wouldn't
    know where to move the police to make progress. I did this by initializing
    the clock for all known states to be 0, and propagating the clock to other
    states as the search went on. A winning state wants the clock to be as small
    as possible, while a losing state wants the opposite. So I made the search a
    BFS and "prioritized" the winning states, i.e. making them come earlier in
    the search so they get smaller clock recordings.

    Running time wise, from the perspective of our state graph, it should be
    O(V + E) since every state (node) is in the BFS queue at most once, and we
    update the neighboring state, visiting each edge at most once. This should
    translate to O(N**3) where N is the number of locations in the map. V is
    O(N**2) given what each state contains. Meanwhile each location has up to N
    neighbors, summing up to O(N**3) edges in our state graph.
*/

#include <bits/stdc++.h>
using namespace std;

const int N = 501;

vector<int> nei[N];
int vis[N][N][2], res[N][N][2], deg[N][N][2], tim[N][N][2];
deque<array<int, 3>> sea;

int main() {
    // Read input
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int a;
            cin >> a;
            if (a) nei[i].push_back(j);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            deg[i][j][0] = int(nei[i].size()) + 1;
            deg[i][j][1] = int(nei[j].size());
        }
    }

    // Initialize known states
    auto win = [&](int p, int r, int g, int t) -> void {
        if (vis[p][r][g]) return;
        res[p][r][g] = 1;
        tim[p][r][g] = t;
        vis[p][r][g] = 1;
        sea.push_front({p, r, g});
    };
    auto lose = [&](int p, int r, int g, int t, int f = 0) -> void {
        if (vis[p][r][g]) return;
        res[p][r][g] = -1;
        tim[p][r][g] = max(tim[p][r][g], t);
        if (f || !--deg[p][r][g]) {
            vis[p][r][g] = 1;
            sea.push_back({p, r, g});
        }
    };

    for (int i = 0; i < n; i++) {
        win(i, i, 0, 0);
        lose(i, i, 1, 0, 1);
    }

    // Perform search
    while (sea.size()) {
        auto [p, r, g] = sea.front();
        sea.pop_front();
        int t = tim[p][r][g];
        for (int i : nei[g ? p : r]) {
            int pp = g ? i : p, pr = g ? r : i;
            if (res[p][r][g] < 0) {
                win(pp, pr, !g, t + 1);
            } else {
                lose(pp, pr, !g, t + 1);
            }
        }
        if (g) {
            if (res[p][r][g] < 0) {
                win(p, r, !g, t + 1);
            } else {
                lose(p, r, !g, t + 1);
            }
        }
    }

#if DEBUG
    for (int p = 0; p < n; p++) {
        for (int r = 0; r < n; r++) {
            for (int g : {0, 1}) {
                int x = res[p][r][g];
                printf("(p=%i, r=%i, %s go) %s in %i\n", p, r,
                       g ? "robber" : "police",
                       x > 0   ? "wins"
                       : x < 0 ? "loses"
                               : "draws",
                       tim[p][r][g]);
            }
        }
    }
#endif

    // Play game
    int p, r;
    {
        int ap = -1, at = INT_MAX / 2;
        for (int i = 0; i < n; i++) {
            int w = 1, t = 0;
            for (int j = 0; w && j < n; j++) {
                w = res[i][j][0] > 0;
                t = max(t, tim[i][j][0]);
            }
            if (w && t < at) {
                at = t;
                ap = i;
            }
        }
        if (!~ap) {
            cout << "-1\n";
            exit(0);
        }
        p = ap;
    }
    cout << p << "\n";
    cin >> r;
    while (~r) {
        int ap = -1, at = INT_MAX / 2;
        if (res[p][r][1] < 0) {
            at = tim[p][r][1];
            ap = p;
        }
        for (int i : nei[p]) {
            if (res[i][r][1] < 0 && tim[i][r][1] < at) {
                at = tim[i][r][1];
                ap = i;
            }
        }
        p = ap;
        cout << p << "\n";
        cin >> r;
    }
}
