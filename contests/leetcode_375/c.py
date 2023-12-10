class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        mx = max(nums)
        n = len(nums)
        a = []
        for i in range(n):
            if nums[i] == mx:
                a.append(i)
        ans = 0
        # print(a)
        for i in range(len(a)):
            if i + k - 1 >= len(a):
                break
            ans += (a[i] - (a[i - 1] if i else -1)) * (n - a[i + k - 1])
            # print(i, (a[i] - (a[i - 1] if i else -1)), (n - a[i + k - 1]))
        return ans
