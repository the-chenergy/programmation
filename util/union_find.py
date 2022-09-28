class UnionFind:
    def __init__(self, size: int):
        self.size = size
        self._data = [-1] * size

    def find(self, x: int):
        if self._data[x] < 0:
            return x
        self._data[x] = self.find(self._data[x])
        return self._data[x]

    def count(self, x: int):
        return -self._data[self.find(x)]

    def same(self, x: int, y: int):
        return self.find(x) == self.find(y)

    def unite(self, x: int, y: int):
        x = self.find(x)
        y = self.find(y)
        if x == y:
            return False
        if -self._data[x] < -self._data[y]:
            x, y = y, x
        self._data[x] += self._data[y]
        self._data[y] = x
        return True
