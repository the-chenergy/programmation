template <typename T>
vector<int> calc_z(T s) {
    int n = int(s.size());
    vector<int> z(n);
    for (int i = 1, l = -1, r = -1; i < n; i++) {
        if (i < r) z[i] = min(r - i, z[i - l]);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
