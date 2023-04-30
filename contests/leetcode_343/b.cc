class Solution {
public:
    int firstCompleteIndex(vector<int>& arr, vector<vector<int>>& mat) {
        int h = mat.size(), w = mat[0].size(), n = arr.size();
        vector<pair<int, int>> pos(n + 1);
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                pos[mat[y][x]] = {y, x};
            }
        }
        vector<int> rows(h, w);
        vector<int> cols(w, h);
        for (int i = 0; i < n; i++) {
            auto [y, x] = pos[arr[i]];
            if (!--rows[y] | !--cols[x]) return i;
        }
        throw 42;
    }
};
