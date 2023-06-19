/** Solution to Dragon Maid (https://open.kattis.com/problems/dragonmaid).

    Process the queries in order of X. */

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0), cin.tie(0);

    int n;
    cin >> n;
    vector<tuple<int, int, int>> items;
    for (int i = 1; i <= n; i++) {
        int p, v;
        cin >> p >> v;
        items.push_back({v, p, i});
    }
    sort(items.begin(), items.end());
    int q;
    cin >> q;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int x, k;
        cin >> x >> k;
        queries.push_back({x, k, i});
    }
    sort(queries.begin(), queries.end());

    vector<vector<int>> ans(q);
    set<pair<int, int>> order;
    int cur_item = 0;
    for (auto [x, k, i] : queries) {
        while (cur_item < n && get<0>(items[cur_item]) <= x) {
            auto [v, p, j] = items[cur_item];
            order.insert({-p, j});
            cur_item++;
        }
        auto it = order.begin();
        while (k-- && it != order.end()) {
            ans[i].push_back(it->second);
            it++;
        }
    }

    for (int i = 0; i < q; i++) {
        if (!ans[i].size()) {
            cout << "-1\n";
            continue;
        }
        for (auto j : ans[i]) cout << j << " ";
        cout << "\n";
    }
}
