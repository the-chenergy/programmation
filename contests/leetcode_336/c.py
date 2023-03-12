class Solution:
    def beautifulSubarrays(self, nums: List[int]) -> int:
        freq = Counter()
        freq[0] += 1
        tot = 0
        ans = 0
        for x in nums:
            tot ^= x
            ans += freq[tot]
            freq[tot] += 1
        return ans
