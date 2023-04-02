class Solution {
public:
    int findTheLongestBalancedSubstring(string s) {
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            int c = 0, d = 0, x = 0;
            for (int j = i; j < s.size(); j++) {
                c += s[j] == '0';
                d += s[j] == '1';
                if (j > i && s[j] != s[j - 1]) x++;
                if (c == d && x == 1 && s[j] == '1') ans = max(ans, j - i + 1);
            }
        }
        return ans;
    }
};
