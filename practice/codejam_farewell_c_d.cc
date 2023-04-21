/* Solution to "The Decades of Coding Competitions", problem D from the Google
   Code Jam Farewell Round C.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95433/0000000000cad9c6)

   If p and c aren't in the same component, impossible.

   If the component p and c are in have an odd number of colors, then it's
   possible because we can just drive through all of that component's edges.

   Otherwise, try removing one color and see if p and c are still connected
   (even - 1 = odd, duh). This represents visiting all edges except those with
   that one color, and after some working out on paper you'll find that it's
   always possible to still visit an odd number of colors, indeed.

   There are only up to 100 unique colors anyway, so just use 100 (plus 1 for
   the previous case) union-finds. (That's a lot of UFs in one problem, I know.)
*/

#include <bits/stdc++.h>
using namespace std;

static void solve(int /* case_id */) {
    int n, m, q;
    cin >> n >> m >> q;
    vector<tuple<int, int, int>> edges(m);
    unordered_map<int, int> club_id;
    for (auto& [u, v, k] : edges) {
        cin >> u >> v >> k, u--, v--;
        k = club_id.insert({k, (int)club_id.size() + 1}).first->second;
    }
    int num_clubs = (int)club_id.size();

    static int uf[101][10001];
    memset(uf, -1, sizeof(uf[0]) * (num_clubs + 1));
    function<int(int, int)> find = [&](int missing_club, int u) -> int {
        auto& par = uf[missing_club][u];
        return par < 0 ? u : par = find(missing_club, par);
    };
    auto unite = [&](int missing_club, int u, int v) -> void {
        auto& a = uf[missing_club];
        if (u = find(missing_club, u), v = find(missing_club, v), u == v)
            return;
        if (a[u] < a[v]) swap(u, v);
        a[v] += a[u], a[u] = v;
    };

    for (auto [u, v, k] : edges) {
        unite(0, u, v);
        for (int l = 1; l <= num_clubs; l++)
            if (l != k) unite(l, u, v);
    }
    unordered_map<int, bitset<101>> comp_clubs;
    for (auto [u, v, k] : edges) {
        comp_clubs[find(0, u)][k] = 1;
    }

    int ans = 0;
    while (q--) {
        int u, v;
        cin >> u >> v, u--, v--;
        int par_u = find(0, u), par_v = find(0, v);
        if (par_u != par_v) continue;
        auto& c = comp_clubs[par_u];
        if (c.count() & 1) {
            ans++;
            continue;
        }
        for (int i = 1; i <= num_clubs; i++) {
            if (c[i] && find(i, u) == find(i, v)) {
                ans++;
                break;
            }
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int cases;
    cin >> cases;
    for (int i = 1; i <= cases; i++) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
}
