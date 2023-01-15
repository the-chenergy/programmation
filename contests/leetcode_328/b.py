class Solution:
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:
        ds=[[0]*(n+1) for _ in range(n)]
        for t,l,b,r in queries:
            for y in range(t,b+1):
                ds[y][l]+=1
                ds[y][r+1]-=1
        ans=[[0]*n for _ in range(n)]
        for y in range(n):
            cur=0
            for i in range(n):
                cur+=ds[y][i]
                ans[y][i]=cur
        return ans
