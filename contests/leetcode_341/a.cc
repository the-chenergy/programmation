class Solution {
public:
    vector<int> rowAndMaximumOnes(vector<vector<int>>& mat) {
        int ans = 0, c = 0;
        for (int i = 0; i < mat.size(); i++) {
            int cur = reduce(mat[i].begin(), mat[i].end());
            if (cur > c) c = cur, ans = i;
        }
        return {ans, c};
    }
};
