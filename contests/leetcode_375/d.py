class Solution:
    def numberOfGoodPartitions(self, nums: List[int]) -> int:
        occ = {}
        n = len(nums)
        for i in range(n):
            if nums[i] in occ:
                occ[nums[i]][1] = i
            else:
                occ[nums[i]] = [i, i]
        es = []
        for l, r in occ.values():
            es.append([l, 1])
            es.append([r + 1, -1])
        es.sort()
        ct = -1
        d = 0
        for x, y in es:
            d += y
            ct += d == 0
        return 2**ct % (10**9 + 7)
