# print=lambda *a,**aa:None
class Solution:
    def minCost(self, a: List[int], b: List[int]) -> int:
        a.sort()
        b.sort()
        c=Counter(a)
        d=Counter(b)
        e=Counter()
        # print(f'{a=} {b=} {c=} {d=}')
        for x,y in c.items():e[x]+=y
        for x,y in d.items():e[x]+=y
        # print(f'{e=}')
        h=[]
        for x,y in e.items():
            if y%2: return -1
            mx=max(c[x],d[x])
            mn=min(c[x],d[x])
            assert (mx-mn)%2==0, (mx,mn,mx-mn)
            h.extend(x for _ in range((mx-mn)//2))
        h.sort()
        # print(h)
        assert len(h)%2==0, (len(h),)
        mnx=min(a[0],b[0])
        return sum(min(2*mnx,h[i]) for i in range(len(h)//2))
