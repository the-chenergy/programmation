class Solution {
public:
    int isWinner(vector<int>& player1, vector<int>& player2) {
        int s1 = 0, s2 = 0;
        for (int i = 0; i < player1.size(); i++) {
            int mul = 1;
            if (i >= 1 && player1[i - 1] == 10 || i >= 2 && player1[i - 2] == 10) mul = 2;
            s1 += mul * player1[i];
        }
        for (int i = 0; i < player2.size(); i++) {
            int mul = 1;
            if (i >= 1 && player2[i - 1] == 10 || i >= 2 && player2[i - 2] == 10) mul = 2;
            s2 += mul * player2[i];
        }
        if (s1 == s2) return 0;
        return s1 > s2 ? 1 : 2;
    }
};
