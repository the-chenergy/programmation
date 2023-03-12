class Solution:
    def findMinimumTime(self, tasks: List[List[int]]) -> int:
        n = len(tasks)
        t = max(a[1] for a in tasks)
        ans = 0
        for i in range(t + 1):
            ok = any(i > a[1] - a[2] and i <= a[1] for a in tasks)
            if ok:
                ans += 1
                for a in tasks:
                    if i >= a[0] and i <= a[1]:
                        a[2] -= 1
        return ans
