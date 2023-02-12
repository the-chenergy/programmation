class Solution:
    def minimumScore(self, s: str, t: str) -> int:
        i=0
        a=[]
        b=[]
        for j in range(len(s)):
            if s[j]==t[i]:
                a.append(j)
                i+=1
            if i==len(t):
                break
        k=len(t)-1
        for j in range(len(s)-1,-1,-1):
            if s[j]==t[k]:
                b.append(j)
                k-=1
            if k==-1:
                break
        # print(i,k,a,b)
        ans=min(len(t)-len(a),len(t)-len(b))
        for k,i in enumerate(b):
            # print(k,i,bisect_left(a,i),f'{len(t)-1-k=}')
            j=bisect_left(a,i)
            # ans=min(ans,len(t)-(len(t)-1-k+bisect_left(a,i)))
            # print(len(t)-1-k,j)
            # ans=min(ans,len(t)-1-k-j+1)
            ans=min(ans,len(t)-1-k-j)
        return max(ans,0)
