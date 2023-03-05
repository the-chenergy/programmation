class Solution {
public:
    int passThePillow(int n, int time) {
        int i = 0;
        int di = 1;
        while (time--) {
            i += di;
            if (i >= n) {
                di = -1;
                i += di * 2;
            }
            else if (i < 0) {
                di = 1;
                i += di * 2;
            }
        }
        return i + 1;
    }
};
