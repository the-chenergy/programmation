class Solution {
public:
    int minIncrements(int n, vector<int>& cost) {
        long long ans = 0;
        cost.insert(cost.begin(), -INT_MAX / 2);
        function<int(int)> dfs = [&](int cur) -> long long {
            if (cur * 2 > n) return cost[cur];
            long long a = cost[cur * 2] + dfs(cur * 2), b = cost[cur * 2 + 1] + dfs(cur * 2 + 1);
            ans += abs(a - b);
            return max(a, b) + cost[cur];
        };
        dfs(1);
        return ans / 2;
    }
};
