class Solution {
public:
    bool hasTrailingZeros(vector<int>& nums) {
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                if (__builtin_ctz(nums[i] | nums[j]) >= 1) {
                    return 1;
                }
            }
        }
        return 0;
    }
};
