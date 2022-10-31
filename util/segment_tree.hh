struct segment_tree {
    using T = int;
    // using T = ll;
    const T DEFAULT_VALUE = 0;
    // const T DEFAULT_VALUE = INT_MAX;
    // const T DEFAULT_VALUE = INT_MIN;
    // const T DEFAULT_VALUE = ;
    T _get(T x, T y) {
        // return min(x, y);
        // return max(x, y);
        // return gcd(x, y);
        return x + y;
    }
    int _size;
    vector<T> _data;
    segment_tree(int size) : _size(size), _data(2 * _size, DEFAULT_VALUE) {}
    void update(int index, T new_value) {
        for (_data[index += _size] = new_value; index /= 2;)
            _data[index] = _get(_data[index * 2], _data[index * 2 + 1]);
    }
    T query(int begin, int end) {
        T res_a = DEFAULT_VALUE, res_b = DEFAULT_VALUE;
        for (begin += _size, end += _size; begin < end; begin /= 2, end /= 2) {
            if (begin % 2) res_a = _get(res_a, _data[begin++]);
            if (end % 2) res_b = _get(_data[--end], res_b);
        }
        return _get(res_a, res_b);
    }
};
