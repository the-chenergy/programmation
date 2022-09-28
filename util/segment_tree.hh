struct segment_tree {
  using value_t = int;
  // using value_t = ll;
  const value_t DEFAULT_VALUE = 0;
  // const value_t DEFAULT_VALUE = INT_MAX;
  // const value_t DEFAULT_VALUE = INT_MIN;
  // const value_t DEFAULT_VALUE = ;
  value_t _get(value_t x, value_t y) {
    // return min(x, y);
    // return max(x, y);
    // return gcd(x, y);
    return x + y;
  }
  int size;
  vector<value_t> _data;
  segment_tree(int size) : size(size), _data(2 * size, DEFAULT_VALUE) {}
  void update(int index, value_t new_value) {
    for (_data[index += size] = new_value; index /= 2;)
      _data[index] = _get(_data[index * 2], _data[index * 2 + 1]);
  }
  value_t query(int begin, int end) {
    value_t res_a = DEFAULT_VALUE, res_b = DEFAULT_VALUE;
    for (begin += size, end += size; begin < end; begin /= 2, end /= 2) {
      if (begin % 2) res_a = _get(res_a, _data[begin++]);
      if (end % 2) res_b = _get(_data[--end], res_b);
    }
    return _get(res_a, res_b);
  }
};
