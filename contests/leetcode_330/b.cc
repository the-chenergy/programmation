const long MOD = 1E9 + 7;

long modpow(long base, long power) {
    long ans = 1;
    for (; power; power >>= 1, (base *= base) %= MOD) {
        if (power & 1) (ans *= base) %= MOD;
    }
    return ans;
}

class Solution {
public:
    int monkeyMove(int n) {
        return (modpow(2, n) + MOD - 2) % MOD;
    }
};
