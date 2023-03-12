class Solution:
    def vowelStrings(self, words: List[str], left: int, right: int) -> int:
        ans = 0
        for i in range(left, right + 1):
            ans += words[i][0] in 'aoeiu' and words[i][-1] in 'aoeiu'
        return ans
