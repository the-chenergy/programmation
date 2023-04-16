#define printf(...) 0

class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        static vector<vector<int>> nei;
        nei.assign(n, {});
        for (auto& e : edges) {
            nei[e[0]].push_back(e[1]);
            nei[e[1]].push_back(e[0]);
        }
        vector<int> tr(n);
        for (auto& t : trips) {
            int s = t[0], e = t[1];
            deque<int> sea;
            vector<char> vis(n);
            vector<int> par(n, -1);
            sea = {s};
            vis[s] = 1;
            while (sea.size()) {
                int i = sea.back();
                sea.pop_back();
                // tr[i] += price[i];
                for (int j : nei[i]) {
                    if (vis[j]) continue;
                    vis[j] = 1;
                    par[j] = i;
                    sea.push_back(j);
                }
            }
            int x = e;
            while (x != s) {
                tr[x] += price[x];
                x = par[x];
            }
            tr[s] += price[s];
        }
        
        static int dp[51][2];
        memset(dp, 63, sizeof(dp));
        function<void(int, int)> dfs = [&](int i, int p) {
            for (int j : nei[i]) {
                if (j == p) continue;
                dfs(j, i);
            }
            dp[i][0] = tr[i];
            for (int j : nei[i]) {
                if (j == p) continue;
                dp[i][0] += dp[j][1];
            }
            dp[i][1] = tr[i] / 2;
            for (int j : nei[i]) {
                if (j == p) continue;
                dp[i][1] += dp[j][0];
            }
            dp[i][1] = min(dp[i][1], dp[i][0]);
            printf("i=%i p=%i no=%i ye=%i\n", i, p, dp[i][0], dp[i][1]);
        };
        dfs(n > 2 ? 2 : 0, -1);
        
        printf("----\n\n\n");
        return dp[n > 2 ? 2 : 0][1];
    }
};
