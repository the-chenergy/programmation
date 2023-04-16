class Solution {
public:
    int addMinimum(string word) {
        int ans = 0;
        int i = 0, j = 0;
        while (i < word.size() || j % 3) {
            char t = "abc"[j % 3];
            int bad = i == word.size() || word[i] != t;
            ans += bad;
            i += !bad;
            j++;
        }
        return ans;
    }
};
