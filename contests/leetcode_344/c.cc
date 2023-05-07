class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        vector<int> ans, a(n);
        int cur = 0;
        for (auto& q : queries) {
            int i = q[0], x = q[1];
            if (i && a[i] && a[i - 1] == a[i]) cur--;
            if (i + 1 != n && a[i] && a[i + 1] == a[i]) cur--;
            a[i] = x;
            if (i && a[i - 1] == a[i]) cur++;
            if (i + 1 != n && a[i] && a[i + 1] == a[i]) cur++;
            ans.push_back(cur);
        }
        return ans;
    }
};
