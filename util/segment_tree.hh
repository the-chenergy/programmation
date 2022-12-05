
#define binary(f) [](auto _l, auto _r) { return f(_l, _r); }

template <typename T>
// Provides O(log n) range query for any associative binary function and
// O(log n) single-element update.
// Example: segment_tree<int> st(binary(plus()), n);
struct segment_tree {
    int _size;
    T _default;
    vector<T> _data;
    function<T(T, T)> _get;
    segment_tree(function<T(T, T)> f, int size = 0, T value = 0) : _get(f) {
        assign(size, value);
    }
    void assign(int size, T value = 0) {
        _size = size;
        _default = value;
        _data.assign(2 * size, value);
    }
    void update(int i, T x) {
        for (_data[i += _size] = x; i /= 2;)
            _data[i] = _get(_data[i * 2], _data[i * 2 + 1]);
    }
    // Queries f(...) in range [inc b, exc e)
    T query(int b, int e) {
        T x = _default, y = _default;
        for (b += _size, e += _size; b < e; b /= 2, e /= 2) {
            if (b % 2) x = _get(x, _data[b++]);
            if (e % 2) y = _get(_data[--e], y);
        }
        return _get(x, y);
    }
};
