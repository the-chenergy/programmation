class Solution:
    def checkValidGrid(self, grid: List[List[int]]) -> bool:
        n = len(grid)
        a = [None] * n * n
        for y in range(n):
            for x in range(n):
                a[grid[y][x]] = (y, x)
        vis = set()
        for i in range(n * n):
            if a[i] in vis:
                return False
            if i:
                pre = a[i - 1][0] + a[i - 1][1] * 1j
                cur = a[i][0] + a[i][1] * 1j
                if abs(abs(cur - pre) - sqrt(5)) > 1E-6: return False
            vis.add(a[i])
        return a[0][0] == a[0][1] and a[0][1] == 0
