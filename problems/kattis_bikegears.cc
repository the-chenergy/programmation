#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  using ld=double;
  int f,b;
  cin>>f>>b;
  vector<int>fs(f);
  for(int i=0;i<f;i++)cin>>fs[i];
  vector<tuple<ld,int,int>>a;
  for(int i=0;i<b;i++){
    int x;
    cin>>x;
    for(auto y:fs)a.push_back({(ld)y/x,y,x});
  }
  sort(a.begin(),a.end());
  for(auto[r,y,x]:a)cout<<"("<<y<<","<<x<<")\n";
}
