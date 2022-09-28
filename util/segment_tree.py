class SegmentTree:
    DEFAULT_VALUE = 0
    # DEFAULT_VALUE = math.inf
    # DEFAULT_VALUE = -math.inf

    def _get(self, x, y):
        # return min(x, y)
        # return max(x, y)
        # return math.gcd(x, y)
        return x + y

    def __init__(self, size: int):
        self.size = size
        self._data = [SegmentTree.DEFAULT_VALUE] * 2 * size

    def update(self, index: int, new_value):
        index += self.size
        self._data[index] = new_value
        index //= 2
        while index > 0:
            self._data[index] = self._get(self._data[index * 2],
                                          self._data[index * 2 + 1])
            index //= 2

    def query(self, begin: int, end: int):
        res_a = res_b = SegmentTree.DEFAULT_VALUE
        begin += self.size
        end += self.size
        while begin < end:
            if begin % 2:
                res_a = self._get(res_a, self._data[begin])
                begin += 1
            if end % 2:
                end -= 1
                res_b = self._get(self._data[end], res_b)
            begin //= 2
            end //= 2
        return self._get(res_a, res_b)
