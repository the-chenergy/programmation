class Solution:
    def subarrayLCM(self, nums: List[int], k: int) -> int:
        n=len(nums)
        ans=0
        for i in range(n):
            l=1
            for j in range(i,n):
                l=l*nums[j]//gcd(l,nums[j])
                ans+=l==k
        return ans
