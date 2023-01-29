using ll=long long;

priority_queue<ll>a;
priority_queue<ll,vector<ll>,greater<ll>>b;

class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n=weights.size();
        a=decltype(a)(),b=decltype(b)();
        for(int i=1;i<n;i++){
            a.push(weights[i]+weights[i-1]);
            b.push(weights[i]+weights[i-1]);
        }
        ll x=0,y=0;
        while(--k){
            x+=a.top(),y+=b.top();
            a.pop(),b.pop();
        }
        return abs(x-y);
    }
};
