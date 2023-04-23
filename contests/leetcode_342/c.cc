class Solution {
public:
    vector<int> getSubarrayBeauty(vector<int>& nums, int k, int x) {
        int n = nums.size();
        static int ct[101];
        memset(ct, 0, sizeof(ct));
        for (int i = 0; i < k - 1; i++) {
            ct[nums[i] + 50]++;
        }
        vector<int> ans;
        for (int i = k - 1, j = 0; i < n; i++, j++) {
            ct[nums[i] + 50]++;
            
            int s = 0;
            for (int y = -50; y <= 50; y++) {
                s += ct[y + 50];
                if (s >= x) {
                    ans.push_back(y);
                    break;
                }
                if (y >= 0) {
                    ans.push_back(0);
                    break;
                }
            }
            
            ct[nums[j] + 50]--;
        }
        return ans;
    }
};
