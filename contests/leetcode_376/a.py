class Solution:
    def findMissingAndRepeatedValues(self, grid: List[List[int]]) -> List[int]:
        c = Counter()
        for row in grid:
            for x in row:
                c[x] += 1
        for i in range(1, len(grid)**2 + 1):
            if c[i] == 0:
                b = i
            elif c[i] == 2:
                a = i
        return a, b
