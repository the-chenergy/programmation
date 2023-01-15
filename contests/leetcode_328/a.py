class Solution:
    def differenceOfSum(self, nums: List[int]) -> int:
        es=sum(nums)
        ds=0
        for x in nums:
            x=str(x)
            for c in x:
                ds+=int(c)
        return abs(es-ds)
