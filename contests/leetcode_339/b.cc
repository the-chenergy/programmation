class Solution {
public:
    vector<vector<int>> findMatrix(vector<int>& nums) {
        map<int, int> f;
        for (int x : nums) f[x]++;
        vector<vector<int>> ans;
        while (f.size()) {
            ans.push_back({});
            for (auto it = f.begin(); it != f.end(); ) {
                ans.back().push_back(it->first);
                if (it->second == 1) {
                    it++;
                    f.erase(prev(it));
                } else {
                    it->second--;
                    it++;
                }
            }
        }
        return ans;
    }
};
