
class Solution {
public:
    int miceAndCheese(vector<int>& reward1, vector<int>& reward2, int k) {
        int n = reward1.size();
        vector<array<int, 2>> diff(n);
        for (int i = 0; i < n; i++) {
            diff[i] = {reward1[i] - reward2[i], i};
        }
        sort(diff.rbegin(), diff.rend());
        int ans = 0;
        for (int i = 0; i < k; i++) {
            ans += reward1[diff[i][1]];
        }
        for (int i = k; i < n; i++) {
            ans += reward2[diff[i][1]];
        }
        return ans;
    }
};
