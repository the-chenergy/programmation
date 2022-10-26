struct union_find {
    vector<int> _data;
    union_find(int size) : _data(size, -1){};
    int count(int x) { return -_data[find(x)]; }
    int find(int x) { return _data[x] < 0 ? x : _data[x] = find(_data[x]); }
    bool same(int x, int y) { return find(x) == find(y); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (-_data[x] < -_data[y]) swap(x, y);
        _data[x] += _data[y], _data[y] = x;
        return true;
    }
};
