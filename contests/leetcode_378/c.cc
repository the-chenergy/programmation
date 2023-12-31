class Solution {
public:
    int maximumLength(string s) {
        int n = s.size();
        int lo = 0, hi = n + 1;
        while (hi - lo > 1) {
            int m = (lo + hi) / 2;
            vector<int> ct(26), c(26);
            int dis = 0, ok = 0;
            for (int i = 0; i < n; i++) {
                if (!ct[s[i] - 'a']) {
                    dis++;
                }
                ct[s[i] - 'a']++;
                if (i + 1 >= m && dis == 1) {
                    c[s[i] - 'a']++;
                    if (c[s[i] - 'a'] >= 3) {
                        ok = 1;
                        break;
                    }
                }
                if (i - m + 1 >= 0) {
                    ct[s[i - m + 1] - 'a']--;
                    if (!ct[s[i - m + 1] - 'a']) {
                        dis--;
                    }
                }
            }
            if (ok) {
                lo = m;
            } else {
                hi = m;
            }
        }
        return lo == 0 ? -1 : lo;
    }
};
