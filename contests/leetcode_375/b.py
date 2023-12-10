class Solution:
    def getGoodIndices(self, v: List[List[int]], t: int) -> List[int]:
        ans = []
        for i in range(len(v)):
            a, b, c, m = v[i]
            if (a**b % 10)**c % m == t:
                ans.append(i)
        return ans
