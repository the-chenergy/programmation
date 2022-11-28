
const ll _POLY_MOD = 3037000493;

vector<array<ll, 2>> _poly_pows{{1, 1}, {127, 131}};

// Pre-computes polynomial hashes of a given string s in O(n), then provides
// functions to hash any substring of s in O(1).
struct poly_hashed {
    int _size = 0;
    vector<array<ll, 2>> _pre;
    poly_hashed() {}
    poly_hashed(string s) { assign(s); }
    // Re-initializes with string s
    void assign(string s) {
        _size = int(s.size());
        _pre.assign(_size + 1, {});
        int i = int(_poly_pows.size());
        if (i < _size + 1) {
            _poly_pows.resize(_size + 1);
            for (; i <= _size; i++)
                for (int j = 0; j < 2; j++)
                    _poly_pows[i][j] =
                        _poly_pows[i - 1][j] * _poly_pows[1][j] % _POLY_MOD;
        }
        for (i = 0; i < _size; i++)
            for (int j = 0; j < 2; j++)
                _pre[i + 1][j] =
                    (_pre[i][j] * _poly_pows[1][j] + s[i]) % _POLY_MOD;
    }
    // Hashes s[b..e)
    ull hash_substring(int b, int e) {
        array<ll, 2> h;
        for (int j = 0; j < 2; j++) {
            h[j] = (_pre[e][j] - _pre[b][j] * _poly_pows[e - b][j]) % _POLY_MOD;
            if (h[j] < 0) h[j] += _POLY_MOD;
        }
        return (ull(h[1]) << 32) | h[0];
    }
    // Hashes s[b..b+c)
    ull hash_substr(int b, int c) { return hash_substring(b, b + c); }
};

ull poly_hash(string s) {
    array<ull, 2> h{0, 0};
    for (char c : s)
        for (int j = 0; j < 2; j++)
            h[j] = (h[j] * _poly_pows[1][j] + c) % _POLY_MOD;
    return (h[1] << 32) | h[0];
}
