class Solution:
    def countTestedDevices(self, a: List[int]) -> int:
        ans = 0
        for i in range(len(a)):
            if a[i] > 0:
                ans += 1
                for j in range(i + 1, len(a)):
                    a[j] -= 1
        return ans
