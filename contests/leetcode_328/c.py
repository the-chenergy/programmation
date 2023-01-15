class Solution:
    def countGood(self, nums: List[int], k: int) -> int:
        # print(nums,k)
        ans=0
        n=len(nums)
        ct=Counter()
        tot=0
        ep=[n+1]*n
        b=0
        e=0
        while e<=n:
            if tot>=k:
                ep[b]=e
                c=ct[nums[b]]
                tot-=c*(c-1)//2
                ct[nums[b]]-=1
                c=ct[nums[b]]
                tot+=c*(c-1)//2
                b+=1
            else:
                if e==n:
                    break
                c=ct[nums[e]]
                tot-=c*(c-1)//2
                ct[nums[e]]+=1
                c=ct[nums[e]]
                tot+=c*(c-1)//2
                e+=1
            # print(b,e,tot,ct)
        # print(ep)
        for b in range(n):
            ans+=n+1-ep[b]
        return ans
