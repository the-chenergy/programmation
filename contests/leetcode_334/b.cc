class Solution {
public:
    vector<int> divisibilityArray(string word, int m) {
        vector<int>ans;
        using ll=long long;
        ll s=0;
        for(int i=0;i<word.size();i++){
            (s*=10LL)+=ll(word[i]-'0');
            s%=m;
            ans.push_back(s%m==0);
        }
        return ans;
    }
};
