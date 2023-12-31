class Solution:
    def maximumLength(self, s: str) -> int:
        n = len(s)
        a = Counter()
        for i in range(n):
            for j in range(i + 1, n+1):
                t = s[i:j]
                a[t] += 1
        ans = -1
        for i in range(n):
            for j in range(i + 1, n+1):
                t = s[i:j]
                if len(set(t)) > 1:
                    continue
                if a[t] >= 3:
                    ans = max(ans, len(t))
        return ans
