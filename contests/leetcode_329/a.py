class Solution:
    def alternateDigitSum(self, n: int) -> int:
        p=1
        ans=0
        for x in str(n):
            ans+=p*int(x)
            p*=-1
        return ans
