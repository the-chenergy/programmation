class Solution:
    def minCapability(self, nums: List[int], k: int) -> int:
        lo=0
        hi=2**30
        n=len(nums)
        while hi-lo>1:
            b=(lo+hi)//2
            s=0
            i=0
            while i<n:
                if nums[i]<=b:
                    s+=1
                    if s==k: break
                    i+=2
                else:
                    i+=1
            if s>=k: hi=b
            else: lo=b
        return hi
