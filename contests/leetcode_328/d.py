class Solution:
    def maxOutput(self, n: int, edges: List[List[int]], price: List[int]) -> int:
        nei=[[] for i in range(n)]
        for u,v in edges:
            nei[u].append(v)
            nei[v].append(u)
        ans=0
        def dfs(u,p):
            nonlocal ans
            h=[]
            hh=[]
            for v in nei[u]:
                if v==p:continue
                c=dfs(v,u)
                # print(f'{u=}, {p=}, {v=}, {c=}')
                h.append(c)
                ans=max(ans,c[1])
                c=c.copy()
                c[0],c[1]=c[1],c[0]
                hh.append(c)
            if len(h)==0:
                return [0,price[u],u]
            if len(h)==1:
                ans=max(ans,h[0][0]+price[u])
                return [h[0][0]+price[u],h[0][1]+price[u],u]
            h.sort()
            hh.sort()
            # print(f'  {u=} {p=} {h=} {hh=}')
            if h[-1][2]!=hh[-1][2]:
                ans=max(ans,h[-1][0]+hh[-1][0]+price[u])
                return [h[-1][0]+price[u],hh[-1][0]+price[u],u]
            else:
                if h[-1][0]+hh[-2][0]>h[-2][0]+hh[-1][0]:
                    x=-1
                    y=-2
                else:
                    x=-2
                    y=-1
                ans=max(ans,h[x][0]+hh[y][0]+price[u])
            return [h[-1][0]+price[u],hh[-1][0]+price[u],u]
        dfs(0,0)
        return ans
