class Solution:
    def maxScore(self, nums: List[int]) -> int:
        nums.sort(reverse=True)
        pre = accumulate(nums)
        ans = sum(x > 0 for x in pre)
        return ans
