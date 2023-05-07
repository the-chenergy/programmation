class Solution {
public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        vector<int> ans;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            set<int> d1, d2;
            for (int j = 0; j <= i; j++) d1.insert(nums[j]);
            for (int j = i + 1; j <= n - 1; j++) d2.insert(nums[j]);
            ans.push_back(-((int)d2.size() - (int)d1.size()));
        }
        return ans;
    }
};
