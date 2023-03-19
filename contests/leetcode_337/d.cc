#define cout 0 && cout
class Solution {
public:
    int findSmallestInteger(vector<int>& nums, int value) {
        for (auto& x : nums) ((x %= value) += value) %= value, cout << x << " "; cout << "\n";
        multiset<int> s(nums.begin(), nums.end());
        int j = 0;
        while (1) {
            auto it = s.find(j % value);
            if (it == s.end()) return j;
            s.erase(it);
            j++;
        }
        throw 43;
    }
};
