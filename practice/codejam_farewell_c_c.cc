/* Solution to "Evolutionary Algorithms", problem C from the Google Code Jam
   Farewell Round C.
   (https://codingcompetitions.withgoogle.com/codejam/round/0000000000c95433/0000000000cad08b)

   A very wordy way to tell us to find the number of nodes smaller than some
   threshold, for every subtree.

   This can be done using the subtree-merging trick I discovered a while ago.
   The general idea is, we can run a DFS and let each node return all values
   from its subtree, in only O(N log N) time. This is because when we have all
   children of one node return its subtree values, we can cleverly only keep the
   biggest child-subtree as the main branch and merge the other children's
   return values into it. Even in the worst case which is a complete binary
   tree, only up to half of the values need to be copied over at each level,
   with only log N levels in total, making this process incredibly efficient.

   In the case of our problem, when we're processing a node, we want to know how
   many of its descendants' values are below some threshold. With the technique
   described above, we now have access to all of the node's descendant values.
   So if we use an order-statistic tree to store them, that would allow us to
   both query the numbers below some threshold and insert new values very
   efficiently (in log N).
*/

#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
using namespace __gnu_pbds;
template <typename K, typename V>
using ordered_map =
        tree<K, V, less<K>, rb_tree_tag, tree_order_statistics_node_update>;
template <typename T>
using ordered_set = ordered_map<T, null_type>;
// find_by_order(int) -> iterator
// order_of_key(K) -> int (index of first >=)

static void solve(int /* case_id */) {
    int n, k;
    cin >> n >> k;
    vector<int> scores(n);
    for (auto& s : scores) cin >> s;
    vector<vector<int>> children(n);
    for (int i = 1; i < n; i++) {
        int par;
        cin >> par, par--;
        children[par].push_back(i);
    }

    auto sorted_scores = scores;
    sort(sorted_scores.begin(), sorted_scores.end());
    using S = ordered_set<pair<int, int>>;
    long long ans = 0;
    function<S*(int)> calc = [&](int cur) -> S* {
        if (children[cur].empty()) {
            S* ret = new S();
            ret->insert({scores[cur], cur});
            return ret;
        }
        vector<S*> child_scores(children[cur].size());
        int biggest = -1;
        for (int c = 0; c < (int)children[cur].size(); c++) {
            child_scores[c] = calc(children[cur][c]);
            if (!~biggest || (int)child_scores[c]->size() > biggest)
                biggest = c;
        }
        auto all_subtree_scores = child_scores[biggest];
        for (int c = 0; c < (int)children[cur].size(); c++) {
            if (c == biggest) continue;
            for (auto score : *child_scores[c])
                all_subtree_scores->insert(score);
            delete child_scores[c];
        }

        int bound = (scores[cur] + k - 1) / k;
        long long all_good =
                lower_bound(sorted_scores.begin(), sorted_scores.end(), bound) -
                sorted_scores.begin();
        long long subtree_good = all_subtree_scores->order_of_key({bound, -1});
        ans += (all_good - subtree_good) * subtree_good;

        all_subtree_scores->insert({scores[cur], cur});
        return all_subtree_scores;
    };
    delete calc(0);

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
