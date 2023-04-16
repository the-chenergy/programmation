class Solution {
public:
    int maxDivScore(vector<int>& nums, vector<int>& divisors) {
        sort(divisors.begin(), divisors.end());
        int ans = divisors[0], as = 0;
        for (auto x : divisors) {
            int sc = 0;
            for (auto y : nums) sc += y % x == 0;
            if (sc > as) ans = x, as = sc;
        }
        return ans;
    }
};
