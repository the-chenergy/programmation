from sortedcontainers import SortedList


class Solution:
    def maxFrequencyScore(self, nums: List[int], k: int) -> int:
        nums.sort()
        ps = [0]
        for x in nums:
            ps.append(ps[-1] + x)
        n = len(nums)
        ind = {nums[i]: i for i in range(n)}
        l = 0
        r = 0
        cost = 0
        ans = 0
        sl = SortedList()
        while r <= n:
            if cost <= k:
                ans = max(ans, r - l)
                if r == n:
                    break
                sl.add(nums[r])
                r += 1
            else:
                sl.remove(nums[l])
                l += 1
            med = sl[len(sl) // 2]
            m = ind[med]
            cost_l = med * (m - l) - (ps[m] - ps[l])
            cost_r = (ps[r] - ps[m]) - med * (r - m)
            cost = cost_l + cost_r
        return ans
