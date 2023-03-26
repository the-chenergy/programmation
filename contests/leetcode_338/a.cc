class Solution {
public:
    int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        int ans = min(numOnes, k);
        if (numOnes >= k) return ans;
        if (numOnes + numZeros >= k) return ans;
        return ans - min(numNegOnes, k - numOnes - numZeros);
    }
};
