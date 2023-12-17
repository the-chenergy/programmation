pal = set(range(10))
for x in range(1, 10**4):
    pal.add(int(str(x) + str(x)[::-1]))
    for y in range(10):
        pal.add(int(str(x) + str(y) + str(x)[::-1]))
pal = sorted(pal)
# print(pal[:100])


class Solution:
    def minimumCost(self, nums: List[int]) -> int:
        l = 0
        r = len(pal)
        while r - l > 2:
            mid = (l + r) // 2
            cost_l = sum(abs(x - pal[mid]) for x in nums)
            cost_r = sum(abs(x - pal[mid + 1]) for x in nums)
            if cost_l < cost_r:
                r = mid + 1
            else:
                l = mid
        return sum(abs(x - pal[l + 1]) for x in nums)
