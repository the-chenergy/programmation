#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  string s;
  cin>>s;
  int n=s.size();
  vector<int>dp(n+1,1);
  for(int i=n-1;i>=0;i--){
    for(int j=i+1;j<n;j++){
      if(s[j]>s[i])dp[i]=max(dp[i],dp[j]+1);
    }
  }
  cout<<26-*max_element(dp.begin(),dp.end());
}
