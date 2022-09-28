#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  vector<map<char,int>>trie(1);
  while(true){
    string s;
    cin>>s;
    if(s=="#")break;
    int cur=0;
    for(auto ch:s){
      int&nxt=trie[cur][ch];
      if(!nxt){
        nxt=trie.size();
        trie.emplace_back();
      }
      cur=nxt;
    }
    trie[cur]['$']=1;
  }
  while(true){
    string s;
    while(true){
      char ch;cin>>ch;
      if(ch=='#')return 0;
      if(ch=='|')break;
      s.push_back(ch);
    }
    int n=s.size();
    vector<int>dp(n+1);
    int ans=0;
    for(int beg=n-1;beg>=0;beg--){
      dp[beg]=dp[beg+1];
      int cur=0;
      for(int i=beg;i<n;i++){
        char ch=s[i];
        cur=trie[cur][ch];
        if(!cur)break;
        if(trie[cur]['$']){
          dp[beg]=max(dp[beg],1+dp[i+1]);
          ans=max(ans,dp[beg]);
        }
      }
    }
    cout<<ans<<"\n";
  }
}
