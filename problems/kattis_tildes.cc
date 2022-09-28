#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;
using ull = uint64_t;
const double PI = 3.141592653589793;

struct union_find {
  vector<int> _data;
  union_find(int size) : _data(size, -1){};
  int count(int x) { return -_data[find(x)]; }
  int find(int x) { return _data[x] < 0 ? x : _data[x] = find(_data[x]); }
  bool same(int x, int y) { return find(x) == find(y); }
  bool unite(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return false;
    if (-_data[x] < -_data[y]) swap(x, y);
    _data[x] += _data[y], _data[y] = x;
    return true;
  }
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int n,q;cin>>n>>q;
  union_find uf(n+1);
  while(q--){
    char f;
    cin>>f;
    if(f=='t'){
      int x,y;
      cin>>x>>y;
      uf.unite(x,y);
    }else{
      int x;
      cin>>x;
      cout<<uf.count(x)<<"\n";
    }
  }
}
