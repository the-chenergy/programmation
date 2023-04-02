#define printf(...) 0
class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        printf("----\n");
        vector<bool> ban(n);
        for (int i : banned) ban[i] = true;
        vector<set<int>> unseen(2);
        for (int i = 0; i < n; i++) {
            if (i == p || ban[i]) continue;
            printf("ban i=%i\n", i);
            unseen[i % 2].insert(i);
        }
        vector<int> ans(n, -1);
        ans[p] = 0;
        deque<int> bfs = {p};
        auto flip = [&](int x, int l) -> int {
            int r = l + k - 1;
            return r - (x - l);
        };
        while (bfs.size()) {
            int cur = bfs.front();
            bfs.pop_front();
            int l = max(cur + 1 - k, 0);
            int r = min(cur + k - 1, n - 1);
            if (l > r) continue;
            int l_tar = flip(cur, l);
            int r_tar = flip(cur, r - k + 1);
            printf("cur=%i l=%i l_tar=%i r=%i r_tar=%i\n", cur, l, r, l_tar, r_tar);
            auto& nei = unseen[l_tar % 2];
            for (auto it = nei.lower_bound(l_tar); it != nei.end(); ) {
                if (*it > r_tar) break;
                ans[*it] = ans[cur] + 1;
                bfs.push_back(*it);
                it = nei.erase(it);
            }
        }
        return ans;
    }
};
