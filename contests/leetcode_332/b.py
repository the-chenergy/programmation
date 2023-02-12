class Solution:
    def countFairPairs(self, nums: List[int], lower: int, upper: int) -> int:
        nums.sort()
        ans=0
        for i,x in enumerate(nums):
            l=bisect_left(nums,lower-x)
            r=bisect_right(nums,upper-x)
            ans+=r-l
            if l<=i and r>i: ans-=1
        return ans//2
