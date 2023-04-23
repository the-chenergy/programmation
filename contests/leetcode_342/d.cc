class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();
        
        int ones = count(nums.begin(), nums.end(), 1);
        if (ones) return n - ones;
        
        for (int r = 2; r <= n; r++) {
            for (int i = 0; i + r <= n; i++) {
                int g = 0;
                for (int j = i; j < i + r; j++) g = __gcd(g, nums[j]);
                if (g == 1) return r - 1 + n - 1;
            }
        }
        
        return -1;
    }
};
