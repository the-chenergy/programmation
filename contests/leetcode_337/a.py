class Solution:
    def evenOddBit(self, n: int) -> List[int]:
        ans = [0, 0]
        for i, x in enumerate(reversed(bin(n))):
            if i % 2:
                ans[1] += x == '1'
            else:
                ans[0] += x == '1'
        return ans
