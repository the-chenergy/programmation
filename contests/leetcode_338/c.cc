using ll = long long;

class Solution {
public:
    vector<long long> minOperations(vector<int>& nums, vector<int>& queries) {
        sort(nums.begin(), nums.end());
        vector<ll> pre = {0};
        pre.reserve(nums.size() + 1);
        for (auto x : nums) pre.push_back(pre.back() + x);
        
        vector<ll> ans;
        int n = nums.size();
        ans.reserve(queries.size());
        for (auto q : queries) {
            int lo = lower_bound(nums.begin(), nums.end(), q) - nums.begin();
            int hi = upper_bound(nums.begin(), nums.end(), q) - nums.begin();
            ans.push_back(1LL * q * lo - pre[lo] + (pre.back() - pre[hi]) - 1LL * q * (n - hi));
        }
        return ans;
    }
};
