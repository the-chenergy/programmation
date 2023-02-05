class Solution:
    def vowelStrings(self, words: List[str], queries: List[List[int]]) -> List[int]:
        a=[0]
        for i in range(len(words)):
            a.append(a[-1]+int(words[i][0] in 'aeiou' and words[i][-1] in 'aeiou'))
        # print(a)
        ans=[]
        for b,e in queries:
            ans.append(a[e+1]-a[b])
        return ans
